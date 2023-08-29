#include<iostream>
using namespace std;

void InsertionSort(int* arr, int size) {
    if(size>1) {
        int current = 1;
        int walker;
        while(current < size) {
            int temp = arr[current];
            walker = current - 1;
            while(walker >= 0 && temp < arr[walker]) {
                arr[walker+1] = arr[walker];
                walker --;
            }
            arr[walker +1] = temp;
            current ++;
        }
    }
}

int main() {
    int arr[] = {23,78,45,8,32,56};
    InsertionSort(arr,sizeof(arr)/sizeof(arr[0]));
    for (int i =0; i<sizeof(arr)/sizeof(arr[0]); i++)
        cout<<arr[i]<<" ";
}