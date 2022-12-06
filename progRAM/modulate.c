/*Source file for RAM modulation.
CREATED: 10/13/22
LAST MODIFIED: 12/5/22

Changelog:
12/5/22
	- kicked 2nd array out of cache
	- refactored multithreading
12/2/22
	- fixed RAM blocking
	- reintegrated RAM
10/18/22
	- cleaned up code
*/

#include "modulate.h"
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>



//--- THREADED FUNCTIONS ---///
void *oscillate(void *arg) { //internal function that oscillates a specified chunk of memory for a set time

	int bits = *((int *) arg);
	//storing vals in here for faster writing
	printf("Reserving Memory.\n");

	unsigned char distract_processor = 1; //keeps RAM active, cache free

	unsigned char *RAM_array1      = (unsigned char*)malloc(sizeof(unsigned char) * (unsigned int)BLOCK_SIZE); //first mem array
	unsigned char *RAM_read_spot   = (unsigned char*)malloc(sizeof(unsigned char) * (unsigned int)BLOCK_SIZE); //temp location for reading
	unsigned char *cache_trick     = (unsigned char*)malloc(sizeof(unsigned char) * (unsigned int)CACHE_SIZE); //pushes heap out by 128MB
	unsigned char *RAM_array2      = (unsigned char*)malloc(sizeof(unsigned char) * (unsigned int)BLOCK_SIZE); //second mem array
	unsigned char *RAM_read_spot_2 = (unsigned char*)malloc(sizeof(unsigned char) * (unsigned int)BLOCK_SIZE); //2nd temp location for reading

	//cache avoidance program
	pid_t pid = fork();
	if (pid == 0) {
		for (unsigned int i=0; i<(unsigned int)CACHE_SIZE; i++) {
			cache_trick[i]=0xAA; //fill with garbage
		}
		while (distract_processor==1) {
			for (unsigned int i=0; i<(unsigned int)CACHE_SIZE; i++) {
				cache_trick[i] = cache_trick[i]; //may cause EM issues?
			}
		}

	} else { //normal program
		//fill usable blocks
		for (unsigned int i=0; i<(unsigned int)BLOCK_SIZE; i++) {
			RAM_array1[i] = 0x00;
			RAM_array2[i] = 0xFF;
		}

		printf("Attempting to transmit 32b on this core, est. %lims to complete.\n", 32*time_per_bit_ms);
		time_t bit_end_time = time(NULL) * 1000;
		time_t start, end;
		start = time(NULL) * 1000;
		
		for (char i = 0; i<32; i++) {
			bit_end_time = bit_end_time+time_per_bit_ms;
			if ((bits>>i)&&0x00000001) {
				while (time(NULL)*1000 < bit_end_time) {
					//READ RAM 1
					for (unsigned int i=0; i<(unsigned int)BLOCK_SIZE; i++) { RAM_read_spot[i] = RAM_array1[i]; } //temp var, used to oscillate 0s and 1s
					//write RAM 1
					memcpy(RAM_array1, RAM_array2, (unsigned int)BLOCK_SIZE);

					//READ RAM 2
					for (unsigned int i=0; i<(unsigned int)BLOCK_SIZE; i++) { RAM_read_spot_2[i] = RAM_array2[i]; } //dummy location
					//write RAM 2
					memcpy(RAM_array2, RAM_read_spot, (unsigned int)BLOCK_SIZE);

				}
			} else {
				while (time(NULL)*1000<bit_end_time) {};
			}
		}

		end = (time(NULL) * 1000) - start;
		printf("Done transmitting. Took %ldms.\n", end); //end should equal 32*time_per_bit_ms

		printf("Freeing memory.\n");
		free(RAM_read_spot_2);
		free(RAM_array2);
		free(cache_trick);
		free(RAM_read_spot);
		free(RAM_array1);

		distract_processor = 0; //ends forked process

		free(arg);

		kill(pid, SIGTERM); //makes sure killed process is dead

	}
	pthread_exit(NULL);
}



//--- PUBLIC FUNCTIONS ---//
void modulate_i(int bits) {

	//storing vals in here for faster writing
	printf("Reserving Memory.\n");

	unsigned char distract_processor = 1; //keeps RAM active, cache free

	unsigned char *RAM_array1      = (unsigned char*)malloc(sizeof(unsigned char) * (unsigned int)BLOCK_SIZE); //first mem array
	unsigned char *RAM_read_spot   = (unsigned char*)malloc(sizeof(unsigned char) * (unsigned int)BLOCK_SIZE); //temp location for reading
	unsigned char *cache_trick     = (unsigned char*)malloc(sizeof(unsigned char) * (unsigned int)CACHE_SIZE); //pushes heap out by 128MB
	unsigned char *RAM_array2      = (unsigned char*)malloc(sizeof(unsigned char) * (unsigned int)BLOCK_SIZE); //second mem array
	unsigned char *RAM_read_spot_2 = (unsigned char*)malloc(sizeof(unsigned char) * (unsigned int)BLOCK_SIZE); //2nd temp location for reading

	//cache avoidance program
	pid_t pid = fork();
	if (pid == 0) {
		for (unsigned int i=0; i<(unsigned int)CACHE_SIZE; i++) {
			cache_trick[i]=0xAA; //fill with garbage
		}
		while (distract_processor==1) {
			for (unsigned int i=0; i<(unsigned int)CACHE_SIZE; i++) {
				cache_trick[i] = cache_trick[i]; //may cause EM issues?
			}
		}


	} else { //normal program
		//fill usable blocks
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
					//READ RAM 1
					for (unsigned int i=0; i<(unsigned int)BLOCK_SIZE; i++) { RAM_read_spot[i] = RAM_array1[i]; } //temp var, used to oscillate 0s and 1s
					//write RAM 1
					memcpy(RAM_array1, RAM_array2, (unsigned int)BLOCK_SIZE);

					//READ RAM 2
					for (unsigned int i=0; i<(unsigned int)BLOCK_SIZE; i++) { RAM_read_spot_2[i] = RAM_array2[i]; } //dummy location
					//write RAM 2
					memcpy(RAM_array2, RAM_read_spot, (unsigned int)BLOCK_SIZE);

				}
			} else {
				while (time(NULL)*1000<bit_end_time) {};
			}
		}

		end = (time(NULL) * 1000) - start;
		printf("Done transmitting. Took %ldms.\n", end); //end should equal 32*time_per_bit_ms

		printf("Freeing memory.\n");
		free(RAM_read_spot_2);
		free(RAM_array2);
		free(cache_trick);
		free(RAM_read_spot);
		free(RAM_array1);

		distract_processor = 0; //ends forked process

		kill(pid, SIGTERM); //makes sure killed process is dead
	}

	return;
}



void multi_modulate_i(int bits, int cores) {
	printf("Attempting to transmit 32b on all cores (-1), est. %lims to complete.\n", 32*time_per_bit_ms);
	pthread_t thread_id[cores];

	for (int i=0; i<cores-1; i++) { //need to save 1 core as main, rest are secondary
		int *arg = malloc(sizeof(*arg));
		 *arg = bits;
		pthread_create(&thread_id[i], NULL, oscillate, arg);
	};
	time_t bit_end_time = time(NULL) * 1000;
	bit_end_time = bit_end_time + (32*time_per_bit_ms);
	while (time(NULL)*1000<bit_end_time) {};

	for (int j=0;j<cores-1; j++) {
		pthread_join(thread_id[j], NULL);
	}
	
}
