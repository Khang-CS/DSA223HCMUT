#include<iostream>
using namespace std;


void merge(int* arr, int l, int m, int r) {
    int size1 = m-l+1;
    int size2 = r-(m+1) +1;

    int* L = new int[size1];
    int* R = new int[size2];

    for(int i = 0; i<size1; i++) {
        L[i] = arr[i+l];
    }

    for(int i = 0; i<size2; i++) {
        R[i] = arr[i+m+1];
    }

    int i = 0;
    int j = 0;
    int k = l;
    while(i<size1 && j<size2) {
        if(L[i]<R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i<size1)   {
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j<size2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    delete [] L;
    delete [] R;
}

void mergeSort(int* arr, int l, int r) {
    if(l<r) {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr,m+1,r);
        merge(arr,l,m,r);
    }
}



int main() {
    int arr[] = {94, 87, 30, 77, 21, 42, 85, 89, 93, 37, 6, 10, 52, 54, 40, 28, 17, 6, 9, 86, 86, 78, 72, 24, 35, 52, 81, 79, 67, 31, 74, 82, 24, 0, 91, 66, 100, 60, 78, 48, 31, 58, 16, 28, 95, 100, 63, 27, 10, 57, 7, 84, 21, 48, 18, 47, 36, 60, 36, 55, 51, 84, 41, 4, 19, 52, 89, 63, 79, 99, 2, 27, 55, 63, 40, 95, 3, 90, 49, 17, 59, 54, 26, 30, 12, 98, 2, 37, 87, 62, 77, 19, 8, 64, 29, 15, 51, 15, 32, 72};
    int n = sizeof(arr)/sizeof(arr[0]);
    mergeSort(arr,0,n-1);
    for (int i =0; i<sizeof(arr)/sizeof(arr[0]); i++)
        cout<<arr[i]<<" ";
}