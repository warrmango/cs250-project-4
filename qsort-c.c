#include <stdio.h>
#include <stdlib.h>

void quicksort_c(long * array, long first, long last){
   long i, j, pivot, temp;

   if(first<last){
      pivot=first;
      i=first;
      j=last;

      while(i<j){
         while(array[i]<=array[pivot]&&i<last)
            i++;
         while(array[j]>array[pivot])
            j--;
         if(i<j){
            temp=array[i];
            array[i]=array[j];
            array[j]=temp;
         }
      }

      temp=array[pivot];
      array[pivot]=array[j];
      array[j]=temp;
      quicksort_c(array,first,j-1);
      quicksort_c(array,j+1,last);
   }
}


