#include<iostream>
#include<random>
#include<iomanip>
#include<fstream>

using namespace std;
const int MIN = 1;
const int MAX = 100;

int main(){

    random_device rd;
    default_random_engine eng(rd());
    uniform_real_distribution<double>dist(MIN,MAX);

    ofstream MyFile("asg1_1a.txt");

    for(int n= 0; n < 32768 ; ++n)
    {
        MyFile<<setprecision(10)
            <<dist(eng)<<"\n";
    }
    cout<<endl;

    MyFile.close();
    return 0;
}