#include <stdio.h>
#include <stdlib.h>


char b[128];
char n[128];
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

    fscanf(fptr,"%s", n);

    fclose(fptr);

    

}

int main()
{   
    read_b_value();
    read_n_value();
    
    printf("value b = %s",b);
    printf("\n");
    printf("value n = %s",n);
    printf("\n");
  
   return 0;
}
