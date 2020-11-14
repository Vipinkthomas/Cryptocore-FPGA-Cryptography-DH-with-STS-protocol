// #include <stdio.h>
// #include <stdlib.h>


// char b[130];
// char n[130];
// __u32 n1[128];
char *read_b_value(){

    
    FILE *fptr;

    if ((fptr = fopen("/home/data_user/b.txt","r")) == NULL){
        printf("Error! opening file");

        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    fscanf(fptr,"%s", b);
    // fscanf(fptr,"%08x", b);

    // printf("Value of b=%s", b);
    fclose(fptr);

    

}
char *read_n_value(){

    
    FILE *fptr;

    if ((fptr = fopen("/home/data_user/n.txt","r")) == NULL){
        printf("Error! opening file");

        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    fscanf(fptr,"%s", n);
    // fscanf(fptr,"%08x", n);

    fclose(fptr);

    

}

// int main()
// {   
//     read_b_value();
//     read_n_value();
    
//     printf("%08x",b[2]);
//     printf("\n");
//     // printf("value n = %s",n);
//     printf("\n");
  
//    return 0;
// }

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
int open_physical (int);
void close_physical (int);

char b[130];
char n[130];

int main(void)
{
    read_b_value();
    read_n_value();

	int dd = -1;
	int ret_val;

	__u32 trng_val = 0;
	__u32 i = 0;
	
	double seconds;
	struct timespec tstart={0,0}, tend={0,0};

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
	{ n },
	{ b },
	{  },
	{  },
	};
	
	
	// Read random b from TRNG FIRO
	// i = 0;
	// while (i < ModExp_512_test.prec/32) {
	// 	ret_val = ioctl(dd, IOCTL_READ_TRNG_FIFO, &trng_val);
	// 	if(ret_val == 0) {
	// 		ModExp_512_test.b[i] = trng_val;
	// 		i++;
	// 	} else if (ret_val == -EAGAIN) {
	// 		printf("TRNG FIFO empty\n");
	// 	} else {
	// 		printf("Error occured\n");
	// 	}
	// }	

	printf("B: 0x");
	for(i=0; i<ModExp_512_test.prec/32; i++){
		printf("%08x", ModExp_512_test.b[i]);
	}
	printf("\n\n");
	
	// Read random e word from TRNG FIRO and clear msb
	i = 0;
	while (i < 1) {
		ret_val = ioctl(dd, IOCTL_READ_TRNG_FIFO, &trng_val);
		if(ret_val == 0) {
			trng_val &= 0x7FFFFFFF;
			ModExp_512_test.e[0] = trng_val;
			i++;
		} else if (ret_val == -EAGAIN) {
			printf("TRNG FIFO empty\n");
		} else {
			printf("Error occured\n");
		}
	}	

	// Read remaining random e words from TRNG FIRO
	i = 1;
	while (i < ModExp_512_test.prec/32) {
		ret_val = ioctl(dd, IOCTL_READ_TRNG_FIFO, &trng_val);
		if(ret_val == 0) {
			ModExp_512_test.e[i] = trng_val;
			i++;
		} else if (ret_val == -EAGAIN) {
			printf("TRNG FIFO empty\n");
		} else {
			printf("Error occured\n");
		}
	}	
	
	printf("E: 0x");
	for(i=0; i<ModExp_512_test.prec/32; i++){
		printf("%08x", ModExp_512_test.e[i]);
	}
	printf("\n\n");	

	printf("N: 0x");
	for(i=0; i<ModExp_512_test.prec/32; i++){
		printf("%08x", ModExp_512_test.n[i]);
	}
	printf("\n\n");	
	
	clock_gettime(CLOCK_MONOTONIC, &tstart);
	ret_val = ioctl(dd, IOCTL_MWMAC_MODEXP, &ModExp_512_test);
	if(ret_val != 0) {
		printf("Error occured\n");
	}
	clock_gettime(CLOCK_MONOTONIC, &tend);

	printf("C = ModExp(R,R,E,B,P): 0x");
	for(i=0; i<ModExp_512_test.prec/32; i++){
		printf("%08x", ModExp_512_test.c[i]);
	}
	printf("\n\n");

	seconds = ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec);
	if (seconds*1000000.0 > 1000.0)
		printf("ModExp 512 took about %.5f ms\n\n", seconds*1000.0);
	else 
		printf("ModExp 512 took about %.5f us\n\n", seconds*1000000.0);	

	// Clear c
	for(i=0; i<ModExp_512_test.prec/32; i++){
		ModExp_512_test.c[i] = 0;
	}	
	
	ModExp_512_test.sec_calc = 1;		

	clock_gettime(CLOCK_MONOTONIC, &tstart);
	ret_val = ioctl(dd, IOCTL_MWMAC_MODEXP, &ModExp_512_test);
	if(ret_val != 0) {
		printf("Error occured\n");
	}
	clock_gettime(CLOCK_MONOTONIC, &tend);

	printf("C = ModExp(R,R,E,B,P): 0x");
	for(i=0; i<ModExp_512_test.prec/32; i++){
		printf("%08x", ModExp_512_test.c[i]);
	}
	printf("\n\n");

	seconds = ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec);
	if (seconds*1000000.0 > 1000.0)
		printf("ModExp 512 (sec calc) took about %.5f ms\n\n", seconds*1000.0);
	else 
		printf("ModExp 512 (sec calc) took about %.5f us\n\n", seconds*1000000.0);
	
	close_physical (dd);   // close /dev/cryptocore
	return 0;
}

// Open /dev/cryptocore, if not already done, to give access to physical addresses
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

// Close /dev/cryptocore to give access to physical addresses
void close_physical (int dd)
{
   close (dd);
}

