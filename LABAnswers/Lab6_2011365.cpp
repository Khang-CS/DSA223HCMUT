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

class Heap {
    public:
        int* arr;
        int count;
        int capacity;
        int heap_type;
    
    public:
        int getCount() {return count;}
        void CopyData(int* data, int size) {
            memcpy(this -> arr, data, sizeof(int)*size);
            this -> count = size;
        }

        void CreateHeap(int capacity, int heap_type) {
            this -> heap_type = heap_type;
            this -> count = 0;
            this -> capacity = capacity;
            this -> arr = new int [this -> capacity];
            
            if (this -> arr == NULL) {
                cout<<"Not enough memory";
                exit(-1);
            }
        }

        ~Heap() {
            delete [] this -> arr;
        }

        void ReHeapUp(long position) {
            if (position > 0) {
                long parent = (position - 1)/2;
                

                //For max-heap
                if (this -> heap_type == MAX_HEAP && this -> arr[position] > this -> arr[parent]) {
                    int temp = this -> arr[position];
                    this -> arr[position] = this -> arr[parent];
                    this -> arr[parent] = temp;
                    ReHeapUp(parent);
                    
                }
                //For min-heap
                if(this -> heap_type == MIN_HEAP && this -> arr[position] < this -> arr[parent]) {
                    int temp = this -> arr[position];
                    this -> arr[position] = this -> arr[parent];
                    this -> arr[parent] = temp;
                    ReHeapUp(parent);
                }
            }
        }

        void ReHeapDown(int position, int lastPosition) {
            long leftChild = 2*position + 1;
            long rightChild = 2*position + 2;
            long child;

            //For max-heap
            if(this -> heap_type == MAX_HEAP) {
                if(leftChild <= lastPosition) {
                    if(rightChild<=lastPosition && this -> arr[rightChild] > this->arr[leftChild])
                        child = rightChild;
                    else
                        child = leftChild;
                    if(this->arr[child] > this ->arr[position]) {
                        int temp = this -> arr[child];
                        this -> arr[child] = this -> arr[position];
                        this -> arr[position] = temp;
                        ReHeapDown(child, lastPosition);
                    }
                }
            }
            
            //For min-heap
            else {
                if(leftChild <= lastPosition) {
                    if(rightChild<=lastPosition && this -> arr[rightChild] < this->arr[leftChild])
                        child = rightChild;
                    else
                        child = leftChild;
                    if(this->arr[child] < this ->arr[position]) {
                        int temp = this -> arr[child];
                        this -> arr[child] = this -> arr[position];
                        this -> arr[position] = temp;
                        ReHeapDown(child, lastPosition);
                    }
                }
            }
            
        }

        bool InsertHeap(int DataIn) {
            if (this -> count == this -> capacity) 
                return false;
            else {
                this -> arr[this->count] = DataIn;
                ReHeapUp(this -> count);
                this -> count ++;
                return true;
            }
        }

        bool DeleteHeap (int &DataOut) {
            if(this -> count<=0) 
                return false;
            else {
                DataOut = this -> arr[0];
                this -> arr[0] = this -> arr[count-1];
                count = count -1;
                ReHeapDown(0,count-1);
                return true;
            }
        }

        void BuildHeap() {
            long position = this -> count /2 -1;
            while(position >= 0) {
                ReHeapDown(position,count-1);
                position--;
            }
        }

        bool IsHeap() {
            long position = this -> count/2 -1;
            long lastPosition = this -> count - 1;
            while(position >= 0) {
                long leftChild = 2*position + 1;
                long rightChild = 2*position + 2;
                long child;

                if(this->heap_type == MAX_HEAP) {
                    if(leftChild <= lastPosition) {
                        if(rightChild<=lastPosition && this->arr[rightChild] > this->arr[leftChild])
                            child = rightChild;
                        else
                            child = leftChild;
                        if(this -> arr[child] > this -> arr[position])
                            return false;
                    }
                }

                position --;
            }

            return true;
        }

        void PrintHeap() {
            for (long i = 0; i<this ->count; i++) {
                cout<<this -> arr[i]<<" ";
            }

            cout<<endl;
        }
};

int* arr1 = NULL;
Heap  heap;


long lrand() {
    #define CHAR_BITS 8
    long r =0;
    for (int i=0; i<sizeof(long)/sizeof(int); i++) {
        r= r<<(sizeof(int)*CHAR_BITS);
        r |= rand();
    }

    return r;
}

bool IsSorted(int nType) {
    if(nType == DEC_SORT)
        for(int i = 0; i<ARRAY_SIZE; i++)
            if(arr1[i]!=ARRAY_SIZE-1-i)
                return false;
    else if(nType == INC_SORT)
        for (int i=0; i<ARRAY_SIZE; i++)
            if(arr1[i]!=i)
                return false;
    
    return true;
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
    long count = ARRAY_SIZE, current;
    current = 1;
    while(current < count) {
        long temp = arr[current];
        long walker = current -1;
        while(walker >= 0 && temp < arr[walker]) {
            arr[walker + 1] = arr[walker];
            walker --;
        }
        arr[walker+1] = temp;
        current ++;
    }
}

