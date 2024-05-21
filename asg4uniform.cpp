#include<iostream>
#include<fstream>
#include<string>
#include<chrono>
using namespace std;
auto start = chrono::steady_clock::now();

int partition(string arr[], int start , int end , int *cnt){
    int pivot = stoi(arr[end]);
    int i = start - 1;

    for(int curr = start ; curr<=end ; curr++){
        if(stoi(arr[curr])<pivot){
            i++;
            swap(arr[i],arr[curr]);
            (*cnt)++;
            return(i+1);
        }
    }
    swap((arr[i+1]),arr[end]);
    (*cnt)++;
    return(i+1);
}

int randmizedpartition(string arr[], int initial , int final , int *count){
    int i = rand() % (final - initial ) + initial;
    return partition(arr,initial,final , count);
}

void quickSort(string arr[], int start , int end , int *cnt){
    if(start >= end)
        return ;
    int p = randmizedpartition(arr,start,end , cnt);
    quickSort(arr , start , p-1 , cnt);

    quickSort(arr , p+1 , end , cnt);
}

int main(){
    remove("4quickuniformcount.txt");
    remove("4qcountnumber.txt");
    int d = 1 ;
    while(d<33000){
    static int j=0;
    string text[d];
    int i , k[d];

    ifstream MyFile("RandomUniformD.txt");
    for(i=0;i<d;i++){
        getline(MyFile, text[i]);
    }
    int cnt=0 , total= 0;
    quickSort(text,0,d-1,&cnt);
    total+=cnt;

    k[j]=total;

    cout<<"no of comparisions "<<d<<" "<<k[j]<<endl;
    ofstream writecountfile;
    writecountfile.open("4quickuniformcount.txy",fstream::app);
    writecountfile<<k[j]<<'\n';
    writecountfile.close();
    ofstream writefile("4Aftersortquickuniform.txy");
    for(i=0;i<d;i++){
        writefile<<text[i]<<endl;
    }
    j++;
    MyFile.close();
    writefile.close();

    ofstream myFile("4qCountnumber.txt",fstream::app);
    myFile<<d<<endl;
    myFile.close();
    d=d*2;
    }
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout<<chrono::duration<double,milli>(diff).count()<<"ms"<<endl;
    return 0;
}