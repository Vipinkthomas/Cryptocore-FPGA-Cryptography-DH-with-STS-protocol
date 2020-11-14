#include <stdio.h>
#include <stdlib.h>


char b1[129];
char n1[129];

char *read_b_value(){

    
    FILE *fptr;

    if ((fptr = fopen("/home/data_user/b.txt","r")) == NULL){
        printf("Error! opening file");

        // Program exits if the file pointer returns NULL.
        exit(1);
    }
    

    fscanf(fptr,"%s", b1);
    // fscanf(fptr,"%08x", b);

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

    // fscanf(fptr,"%s", n1);
    fscanf(fptr,"%s", n1);

    fclose(fptr);

}

int main()
{   
    read_b_value();
    read_n_value();
    
    // printf("%08x",b[2]);
    printf("\n");
    int num = (int)strtol(n1, NULL, 16); 
    printf("%X",num);
    // printf("\n");
	// printf(b1);
  
   return 0;
}

	
