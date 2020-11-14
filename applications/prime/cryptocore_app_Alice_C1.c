#include <stdio.h>
#include <stdlib.h>

int main()
{
   char num;
   FILE *fptr;

   if ((fptr = fopen("/home/data_user/b.txt","r")) == NULL){
       printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
       exit(1);
   }

   fscanf(fptr,"%s", &num);

   printf("Value of n=%s", num);
   fclose(fptr); 
  
   return 0;
}
