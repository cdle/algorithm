#include<iostream>
using namespace std;

//归并排序
template<typename T>
void mergeSort(T* arr,int e, int b = 1)
{
    if(e!=b)
    {
        int d = (e-b)/2;
        mergeSort(arr, b+d, b); 
        mergeSort(arr, e, b+d+1);
        if(arr[b+d-1]<arr[b+d])//优化
        {
            T* cp = new T[e-b+1];
            copy(arr+(b--)-1, arr+e, cp);
            T* xp = cp;
            T* mp = cp + d;
            T* yp = mp + 1;
            while(b<e){
                arr[b++] = (xp<=mp && *xp>*yp) ? *(xp++) : *(yp++);
            };
            delete[] cp;
        }
    }
}

//自下而上的归并排序
template<typename T>
void mergeSortUB(T* arr,int n)
{
    for(int t =1; t<=n; t+=t)
    {
        for(int r=0; r+t < n; r+=t+t)
        {
            int b = r+1;
            int e = min(r+t+t,n);
            int d = t-1;
            if(arr[b+d-1]<arr[b+d])
            {
                T* cp = new T[e-b+1];
                copy(arr+(b--)-1, arr+e, cp);
                T* xp = cp;
                T* mp = cp + d;
                T* yp = mp + 1;
                while(b<e){
                    arr[b++] = (xp<=mp && *xp>*yp) ? *(xp++) : *(yp++);
                };
                delete[] cp;
            }
        }
    }
}

//快速排序
template<typename T>
void quickSort(T *arr,int n,int j=1)
{
    if(n<=1)return;
    int v = arr[j-1];
    int q = j;
    for(int i=0; i<n-1; i++)
    {
        if(v<arr[q+i])
        {
            swap(arr[j++],arr[q+i]);
        }
    }
    swap(arr[q-1],arr[j-1]);
    quickSort(arr,j-q,q);
    quickSort(arr,n-j+q-1,j+1);
}

//双路快速排序
template<typename T>
void quickSort2Ways(T *arr,int m,int n)
{
    if(n-m==1)
    {
        if(arr[m]<arr[n])
        {
            swap(arr[m],arr[n]);
        }
    }else if(n>m){
        int i = m+1;
        int j = n;
        int v = arr[m];
        while(true)
        {
            while(arr[i++]>v);
            while(arr[j--]<v);
            if(i-1>j+1)break;
            swap(arr[i-1],arr[j+1]);
        };
        swap(arr[i-2],arr[m]);
        quickSort2Ways(arr,m,i-3);
        quickSort2Ways(arr,i-1,n);
    }
}

//三路快速排序
template<typename T>
void quickSort3Ways(T *arr,int m,int n)
{
    int l = m;
    int p = m+1;
    int r = n+1;
    int v = arr[m];
    while(p<r){
        if(arr[p]>v){
            swap(arr[l+1],arr[p]);
            l++;
            p++;
        }else if(arr[p]==v){
            p++;
        }else{
            swap(arr[p],arr[r-1]);
            r--;
        }
    }
    if(l>m){
        swap(arr[m],arr[l]);
        quickSort3Ways(arr,m,l-1);
    }
    if(r<n)quickSort3Ways(arr,r,n);
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
