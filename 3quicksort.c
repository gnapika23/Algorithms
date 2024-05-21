#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int arr[], int low, int high, long *comparisons){
    int i = (low - 1); 
    int pivot = arr[high];
    for (int j = low; j <= high- 1; j++){
        
        if (arr[j] <= pivot){
            i++;    
            swap(&arr[i], &arr[j]);
            (*comparisons)++;
        }
    }
    swap(&arr[i + 1], &arr[high]);
    (*comparisons)++;
    return (i + 1);
}

void quickSort(int arr[], int low, int high, long *comparisons){
    if (low < high) {
        int pi = partition(arr, low, high, comparisons);

        quickSort(arr, low, pi - 1, comparisons);
        quickSort(arr, pi + 1, high, comparisons);
    }
}

int is_array_sorted(int *arr, int length){
    for (int i = 0; i < length - 1; i++)
        if (arr[i] > arr[i + 1])
            return 0;

    return 1;
}

void text_to_arr(int *arr, int n){

    FILE *fin = fopen("uniform_data.csv", "r");

    int temp = 0;
    for (int i = 0; i < n; i++){
        int skip_line = rand() % 10;

        for (int j = 0; j < skip_line; j++)
            fscanf(fin, "%d\n", &temp);

        fscanf(fin, "%d\n", &temp);
        arr[i] = (int)temp;
    }

    fclose(fin);
}

int main(){
    srand(time(0));


    FILE* fp2 = fopen("observation_uniform.csv", "w");

    int max_power = 16;
    int num_of_it = 10;

    if (fp2) {
        fprintf(fp2, "Input size,Comparisons,Time (ms)\n");
        int inputSize = 2;
        for(int p = 0; p < max_power; p++){
            long long total_comparisons = 0;
            float total_time = 0;
            for(int k = 0; k < num_of_it; k++){

                int input[inputSize];

                text_to_arr(input, inputSize);

                long comparisons = 0;
                
                float start = clock();
                
                quickSort(input, 0, inputSize - 1, &comparisons);
                
                float end = clock();
       
                float timeTaken = (end - start) * 1000 / CLOCKS_PER_SEC ;

                total_comparisons += comparisons;
                total_time += timeTaken;
                if (is_array_sorted(input, sizeof(input) / sizeof(int)) == 1)
                    printf("Num = %d Run %d: %ld comparison, %0.4f ms\n", inputSize, k + 1, comparisons, timeTaken);
                else
                {
                    printf("Array Not Sorted\n");
                    break;
                }
            }

            long avg_comparisons = total_comparisons / num_of_it;
            float avg_time = total_time / num_of_it;
            
            fprintf(fp2, "%d,%ld,%0.4f\n", inputSize, avg_comparisons, avg_time);

            inputSize *= 2;
        }
        fclose(fp2);
    } else {
        printf("Failed to open output file: %s\n", "1.csv");
        return 1;
    }


    return 0;
}