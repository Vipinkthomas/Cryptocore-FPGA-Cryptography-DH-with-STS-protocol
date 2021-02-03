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

	ModExp_params_t ModExp_512_test = { 512,
	1,
	0,
	{  },
	{  },
	{  },
	{  },
	};
    
	
	//----------------------------------------------------->>
	FILE *fp1 = fopen("/home/alice/e.txt", "r");
    if (fp1 == NULL) {
        fprintf(stderr, "Can't read file");
        return 0;
    }

    Fileread(fp1);
	
	i = 0;
	while (i < ModExp_512_test.prec/32) {
		
		ModExp_512_test.e[i] = output[i];
		i++;
		
	}	

	FILE *fp2 = fopen("/home/data_user/n.txt", "r");
    if (fp2 == NULL) {
        fprintf(stderr, "Can't read file");
        return 0;
    }

    Fileread(fp2);
	
	i = 0;
	while (i < ModExp_512_test.prec/32) {
		
		ModExp_512_test.n[i] = output[i];
		i++;
		
	}	
	////-------------------------------------------------------->>

    
 
	printf("\n\n");
	printf("N: 0x");
	for(i=0; i<ModExp_512_test.prec/32; i++){
		printf("%08x", ModExp_512_test.n[i]);
	}
	printf("\n\n");
	
	printf("E: 0x");
	for(i=0; i<ModExp_512_test.prec/32; i++){
		printf("%08x", ModExp_512_test.e[i]);
	}
	printf("\n\n");	

	FILE *fp3 = fopen("/home/alice/cBob.txt", "r");
    if (fp3 == NULL) {
        fprintf(stderr, "Can't read file");
        return 0;
    }

    Fileread(fp3);

	i = 0;
	while (i < ModExp_512_test.prec/32) {
		
		ModExp_512_test.b[i] = output[i];
		i++;
		
	}
	printf("B/cBob: 0x");
	for(i=0; i<ModExp_512_test.prec/32; i++){
		printf("%08x", ModExp_512_test.b[i]);
	}
	printf("\n\n");

	FILE *fp4 = fopen("/home/alice/cAlice.txt", "r");
    if (fp4 == NULL) {
        fprintf(stderr, "Can't read file");
        return 0;
    }

    Fileread(fp4);

	FILE *fwrite = fopen("/home/alice/cAliceBob.txt", "w");
    
    char hexString [256]= "";


  
		for(i=0 ; i< ModExp_512_test.prec/32; i++){
        sprintf(hexString, "%08x", output[i]);
        fprintf(fwrite,"%s",hexString);
    }
	    for(i=0 ; i< ModExp_512_test.prec/32; i++){
        sprintf(hexString, "%08x", ModExp_512_test.b[i]);
        fprintf(fwrite,"%s",hexString);
    }

	ret_val = ioctl(dd, IOCTL_MWMAC_MODEXP, &ModExp_512_test);
	if(ret_val != 0) {
		printf("Error occured\n");
	}

	printf("secret = ModExp(R,R,E,C2,P): 0x");
	for(i=0; i<ModExp_512_test.prec/32; i++){
		printf("%08x", ModExp_512_test.c[i]);
	}
	printf("\n\n");

	FILE *f_write = fopen("/home/alice/secret.txt", "w");
    
    char hex_String [128]= "";
      for(i=0 ; i< ModExp_512_test.prec/32; i++){
        sprintf(hex_String, "%08x", ModExp_512_test.c[i]);
        fprintf(f_write,"%s",hex_String);
    }

	

	close_physical (dd);   // close /dev/cryptocore
    //file close and free
    
    fclose(fp1);
	fclose(fp3);
	fclose(fp2);
	fclose(fp4);
	fclose(f_write);
	fclose(fwrite);
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
{	char n_string[512]="";
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
