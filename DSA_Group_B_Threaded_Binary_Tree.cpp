#include <bits/stdc++.h>
using namespace std;

struct node
{
    int data;
    node *left;
    node *right;
    bool leftThread;  // this is true if left pointer is thread else false
    bool rightThread; // this is true if right pointer is thread else false

    node(int data)
    {
        this->data = data;
        left = right = NULL;
        leftThread = rightThread = false;
    }
};

class TBT
{
    node *head = new node(1000); // dummy pointer who's left pointer is pointing to root;

    node *root;

public:
    TBT()
    {
        root = NULL;
    }

    void insert(int key);
    void InorderTraversal();
};

void TBT ::insert(int key)
{
    node *ptr = root;
    node *parent = NULL; // this will store parent of which new node will be child

    // for finding the position of new node
    while (ptr != head && ptr != NULL)
    {
        // if new node is alredy present
        if (ptr->data == key)
        {
            cout << key << " is already present is TBT." << endl;
            return;
        }

        parent = ptr; // update parent

        // if key is less than ptr->data then move left if ptr has left child
        if (key < ptr->data)
        {
            // if this is not thread then update ptr to it's left child
            if (ptr->leftThread == false)
            {
                ptr = ptr->left;
            }

            // else we find the position of new node so, break
            else
            {
                break;
            }
        }

        // if key is greater than ptr->data then move right if ptr has right child
        else if (key > ptr->data)
        {
            // if this is not thread then update ptr to it's right child
            if (ptr->rightThread == false)
            {
                ptr = ptr->right;
            }

            // else we find the position of new node so, break
            else
            {
                break;
            }
        }
    }

    node *temp = new node(key);

    // if parent is null then this is first node i.e. root node
    if (parent == NULL)
    {
        root = temp;
        root->leftThread = true;
        root->rightThread = true;
        head->left = root;
        root->left = head;
        root->right = head;
        cout << "Tree created successfully" << endl;
        return;
    }

    // if key is greater than parent key insert it in left
    else if (key < parent->data)
    {
        temp->left = parent->left;
        parent->left = temp;
        parent->leftThread = false;
        temp->leftThread = true;
        temp->rightThread = true;
        temp->right = parent;
    }

    // if key is greater than parent key insert it in right
    else
    {
        temp->right = parent->right;
        parent->right = temp;
        parent->rightThread = false;
        temp->leftThread = true;
        temp->rightThread = true;
        temp->left = parent;
    }
    cout << "Inserted successfully." << endl;
    return;
}

void TBT ::InorderTraversal()
{
    node *ptr = head->left;

    // traversal is carried out until ptr is not pointing to head
    while (ptr != head)
    {
        // move ptr to the left most node of tree
        while (ptr->leftThread == false)
        {
            ptr = ptr->left;
        }

        // traverse thow threads of left most node
        while (ptr->rightThread == true && ptr->right != head)
        {
            // print the data
            cout << ptr->data << " ";

            // update the ptr with thread pointing node
            ptr = ptr->right;
        }

        // this will print the root data of tree or subtree
        cout << ptr->data << " ";

        // now move ptr to right subtree
        ptr = ptr->right;
    }
}

int main()
{
    TBT bt;
    int ch;
    int n;
    int ele;

    cout << "+++----Threaded Binary Tree----+++" << endl;
    while (1)
    {
        cout << "______________MENU________________" << endl
             << "\t1.Create" << endl
             << "\t2.Insert" << endl
             << "\t3.Display" << endl
             << "\t4.Exit" << endl
             << "Enter your choice :";
        cin >> ch;

        switch (ch)
        {
        case 1:
            cout << "Enter root element : ";
            cin >> n;
            bt.insert(n);
            break;
        case 2:
            cout << "Enter number of elements you want to insert : ";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                cout << "Enter element " << i + 1 << " : ";
                cin >> ele;
                bt.insert(ele);
            }
            break;

        case 3:
            cout << "Inorder traversal of TBT : ";
            bt.InorderTraversal();
            cout << endl;
            break;

        case 4:
            cout << "Thanks" << endl;
            return 0;

        default:
            cout << "Entered wrong choice" << endl;
            break;
        }
    }
    return 0;
}