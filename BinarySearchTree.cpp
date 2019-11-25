#include <iostream>
#include <queue>
#include <cassert>

using namespace std;

template <typename Key, typename Value>
class BinarySearchTree
{
private:
    struct Node
    {
        Key key;
        Value value;
        Node *left;
        Node *right;

        Node(Key key, Value value)
        {
            this->key = key;
            this->value = value;
            this->left = this->right = NULL;
        };

        ~Node()
        {
            cout << "destroy:" << key << "!" << endl;
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
        destroy(root); //后序遍历销毁
        cout << "left:" << count << "!" << endl;
    }

    int size()
    {
        return count;
    }

    bool isEmpty()
    {
        return count == 0;
    }

    void insert(Key key, Value value) //使用递归实现起来较简单
    {
        if (count != 0)
        {
            Node *p = root;
            do
            {
                if (p->key == key)
                {
                    p->value = value;
                    return;
                }
                else if (p->key > key)
                {
                    if (p->left == NULL)
                    {
                        p->left = new Node(key, value);
                        break;
                    }
                    p = p->left;
                }
                else
                {
                    if (p->right == NULL)
                    {
                        p->right = new Node(key, value);
                        break;
                    }
                    p = p->right;
                }
            } while (true);
        }
        else
        {
            root = new Node(key, value);
        }
        count++;
    }

    bool contain(Key key)
    {
        Node *p = root;
        while (p != NULL)
        {
            if (p->key == key)
            {
                return true;
            }
            else if (p->key > key)
            {
                p = p->left;
            }
            else
            {
                p = p->right;
            }
        }
        return false;
    }

    Value *search(Key key) //比递归简洁
    {
        Node *p = root;
        while (p != NULL)
        {
            if (p->key == key)
            {
                return &(p->value);
            }
            else if (p->key > key)
            {
                p = p->left;
            }
            else
            {
                p = p->right;
            }
        }
        return NULL;
    }

    void preOrder() //前序遍历
    {
        preOrder(root);
    }

    void inOrder() //中序遍历
    {
        inOrder(root);
    }

    void postOrder() //后序遍历
    {
        postOrder(root);
    }

    void levelOrder() //层序遍历
    {
        if (count == 0)
            return;
        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            Node *node = q.front();
            cout << "Key:" << node->key << "  Value:" << node->value << endl;
            q.pop();
            if (node->left != NULL)
                q.push(node->left);
            if (node->right != NULL)
                q.push(node->right);
        }
    }

    Key minimun()
    {
        assert(count != 0);
        Node *p = root;
        while (p->left != NULL)
        {
            p = p->left;
        }
        return p->key;
    }

    Key maximun()
    {
        assert(count != 0);
        Node *p = root;
        while (p->right != NULL)
        {
            p = p->right;
        }
        return p->key;
    }

    void removeMin()
    {
        assert(count != 0);
        Node *p = root;
        Node *t = NULL;
        while (p->left != NULL)
        {
            t = p;
            p = p->left;
        }
        if (p->right != NULL)
        {
            if (t == NULL)
            {
                root = p->right;
            }
            else
            {
                t->left = p->right;
            }
        }
        delete p;
        count--;
    }

    void removeMax()
    {
        assert(count != 0);
        root = removeMax(root);
    }

    void remove(Key key)
    {
        assert(count != 0);
        root = remove(root, key);
    }

private:
    void preOrder(Node *node)
    {
        if (node != NULL)
        {
            cout << "Key:" << node->key << "  Value:" << node->value << endl;
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void inOrder(Node *node)
    {
        if (node != NULL)
        {
            inOrder(node->left);
            cout << "Key:" << node->key << "  Value:" << node->value << endl;
            inOrder(node->right);
        }
    }

    void postOrder(Node *node)
    {
        if (node != NULL)
        {
            postOrder(node->left);
            postOrder(node->right);
            cout << "Key:" << node->key << "  Value:" << node->value << endl;
        }
    }

    void destroy(Node *node)
    {
        if (node != NULL)
        {
            destroy(node->left);
            destroy(node->right);
            delete node;
            count--;
        }
    }

    Node *removeMax(Node *node)
    {
        if (node->right == NULL)
        {
            count--;
            Node *left = node->left;
            delete node;
            return left;
        }
        else
        {
            node->right = removeMax(node->right);
            return node;
        }
    }

    Node *remove(Node *node, Key key)
    {
        if (node->key > key)
        {
            if (node->left == NULL)
                return NULL;
            node->left = remove(node->left, key);
            return node;
        }
        else if (node->key < key)
        {
            if (node->right == NULL)
                return NULL;
            node->right = remove(node->right, key);
            return node;
        }
        else
        {
            Node *tmp;
            count--;
            if (node->left == NULL)
            {
                tmp = node->right;
            }
            else if (node->right == NULL)
            {
                tmp = node->left;
            }
            else
            {
                tmp = node->right;
                Node *tmp2 = NULL;
                while (tmp != NULL)
                {
                    tmp2 = tmp;
                    tmp = tmp->right;
                }
                if (tmp2 != NULL)
                {
                    tmp2->right = NULL;
                }
                tmp->right = node->right;
                tmp->left = node->left;
            }
            delete node;
            return tmp;
        }
    }
};

int main()
{
    BinarySearchTree<int, int> *bst = new BinarySearchTree<int, int>();
    bst->insert(3, 3);
    bst->insert(4, 4);
    bst->insert(5, 5);
    bst->insert(1, 1);
    bst->insert(2, 2);
    bst->removeMin();
    bst->remove(5);
    bst->removeMax();
    bst->remove(3);
    bst->removeMax();
    cout << "---------" << endl;
    delete bst;
    return 0;
}
