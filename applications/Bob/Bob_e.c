#include <asm-generic/fcntl.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdint.h>
#include <inttypes.h>

#include "../include/cryptocore_ioctl_header.h"
__u32 *output;
/* Prototypes for functions used to access physical memory addresses */
int open_physical (int);
void close_physical (int);
int main(void)
{	
	

	int dd = -1;
	int ret_val;
	__u32 trng_val = 0;
	__u32 i = 0;

	double seconds;
	struct timespec tstart={0,0}, tend={0,0};

	// Random number creator for Ephermeral DH - exponent component
	if ((dd = open_physical (dd)) == -1)
      return (-1);

	// Stop TRNG and clear FIFO
	trng_val = 0x00000010;
	ret_val = ioctl(dd, IOCTL_SET_TRNG_CMD, &trng_val);
	if(ret_val != 0) {
		printf("Error occured\n");
	}

	usleep(10);

// Configure Feedback Control Polynomial
	trng_val = 0x0003ffff;
	ret_val = ioctl(dd, IOCTL_SET_TRNG_CTR, &trng_val);
	if(ret_val != 0) {
		printf("Error occured\n");
	}

// Configure Stabilisation Time
	trng_val = 0x00000050;
	ret_val = ioctl(dd, IOCTL_SET_TRNG_TSTAB, &trng_val);
	if(ret_val != 0) {
		printf("Error occured\n");
	}

// Configure Sample Time
	trng_val = 0x00000006;
	ret_val = ioctl(dd, IOCTL_SET_TRNG_TSAMPLE, &trng_val);
	if(ret_val != 0) {
		printf("Error occured\n");
	}

// Start TRNG
	trng_val = 0x00000001;
	ret_val = ioctl(dd, IOCTL_SET_TRNG_CMD, &trng_val);
	if(ret_val != 0) {
		printf("Error occured\n");
	}

	usleep(10);

		ModExp_params_t ModExp_512_test = { 512,
	1,
	0,
	{  },
	{  },
	{  },
	{  },
	};

	clock_gettime(CLOCK_MONOTONIC, &tstart);

	// Read TRNG FIRO
	ModExp_512_test.e[0]=0x0;
	ModExp_512_test.e[1]=0xffffffff;
	for(i=2; i<ModExp_512_test.prec/32; i++){
		ret_val = ioctl(dd, IOCTL_READ_TRNG_FIFO, &trng_val);
		if(ret_val == 0) {
			ModExp_512_test.e[i] = trng_val;
		} else{
			printf("Error occured\n");
		}
	}

    FILE *f_write = fopen("/home/vipin/e.txt", "w");
    
    char hexString [128]= "";
      for(i=0 ; i< ModExp_512_test.prec/32; i++){
        sprintf(hexString, "%08x,", ModExp_512_test.e[i]);
        fprintf(f_write,"%s",hexString);
    }
	
	i = 0;
	printf("E: 0x");
	for(i=0; i<ModExp_512_test.prec/32; i++){
		printf("%08x", ModExp_512_test.e[i]);
	}

	close_physical (dd);   // close /dev/cryptocore
    //file close and free
    fclose(f_write);
	return 0;
}

int open_physical (int dd)
{
   if (dd == -1)
      if ((dd = open( "/dev/cryptocore", (O_RDWR | O_SYNC))) == -1)
      {
         printf ("ERROR: could not open \"/dev/cryptocore\"...\n");
         return (-1);
      }
   return dd;
}


void close_physical (int dd)
{
   close (dd);
}