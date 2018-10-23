#include <stdlib.h>
#include <stdio.h>

void swap(int *a, int *b){int temp = *a; *a = *b; *b = temp;}
int less(int a, int b){if(a <= b) return 1; else return 0;}
void print(int array[], int n){int i; for(i=0;i<n;i++)printf("%d ",array[i]);printf("\n");}
void bubbleSort(int a[], int lo, int hi);
void selectSort(int array[], int, int);
void insertionSort(int a[], int lo, int hi);
int main (void){

	int array[10] = {5, 2, 3, 6, 7, 1, 9, 10, 8, 4};

	//selectSort(array, 0, 9);
	//bubbleSort(array,0,9);
	insertionSort(array,0,9);
	print(array,10);

	return 0;
}
void selectSort(int array[], int lo, int hi){
	int i, j, min;
   for (i = lo; i <= hi-1; i++) {
      min = i;
      for (j = i+1; j <= hi; j++) {
         if (less(array[j],array[min])) min = j;
      }
      swap(&array[i], &array[min]);
   }
}

void bubbleSort(int a[], int lo, int hi)
{
   int i, j, nswaps;
   for (i = lo; i < hi; i++) {
      nswaps = 0;
      for (j = hi; j > i; j--) {
         if (less(a[j], a[j-1])) {
            swap(&a[j], &a[j-1]);
            nswaps++;
         }
      }
      if (nswaps == 0) break;
   }
}

void insertionSort(int a[], int lo, int hi)
{
   int i, j, val;
   for (i = lo+1; i <= hi; i++) {
      val = a[i];
      for (j = i; j > lo; j--) {
         if (!less(val,a[j-1])) break;
         a[j] = a[j-1];
      }
      a[j] = val;
   }
}




