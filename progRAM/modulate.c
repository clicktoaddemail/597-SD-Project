/*Source file for RAM modulation.
CREATED: 10/13/22
LAST MODIFIED: 12/2/22

Changelog:
12/2/22
	- fixed RAM blocking
	- reintegrated RAM
10/18/22
	- cleaned up code
10/17/22
	- completed multithreading
*/

#include "modulate.h"
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>



//--- THREADED FUNCTIONS ---///
void *oscillate(void *end_time) { //internal function that oscillates a specified chunk of memory for a set time

	unsigned char * RAM_array1 = (unsigned char*)malloc(sizeof(unsigned char) * (unsigned int)BLOCK_SIZE);
	unsigned char * RAM_array2 = (unsigned char*)malloc(sizeof(unsigned char) * (unsigned int)BLOCK_SIZE);

	for (int i=0; i<(unsigned int)BLOCK_SIZE; i++) {
		RAM_array1[i] = 0x00;
		RAM_array2[i] = 0xFF;
	}
	time_t bit_end_time = *(time_t *)end_time;


	while (time(NULL)*1000 < bit_end_time) {
		memcpy(RAM_array1, RAM_array2, (unsigned int)BLOCK_SIZE);
		memcpy(RAM_array2, RAM_array1, (unsigned int)BLOCK_SIZE);
	}

	free(RAM_array1);
	free(RAM_array2);

	pthread_exit(NULL);
}



//--- PUBLIC FUNCTIONS ---//
void modulate_i(int bits) {
	printf("Reserving memory.\n");

	unsigned char * RAM_array1 = (unsigned char*)malloc(sizeof(unsigned char) * (unsigned int)BLOCK_SIZE);
	unsigned char * RAM_array2 = (unsigned char*)malloc(sizeof(unsigned char) * (unsigned int)BLOCK_SIZE);

	for (unsigned int i=0; i<(unsigned int)BLOCK_SIZE; i++) {
		RAM_array1[i] = 0x00;
		RAM_array2[i] = 0xFF;
	}

	printf("Attempting to transmit 32b on a single core, est. %lims to complete.\n", 32*time_per_bit_ms);
	time_t bit_end_time = time(NULL) * 1000;
	time_t start, end;
	start = time(NULL) * 1000;
	
	for (char i = 0; i<32; i++) {
		bit_end_time = bit_end_time+time_per_bit_ms;
		if ((bits>>i)&&0x00000001) {
			while (time(NULL)*1000 < bit_end_time) {
				memcpy(RAM_array1,RAM_array2, (unsigned int)BLOCK_SIZE);//    memcpy array1->array2
				memcpy(RAM_array2,RAM_array1, (unsigned int)BLOCK_SIZE);//    memcpy array2->array1
			}
		} else {
			while (time(NULL)*1000<bit_end_time) {};
		}
	}

	end = (time(NULL) * 1000) - start;
	printf("Done transmitting. Took %ldms.\n", end); //end should equal 32*time_per_bit_ms

	printf("Freeing memory.\n");
	free(RAM_array1);
	free(RAM_array2);	
	

	return;
}



void multi_modulate_i(int bits, int cores) {
	pthread_t thread_id[cores];

	printf("Attempting to transmit 32b on all cores, est. %lims to complete.\n", 32*time_per_bit_ms);
	time_t bit_end_time = time(NULL) * 1000;
	time_t start, end;
	start = time(NULL) * 1000;

	for (char i = 0;i<32;i++) {
		bit_end_time = bit_end_time+time_per_bit_ms;
		if ((bits>>i)&&0x00000001) { //only multithreads if there is a 1, to amplify the signal
			for (int j=0;j<cores; j++) {
				pthread_create(&thread_id[j], NULL, oscillate, (void *)&bit_end_time);
			}

			for (int j=0;j<cores; j++) {
				pthread_join(thread_id[j], NULL);
			}
		} else {
			while (time(NULL)*1000<bit_end_time) {};
		}
	}
	end = (time(NULL) * 1000) - start;
	printf("Done transmitting. Took %ldms.\n", end); //end should equal 32*time_per_bit_ms
	
}
