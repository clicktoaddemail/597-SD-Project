/* C program for pulsing a block of RAM to create some sort of EM response
that can be received on an external device.
CREATED: 10/4/22
MODIFIED: 10/4/22

CHANGELOG: 
10/4/22
	- created

*/
#include <unistd.h>
#include <stdio.h>

#define KILO 1024
#define MEGA KILO*1024
#define GIGA MEGA*1024

#define BLOCK_SIZE MEGA //adjust this to adjust memory block size

static unsigned char RAM_block[BLOCK_SIZE]; //1MB
static unsigned char is_one;

int main(void) {

	is_one = 0x00;

	while (1) {

		if (is_one==0x00) {
			is_one = 0xFF; //all high, maximum power draw
		} else {
			is_one = 0x00; //all off, changes power draw
		}

		//updates block
		for (unsigned int i=0; i<BLOCK_SIZE; i++) {
			RAM_block[i] = is_one;
		}
		printf("%x\n",is_one);
		sleep(1); //1s delay
	}
	return 0;
}
