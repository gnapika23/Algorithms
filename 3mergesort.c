#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


void merge(int *arr, int initial, int mid, int final, long *comparisons){
    int size1 = mid - initial + 1;
    int arr1[size1];
    for (int i = 0; i < size1; i++)
        arr1[i] = arr[initial + i];

    int size2 = final - mid;
    int arr2[size2];

    for (int i = 0; i < size2; i++)
        arr2[i] = arr[mid + 1 + i];

    int arr1_pos = 0;
    int arr2_pos = 0;
    int arr_pos = initial;

    while (arr1_pos < size1 && arr2_pos < size2){
        if (arr1[arr1_pos] < arr2[arr2_pos]){
            arr[arr_pos] = arr1[arr1_pos];
            arr1_pos++;
            arr_pos++;
            (*comparisons)++;
        }
        else{
            arr[arr_pos] = arr2[arr2_pos];
            arr2_pos++;
            arr_pos++;
            (*comparisons)++;
        }
    }

    while (arr1_pos < size1){
        arr[arr_pos] = arr1[arr1_pos];
        arr1_pos++;
        arr_pos++;
        (*comparisons)++;
    }

    while (arr2_pos < size2){
        arr[arr_pos] = arr2[arr2_pos];
        arr2_pos++;
        arr_pos++;
        (*comparisons)++;
    }
}

void merge_sort(int *arr, int initial, int final, long *comparisons){
    if (initial < final){
        int mid = (initial + final) / 2;
        merge_sort(arr, initial, mid, comparisons);
        merge_sort(arr, mid + 1, final, comparisons);
        merge(arr, initial, mid, final, comparisons);
    }
}

int is_array_sorted(int *arr, int length)
{
    for (int i = 0; i < length - 1; i++)
        if (arr[i] > arr[i + 1])
            return 0;

    return 1;
}

void text_to_arr(int *arr, int n)
{

    FILE *fin = fopen("uniform_data.csv", "r");

    int temp = 0;
    for (int i = 0; i < n; i++)
    {
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

    int max_power = 19;
    int num_of_it = 100;

    if (fp2) {
        fprintf(fp2, "Input size,Comparisons,Time (ms)\n");
    
        int inputSize = 2;
        for(int p = 0; p < max_power; p++){
            long total_comparisons = 0;
            float total_time = 0;
            for(int k = 0; k < num_of_it; k++){

                int input[inputSize];

                text_to_arr(input, inputSize);

                long comparisons = 0;
                
                float start = clock();
                
                merge_sort(input, 0, inputSize - 1, &comparisons);
                
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