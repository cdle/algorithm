#include<iostream>
#include<assert.h>
using namespace std;

template<typename Item>
class MaxIndexHeap
{
private:
    int capacity;
    int count;
    int* indexs;
    int* reverse;
    Item* items;
    void shiftUp(int k)
    {
        while(k/2>=1)
        {
            if(items[indexs[k/2]]>items[indexs[k]])break;
            swap(indexs[k/2],indexs[k]);
            reverse[indexs[k/2]]=k;
            reverse[indexs[k]]=k/2;
            k /= 2;
        }
    }

    void shiftDown(int k)
    {
        int j = 2*k;
        while(j<=count)
        {
            if(j+1<=count && items[indexs[j+1]]>items[indexs[j]])j++;
            if(items[indexs[j]]<=items[indexs[k]])break;
            swap(indexs[j],indexs[k]);
            reverse[indexs[j]]=k;
            reverse[indexs[k]]=j;
            k=j;
        }
    }
public:
    MaxIndexHeap(int n)
        :count(0),capacity(n)
    {
        indexs = new int[n+1];
        reverse = new int[n+1];
        for(int i=1; i<=n; i++)
        {
            reverse[i]=0;
        }
        items = new Item[n+1];
    }

    MaxIndexHeap(Item* arr,int n)
        :count(n),capacity(n)
    {
        indexs = new int[n+1];
        items = new Item[n+1];
        reverse = new int[n+1];
        for(int i=1; i<=n; i++)
        {
            indexs[i]=i;
            reverse[i]=i;
            items[i]=arr[i-1];
        }
        for(int i=n/2; i>=1; i--)
        {
            shiftDown(i);
        }
    }

    ~MaxIndexHeap()
    {
        delete[] indexs;
        delete[] items;
        delete[] reverse;
    }

    void insert(int index,Item item)
    {
        assert(count<capacity);
        count++;
        indexs[count]=index+1;
        reverse[indexs[count]]=count;
        items[index+1]=item;
        shiftUp(count);
    }

    int extractMaxIndex()
    {
        assert(count>=1);
        swap(indexs[1],indexs[count]);
        reverse[indexs[count]]=1;
        reverse[indexs[1]]=0;
        count--;
        shiftDown(1);
        return indexs[count+1]-1;
    }

    Item getValue(int k)
    {
        assert(contain(k));
        return items[k+1];
    }

    bool isEmpty()
    {
        return count==0;
    }

    bool contain(int k)
    {
        assert(k>=0 && k<capacity);
        return reverse[k+1] != 0;
    }

    void change(int k,Item item)
    {
        assert(contain(k));
        items[k+1]=item;
        int i = reverse[k+1];
        shiftDown(i);
        shiftUp(i);
        return;
    }
};

int main()
{
    int arr[5] = {1,2,3,5,4};
    MaxIndexHeap<int> heap(arr,5);
    cout << endl;
    while(!heap.isEmpty()){
        cout << heap.getValue(heap.extractMaxIndex()) << " ";
    }
    heap.insert(0,3);
    heap.insert(4,4);
    heap.insert(3,5);
    heap.insert(1,1);
    heap.change(3,100);
    heap.insert(2,2);
    cout << endl;
    while(!heap.isEmpty()){
        cout << heap.getValue(heap.extractMaxIndex()) << " ";
    }
    return 0;
}
