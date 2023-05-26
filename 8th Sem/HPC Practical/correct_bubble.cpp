#include<iostream>
#include<stdlib.h>
#include<omp.h>
using namespace std;

void bubble(int *a, int n);
void swap(int &a, int &b);

void bubble(int *a, int n){
    int swapped;
    
    for(int i = 0;  i < n; i++ ){       
        int first = i % 2;      
        swapped = 0;
		#pragma omp parallel sections
        {
            #pragma omp section
            {
                for(int j = first; j < n-1; j += 2) {       
                    if(a[j] > a[j+1]) {       
                        swap(a[j],  a[j+1]);
                        swapped = 1;
                    }       
                }  
                if(swapped==0)
                  break;
            }
        }
    }
}

void swap(int &a, int &b){
    int test;
    test=a;
    a=b;
    b=test;
}

int main(){
    int n;
	//double start_time, end_time, 
	
    cout<<"\nEnter total no of elements:";
    cin>>n;
    int a[n];
	int b[n];
	
    cout<<"\nEnter elements:";
    for(int i=0;i<n;i++){
        cin>>a[i];
		b[i] = a[i];
    }

    //start_time = omp_get_wtime(); // start timer for sequential algorithm
    bubble(a,n);
    //end_time = omp_get_wtime(); // end timer for sequential algorithm
    //cout << "\nSequential Time: " << end_time - start_time << " seconds" << endl;

    //start_time = omp_get_wtime(); // start timer for parallel algorithm
	#pragma omp parallel
	{
	    bubble(b,n);
	}
    //end_time = omp_get_wtime(); // end timer for parallel algorithm
    //cout << "\nParallel Time: " << end_time - start_time << " seconds" << endl;
	
    cout<<"\nSorted array is:";
    for(int i=0;i<n;i++){
        cout<<" "<< a[i];
    }
	
	cout<<"\nSorted array is:";
    for(int i=0;i<n;i++){
        cout<<" "<< b[i];
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
*/