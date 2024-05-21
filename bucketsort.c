#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

const int N = 1000000;

typedef struct LL
{
    float data;
    struct LL *next;
    struct LL *prev;
} node;
node *LL_insert(node *list, float d){
    node *new_node = (node *)malloc(sizeof(node));
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->data = d;
    if (list == NULL)
        list = new_node;
    else{
        node *temp = list;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new_node;
        new_node->prev = temp;
    }
    return list;
}

void showLL(node *list){
    node *temp = list;
    while (temp != NULL){
        printf("%0.2f->", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

node *delete_start(node *list, float *d){
    node *temp = list;
    list = list->next;
    if (list != NULL && list->prev != NULL)
        list->prev = NULL;

    *d = temp->data;
    free(temp);
    return list;
}
void swap(float *a, float *b){
    float c = *a;
    *a = *b;
    *b = c;
}
node *insertion_sort(node *list, int *count){
    if (list != NULL){
        node *ahead = list->next;
        while (ahead != NULL){
            node *rev = ahead;
            while (rev->prev != NULL && rev->prev->data > rev->data){
                swap(&(rev->data), &(rev->prev->data));
                rev = rev->prev;
                (*count)++;
            }
            ahead = ahead->next;
            (*count)++;
        }
        return list;
    }
    return NULL;
}
void bucket_sort(float *arr, int n, int *count){
    node *bins[n];
    for (int i = 0; i < n; i++)
        bins[i] = NULL;
    int pos = 0;
    for (int i = 0; i < n; i++){
        pos = (int)(n * arr[i]);
        bins[pos] = LL_insert(bins[pos], arr[i]);
    }
    for (int i = 0; i < n; i++)
        bins[i] = insertion_sort(bins[i], count);

    pos = 0;
    float temp;
    for (int i = 0; i < n; i++){
        while (bins[i] != NULL){
            bins[i] = delete_start(bins[i], &temp);
            arr[pos] = temp;
            pos++;
        }
    }
}

int main() {
    float *arr = malloc(N * sizeof(float));
    int count = 0; 
    if (arr == NULL) {
        printf("Memory allocation failed");
        return 1;
    }
    FILE *file = fopen("NormalisedNormalDataset.txt", "r");
    if (file == NULL) {
        printf("Error opening file");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        fscanf(file, "%f", &arr[i]);
    }
    fclose(file);
    FILE *f = fopen("RandomUniformID.txt", "w");
	FILE *f1 = fopen("RandomUniformID.csv", "w");
	fprintf(f1, "size,avg_count,avg_time\n");
    const int num_iter = 100;
    for (int size = 2; size <= N; size *= 2) {
    	
    	int avg_count = 0;
    	double avg_time = 0;
        for (int i = 0; i < num_iter; i++) {
            count = 0; 
            float *subset = malloc(size * sizeof(float));
            srand(time(NULL));
            for (int i = 0; i < size; i++) {
                int randomIndex = rand() % N;
                subset[i] = arr[randomIndex];
            }
            clock_t start = clock();
            bucket_sort(subset, size, &count);
            clock_t end = clock();
            double elapsedTime = (double)(end - start) * 1000 / CLOCKS_PER_SEC;
			printf("Size: %d, Run: %d, Comparisons: %d, Time: %f\n", size, i + 1, count, elapsedTime);
            fprintf(f, "Size: %d, Run: %d, Comparisons: %d, Time: %f\n", size, i + 1, count, elapsedTime);
            free(subset);
            avg_count += count;
            avg_time += elapsedTime;
        }
        avg_count /= num_iter;
        avg_time /= num_iter;
        fprintf(f1, "%d,%d,%f\n", size, avg_count, avg_time);
    }
    fclose(f);
	fclose(f1);

    
    return 0;
}