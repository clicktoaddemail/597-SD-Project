/* C program for pulsing a block of RAM to create some sort of EM response
that can be received on an external device.
CREATED: 10/4/22
MODIFIED: 12/5/22

CHANGELOG:
12/5/22
	- changed sending pattern.
	- reintegrated multithreading
12/2/22
	- reintegrated multithreading
10/31/22
	- made program loop indefinately
*/
#include <stdio.h>
#include <time.h>

#include "modulate.h"



//DRIVER CODE FOR RAM MODULATION
int main(void) {
	//32b over a single core

	while (1) {
		int TestBits = 0xF0F0F0F0; //0b1111 0000 1111 0000 1111 0000 1111 0000
		multi_modulate_i(TestBits,4);
		//wait 1000ms between transmissions
		printf("Waiting...\n");
		time_t end = time(NULL) * 1000;
		while ((time(NULL) * 1000) < end+(long int)10000) {} //waits for processor to forget it had stuff in cache/RAM, and clean up forked processes

	}
	return 0;
}


