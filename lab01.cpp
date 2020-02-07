/*
 Author @ Xin Wang
 */

/*
 The execution time for selection sort is O(n^2);
 The execution time for merge sort is O(nlogn);
 The execution time for my modified merge sort is also O(nlogn);
 */

/*
 The way I modified the merge sort(selection sort called within merge sort as required) is that:
    1.The mergeSort function reamined the same but call mergeMod(modified merge function) instead.
    2.In the modified merge function(mergeMod),I divide the array into two parts in the middle(left part and right part).
    3.For all merge steps but the last merge, I call selection sort to sort left part only.(if(left==0))
    4.For the last merge step, I use the normal merge function to sort the full-size array.
    5.Then the time used is: (logn-log4+1+2)*constant*n-2(logn-log4+1), which is (logn)(constant-2)(n), which is O(nlogn).
 */




#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<chrono>
using namespace std::chrono;

void populateArray(int arr[],std::size_t size)
{
    long temp=4*size;
    for(int i =0; i<size; ++i)
    {
        arr[i]=(std::rand()%temp+1)+1;
    }
}

void printArray(int arr[], std::size_t size)
{
    for(int i=0;i<size;++i)
    {
        std::cout<<arr[i]<<" ";
    }
    std::cout<<"\n";
}

void selectionSort(int arr[], std::size_t size)
{
    for(int i=0;i<(size-1);++i)
    {
        int minIdx=i;
        for(int j=(i+1);j<size;++j)
        {
            if(arr[j]<arr[minIdx]) minIdx=j;
        }
        if(minIdx !=i) std::swap(arr[i],arr[minIdx]);
    }
}

void merge(int arr[], int left, int m, int r)
{
    int i,j,k;
    int n1=m-left+1;
    int n2=r-m;
    
    int L[n1], R[n2];
    
    for(i=0;i<n1;++i)
    {
        L[i]=arr[left+1];
    }
    for(j=0;j<n2;++j)
    {
        R[i]=arr[r+1];
    }
    
    i=0;
    j=0;
    k=left;
    while(i<n1 && j<n2)
    {
        if(L[i]<=R[j])
        {
            arr[k]=L[i];
            ++i;
        }
        else
        {
            arr[k]=R[j];
            ++j;
        }
        ++k;
    }
    while(i<n1)
    {
        arr[k]=L[i];
        ++i;
        ++k;
    }
    while(j<n2)
    {
        arr[k]=R[j];
        ++j;
        ++k;
    }
}

void mergeSort(int arr[], int left, int r)
{
    if(left<r)
    {
        int m = left+(r-left)/2;
        
        mergeSort(arr,left,m);
        mergeSort(arr,m+1,r);
        merge(arr, left, m, r);
    }
}

void mergeMod(int arr[], int left, int m, int r)
{
    if(left!=0)
    {
        int n1=m-left+1;
        int L[n1];
        for(int i=0;i<n1;i++)
        {
            L[i]=arr[left+i];
        }
        selectionSort(L,n1);
    }
    else
    {
        merge(arr,left,m,r);
    }
}

