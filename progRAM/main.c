/* C program for pulsing a block of RAM to create some sort of EM response
that can be received on an external device.
CREATED: 10/4/22
MODIFIED: 12/2/22

CHANGELOG:
12/2/22
	- reintegrated multithreading
10/31/22
	- made program loop indefinately
10/29/22
	- changed test vectors to a pattern that can be discerned on demodulation
	- adjusted comments
10/17/22
	- reintegrated tests
*/
#include <stdio.h>
#include <time.h>
//#include <sys/sysinfo.h>

#include "modulate.h"



//DRIVER CODE FOR RAM MODULATION
int main(void) {
	//32b over a single core

	while (1) {
		int TestBits = 0xF0A5C3F0; //0b1111 0000 1010 0101 1100 0011 1111 0000
		modulate_i(TestBits);
		//wait 1000ms between transmissions
		printf("Waiting...\n");
		time_t end = time(NULL) * 1000;
		while ((time(NULL) * 1000) < end+1000) {}

	}
	return 0;
}


