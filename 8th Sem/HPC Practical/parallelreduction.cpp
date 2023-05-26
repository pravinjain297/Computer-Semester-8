#include<iostream>
#include<climits>
#include<vector>
#include<omp.h>
using namespace std;

void min_reduction(vector<int>& arr){
    int min_val = INT_MAX;
    #pragma omp parallel for reduction(min: min_val)
    for(int i=0; i<arr.size(); i++){
        if(arr[i] < min_val)
            min_val = arr[i];
    }
    cout<<"\nMin value: "<<min_val;
}

void max_reduction(vector<int>& arr){
    int max_val = INT_MIN;
    #pragma omp parallel for reduction(max: max_val)
    for(int i=0; i<arr.size(); i++){
        if(arr[i] > max_val)
            max_val = arr[i];
    }
    cout<<"\nMax value: "<<max_val;
}

void sum(vector<int>& arr){
    int sum=0;
    #pragma omp parallel for reduction(+: sum)
    for(int i=0; i<arr.size(); i++){
        sum += arr[i];   
    }
    cout<<"\nSum: "<<sum;
}

void average(vector<int>& arr){
    int sum=0, avg;
    #pragma omp parallel for reduction(+: sum)
    for(int i=0; i<arr.size(); i++){
        sum += arr[i];   
    }
    avg=(double) sum / arr.size();
    cout<<"\nAverage: "<<avg;
}
int main(){
    int n,i,elements;
    vector<int> arr;
    
    cout<<"Enter no of elements: ";
    cin>>n;
    
    cout<<"Enter elements: ";
    for(int i=0; i<n; i++){
        cin>>elements;
        arr.push_back(elements);
    }
    
    min_reduction(arr);
    max_reduction(arr);
    sum(arr);
    average(arr);
    return 0;
}

/*
Enter no of elements: 3
Enter elements: 1 2 3

Min value: 1
Max value: 3
Sum: 6
Average: 2

*/