void ShellSort(int* arr) {
    long n = ARRAY_SIZE, i, j, temp, interval;
    
	for(interval = n/2; interval > 0; interval /= 2){
		for(i = interval; i < n; i++){
			temp = arr[i];
			for(j = i; j >= interval && arr[j - interval] > temp; j -= interval){
				arr[j] = arr[j - interval];				
			}
			arr[j] = temp;
		}
    }
}

void swap(int &xp, int &yp)
{
    int temp = xp;
    xp = yp;
    yp = temp;
}

void SelectionSort(int* arr) {
    long i, j, min_idx, n=ARRAY_SIZE;
    
    for (i = 0; i < n-1; i++)
    {
	
	min_idx = i;
	for (j = i+1; j < n; j++)
	    if (arr[j] < arr[min_idx])
		min_idx = j;

	
        swap(arr[min_idx], arr[i]);
    }
}

void heapify(int arr[], int N, int i)
{
 
    // Initialize largest as root
    int largest = i;
 
    // left = 2*i + 1
    int l = 2 * i + 1;
 
    // right = 2*i + 2
    int r = 2 * i + 2;
 
    // If left child is larger than root
    if (l < N && arr[l] > arr[largest])
        largest = l;
 
    // If right child is larger than largest
    // so far
    if (r < N && arr[r] > arr[largest])
        largest = r;
 
    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
 
        // Recursively heapify the affected
        // sub-tree
        heapify(arr, N, largest);
    }
}

void HeapSort(int* arr) {
    long N = ARRAY_SIZE, i;
    for (i = N / 2 - 1; i >= 0; i--)
        heapify(arr, N, i);
 
    // One by one extract an element
    // from heap
    for (i = N - 1; i > 0; i--) {
 
        // Move current root to end
        swap(arr[0], arr[i]);
 
        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

void BubbleSort(int* arr) {
    long i, j, n = ARRAY_SIZE;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
  
        // If no two elements were swapped by inner loop,
        // then break
        if (swapped == false)
            break;
    }
}

void quickSort(int a[], int l, int r){
	int p = a[(l+r)/2];
	int i = l, j = r;
	while (i < j){
		while (a[i] < p){
			i++;
		}
		while (a[j] > p){
			j--;
		}
		if (i <= j){
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			i++;
			j--;
		}
	}
	if (i < r){
		quickSort(a, i, r);
	}
	if (l < j){
		quickSort(a, l, j);
	}
}

void QuickSort(int*arr) {
    quickSort(arr,0,ARRAY_SIZE-1);
}


void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    
    int L[n1], R[n2];
 
    
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
   
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;

        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
 
        merge(arr, l, m, r);
    }
}

void MergeSort(int* arr) {
    mergeSort(arr,0,ARRAY_SIZE-1);
}

void Sorting(void(*SortFunc)(int*), int nSortType = INC_SORT) {
    DWORD startTime;
    DWORD endTime;
    long i;
    char strMessage[80];
    
    if(nSortType == INC_SORT)
        strcpy(strMessage,"The array is sorted in increasing order");
    else 
        strcpy(strMessage,"The array is sorted in decreasing order");

    //Sorting random array
    cout<<"Sorting an random array..."<<endl;

    startTime = GetTickCount();
    (*SortFunc)(arr1);
    endTime = GetTickCount();

    if(IsSorted(nSortType))
        cout<<strMessage<<endl;
    else
        cout<<"The array is unorder"<<endl;
    
    cout<<"Time (ms): "<<(endTime-startTime)/1000.0<<endl;

    //Sorting increasing array
    for(i=0; i<ARRAY_SIZE; i++) 
        arr1[i] = i;
    
    cout<<"Sorting an increasing array ..."<<endl;
    startTime = GetTickCount();
    (*SortFunc)(arr1);
    endTime = GetTickCount();

    if(IsSorted(nSortType))
        cout<<strMessage<<endl;
    else 
        cout<<"The array is unorder"<<endl;
    
    cout<<"Time (ms): "<<(endTime - startTime)/1000.0<<endl;

    //Sorting decreasing array
    for(i=0; i<ARRAY_SIZE; i++) 
        arr1[i] = ARRAY_SIZE - 1- i;

    cout<<"Sorting an decreasing array..."<<endl;

    startTime = GetTickCount();
    (*SortFunc)(arr1);
    endTime = GetTickCount();

    if(IsSorted(nSortType))
        cout<<strMessage<<endl;
    cout<<"Time (ms): "<<(endTime-startTime)/1000.0<<endl;
}

int main() {
    //Create array;
    int x;
    heap.CreateHeap(100,MAX_HEAP);
    heap.InsertHeap(6);
    heap.InsertHeap(12);
    heap.InsertHeap(4);
    heap.InsertHeap(19);
    heap.InsertHeap(22);
    heap.InsertHeap(3);
    heap.InsertHeap(2);
    heap.InsertHeap(15);
    heap.InsertHeap(13);
    heap.InsertHeap(17);
    heap.InsertHeap(30);
    heap.DeleteHeap(x);
    heap.DeleteHeap(x);
    heap.DeleteHeap(x);
    heap.PrintHeap();
    return 0;

}