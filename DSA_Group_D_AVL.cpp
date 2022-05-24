
/*
A Dictionary stores keywords and its meanings. Provide facility for adding new
keywords, deleting keywords, updating values of any entry. Provide facility to display
whole data sorted in ascending/ Descending order. Also find how many maximum
comparisons may require for finding any keyword. Use Height balance tree and find the
complexity for finding a keyword
*/

#include <bits/stdc++.h>
using namespace std;

struct node
{
    string keyword;
    string meaning;

    node *left;
    node *right;
    int height;

    node(string keyword, string meaning)
    {
        this->keyword = keyword;
        this->meaning = meaning;
        left = right = NULL;
        height = 1;
    }
};

class Dictionary
{
    node *getSucc(node *n);
    node *RightRotate(node *x);
    node *LeftRotate(node *y);
    int getBalanceFactor(node *n);
    int getHeight(node *n);

public:
    node *root;
    Dictionary()
    {
        root = NULL;
    }
    node *insert(node *n, string keyword, string meaning);
    void search(node *n, string keyword);
    node *remove(node *n, string keyword);
    node *update(node *n, string keyword);
    void displayAscendingOrder(node *n);
    void displayDescendingOrder(node *n);
};

node *Dictionary::getSucc(node *n)
{
    node *current = n->right;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

int Dictionary ::getHeight(node *n)
{

    if (n == NULL)
    {
        return 0;
    }

    return n->height;
}

int Dictionary ::getBalanceFactor(node *n)
{
    if (n == NULL)
    {
        return 0;
    }

    return getHeight(n->left) - getHeight(n->right);
}
node *Dictionary::RightRotate(node *x)
{
    node *y = x->left;
    x->left = y->right;
    y->right = x;

    // update height
    // Note - after rotation x is right child of y so we have to update height of x first
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

node *Dictionary ::LeftRotate(node *y)
{
    node *x = y->right;
    y->right = x->left;
    x->left = y;

    // update height
    // Note - after rotation y is left child of x so we have to update height of y first
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(y->right)) + 1;

    return x;
}

node *Dictionary ::insert(node *n, string keyword, string meaning)
{
    if (n == NULL)
    {
        n = new node(keyword, meaning);
        cout << "Inserted successfully" << endl;
        return n;
    }

    if (keyword < n->keyword)
    {
        n->left = insert(n->left, keyword, meaning);
    }
    else if (keyword > n->keyword)
    {
        n->right = insert(n->right, keyword, meaning);
    }
    else
    {
        cout << keyword << " is already present in Dictionary." << endl;
        return n;
    }

    n->height = max(getHeight(n->left), getHeight(n->right)) + 1;
    int bf = getBalanceFactor(n);
    // lef-left insertion -> right rotate
    if (bf > 1 && keyword < n->left->keyword)
    {
        return RightRotate(n);
    }

    // left-right insertion -> left rotate then right rotate
    if (bf > 1 && keyword > n->left->keyword)
    {
        n->left = LeftRotate(n->left);
        return RightRotate(n);
    }

    // right-right insertion -> left rotate
    if (bf < -1 && keyword > n->right->keyword)
    {
        return LeftRotate(n);
    }

    // right-left insertion -> right rotate then left rotate
    if (bf < -1 && keyword < n->right->keyword)
    {
        n->right = RightRotate(n->right);
        return LeftRotate(n);
    }

    return n;
}

void Dictionary::displayAscendingOrder(node *n)
{
    if (n != NULL)
    {
        displayAscendingOrder(n->left);
        cout << "bf : " << getBalanceFactor(n) << "\t" << n->keyword << " : " << n->meaning << endl;
        displayAscendingOrder(n->right);
    }
}

void Dictionary::displayDescendingOrder(node *n)
{
    if (n != NULL)
    {
        displayDescendingOrder(n->right);
        cout << "bf : " << getBalanceFactor(n) << "\t" << n->keyword << " : " << n->meaning << endl;
        displayDescendingOrder(n->left);
    }
}

void Dictionary::search(node *n, string keyword)
{
    if (n == NULL)
    {
        cout << keyword << " is not present in dictionary." << endl;
        return;
    }

    if (keyword < n->keyword)
    {
        search(n->left, keyword);
    }
    else if (keyword > n->keyword)
    {
        search(n->right, keyword);
    }
    else
    {
        cout << n->keyword << " : " << n->meaning << endl;
    }

    return;
}

node *Dictionary::update(node *n, string keyword)
{
    if (n == NULL)
    {
        cout << keyword << " is not present in dictionary." << endl;
        return NULL;
    }

    if (keyword < n->keyword)
    {
        n->left = update(n->left, keyword);
        return n;
    }
    else if (keyword > n->keyword)
    {
        n->right = update(n->right, keyword);
        return n;
    }
    else
    {
        string updatedMeaning;
        cout << "Enter new meaning : ";
        getline(cin, updatedMeaning);
        n->meaning = updatedMeaning;
        cout << "updated successfully" << endl;
        return n;
    }

    return n;
}

node *Dictionary ::remove(node *n, string keyword)
{
    if (n == NULL)
    {
        cout << keyword << " not present in dictionary." << endl;
        return n;
    }

    if (keyword < n->keyword)
    {
        n->left = remove(n->left, keyword);
    }
    else if (keyword > n->keyword)
    {
        n->right = remove(n->right, keyword);
    }
    else
    {
        cout << "Deleted successfully" << endl;
        if (n->left == NULL && n->right == NULL)
        {
            delete n;
            return NULL;
        }
        else if (n->right == NULL)
        {
            node *temp = n;
            n = n->left;
            delete temp;
            return n;
        }
        else if (n->left == NULL)
        {
            node *temp = n;
            n = n->right;
            delete temp;
            return n;
        }
        else
        {
            node *temp = getSucc(n);
            n->keyword = temp->keyword;
            n->meaning = temp->meaning;
            n->right = remove(n->right, temp->keyword);
            return n;
        }
    }

    if (n == NULL)
    {
        return n;
    }

    n->height = max(getHeight(n->left), getHeight(n->right)) + 1;
    int bf = getBalanceFactor(n);

    // left left case -> right rotate
    if (bf > 1 && getBalanceFactor(n->left) >= 0)
    {
        return RightRotate(n);
    }

    // left right case -> left rotate then right rotate
    if (bf > 1 && getBalanceFactor(n->left) < 0)
    {
        n->left = LeftRotate(n->left);
        return RightRotate(n);
    }

    // right right case -> left rotate
    if (bf < -1 && getBalanceFactor(n->right) <= 0)
    {
        return LeftRotate(n);
    }

    // right left case -> right rotate then left rotate
    if (bf < -1 && getBalanceFactor(n->right) > 0)
    {
        n->right = RightRotate(n->right);
        return LeftRotate(n);
    }
    return n;
}

int main()
{
    int ch;
    Dictionary dic;
    string word, mean;
    cout << "+++----Dictionary ADT using AVL----+++" << endl;
    while (1)
    {
        cout << "____________MENU_____________" << endl
             << "\t1.Insert" << endl
             << "\t2.Search" << endl
             << "\t3.Update" << endl
             << "\t4.Remove" << endl
             << "\t5.Display in ascending order" << endl
             << "\t6.Display in descending order" << endl
             << "\t7.Exit" << endl
             << "Enter your choice : ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            cout << "Enter word : ";
            cin.get();
            getline(cin, word);
            cout << "Enter Meaning : ";
            getline(cin, mean);
            dic.root = dic.insert(dic.root, word, mean);
            break;

        case 2:
            cout << "Enter word : ";
            cin.get();
            getline(cin, word);
            dic.search(dic.root, word);
            break;

        case 3:
            cout << "Enter word : ";
            cin.get();
            getline(cin, word);
            dic.root = dic.update(dic.root, word);
            break;

        case 4:
            cout << "Enter word : ";
            cin.get();
            getline(cin, word);
            dic.root = dic.remove(dic.root, word);
            break;

        case 5:
            if (dic.root == NULL)
            {
                cout << "Dictionary is empty." << endl;
            }
            else
            {
                dic.displayAscendingOrder(dic.root);
            }
            break;

        case 6:
            if (dic.root == NULL)
            {
                cout << "Dictionary is empty." << endl;
            }
            else
            {
                dic.displayDescendingOrder(dic.root);
            }
            break;

        case 7:
            cout << "Thanks" << endl;
            return 0;

        default:
            cout << "Entered wrong choice" << endl;
            break;
        }
    }

    return 0;
}