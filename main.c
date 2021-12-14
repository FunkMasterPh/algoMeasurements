#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#define SIZE 300000

struct timeval stop, start;

int *merge_b;


int c(const void* a, const void* b){
    return (*(const int*)a - *(const int*)b);
}

void merge(int merge_a[], int l, int mid, int h) {
    int i = l;
    int j = mid + 1;
    int k = l;

    while(i <= mid && j <= h) {
        if(merge_a[i] < merge_a[j]) merge_b[k++] = merge_a[i++];
        else merge_b[k++] = merge_a[j++];
    }
    for(; i <= mid; i++) merge_b[k++] = merge_a[i];
    for(; j <= h; j++) merge_b[k++] = merge_a[j];
    for(i = l; i <= h; i++) merge_a[i] = merge_b[i];
}

void mergeSort(int merge_a[], int size) {
    int mid, p, h, i, l;
    
    for(p = 2; p <= size; p = p * 2) {
        for(i = 0; i + p - 1 < size; i = i + p) {
            l = i;
            h = i + p - 1;
            mid = (l+h) / 2;
            merge(merge_a, l, mid, h);
        }
        if(size - i > p / 2) {
            l = i;
            h = i + p - 1;
            mid = (l + h) / 2;
            merge(merge_a, l, mid, size - 1);
        }
    }
    if(p / 2 < size) merge(merge_a, 0, p / 2 - 1, size - 1);
    
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