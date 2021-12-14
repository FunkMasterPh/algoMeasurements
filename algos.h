#ifndef ALGOS_H_
#define ALGOS_H_

#define SIZE 300000

struct timeval stop, start;

void merge(int merge_a[], int low, int mid, int high);
void mergeSort(int merge_a[], int size);
void insertionSort(int a[], int size);
void swap(int *a, int *b);
void bubbleSort(int arr[], int size);
int* createArr(int size, char* argv);
int c(const void* a, const void* b);
void sortTimer(char* argv1, char* argv2, int choice, char* alg);

#endif