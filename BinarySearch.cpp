#include <iostream>
#include <algorithm>

using namespace std;

template<typename T>
int binarySearch(T* arr, int n, T target)
{
    int l = 0, r = n-1;
    while(l<=r){
        int mid = l+(r-l)/2;
        if(arr[mid] == target){
            return mid;
        }else if(arr[mid] > target){
            r = mid-1;
        }else{
            l = mid+1;
        }
    }
    return -1;
}

int main()
{
    int arr[10] = {2,4,1,3,5,6,7,8,9,0};
    sort(arr,arr+10);
    cout << binarySearch(arr,10,9) << endl;
    return 0;
}
