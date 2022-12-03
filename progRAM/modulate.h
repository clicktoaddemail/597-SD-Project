/* Header file for RAM modulation, contains function headers and everything
needed to make a program to modulate RAM.
CREATED: 10/13/22
LAST MODIFIED: 10/29/22

Changelog:
12/2/22
	- changed macros
10/29/22
	- increased block size to 2 MB
10/18/22
	- cleaned up code
10/14/22
	- added multithreaded modulation for an int

*/
#ifndef MODULATE_H
#define MODULATE_H

#define KILO 1024
#define MEGA KILO*1024
#define GIGA MEGA*1024
#define BLOCK_SIZE GIGA

//--- PUBLIC VARIABLES ---//
static long int time_per_bit_ms = 200;	 	//time to spend on each bit, in ms
						//defaults to 1000ms


//--- PUBLIC FUNCTIONS ---//
void modulate_i(int bits);
	/* Modulates a given integer with the given globals above on a 
	single core.
	*/

void multi_modulate_i(int bits, int cores);
	/* Modulates a given integer with the given globals across multiple
	cores.
	*/

#endif
