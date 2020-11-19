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


/* Prototypes for functions used to access physical memory addresses */
void Fileread(FILE *,__u32 *);

int main(void)
{	

    __u32 *output_b,*output_n,*output_c2;

    FILE *fp = fopen("/home/data_user/b.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Can't read 1.txt");
        return 0;
    }

    Fileread(fp,output_b);
	printf("%s","sdfsdfsdf");

	fclose(fp);
	return 0;
}

void Fileread(FILE *f,__u32 *output)
{	
	char n_string[] = "";
	fscanf(f,"%s", n_string);
    __u32 *temp_n;
    char *tok_n;
    int elements_n = 0;
    int len_n = 1 + strlen(n_string) / 2;            // estimate max num of elements
    output = malloc(len_n* sizeof(*output));

    if (output == NULL)
        exit(-1);                               // memory alloc error

    tok_n = strtok(n_string, ",");                  // parse the string
    while (tok_n != NULL) {
        if (elements_n >= len_n)
            exit(-2);                           // error in length assumption
        if (1 != sscanf(tok_n, "%x", output+ elements_n))
            exit(-3);                           // error in string format
        elements_n++;
        tok_n = strtok(NULL, ",");
    }

    temp_n = realloc(output, elements_n * sizeof(*output)); // resize the array
    if (temp_n == NULL)
        exit(-4);                               // error in reallocating memory
    output= temp_n;
}
