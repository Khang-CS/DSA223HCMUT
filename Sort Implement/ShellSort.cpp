#include<iostream>
using namespace std;


void SortSegment(int* arr, int segment, int k, int size);
void ShellSort(int* arr, int size) {
    int k = size/2;
    while(k>0) {
        int segment = 0;
        while(segment < k) {
            SortSegment(arr, segment, k, size);
            segment ++;
        }
        k/=2;
    }
}

void SortSegment(int* arr, int segment, int k, int size) {
    int current = segment + k;
    int walker;
    while(current<size) {
        int temp = arr[current];
        walker = current - k;
        while(walker >= 0 && temp<arr[walker]) {
            arr[walker+k] = arr[walker];
            walker-=k;
        }
        arr[walker+k] = temp;
        current+=k;
    }
}



int main() {
    int arr[] = {23, 31, 49, 26, 39, 2, 41, 24, 18, 32, 10, 42, 16, 44, 37, 19, 35, 48, 25, 15, 13, 43, 47, 17, 30, 22, 21, 36, 38, 29, 12, 45, 46, 14, 5, 20, 34, 7, 33, 6, 8, 11, 9};
    ShellSort(arr,sizeof(arr)/sizeof(arr[0]));
    for (int i =0; i<sizeof(arr)/sizeof(arr[0]); i++)
        cout<<arr[i]<<" ";
}