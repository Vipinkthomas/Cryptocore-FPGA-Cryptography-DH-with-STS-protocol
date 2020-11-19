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
int Fileread(char *,__u32 *);

int main(void)
{	
    char * subPath = "/home/data_user/b.txt";
    __u32 *output_b;

    Fileread(subPath,output_b);

	return 0;
}

int Fileread(char *Path,__u32 *output)
{
    printf("%s",Path);
    FILE *fp = fopen(Path, "r");
    if (fp == NULL) {
        fprintf(stderr, "Can't read 1.txt");
        return 0;
    }
printf("%s","ssdgsdfsda");
char n_string[] = "";
//fscanf(fp,"%s", n_string);
fclose(fp);
    
}
