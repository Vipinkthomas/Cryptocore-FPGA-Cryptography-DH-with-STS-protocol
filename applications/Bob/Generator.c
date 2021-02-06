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

__u32 *output;// For reading the content of the file to a pointer

/* Prototypes for functions used to access physical memory addresses */
int open_physical (int);
void close_physical (int);
void Fileread(FILE *);
bool isGen(ModExp_params_t)

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

	usleep(10); // For reading the content of the file to a pointer

	// For reading the content of the file to a pointer

    ModExp_params_t ModExp_4096_test = { 4096,
	1,
	0,
	{  },
	{  },
	{  },
	{  },
	};

	// For reading the content of the file to a pointer
    FILE *fp1 = fopen("/home/data_user/n.txt", "r");
    if (fp1 == NULL) {
        fprintf(stderr, "Can't read file");
        return 0;
    }

    Fileread(fp1);
	
	i = 0;
	while (i < ModExp_4096_test.prec/32) {
		
		ModExp_4096_test.n[i] = output[i];
		i++;
		
	}	

    ModExp_4096_test.b[0]=0x0; // For reading the content of the file to a pointer
	ModExp_4096_test.b[1]=0xffffffff; // For reading the content of the file to a pointer
    while(true){
	for(i=2; i<ModExp_4096_test.prec/32; i++){
		ret_val = ioctl(dd, IOCTL_READ_TRNG_FIFO, &trng_val);
		if(ret_val == 0) {
			ModExp_4096_test.b[i] = trng_val;
		} else{
			printf("Error occured\n");
		}
	}

    if(isGen(ModExp_4096_test))
    break;

    }


	
	FILE *f_write = fopen("/home/data_user/gen.txt", "w");
    
    char hexString [128]= "";
      for(i=0 ; i< ModExp_4096_test.prec/32; i++){
        sprintf(hexString, "%08x,", ModExp_4096_test.c[i]);
        fprintf(f_write,"%s",hexString);
    }
	printf("CBob = ModExp(R,R,E,B,P): 0x");
	for(i=0; i<ModExp_4096_test.prec/32; i++){
		printf("%08x", ModExp_4096_test.c[i]);
	}
	printf("\n\n");

	FILE *f_write = fopen("/home/bob/gen.txt", "w");//Writing e to e.txt
    
    char hexString [128]= "";//Writing e to e.txt

	//Writing gen to gen.txt
    for(i=0 ; i< ModExp_4096_test.prec/32; i++){
        sprintf(hexString, "%08x,", ModExp_4096_test.c[i]);
        fprintf(f_write,"%s",hexString);
    }

	
	printf("gen has been created");
	printf("\n\n");


	close_physical (dd);   // close /dev/cryptocore
    //file close and free
    fclose(fp1);
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

bool isGen(ModExp_4096_test)
{	
    ret_val = ioctl(dd, IOCTL_MWMAC_MODEXP, &ModExp_4096_test);
    if(ret_val != 0) {
		printf("Error occured\n");
	}
}

