#include<iostream>
using namespace std;





void quickSort(int* arr, int l, int r) {
    int pivot = arr[(l+r)/2];
    int i = l;
    int j = r;
    while(i<j) {
        while(arr[i]<pivot) {
            i++;
        }

        while(arr[j]>pivot) {
            j--;
        }

        if(i<=j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    if(i<r) {
        quickSort(arr,i,r);
    }

    if(l<j) {
        quickSort(arr,l,j);
    }
}

int main() {
    int arr[] = {94, 87, 30, 77, 21, 42, 85, 89, 93, 37, 6, 10, 52, 54, 40, 28, 17, 6, 9, 86, 86, 78, 72, 24, 35, 52, 81, 79, 67, 31, 74, 82, 24, 0, 91, 66, 100, 60, 78, 48, 31, 58, 16, 28, 95, 100, 63, 27, 10, 57, 7, 84, 21, 48, 18, 47, 36, 60, 36, 55, 51, 84, 41, 4, 19, 52, 89, 63, 79, 99, 2, 27, 55, 63, 40, 95, 3, 90, 49, 17, 59, 54, 26, 30, 12, 98, 2, 37, 87, 62, 77, 19, 8, 64, 29, 15, 51, 15, 32, 72};
    int n = sizeof(arr)/sizeof(arr[0]);
    quickSort(arr,0,n-1);
    for (int i =0; i<sizeof(arr)/sizeof(arr[0]); i++)
        cout<<arr[i]<<" ";
}