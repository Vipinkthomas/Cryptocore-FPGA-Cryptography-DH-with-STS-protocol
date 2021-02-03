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

#include "../../include/cryptocore_ioctl_header.h"
__u32 *output;
/* Prototypes for functions used to access physical memory addresses */
int open_physical (int);
void close_physical (int);
void Fileread(FILE *);

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

	struct TRNG_params TRNG_512_test = { 4096, 
	{  } };


	clock_gettime(CLOCK_MONOTONIC, &tstart);

	// Read TRNG FIRO
	TRNG_512_test.rand[0]=0x0;
	TRNG_512_test.rand[1]=0xffffffff;
	for(i=2; i<TRNG_512_test.prec/32; i++){
		ret_val = ioctl(dd, IOCTL_READ_TRNG_FIFO, &trng_val);
		if(ret_val == 0) {
			TRNG_512_test.rand[i] = trng_val;
		} else{
			printf("Error occured\n");
		}
	}

	clock_gettime(CLOCK_MONOTONIC, &tend);

	//Writing e to e.txt
	FILE *f_write = fopen("/home/bob/e.txt", "w");
    
    char hexString [128]= "";
      for(i=0 ; i< TRNG_512_test.prec/32; i++){
        sprintf(hexString, "%08x,", TRNG_512_test.rand[i]);
        fprintf(f_write,"%s",hexString);
    }

	printf("Exponent has been created");
	printf("\n\n");

	seconds = ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec);
	if (seconds*1000000.0 > 1000.0)
		printf("Reading 512 random bits took about %.5f ms\n", seconds*1000.0);
	else 
		printf("Reading 512 random bits took about %.5f us\n", seconds*1000000.0);	

	close_physical (dd);
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
