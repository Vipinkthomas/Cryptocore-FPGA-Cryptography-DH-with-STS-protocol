#include <stdio.h>
#include <stdlib.h>


char b[128];

char *read_b_value(){

    // char b[128];
    FILE *fptr;

    if ((fptr = fopen("/home/data_user/b.txt","r")) == NULL){
        printf("Error! opening file");

        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    fscanf(fptr,"%s", b);

    // printf("Value of b=%s", b);
    fclose(fptr);

    return b;

}

int main()
{   
    read_b_value();
    
    printf("%s",b);
    printf("\n");
  
   return 0;
}
