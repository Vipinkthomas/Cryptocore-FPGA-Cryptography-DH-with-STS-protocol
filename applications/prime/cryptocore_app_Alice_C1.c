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
int Fileread(__u32 *);

int main(void)
{	
    //char * subPath = "/home/data_user/b.txt";
    __u32 *output_b;

    Fileread(output_b);

	return 0;
}

int Fileread(__u32 *output)
{   
    char n_string[] = "";
    //printf("%s",Path);
    FILE *fp = fopen("/home/data_user/c2.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Can't read c2.txt");
        return 0;
    }

    fscanf(fp,"%s", n_string);
fclose(fp);
    
}
