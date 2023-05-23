#include<iostream>
#include<stdlib.h>
#include<omp.h>
using namespace std;

void bubble(int *, int);
void swap(int &, int &);
void bubble(int *a, int n){
    int swapped;
    for(  int i = 0;  i < n;  i++ )
     {       
        int first = i % 2;      
        swapped=0;
        #pragma omp parallel for shared(a,first)
        for(  int j = first;  j < n-1;  j += 2  )
          {       
            if(  a[ j ]  >  a[ j+1 ]  )
             {       
                    swap(  a[ j ],  a[ j+1 ]  );
                    swapped=1;
             }       
              }  
              if(swapped==0)
              break;
     }
}

void swap(int &a, int &b){
    int test;
    test=a;
    a=b;
    b=test;

}

int main(){
    int *a,n;
    cout<<"\nEnter total no of elements:";
    cin>>n;
    a=new int[n];
    cout<<"\nEnter elements:";
    for(int i=0;i<n;i++){
        cin>>a[i];
    }

    double start_time = omp_get_wtime(); // start timer for sequential algorithm
    bubble(a,n);
    double end_time = omp_get_wtime(); // end timer for sequential algorithm
    cout << "\nSequential Time: " << end_time - start_time << " seconds" << endl;

    start_time = omp_get_wtime(); // start timer for parallel algorithm
    bubble(a,n);
    end_time = omp_get_wtime(); // end timer for parallel algorithm
    
    cout << "\nParallel Time: " << end_time - start_time << " seconds" << endl;

    cout<<"\nSorted array is:";
    for(int i=0;i<n;i++){
        cout<<" "<< a[i];
    }

    return 0;
}

/*
hduser@ubuntu-OptiPlex-390:~$ g++ -o b -fopenmp bubble.cpp
hduser@ubuntu-OptiPlex-390:~$ ./b

Enter total no of elements:6

Enter elements:7
5
1
2
0
8

Sequential Time: 0.000811231 seconds

Parallel Time: 3.682e-06 seconds

Sorted array is: 0 1 2 5 7 8

hduser@ubuntu-OptiPlex-390:~$ 


*/
