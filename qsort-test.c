//
// CS250 Computer Archtecture Purdue University
// Tester for qsort
// 
// (C) Gustavo Rodriguez-Rivera grr@purdue.edu
// Do not post in Github or any public repository
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quicksort_c(long array[25], long first, long last);
void quicksort_asm(long array[25], long first, long last);

void
usage()
{
    printf("qsort-test test1|test2|test3|bench|cbench|bench2|unaligned\n");
}

void
printArray(long * array, long n, char *  header) {
    puts(header);
    for (long i = 0; i < n; i++) {
        printf("array[%ld]=%ld\n", i, array[i] );
    }
}

long * cloneArray(long n, long * array) {
    long * newArray = malloc(n*sizeof(long));
    if ( newArray == NULL) {
        printf( "Not enough memory\n");
        exit(1);
    }
    memcpy( newArray, array, n*sizeof(long)); 
    return newArray;
}

void checkArray(long n, long *orgArray, long *array) {
    quicksort_c(orgArray, 0, n-1);
    for ( long i = 0; i < n; i++) {
        if ( orgArray[i] != array[i] ) {
            printArray(orgArray, n, "-------EXPECTED ------");
            printf("\n*** Test failed...\n");
            exit(1);
        }
    }
    printf("\n>>> Test passed...\n");
    exit(0);
}

int 
main( int argc, char ** argv) 
{
   if (argc < 2) {
      usage();
      exit(1);
   } 

   printf("Running %s...\n", argv[1]);

   if ( !strcmp(argv[1],"test1") ) {
     long array [] = { 20, 4, 12, 78, 4, 27, 9, 6, 3, 5 };
     long n = sizeof(array)/sizeof(long);
     long * orgArray = cloneArray(n, array);
     printArray(array, n, "----- BEFORE SORTING -----");
     quicksort_asm(array, 0, n-1);
     printArray(array, n, "----- AFTER SORTING -----");
     checkArray(n, orgArray, array);
   }
   else if ( !strcmp(argv[1],"test2") ) {
     long array [] = { 5, 2, 7, 8, 1, 0, 9, 3, 7, 10, 11, 18, 4, 7, 9, 9, 18, 7, 12};
     long n = sizeof(array)/sizeof(long);
     long * orgArray = cloneArray(n, array);
     printArray(array, n, "----- BEFORE SORTING-----");
     quicksort_asm(array, 0, n-1);
     printArray(array, n, "----- AFTER SORTING -----");
     checkArray(n, orgArray, array);
   }
   else if ( !strcmp(argv[1],"test3") ) {
     long array [] = { 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
     long n = sizeof(array)/sizeof(long);
     long * orgArray = cloneArray(n, array);
     printArray(array, n, "----- BEFORE SORTING -----");
     quicksort_asm(array, 0, n-1);
     printArray(array, n, "----- AFTER SORTING -----");
     checkArray(n, orgArray, array);
   }
   else if ( !strcmp(argv[1],"bench2") ) {
   	printf("Run as \"time ./qsort-test bench2\"\n");
   	long n = 50000000;

   	long * array;
   	array = malloc(n*sizeof(long));
   	if ( array == NULL) {
      		printf( "Not enough memory\n");
      		exit(1);
   	}

   	for (long i = 0; i < n; i++) {
       		array[i] = rand(); 
   	}

   	quicksort_asm(array, 0, n-1);
   }
   else if ( !strcmp(argv[1],"bench") || !strcmp(argv[1],"cbench") ) {
   	printf("Run as \"time ./qsort-test bench\"\n");
   	long n = 50000000;
   	//long n = 50;

   	long * array;
   	array = malloc(n*sizeof(long));
   	if ( array == NULL) {
      		printf( "Not enough memory\n");
      		exit(1);
   	}

	long n10 = n/10;
   	for (long j = 0; j < n10; j++) {
		long i = j * 10;
		array[i] = 0*n10 + j;
		array[i+1] = 1*n10 + j;
		array[i+2] = 2*n10 + j;
		array[i+3] = 3*n10 + j;
		array[i+4] = 4*n10 + j;
		array[i+5] = 5*n10 + j;
		array[i+6] = 6*n10 + j;
		array[i+7] = 7*n10 + j;
		array[i+8] = 8*n10 + j;
		array[i+9] = 9*n10 + j;
   	}

     	//printArray(array, n, "----- BEFORE SORTING -----");

	if (!strcmp(argv[1],"bench")) {
   		quicksort_asm(array, 0, n-1);
	}
	else {
   		quicksort_c(array, 0, n-1);
	}	

     	//printArray(array, n, "----- AFTER SORTING -----");

   	for (long i = 0; i < n; i++) {
		if (array[i] != i ) {
     			//printArray(array, n, "----- EXPECTED -----");
            		printf("\n*** Test failed...\n");
            		exit(1);
		}
   	}

    	printf("\n>>> Test passed...\n");
    	exit(0);

   }
   else if ( !strcmp(argv[1],"unaligned") ) {
        // Run the same benchmark unaligned
   	printf("Run as \"time ./qsort-test unaligned\"\n");
   	long n = 50000000;

   	long * array;
   	array = malloc(n*sizeof(long)+1);

        // Unalign array
        array = (long *) ((char*)array + 3);
   	if ( array == NULL) {
      		printf( "Not enough memory\n");
      		exit(1);
   	}

   	for (long i = 0; i < n; i++) {
       		array[i] = rand(); 
   	}

   	quicksort_asm(array, 0, n-1);
   }
   else {
     printf("Invalid test %s\n", argv[1]);
     exit(1);
   }

   exit(0);

}

