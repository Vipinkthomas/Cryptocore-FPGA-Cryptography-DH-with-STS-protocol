#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>



void Fileread(FILE **);
char n_string[];
__u32 *output_b,*output_n,*output_c2;

int main(void)
{	
	

	

    
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
	
    //file close and free
    fclose(fp1);
    fclose(fp2);
	
	return 0;
}

// Open /dev/cryptocore, if not already done, to give access to physical addresses

void Fileread(FILE **fp)
{	char n_string[512]="";
	__u32 *output, *temp_n;
	fscanf(*fp,"%s", n_string);
	printf("%s,%p","start of function1\n",*fp);
    char *tok_n;
    int elements_n = 0;
    printf("%s,%s","start of function2\n",n_string);
    int len_n = 1 + strlen(n_string) / 2;            // estimate max num of elements
	printf("%s","mid1 of function");  
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
    printf("%s","end of function");
	output_b=output;
	//free(output);
	//free(n_string);
	//fclose(fp);
}
