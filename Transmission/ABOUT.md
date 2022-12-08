# RAM Modulation
## Installation
### Hardware Requirements:
- At least 2 CPU cores
- At least 1 GB RAM

### Software Requirements:
- GNU gcc compiler
- make
- Linux prefered 

### Steps:
1. Download the repository and extract the Transmission directory to the transmitting device.
2. Navigate to the progRAM directory in a terminal.
3. (Optional) Open main.c or modulate.h in a text editor to change the parameters as desired.
4. Compile using `make`.
5. Give propper permissions to the executable.
6. Begin transmission with `./progRAM'.

## Manual
### main.c
This file contains the primary entry point for transmission. Modifying `TestBits' will result in a different vector being transmitted. It is strongly advised to wait in between sending test vectors, such that the processor has enough time to clean up memory in between transmissions.

### modulate.h
This file contains the headers and configurable variables for transmission.
Variables:
- `BLOCK_SIZE`: The size of the memory block to be used for transmission
- `CACHE_SIZE`: The size of the cache block to be used (this is an attempt to prevent the OS from caching the program)
- `time_per_bit_ms`: The time taken to transmit a single bit
Functions:
- `modulate_i(int bits)`: Single core modulation function that transmits the given 32b vector
- `modulate_i(int bits, int cores)`: Multicore modulation function that transmits the given 32b vector on n-1 cores

## Deinstallation
1. Navigate to the progRAM directory in a terminal.
2. `$ make clean`
3. Delete other remaining files.