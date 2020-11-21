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
void Fileread(FILE **);
__u32 *output_b,*output_n,*output_c2;

int main(void)
{	
	int dd = -1;
	int ret_val;

	__u32 trng_val = 0;
	__u32 i = 0;
	
	double seconds;
    
	//READ B from the file b.txt inside data_user
    FILE *fp1 = fopen("/home/data_user/b.txt", "r");
    if (fp1 == NULL) {
        fprintf(stderr, "Can't read file");
        return 0;
    }

    Fileread(&fp1);
    FILE *fp2 = fopen("/home/data_user/n.txt", "r");
    if (fp2 == NULL) {
        fprintf(stderr, "Can't read file");
        return 0;
    }

    Fileread(&fp2);

	////
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
	{  },
	{  },
	{ 0x0ff8ee95,0x8b0897a4,0x4a4a38f3,0x4da713c3,
	0x68f7b7c8,0x80e2fbcd,0xd0f50460,0xe1e7471d,
	0x5fd20690,0xea38c7a0,0x12a40752,0x48bfae37,
	0x690d523c,0xa911ec8b,0x249caad3,0x094f2f51 },
	{  },
	};
	
	
	// Read  b from file's output
	i = 0;
	while (i < ModExp_512_test.prec/32) {
		
		ModExp_512_test.b[i] = output_b[i];
		i++;
		
	}	

	// Read n from file's output
	i = 0;
	while (i < ModExp_512_test.prec/32) {
		
		ModExp_512_test.n[i] = output_n[i];
		i++;
		
	}	

	printf("B: 0x");
	for(i=0; i<ModExp_512_test.prec/32; i++){
		printf("%08x", ModExp_512_test.b[i]);
	}
	printf("\n\n");
	

	// Read random e word from TRNG FIRO and clear msb
	// i = 0;
	// while (i < 1) {
	// 	ret_val = ioctl(dd, IOCTL_READ_TRNG_FIFO, &trng_val);
	// 	if(ret_val == 0) {
	// 		trng_val &= 0x7FFFFFFF;
	// 		ModExp_512_test.e[0] = trng_val;
	// 		i++;
	// 	} else if (ret_val == -EAGAIN) {
	// 		printf("TRNG FIFO empty\n");
	// 	} else {
	// 		printf("Error occured\n");
	// 	}
	// }	

	// // Read remaining random e words from TRNG FIRO
	// i = 1;
	// while (i < ModExp_512_test.prec/32) {
	// 	ret_val = ioctl(dd, IOCTL_READ_TRNG_FIFO, &trng_val);
	// 	if(ret_val == 0) {
	// 		ModExp_512_test.e[i] = trng_val;
	// 		i++;
	// 	} else if (ret_val == -EAGAIN) {
	// 		printf("TRNG FIFO empty\n");
	// 	} else {
	// 		printf("Error occured\n");
	// 	}
	// }	
	
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
	// write c to c1.txt

	FILE *f_write = fopen("/home/data_user/c1.txt", "w");
    
    char hexString [128]= "";
	int x;
      for(x=0 ; x< ModExp_512_test.prec/32; x++){
        sprintf(hexString, "%08x,", ModExp_512_test.c[x]);
        fprintf(f_write,"%s",hexString);
    }
    
    
	

	printf("C = ModExp(R,R,E,B,P): 0x");
	for(i=0; i<ModExp_512_test.prec/32; i++){
		printf("%08x", ModExp_512_test.c[i]);
	}
	printf("\n\n");
    

    FILE *fp3 = fopen("/home/data_user/c2.txt", "r");
    if (fp2 == NULL) {
        fprintf(stderr, "Can't read file");
        return 0;
    }

    Fileread(&fp3);

	i = 0;
	while (i < ModExp_512_test.prec/32) {
		
		ModExp_512_test.b[i] = output_c2[i];
		i++;
		
	}	
	printf("B/C2: 0x");
	for(i=0; i<ModExp_512_test.prec/32; i++){
		printf("%08x", ModExp_512_test.b[i]);
	}
	printf("\n\n");

	ret_val = ioctl(dd, IOCTL_MWMAC_MODEXP, &ModExp_512_test);
	if(ret_val != 0) {
		printf("Error occured\n");
	}
	clock_gettime(CLOCK_MONOTONIC, &tend);

	printf("secret = ModExp(R,R,E,C2,P): 0x");
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
	
	close_physical (dd);   // close /dev/cryptocore
    //file close and free
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
	
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
void Fileread(FILE **fp)
{	
	char *n_string;
	__u32 *output, *temp_n;
	n_string = malloc(256* sizeof(char));
	fscanf(*fp,"%s", n_string);
    char *tok_n;
    int elements_n = 0;
    printf("%s,%s","start of function\n",n_string);
    int len_n = 1 + strlen(n_string) / 2;            // estimate max num of elements
	printf("%s","mid1 of function");  
    output = malloc(len_n* sizeof(*output));

    if (output == NULL)
        exit(-1);                               // memory alloc error
	printf("%s","mid2 of function");  
    tok_n = strtok(n_string, ",");   
    while (tok_n != NULL) {
        if (elements_n >= len_n)
            exit(-2);                           // error in length assumption
        if (1 != sscanf(tok_n, "%x", output + elements_n))
            exit(-3);                           // error in string format
        elements_n++;
        tok_n = strtok(NULL, ",");
    }

    temp_n = realloc(output, elements_n * sizeof(*output)); // resize the array
    if (temp_n == NULL)
        exit(-4);                               // error in reallocating memory
    output = temp_n;
    printf("%s","end of function");
	output_b=output;
	//free(output);
	//free(n_string);
	//fclose(fp);
}
