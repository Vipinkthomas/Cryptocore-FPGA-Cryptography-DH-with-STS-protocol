#include <stdio.h>
#include <stdlib.h>


char b[130];
char n[130];
__u32 n1[128];
char *read_b_value(){

    
    FILE *fptr;

    if ((fptr = fopen("/home/data_user/b.txt","r")) == NULL){
        printf("Error! opening file");

        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    fscanf(fptr,"%s", b);

    // printf("Value of b=%s", b);
    fclose(fptr);

    

}
char *read_n_value(){

    
    FILE *fptr;

    if ((fptr = fopen("/home/data_user/n.txt","r")) == NULL){
        printf("Error! opening file");

        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    fscanf(fptr,"%s", n1);

    fclose(fptr);

    

}

int main()
{   
    read_b_value();
    read_n_value();
    
    printf("value b = %s",b);
    printf("\n");
    printf("value n = %s",n1);
    printf("\n");
  
   return 0;
}
