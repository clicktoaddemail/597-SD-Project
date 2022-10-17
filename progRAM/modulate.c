/*Source file for RAM modulation.
CREATED: 10/13/22
LAST MODIFIED: 10/17/22

Changelog:
10/17/22
	- completed multithreading
10/14/22
	- refactoring
	- added multithreaded modulation for an integer
	- TODO: complete multithreading
*/

#include "modulate.h"
#include <time.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t perform_swaps = PTHREAD_MUTEX_INITIALIZER;


unsigned char RAM_array1[MEGA];
unsigned char RAM_array2[MEGA];



//--- THREADED FUNCTIONS ---///
void *oscillate(void *end_time) { //internal function that oscillates a specified chunk of memory for a set time
	
	time_t bit_end_time = *(time_t *)end_time;

	pthread_mutex_lock(&perform_swaps);
	while (time(NULL)*1000 < bit_end_time) {
		memcpy(RAM_array1,RAM_array2, block_size);
		memcpy(RAM_array2,RAM_array1, block_size);
	}
	pthread_mutex_unlock(&perform_swaps);
	pthread_exit(NULL);
}



//--- PUBLIC FUNCTIONS ---//
void modulate_i(int bits) {
	
	unsigned char RAM_array1[block_size];
	unsigned char RAM_array2[block_size];
	time_t bit_end_time = time(NULL) * 1000;
	
	for (char i = 0; i<32; i++) {
		bit_end_time = bit_end_time+time_per_bit_ms;
		if ((bits>>i)&&0x00000001) {
			while (time(NULL)*1000 < bit_end_time) {
				memcpy(RAM_array1,RAM_array2, block_size);//    memcpy array1->array2
				memcpy(RAM_array2,RAM_array1, block_size);//    memcpy array2->array1
			}
		} else {
			while (time(NULL)*1000<bit_end_time) {};
		}
	}
	return;
}



void multi_modulate_i(int bits, int cores) {
	pthread_t thread_id;
	time_t bit_end_time = time(NULL) * 1000;
	for (char i = 0;i<32;i++) {
		bit_end_time = bit_end_time+time_per_bit_ms;
		if ((bits>>i)&&0x00000001) { //only multithreads if there is a 1, to amplify the signal, might add delay....
			pthread_mutex_lock(&perform_swaps);
			for (int j=0;j<cores; j++) {
				pthread_create(&thread_id, NULL, oscillate, (void *)&bit_end_time);
			}
			pthread_mutex_unlock(&perform_swaps); //release the threads
		} else {
			while (time(NULL)*1000<bit_end_time) {};
		}
	}	
}
