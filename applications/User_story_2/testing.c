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


#include "../include/cryptocore_ioctl_header.h"

int open_physical(int);
void close_physical(int);

int main(void) {

int dd=-1;
int ret_val;

__u32 i =0;
__u32 trng_val = 0;
__u32 rw_prec = 0;

double seconds;
struct timespec tstart={0,0}, tend={0,0};

if (dd = open_physical(dd) == -1) {
    return dd=-1;
}
        


// Stop TRNG and clear FIFO
	trng_val = 0x00000010;
	ret_val = ioctl(dd, IOCTL_SET_TRNG_CMD, &trng_val);
	if(ret_val != 0) {
		printf("Error occured\n");
	}

	usleep(10);

// Configure Feedback Control Polynomial
	trng_val = 0x0003ffff;
	ret_val = ioctl(dd, IOCTL_SET_TRNG_CTR, &trng_val);
	if(ret_val != 0) {
		printf("Error occured\n");
	}

// Configure Stabilisation Time
	trng_val = 0x00000050;
	ret_val = ioctl(dd, IOCTL_SET_TRNG_TSTAB, &trng_val);
	if(ret_val != 0) {
		printf("Error occured\n");
	}

// Configure Sample Time
	trng_val = 0x00000006;
	ret_val = ioctl(dd, IOCTL_SET_TRNG_TSAMPLE, &trng_val);
	if(ret_val != 0) {
		printf("Error occured\n");
	}

// Start TRNG
	trng_val = 0x00000001;
	ret_val = ioctl(dd, IOCTL_SET_TRNG_CMD, &trng_val);
	if(ret_val != 0) {
		printf("Error occured\n");
	}

	usleep(10);


 Mod_exp_parameters_t Mod_exp_parameters = { 512,1,0,
{} ,
{} ,
{0xe8866e4b, 0x8b4cafa2, 0x63f190c6, 0x35bbc098,
0xe8950a1b, 0xff87418d, 0x574ea3f9, 0x0dab411d,
0x37882021, 0x5274e9c1, 0x71e70ebf, 0x598c9656,
0xb834a93d, 0xe4c81225, 0x05a34701, 0x9c3a9c3f},
 {}
};
if(Mod_exp_parameters.prec%32 == 0) {
    rw_prec = Mod_exp_parameters.prec;
}
    else {
        rw_prec = (Mod_exp_parameters.prec/32 +1) *32;
    }

// reading exponent

 for (i=0; i<rw_prec/32; i++) {
    ret_val = ioctl(dd, IOCTL_READ_TRNG_FIFO, &trng_val);
    if (ret_val == 0) {
        
        Mod_exp_parameters.e[i] = trng_val;
    }
    else {
        printf("error reading the base from TRNG");
    }
}
// printing exponent
 for ( i= 0; i <rw_prec/32; i++) {


    printf("%08x", Mod_exp_parameters.e[i]);
    }


// reading base
for ( i= 0; i <rw_prec/32; i++) {
    ret_val = ioctl(dd,IOCTL_READ_TRNG_FIFO, &trng_val);
        if (ret_val ==0) {
            trng_val &= 0x7FFFFFFF;
            Mod_exp_parameters.b[i] = trng_val;
        }
        else
            printf("error reading the base from TRNG");
    }



 // printing base
 for ( i= 0; i <Mod_exp_parameters.prec/32; i++) {


    printf("%08x", Mod_exp_parameters.b[i]);
    }

    // printing modulus
 for ( i= 0; i <rw_prec/32; i++) {


    printf("%08x", Mod_exp_parameters.n[i]);
    }




// Executing the function



        ret_val = ioctl(dd, IOCTL_Modular_Expont, &Mod_exp_parameters);   
            if (ret_val == 0) {
                    for ( i =0; i< rw_prec/32; i++) {
               printf("%08x ", Mod_exp_parameters.c[i]);
                    }

            }
       // printing the result

    for ( i= 0; i <rw_prec/32; i++) {


    printf("%08x", Mod_exp_parameters.c[i]);
    }







close_physical(dd);

return 0;

}

int open_physical(int dd)  {

    if (dd== -1) {
        if ( (dd= open("/dev/cryptocore", (O_RDWR | O_SYNC)))== -1) {
            printf("open device failed");
            return (-1);        
        }


    return dd;
    }



}

void close_physical( int dd) {

close (dd);


}