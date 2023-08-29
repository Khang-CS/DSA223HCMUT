#include<iostream>
using namespace std;


void SelectionSort(int* arr, int size) {
    int current = 0;
    int walker;
    while(current<size-1) {
        int smallest = current;
        int walker = current+1;
        while(walker<size) {
            if(arr[walker]<arr[smallest]) {
                smallest = walker;
            }
            walker ++;
        }

        int temp = arr[current];
        arr[current] = arr[smallest];
        arr[smallest]= temp;

        current++;
    }
}


int main() {
    int arr[] = {23, 31, 49, 26, 39, 2, 41, 24, 18, 32, 10, 42, 16, 44, 37, 19, 35, 48, 25, 15, 13, 43, 47, 17, 30, 22, 21, 36, 38, 29, 12, 45, 46, 14, 5, 20, 34, 7, 33, 6, 8, 11, 9};
    SelectionSort(arr,sizeof(arr)/sizeof(arr[0]));
    for (int i =0; i<sizeof(arr)/sizeof(arr[0]); i++)
        cout<<arr[i]<<" ";
}