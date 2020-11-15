// #include <stdio.h>
// #include <stdlib.h>


// char b1[129];
// char n1[129];

// char *read_b_value(){

    
//     FILE *fptr;

//     if ((fptr = fopen("/home/data_user/b.txt","r")) == NULL){
//         printf("Error! opening file");

//         // Program exits if the file pointer returns NULL.
//         exit(1);
//     }
    

//     fscanf(fptr,"%s", b1);
//     // fscanf(fptr,"%08x", b);

//     // printf("Value of b=%s", b);
//     fclose(fptr);

    

// }
// char *read_n_value(){

    
//     FILE *fptr;

//     if ((fptr = fopen("/home/data_user/n.txt","r")) == NULL){
//         printf("Error! opening file");

//         // Program exits if the file pointer returns NULL.
//         exit(1);
//     }

//     // fscanf(fptr,"%s", n1);
//     fscanf(fptr,"%s", n1);

//     fclose(fptr);

// }

// int main()
// {   
//     read_b_value();
//     read_n_value();
    
//     // printf("%08x",b[2]);
//     printf("\n");
//     int num = (int)strtol(n1, NULL, 16); 
//     printf("%X",num);
//     // printf("\n");
// 	// printf(b1);
  
//    return 0;
// }

	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int __u32;

int main (void) {
    char input[] = "";

    FILE *fp = fopen("/home/data_user/b.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Can't read 1.txt");
        return 0;
    }

    fscanf(fp,"%s", input);

    __u32 *output, *temp;
    char *tok;
    int elements = 0;
    int len = 1 + strlen(input) / 2;            // estimate max num of elements
    output = malloc(len * sizeof(*output));

    if (output == NULL)
        exit(-1);                               // memory alloc error

    tok = strtok(input, ",");                  // parse the string
    while (tok != NULL) {
        if (elements >= len)
            exit(-2);                           // error in length assumption
        if (1 != sscanf(tok, "%x", output + elements))
            exit(-3);                           // error in string format
        elements++;
        tok = strtok(NULL, ",");
    }

    temp = realloc(output, elements * sizeof(*output)); // resize the array
    if (temp == NULL)
        exit(-4);                               // error in reallocating memory
    output = temp;

    for (len=0; len<elements; len++)
        printf("%x ", output[len]);

    printf("\n");
    free(output);
    return 0;
}
