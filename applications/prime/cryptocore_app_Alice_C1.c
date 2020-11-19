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

    __u32 *output_b;

    FILE *fp = fopen("/home/data_user/b.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Can't read 1.txt");
        return 0;
    }
    Fileread(fp,output_b);

	fclose(fp);
	return 0;
}

void Fileread(FILE *f,__u32 *output)
{
printf("%s","ssdgsdfsda");
char n_string[] = "";
	fscanf(f,"%s", n_string);
    __u32 *temp_n,*output1;
    char *tok_n;
    int elements_n = 0;
    int len_n = 1 + strlen(n_string) / 2;            // estimate max num of elements
    //output1 = malloc(len_n* sizeof(*output1));
}
