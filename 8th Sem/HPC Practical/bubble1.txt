#include<iostream>
#include<stdlib.h>
#include<omp.h>
using namespace std;

void bubble(int *, int);
void swap(int &, int &);


void bubble(int *a, int n)
{
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


void swap(int &a, int &b)
{

    int test;
    test=a;
    a=b;
    b=test;

}

int main()
{

    int *a,n;
    cout<<"\n enter total no of elements=>";
    cin>>n;
    a=new int[n];
    cout<<"\n enter elements=>";
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }

    double start_time = omp_get_wtime(); // start timer for sequential algorithm
    bubble(a,n);
    double end_time = omp_get_wtime(); // end timer for sequential algorithm

    cout<<"\n sorted array is=>";
    for(int i=0;i<n;i++)
    {
        cout<<a[i]<<endl;
    }

    cout << "Time taken by sequential algorithm: " << end_time - start_time << " seconds" << endl;

    start_time = omp_get_wtime(); // start timer for parallel algorithm
    bubble(a,n);
    end_time = omp_get_wtime(); // end timer for parallel algorithm

    cout<<"\n sorted array is=>";
    for(int i=0;i<n;i++)
    {
        cout<<a[i]<<endl;
    }

    cout << "Time taken by parallel algorithm: " << end_time - start_time << " seconds" << endl;

    return 0;
}