void mergeSortMod(int arr[],int left,int r)
{
    if(left<r)
    {
        int m = left+(r-left)/2;
        mergeSort(arr,left,m);
        mergeSort(arr,m+1,r);
        mergeMod(arr,left,m,r);
    }
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    
    //six different number
    const int ArraySize1=100;
    
    const int ArraySize2=1000;
    const int ArraySize3=5000;
    const int ArraySize4=10000;
    const int ArraySize5=20000;
    const int ArraySize6=50000;
     
    std::cout<<"Array size=100"<<"\n";
    int arrS1[ArraySize1];
    populateArray(arrS1,ArraySize1);
    auto startS1=high_resolution_clock::now();
    selectionSort(arrS1,ArraySize1);
    auto stopS1=high_resolution_clock::now();
    auto durationS1=duration_cast<microseconds>(stopS1-startS1);
    std::cout<<"Selection Sort time is: "<<durationS1.count()<<" microseconds"<<std::endl;
    //printArray(arrS1,ArraySize1);
    
    int arrM1[ArraySize1];
    populateArray(arrM1,ArraySize1);
    auto startM1=high_resolution_clock::now();
    mergeSort(arrM1,0,ArraySize1-1);
    auto stopM1=high_resolution_clock::now();
    auto durationM1=duration_cast<microseconds>(stopM1-startM1);
    std::cout<<"Merge Sort time is "<<durationM1.count()<<" microseconds"<<std::endl;
    //printArray(arrS1,ArraySize1);
    
    int arrMS1[ArraySize1];
    populateArray(arrMS1,ArraySize1);
    auto startMS1=high_resolution_clock::now();
    mergeSortMod(arrMS1,0,ArraySize1-1);
    auto stopMS1=high_resolution_clock::now();
    auto durationMS1=duration_cast<microseconds>(stopMS1-startMS1);
    std::cout<<"Modified Merge Sort time is: "<<durationMS1.count()<<" microseconds"<<std::endl;
    //printArray(arrS1,ArraySize1);
    
    
    
    std::cout<<"\n"<<"Array size=1000"<<"\n";
    int arrS2[ArraySize2];
    populateArray(arrS2,ArraySize2);
    auto startS2=high_resolution_clock::now();
    selectionSort(arrS2,ArraySize2);
    auto stopS2=high_resolution_clock::now();
    auto durationS2=duration_cast<microseconds>(stopS2-startS2);
    std::cout<<"Selection Sort time is: "<<durationS2.count()<<" microseconds"<<std::endl;
    
    int arrM2[ArraySize2];
    populateArray(arrM2,ArraySize2);
    auto startM2=high_resolution_clock::now();
    mergeSort(arrM2,0,ArraySize2-1);
    auto stopM2=high_resolution_clock::now();
    auto durationM2=duration_cast<microseconds>(stopM2-startM2);
    std::cout<<"Merge Sort time is: "<<durationM2.count()<<" microseconds"<<std::endl;
    
    int arrMS2[ArraySize2];
    populateArray(arrMS2,ArraySize2);
    auto startMS2=high_resolution_clock::now();
    mergeSortMod(arrMS2,0,ArraySize2-1);
    auto stopMS2=high_resolution_clock::now();
    auto durationMS2=duration_cast<microseconds>(stopMS2-startMS2);
    std::cout<<"Modified Merge Sort time is: "<<durationMS2.count()<<" microseconds"<<std::endl;
    
    
    std::cout<<"\n"<<"Array size=5000"<<"\n";
    int arrS3[ArraySize3];
    populateArray(arrS3,ArraySize3);
    auto startS3=high_resolution_clock::now();
    selectionSort(arrS3,ArraySize3);
    auto stopS3=high_resolution_clock::now();
    auto durationS3=duration_cast<microseconds>(stopS3-startS3);
    std::cout<<"Selection Sort time is: "<<durationS3.count()<<" microseconds"<<std::endl;
    
    int arrM3[ArraySize3];
    populateArray(arrM3,ArraySize3);
    auto startM3=high_resolution_clock::now();
    mergeSort(arrM3,0,ArraySize3-1);
    auto stopM3=high_resolution_clock::now();
    auto durationM3=duration_cast<microseconds>(stopM3-startM3);
    std::cout<<"Merge Sort time is: "<<durationM3.count()<<" microseconds"<<std::endl;
    
    int arrMS3[ArraySize3];
    populateArray(arrMS3,ArraySize3);
    auto startMS3=high_resolution_clock::now();
    mergeSortMod(arrMS3,0,ArraySize3-1);
    auto stopMS3=high_resolution_clock::now();
    auto durationMS3=duration_cast<microseconds>(stopMS3-startMS3);
    std::cout<<"Modified Merge Sort time is: "<<durationMS3.count()<<" microseconds"<<std::endl;
    
    
    std::cout<<"\n"<<"Array size=10000"<<"\n";
    int arrS4[ArraySize4];
    populateArray(arrS4,ArraySize4);
    auto startS4=high_resolution_clock::now();
    selectionSort(arrS4,ArraySize4);
    auto stopS4=high_resolution_clock::now();
    auto durationS4=duration_cast<microseconds>(stopS4-startS4);
    std::cout<<"Selection Sort time is: "<<durationS4.count()<<" microseconds"<<std::endl;
    
    int arrM4[ArraySize4];
    populateArray(arrM4,ArraySize4);
    auto startM4=high_resolution_clock::now();
    mergeSort(arrM4,0,ArraySize4-1);
    auto stopM4=high_resolution_clock::now();
    auto durationM4=duration_cast<microseconds>(stopM4-startM4);
    std::cout<<"Merge Sort time is: "<<durationM4.count()<<" microseconds"<<std::endl;
    
    int arrMS4[ArraySize4];
    populateArray(arrMS4,ArraySize4);
    auto startMS4=high_resolution_clock::now();
    mergeSortMod(arrMS4,0,ArraySize4-1);
    auto stopMS4=high_resolution_clock::now();
    auto durationMS4=duration_cast<microseconds>(stopMS4-startMS4);
    std::cout<<"Modified Merge Sort time is: "<<durationMS4.count()<<" microseconds"<<std::endl;
    
    
    std::cout<<"\n"<<"Array size=20000"<<"\n";
    int arrS5[ArraySize5];
    populateArray(arrS5,ArraySize5);
    auto startS5=high_resolution_clock::now();
    selectionSort(arrS5,ArraySize5);
    auto stopS5=high_resolution_clock::now();
    auto durationS5=duration_cast<microseconds>(stopS5-startS5);
    std::cout<<"Selection Sort time is: "<<durationS5.count()<<" microseconds"<<std::endl;
    
    int arrM5[ArraySize5];
    populateArray(arrM5,ArraySize5);
    auto startM5=high_resolution_clock::now();
    mergeSort(arrM5,0,ArraySize5-1);
    auto stopM5=high_resolution_clock::now();
    auto durationM5=duration_cast<microseconds>(stopM5-startM5);
    std::cout<<"Merge Sort time is: "<<durationM5.count()<<" microseconds"<<std::endl;
    
    int arrMS5[ArraySize5];
    populateArray(arrMS5,ArraySize5);
    auto startMS5=high_resolution_clock::now();
    mergeSortMod(arrMS5,0,ArraySize5-1);
    auto stopMS5=high_resolution_clock::now();
    auto durationMS5=duration_cast<microseconds>(stopMS5-startMS5);
    std::cout<<"Modified Merge Sort time is: "<<durationMS5.count()<<" microseconds"<<std::endl;
    
    
    std::cout<<"\n"<<"Array size=50000"<<"\n";
    int arrS6[ArraySize6];
    populateArray(arrS6,ArraySize6);
    auto startS6=high_resolution_clock::now();
    selectionSort(arrS6,ArraySize6);
    auto stopS6=high_resolution_clock::now();
    auto durationS6=duration_cast<microseconds>(stopS6-startS6);
    std::cout<<"Selection Sort time is: "<<durationS6.count()<<" microseconds"<<std::endl;
    
    int arrM6[ArraySize6];
    populateArray(arrM6,ArraySize6);
    auto startM6=high_resolution_clock::now();
    mergeSort(arrM6,0,ArraySize6-1);
    auto stopM6=high_resolution_clock::now();
    auto durationM6=duration_cast<microseconds>(stopM6-startM6);
    std::cout<<"Merge Sort time is: "<<durationM6.count()<<" microseconds"<<std::endl;
    
    int arrMS6[ArraySize6];
    populateArray(arrMS6,ArraySize6);
    auto startMS6=high_resolution_clock::now();
    mergeSortMod(arrMS6,0,ArraySize6-1);
    auto stopMS6=high_resolution_clock::now();
    auto durationMS6=duration_cast<microseconds>(stopMS6-startMS6);
    std::cout<<"Modified Merge Sort time is: "<<durationMS6.count()<<" microseconds"<<std::endl;
    
    return 0;
}
