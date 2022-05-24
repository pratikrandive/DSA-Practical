
/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <bits/stdc++.h>

using namespace std;

struct node
{
    int data;
    node *left;
    node *right;

    node(int n)
    {
        data = n;
        left = right = NULL;
    }
};

class BST
{

    node *insert_uti(node *root, int ele);
    node *getSucc(node *root);

public:
    BST()
    {
        root = NULL;
    }
    node *root;
    node *_delete(node *root, int ele);
    int getMin(node *root);
    int getDepth(node *root);
    node *mirror(node *root);

    void insert(int ele)
    {
        root = insert_uti(root, ele);
    }

    void search(int ele)
    {
        if (search_util(root, ele))
        {
            cout << ele << " element present" << endl;
        }
        else
        {
            cout << ele << " element not present" << endl;
        }
    }

    void PreOrder(node *root);
    void InOrder(node *root);
    void PostOrder(node *root);
    bool search_util(node *root, int ele);
};

node *BST ::insert_uti(node *root, int ele)
{
    if (root == NULL)
    {
        root = new node(ele);
        return root;
    }

    if (root->data == ele)
    {
        cout << ele << " already present in BST" << endl;
        return root;
    }
    else if (root->data > ele)
    {
        root->left = insert_uti(root->left, ele);
    }
    else
    {
        root->right = insert_uti(root->right, ele);
    }

    return root;
}

void BST ::InOrder(node *root)
{
    if (root != NULL)
    {
        InOrder(root->left);
        cout << root->data << " ";
        InOrder(root->right);
    }
}

void BST ::PreOrder(node *root)
{
    if (root != NULL)
    {
        cout << root->data << " ";
        PreOrder(root->left);
        PreOrder(root->right);
    }
}

void BST ::PostOrder(node *root)
{
    if (root != NULL)
    {
        PostOrder(root->left);
        PostOrder(root->right);
        cout << root->data << " ";
    }
}

int BST ::getMin(node *root)
{
    node *temp = root;
    while (temp->left != NULL)
    {
        temp = temp->left;
    }
    return temp->data;
}

node *BST ::getSucc(node *root)
{
    node *curr = root->right;

    while (curr->left != NULL)
    {
        curr = curr->left;
    }
    return curr;
}

bool BST ::search_util(node *root, int ele)
{
    if (root == NULL)
    {
        return false;
    }

    if (root->data == ele)
    {
        return true;
    }
    else if (root->data > ele)
    {
        return search_util(root->left, ele);
    }
    else
    {
        return search_util(root->right, ele);
    }
}

node *BST ::_delete(node *root, int ele)
{
    if (root == NULL)
    {
        cout << ele << " not found" << endl;
        return NULL;
    }
    if (root->data > ele)
    {
        root->left = _delete(root->left, ele);
    }
    else if (root->data < ele)
    {
        root->right = _delete(root->right, ele);
    }
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            return NULL;
        }
        else if (root->right == NULL)
        {
            node *temp = root;
            root = root->left;
            delete temp;
            return root;
        }
        else if (root->left == NULL)
        {
            node *temp = root;
            root = root->right;
            delete temp;
            return root;
        }
        else
        {
            node *succ = getSucc(root);
            root->data = succ->data;
            root->right = _delete(root->right, succ->data);
            return root;
        }
    }

    return root;
}

int BST::getDepth(node *root)
{
    if (root == NULL)
    {
        return 0;
    }

    if (root->left == NULL && root->right == NULL)
    {
        return 1;
    }

    int leftHeight = getDepth(root->left);
    int rightHeight = getDepth(root->right);

    int ans = 1 + max(leftHeight, rightHeight);

    return ans;
}

node *BST ::mirror(node *root)
{
    if (root == NULL)
    {
        return NULL;
    }

    root->left = mirror(root->left);
    root->right = mirror(root->right);

    node *temp = root->left;
    root->left = root->right;
    root->right = temp;

    return root;
}

int main()
{
    // cout<<"Hello World";
    BST b1;
    int ch;
    int ele;
    int n;

    while (1)
    {
        cout << "\t1.Create" << endl
             << "\t2.Insert" << endl
             << "\t3.Display" << endl
             << "\t4.search" << endl
             << "\t5.Delete" << endl
             << "\t6.Min Value" << endl
             << "\t7.get depth" << endl
             << "\t8.mirror" << endl
             << "\t9.Exit" << endl;
        cout << "Enter your choice : ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            cout << "Enter root elements of tree : ";
            cin >> ele;
            b1.insert(ele);
            break;
        case 2:
            cout << "Enter the no. of elements to insert : ";
            cin >> n;

            for (int i = 0; i < n; i++)
            {
                cout << "Enter element " << i + 1 << " : ";
                cin >> ele;
                b1.insert(ele);
            }

            break;

        case 3:
            cout << "\t1.InOrder" << endl
                 << "\t2.PreOrder" << endl
                 << "\t3.PostOrder" << endl;
            cout << "Enter choice : ";
            cin >> n;

            if (n == 1)
            {
                b1.InOrder(b1.root);
                cout << endl;
            }
            else if (n == 2)
            {
                b1.PreOrder(b1.root);
                cout << endl;
            }
            else if (n == 3)
            {
                b1.PostOrder(b1.root);
                cout << endl;
            }
            else
            {
                cout << "Wrong choice" << endl;
            }

            break;

        case 4:
            cout << "Enter element to search : ";
            cin >> ele;
            b1.search(ele);
            break;

        case 5:
            cout << "Enter element you have to delete : ";
            cin >> ele;
            b1.root = b1._delete(b1.root, ele);
            break;
        case 6:
            cout << b1.getMin(b1.root) << endl;
            break;
        case 7:
            cout << b1.getDepth(b1.root) << endl;
            break;
        case 8:
            b1.root = b1.mirror(b1.root);
            break;
        case 9:
            cout << "Thanks" << endl;
            return 0;
        default:
            cout << "Wrong choice" << endl;
            break;
        }
    }

    return 0;
}
