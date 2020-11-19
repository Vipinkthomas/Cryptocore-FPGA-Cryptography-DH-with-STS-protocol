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
int Fileread();

int main(void)
{	
    //char * subPath = "/home/data_user/b.txt";
    __u32 *output_b;

    Fileread();

	return 0;
}

int Fileread()
{   
    char n_string[1000] = "";
    //printf("%s",Path);
    FILE *fp = fopen("/home/data_user/c2.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Can't read c2.txt");
        return 0;
    }

    fscanf(fp,"%s", n_string);
fclose(fp);
    
}
