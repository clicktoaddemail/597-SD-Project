/* C program for pulsing a block of RAM to create some sort of EM response
that can be received on an external device.
CREATED: 10/4/22
MODIFIED: 10/31/22

CHANGELOG:
10/31/22
	- made program loop indefinately
10/29/22
	- changed test vectors to a pattern that can be discerned on demodulation
	- adjusted comments
10/17/22
	- reintegrated tests
10/14/22
	- integrated modulation into driver code.
	- integrated multithreaded modulation.
*/
#include <stdio.h>
#include <time.h>
#include "modulate.h"



//DRIVER CODE FOR RAM MODULATION
int main(void) {
	//32b over a single core

	while (1) {
		printf("Attempting to transmit 32b on a single core, est. %lims to complete.\n", 32*time_per_bit_ms);
		int TestBits = 0xF0A5C3F0; //0b1111 0000 1010 0101 1100 0011 1111 0000
		time_t start, end;
		start = time(NULL) * 1000;
		modulate_i(TestBits);
		end = (time(NULL) * 1000) - start;	

		printf("Done transmitting. Took %ldms.\n", end); //end should equal 32*time_per_bit_ms
		//wait 1000ms between transmissions
		printf("Waiting...\n");
		while ((time(NULL) * 1000) < end+1000) {}
	}
	return 0;
}


