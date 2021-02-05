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

	if ((dd = open_physical (dd)) == -1)
    return (-1);

	ModExp_params_t ModExp_4096_test = { 4096,
	1,
	0,
	{  },
	{  },
	{  },
	{  },
	};
    
	
	//READ B from the file b.txt inside data_user
    FILE *fp1 = fopen("/home/data_user/b.txt", "r");
    if (fp1 == NULL) {
        fprintf(stderr, "Can't read file");
        return 0;
    }

    Fileread(fp1);

	
    i = 0;
	while (i < ModExp_4096_test.prec/32) {
		
		ModExp_4096_test.b[i] = output[i]; //assign b
		i++;
		
	}

	//Read n from n.txt file in data_user
    FILE *fp2 = fopen("/home/data_user/n.txt", "r");
    if (fp2 == NULL) {
        fprintf(stderr, "Can't read file");
        return 0;
    }

    Fileread(fp2);
	
	i = 0;
	while (i < ModExp_4096_test.prec/32) {
		
		ModExp_4096_test.n[i] = output[i]; //assign n
		i++;
		
	}	
	
	//Read e from e.txt file in alice directory
	FILE *fp3 = fopen("/home/alice/e.txt", "r");
    if (fp3 == NULL) {
        fprintf(stderr, "Can't read file");
        return 0;
    }

    Fileread(fp3);
	
	i = 0;
	while (i < ModExp_4096_test.prec/32) {
		
		ModExp_4096_test.e[i] = output[i]; //assign e
		i++;
		
	}	
	////-------------------------------------------------------->>

    
	//printing out b
	printf("B: 0x");
	for(i=0; i<ModExp_4096_test.prec/32; i++){
		printf("%08x", ModExp_4096_test.b[i]);
	}
	printf("\n\n");

	//printing out n
	printf("N: 0x");
	for(i=0; i<ModExp_4096_test.prec/32; i++){
		printf("%08x", ModExp_4096_test.n[i]);
	}
	printf("\n\n");
	
	//printing out e
	printf("E: 0x");
	for(i=0; i<ModExp_4096_test.prec/32; i++){
		printf("%08x", ModExp_4096_test.e[i]);
	}
	printf("\n\n");	

	clock_gettime(CLOCK_MONOTONIC, &tstart);
	ret_val = ioctl(dd, IOCTL_MWMAC_MODEXP, &ModExp_4096_test);
	clock_gettime(CLOCK_MONOTONIC, &tend);

	if(ret_val != 0) {
		printf("Error occured\n");
	}

	FILE *f_write = fopen("/home/alice/cAlice.txt", "w"); //file pointer for cAlice
    
    char hexString [128]= "";
	//writing the result of Mod Exp to cAlice.txt
      for(i=0 ; i< ModExp_4096_test.prec/32; i++){
        sprintf(hexString, "%08x,", ModExp_4096_test.c[i]);
        fprintf(f_write,"%s",hexString);
    }

	//priting out the value of cAlice
	printf("CAlice = ModExp(R,R,E,B,P): 0x");
	for(i=0; i<ModExp_4096_test.prec/32; i++){
		printf("%08x", ModExp_4096_test.c[i]);
	}
	printf("\n\n");

	

	seconds = ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec);
	if (seconds*1000000.0 > 1000.0)
		printf("Reading 4096 random bits took about %.5f ms\n", seconds*1000.0);
	else 
		printf("Reading 4096 random bits took about %.5f us\n", seconds*1000000.0);

	printf("\n\n");

	ModExp_4096_test.sec_calc = 1;

	clock_gettime(CLOCK_MONOTONIC, &tstart);
	ret_val = ioctl(dd, IOCTL_MWMAC_MODEXP, &ModExp_4096_test);
	clock_gettime(CLOCK_MONOTONIC, &tend);

	seconds = ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec);
	if (seconds*1000000.0 > 1000.0)
		printf("(With sec_calc=1) Reading 4096 random bits took about %.5f ms\n", seconds*1000.0);
	else 
		printf("(With sec_calc=1) Reading 4096 random bits took about %.5f us\n", seconds*1000000.0);

	close_physical (dd);   // close /dev/cryptocore
    //file close and free
    fclose(fp1);
    fclose(fp2);
	fclose(fp3);
	fclose(f_write);
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

// function

void Fileread(FILE *fp)
{	char n_string[4096]="";
	__u32 *temp_n;
	fscanf(fp,"%s", n_string);
    char *tok_n;
    int elements_n = 0;
    int len_n = 1 + strlen(n_string) / 2;            // estimate max num of elements
    output = malloc(len_n* sizeof(*output));

    if (output == NULL)
        exit(-1);                               // memory alloc error 
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
}
