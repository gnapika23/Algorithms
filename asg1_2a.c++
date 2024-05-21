#include<iostream>
#include<fstream>
//#include<random>
//#include<iomanip>
//#include<chrono>
using namespace std;

void merge(string arr[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int i=0;
    int j = 0;
    int k = p;
    string L[n1], M[n2];
    for (i = 0; i < n1; i++){
		L[i] = arr[p + i];
	}
    for (int j = 0; j < n2; j++){
		M[j] = arr[q + 1 + j];
	}
    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            arr[k] = L[i];
            i++;
        } 
        else {
            arr[k] = M[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = M[j];
        j++;
        k++;
    }
}


void mergeSort(string arr[], int l, int r) 
{
	if (l < r) {
		int m = l + (r - l) / 2;

		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}

int check(string arr[] , int n){
    int correct = 0;
    for(int i= 0;i<n;i++){
        if(arr[i]<arr[i-1]){
            correct = 0;
            break;
        }
    }
    return correct;
}

int main(){
    int d;
    cout<<"enter the size of the data"<<endl;
    cin>>d;
    string text[d];
    int i;
    ifstream MyFile("RandomUniformD.txt");
    for(i=0;i<d;i++){
        getline(MyFile,text[i]);
    }
    mergeSort(text,0,d-1);

    ofstream writefile("Aftersortmerge.txt");
    for(i=0;i<d;i++){
        writefile<<text[i]<<endl;
    }

    if(!check(text,d)){
        cout<<"Not sorted"<<endl;
    }else{
        cout<<"sorted"<<endl;
    }

    MyFile.close();
    writefile.close();
}