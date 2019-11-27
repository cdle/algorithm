#include <iostream>
#include <cassert>

using namespace std;

class UnionFind{
private:
    int* parent;
    // int* size;
    int* rank;
    int count;
public:
    UnionFind(int count)
    {
        parent = new int[count];
        rank = new int[count];
        this->count = count;
        for(int i=0; i<count; i++)
        {
            parent[i]=i;
            rank[i]=1;
        }
    }
    
    ~UnionFind()
    {
        delete[] parent;
        delete[] rank;
    }

    int find(int p)
    {
        assert(p>=0&&p<count);
        // while(p!=parent[p])
        // {
        //     parent[p] = parent[parent[p]];//路径压缩
        //     p = parent[p];
        // }
        if(p!=parent[p])
        {
            parent[p] = find(parent[p]);//可预测，可不递归
        }
        return parent[p];
    }

    bool isConnected(int p, int q)
    {
        return find(p) == find(q);
    }

    void unionElements(int p, int q)
    {
        int pRoot = find(p);
        int qRoot = find(q);

        if(qRoot==pRoot)
            return;
        if(rank[pRoot]<rank[qRoot])
        {
            parent[pRoot] = qRoot;
        }
        else if(rank[pRoot]>rank[qRoot])
        {
            parent[qRoot] = pRoot;
        }
        else{
            parent[pRoot] = qRoot;
            rank[qRoot]++;
        }
    }
};

int main()
{
    UnionFind* uf = new UnionFind(100);
    uf->unionElements(1,9);
    cout << uf->find(1) << endl;
    cout << uf->find(9) << endl;
    cout << uf->isConnected(1,9) << endl;
    return 0;
}
