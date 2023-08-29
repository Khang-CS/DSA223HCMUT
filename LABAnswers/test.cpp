#include<iostream>
#include<time.h>
#include<windows.h>
#include<math.h>

using namespace std;


#define ARRAY_SIZE 50000
#define INC_SORT 0
#define DEC_SORT 1

#define MAX_HEAP 0
#define MIN_HEAP 1




long lrand() {
    #define CHAR_BITS 8
    long r =0;
    for (int i=0; i<sizeof(long)/sizeof(int); i++) {
        r= r<<(sizeof(int)*CHAR_BITS);
        r |= rand();
    }

    return r;
}


void ShuffleData(int* arr) {
    //Shuffle data
    long i;
    srand(time(NULL));

    for (i = ARRAY_SIZE-1; i>0; i--) {
        long j = lrand() % ARRAY_SIZE;
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void InsertionSort(int* arr) {
    long count = ARRAY_SIZE,current;
    current = 1;
    while (current < count) {
        int temp = arr[current];
        while 
    }


int main() {
    //Create array;
    
    int* arr1;

    arr1 = new int[ARRAY_SIZE];
    if(arr1 == NULL) {
        cout<<"Not enough memory";
        return 0;
    }

    for (long i =0; i<ARRAY_SIZE; i++) 
        arr1[i] = i;

    
}