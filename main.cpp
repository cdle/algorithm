#include<iostream>
using namespace std;

template<typename T>
void mergeSort(T* arr,int e, int b = 1)
{
    if(e!=b)
    {
        int d = (e-b)/2;
        mergeSort(arr, b+d, b); 
        mergeSort(arr, e, b+d+1);
        T* cp = new T[e-b+1];
        copy(arr+(b--)-1, arr+e, cp);
        T* xp = cp;
        T* mp = cp + d;
        T* yp = mp + 1;
        while(b<e){
            arr[b++] = (xp<=mp && *xp>*yp) ? *(xp++) : *(yp++);
        };
    }
}

int main()
{
    int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}; 
    mergeSort(arr,20);
    for (int i = 0; i < 20; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}  