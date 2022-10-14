/* Header file for RAM modulation, contains function headers and everything
needed to make a program to modulate RAM.
CREATED: 10/13/22
LAST MODIFIED: 10/14/22

Changelog:
10/14/22
	- added multithreaded modulation for an int
10/13/22
	- created

*/
#ifndef MODULATE_H
#define MODULATE_H

#define KILO 1024
#define MEGA KILO*1024
#define GIGA MEGA*1024


//--- PUBLIC VARIABLES ---//
static long int time_per_bit_ms = 1000; 	//time to spend on each bit, in ms
						//defaults to 1000ms
static long int time_between_bits_ms = 0;  	//time to spend waiting between bits
						//in ms, defaults to 0
static int block_size = MEGA;			//the size of the memory block
						//defaults to 1MB


//--- PUBLIC FUNCTIONS ---//
void modulate_i(int bits);
	/* Modulates a given integer with the given globals above on a 
	single core.
	*/

void multi_modulate_i(int bits, int cores);
	/* Modulates a given integer with the given globals across multiple
	cores.
	*/

//TODO: modulate with "n" sized input stream, modulate witn "n" sized input stream on multiple cores

#endif