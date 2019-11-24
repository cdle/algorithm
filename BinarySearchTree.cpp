#include <iostream>

using namespace std;

template<typename Key, typename Value>
class BinarySearchTree{
private:
    struct Node{
        Key key;
        Value value;
        Node *left;
        Node *right;

        Node(Key key,Value value)
        {
            this->key = key;
            this->value = value;
            this->left = this->right = NULL;
        };
    };
    Node *root;
    int count;
public:
    BinarySearchTree()
    {
        root = NULL;
        count = 0;
    }
    ~BinarySearchTree()
    {

    }

    int size()
    {
        return count;
    }

    bool isEmpty()
    {
        return count == 0;
    }

    void insert(Key key, Value value)//使用递归实现起来较简单
    {
        if(count!=0)
        {
            Node* p = root;
            do{
                if(p->key == key){
                    p->value = value;
                    return;
                }else if(p->key > key){
                    if(p->left==NULL)
                    {
                        p->left = new Node(key,value);
                        break;
                    }
                    p = p->left;
                } else {
                    if(p->right==NULL)
                    {
                        p->right = new Node(key,value);
                        break;
                    }
                    p = p->right;
                }
            }while(true);
        } else {
            root = new Node(key,value);
        }
        count ++;
    }

    bool contain(Key key)
    {
        Node* p = root;
        while(p!=NULL)
        {
            if(p->key == key)
            {
                return true;
            }else if(p->key > key){
                p = p->left;
            }else{
                p = p->right;
            }
        }
        return false;
    }

    Value* search(Key key)//比递归简洁
    {
        Node* p = root;
        while(p!=NULL)
        {
            if(p->key == key)
            {
                return &(p->value);
            }else if(p->key > key){
                p = p->left;
            }else{
                p = p->right;
            }
        }
        return NULL;
    }
};

int main()
{
    BinarySearchTree<int,int>* bst = new BinarySearchTree<int,int>();
    bst->insert(1,1);
    bst->insert(2,2);
    bst->insert(2,4);
    if(bst->contain(2))
    {
        cout << *(bst->search(2)) << endl;
    }
    return 0;
}
