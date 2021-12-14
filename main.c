#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#define SIZE 300000

struct timeval stop, start;

int *merge_b;

int c(const void* a, const void* b){
    return (*(const int*)a - *(const int*)b);
}

// functon "splits" one array into two and compares index i (from index 'low'
// until 'mid') to index j, and then copies the smaller element to merge_b.

void merge(int merge_a[], int low, int mid, int high) {
    int i = low; // starting index of merge_a, "first" array to be sorted
    int j = mid + 1; // starting index of "second" array of merge_a to be sorted
    int k = low; // starting index of merge_b
    // sets the upper limits for the two "separate" lists
    while(i <= mid && j <= high) {  
        if(merge_a[i] < merge_a[j]) merge_b[k++] = merge_a[i++];
        else merge_b[k++] = merge_a[j++];
    } // if there are elements left in either lists, copy the remaining
      // element to merge_b
    for(; i <= mid; i++) merge_b[k++] = merge_a[i];
    for(; j <= high; j++) merge_b[k++] = merge_a[j];
    // copy sorted elements back from merge_b to merge_a
    for(i = low; i <= high; i++) merge_a[i] = merge_b[i];
}

void mergeSort(int merge_a[], int size) {
    int low, mid, high, pair, idx;
    // We continously merge a pair of lists. At first, every single element
    // in the list is considered a list. Each time we pass through the
    // loop, we pair up one list to it's neighbor, merge and sort it,
    // which causes the size of each pair (or list) to double every
    // passthrough. 
    for(pair = 2; pair <= size; pair = pair * 2) { 
        for(idx = 0; idx + pair - 1 < size; idx = idx + pair) {
            low = idx;
            high = idx + pair - 1;
            mid = (low+high) / 2;
            merge(merge_a, low, mid, high);
        } // In case of uneven number of elements, we merge left over element.
        if(size - idx > pair / 2) {
            low = idx;
            high = idx + pair - 1;
            mid = (low + high) / 2;
            merge(merge_a, low, mid, size - 1);
        }
    }
    if(pair / 2 < size) merge(merge_a, 0, pair / 2 - 1, size - 1);
    
}

void insertionSort(int a[], int size){
    int j = 0, temp = 0;
    
    for(int i = 1; i < size; i++){  
        temp = a[i];   //stores i index in temp variable,
        j = i - 1;     //and sets j value to one less than i

        while (j >= 0 && a[j] > temp) { 
            a[j+1] = a[j];    //moves any number higher than temp to the right in array
            j = j - 1;      //decrements j to check if there are more higher values to left of starting position
        }
        a[j+1] = temp;  //since j is one less than i j+1 will be the previous element so the lower value (temp) will be stored to the left in array
    }
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int arr[], int size){
    int i, j;
    for (i = 0; i < size-1; i++){
        for (j = 0; j < size-i-1; j++){
            if (arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
        }
    }
}
void randomSwap(int arr[], int size, int toSwap) {
    for(int i = 0; i < toSwap; i++) 
        swap(&arr[rand() % size], &arr[rand() % size]);
}

int* createArr(int size){
    int *ar;
    ar = (int*)malloc(sizeof(int) * size);
    merge_b = (int*)malloc(sizeof(int) * size);
    FILE* f;
    f = fopen("pi.txt", "r");
    if(!f) {
        printf("Failed to open file.\n");
        return NULL;
    }
    for(int i = 0; i < size; i++){
        ar[i] = getc(f);
    }
    fclose(f);

    return ar;
}

int main(){
    
    FILE* log;
    int* arr;
    /*arr = createArr(1000000);
    randomSwap(arr, 1000000, 50000);
    log = fopen("nearly_sorted_50000.txt", "a");
    for(int i = 0; i < 1000000; i++){
        fprintf(log, "%c", arr[i]);
    }
    fclose(log); */
    char choice;

    printf("Choice: \n");
    scanf(" %c", &choice);
    switch(choice){
        case('1'):
            for(int i = 1; i < SIZE; i += 1000){ 
                arr = createArr(i);
                if(arr) {
                    gettimeofday(&start, NULL);
                    insertionSort(arr, i);
                    gettimeofday(&stop, NULL);
                    log = fopen("algodata_pi.csv", "a");
                    if(!log) {
                        printf("Failed to open file.\n");
                        break;
                    }
                    fprintf(log, "IS,%d,%lu\n", i, (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
                    free(arr);
                    free(merge_b);
                    fclose(log);
                } else break;
            } 
        case('2'):
            for(int i = 1; i < SIZE; i += 1000){ 
                arr = createArr(i);
                if(arr) {
                    gettimeofday(&start, NULL);
                    mergeSort(arr, i);
                    gettimeofday(&stop, NULL);
                    log = fopen("algodata_pi.csv", "a");
                    if(!log) {
                        printf("Failed to open file.\n");
                        break;
                    }
                    fprintf(log, "MS,%d,%lu\n", i, (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
                    free(arr);
                    free(merge_b);
                    fclose(log);
                } else break;
            }
        
        case('3'):
            for(int i = 1; i < SIZE; i += 1000){ 
                arr = createArr(i);
                if(arr) {
                    gettimeofday(&start, NULL);
                    bubbleSort(arr, i);
                    gettimeofday(&stop, NULL);
                    log = fopen("algodata_pi.csv", "a");
                    if(!log) {
                        printf("Failed to open file.\n");
                        break;
                    }
                    fprintf(log, "BS,%d,%lu\n", i, (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
                    free(arr);
                    free(merge_b);
                    fclose(log);
                } else break;
            }
            
        case('4'):
            for(int i = 1; i < SIZE; i += 1000){ 
                arr = createArr(i);
                if(arr) {
                    gettimeofday(&start, NULL);
                    qsort(arr, i, sizeof(int), c);
                    gettimeofday(&stop, NULL);
                    log = fopen("algodata_pi.csv", "a");
                    if(!log) {
                        printf("Failed to open file.\n");
                        break;
                    }
                    fprintf(log, "QS,%d,%lu\n", i, (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
                    free(arr);
                    free(merge_b);
                    fclose(log);
                } else break;
            }
           break;
    }
    return 0;
}