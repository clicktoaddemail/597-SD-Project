/* C program for pulsing a block of RAM to create some sort of EM response
that can be received on an external device.
CREATED: 10/4/22
MODIFIED: 10/14/22

CHANGELOG:
10/14/22
	- integrated modulation into driver code.
	- integrated multithreaded modulation.
*/
#include <stdio.h>
#include <time.h>
#include "modulate.h"



//DRIVER CODE FOR RAM MODULATION
int main(void) {
	//test 1: 32b over a single core
/*	printf("Attempting to transmit 32b on a single core, est. %ims to complete.\n",32000);
*/	int TestBits = 0xFF00FF00;
	time_t start, end;
/*	start = time(NULL) * 1000;
	modulate_i(TestBits);
	end = (time(NULL) * 1000) - start;	

	printf("Done transmitting. Took %ldms.\n", end);
*/
	//test 2: 32b over multiple cores
	printf("Attempting to transmit 32b over 4 cores, est. 32000ms to complete.\n");
	start = time(NULL) * 1000;
	multi_modulate_i(TestBits, 4);
	end = (time(NULL) * 1000) - start;

	printf("Done transmitting. Took %ldms.\n",end);
	return 0;
}


