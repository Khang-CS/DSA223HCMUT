#include<iostream>

using namespace std;

void InsertionSort(int* arr, int size) {
    int current = 1;
    int walker;
    while(current<size) {
        int temp = arr[current];
        walker = current-1;
        while(walker>=0 && temp < arr[walker]) {
            arr[walker+1] = arr[walker];
            walker --;
        }

        arr[walker+1] = temp;
        current++;
    }
}

void segmentSort(int* arr, int segment, int k, int size) {
    int current = segment + k;
    int walker;
    while(current<size) {
        int temp = arr[current];
        int walker = current - k;
        while(walker >= 0 && temp < arr[walker]) {
            arr[walker+k] = arr[walker];
            walker -=k;
        }

        arr[walker+k] = temp;
        current +=k;
    }
}

void ShellSort(int* arr, int size) {
    int k = size/2;
    int segment;
    while(k>0) {
        segment = 0;
        while(segment<k) {
            segmentSort(arr, segment, k, size);
            segment++;
        }

        k/=2;
    }
}

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
        arr[smallest] = temp;
        current++;
    }
}

void BubbleSort(int* arr, int size) {
    int current = 0;
    int walker;
    bool flag = false;
    while(current<size && !flag) {
        int temp = arr[current];
        walker = size-1;
        flag = true;
        while(walker>current) {
            if(arr[walker] < arr[walker-1]) {
                int temp = arr[walker-1];
                arr[walker-1] = arr[walker];
                arr[walker] = temp;
                flag = false;
            }
            walker--;
        }
        
    }
}

int main() {
    int arr[] = {94, 87, 30, 77, 21, 42, 85, 89, 93, 37, 6, 10, 52, 54, 40, 28, 17, 6, 9, 86, 86, 78, 72, 24, 35, 52, 81, 79, 67, 31, 74, 82, 24, 0, 91, 66, 100, 60, 78, 48, 31, 58, 16, 28, 95, 100, 63, 27, 10, 57, 7, 84, 21, 48, 18, 47, 36, 60, 36, 55, 51, 84, 41, 4, 19, 52, 89, 63, 79, 99, 2, 27, 55, 63, 40, 95, 3, 90, 49, 17, 59, 54, 26, 30, 12, 98, 2, 37, 87, 62, 77, 19, 8, 64, 29, 15, 51, 15, 32, 72};
    int n = sizeof(arr)/sizeof(arr[0]);
    BubbleSort(arr,n);
    for (int i =0; i<sizeof(arr)/sizeof(arr[0]); i++)
        cout<<arr[i]<<" ";
}