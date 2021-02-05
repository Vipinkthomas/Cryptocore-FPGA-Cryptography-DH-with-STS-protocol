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

/* Prototypes for functions used to access physical memory addresses */

int open_physical (int); // For reading the content of the file to a pointer
void close_physical (int);// For reading the content of the file to a pointer


void Fileread(FILE *);// For reading the content of the file to a pointer

int main(void)
{	
	

	int dd = -1; // For reading the content of the file to a pointer
	int ret_val; // For reading the content of the file to a pointer
	__u32 trng_val = 0; // For reading the content of the file to a pointer
	__u32 i = 0; // For reading the content of the file to a pointer

	double seconds; // For reading the content of the file to a pointer
	struct timespec tstart={0,0}, tend={0,0}; // For reading the content of the file to a pointer

	// Random number creator for Ephermeral DH - exponent component
	if ((dd = open_physical (dd)) == -1) // For reading the content of the file to a pointer
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

	usleep(10); // For reading the content of the file to a pointer

	// For reading the content of the file to a pointer
	struct TRNG_params TRNG_4096_test = { 4096, 
	{  } };


	clock_gettime(CLOCK_MONOTONIC, &tstart); // For reading the content of the file to a pointer

	// Read TRNG FIRO
	TRNG_4096_test.rand[0]=0x0; // For reading the content of the file to a pointer
	TRNG_4096_test.rand[1]=0xffffffff; // For reading the content of the file to a pointer

	// For reading the content of the file to a pointer
	for(i=2; i<TRNG_4096_test.prec/32; i++){
		ret_val = ioctl(dd, IOCTL_READ_TRNG_FIFO, &trng_val);
		if(ret_val == 0) {
			TRNG_4096_test.rand[i] = trng_val;
		} else{
			printf("Error occured\n");
		}
	}

	clock_gettime(CLOCK_MONOTONIC, &tend); //Writing e to e.txt

	
	FILE *f_write = fopen("/home/bob/e.txt", "w");//Writing e to e.txt
    
    char hexString [128]= "";//Writing e to e.txt

	//Writing e to e.txt
    for(i=0 ; i< TRNG_4096_test.prec/32; i++){
        sprintf(hexString, "%08x,", TRNG_4096_test.rand[i]);
        fprintf(f_write,"%s",hexString);
    }

	
	printf("Exponent has been created");
	printf("\n\n");

	//Writing e to e.txt
	seconds = ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec);
	if (seconds*1000000.0 > 1000.0)
		printf("Reading 4096 random bits took about %.5f ms\n", seconds*1000.0);
	else 
		printf("Reading 4096 random bits took about %.5f us\n", seconds*1000000.0);	


	//Writing e to e.txt
	close_physical (dd);
	return 0;

}


//Writing e to e.txt
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

//Writing e to e.txt
void close_physical (int dd)
{
   close (dd);
}
