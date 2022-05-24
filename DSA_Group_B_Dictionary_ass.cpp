/*
A Dictionary stores keywords and its meanings. Provide facility for adding new
keywords, deleting keywords, updating values of any entry. Provide facility to
display whole data sorted in ascending/ Descending order. Also find how many
maximum comparisons may require for finding any keyword. Use Binary Search Tree
for implementation.
*/

#include <bits/stdc++.h>
using namespace std;

class node
{
public:
    string keyword;
    string meaning;

    node *left;
    node *right;

    node(string keyword, string meaning)
    {
        this->keyword = keyword;
        this->meaning = meaning;
        left = right = NULL;
    }
};

class Dictionary
{
    node *getSucc(node *root);

public:
    node *root;

    Dictionary()
    {
        root = NULL;
    }

    node *insert(node *root, string word, string mean);
    void search(node *root, string keyword);
    node *remove(node *root, string keyword);
    node *update(string keyword);
    void display(node *root);
};

node *Dictionary ::getSucc(node *root)
{
    node *current = root->right;
    while (current->left != NULL)
    {
        current = current->left;
    }

    return current;
}

node *Dictionary ::insert(node *root, string word, string mean)
{
    if (root == NULL)
    {
        root = new node(word, mean);
        return root;
    }

    if (word.compare(root->keyword) < 0)
    {
        root->left = insert(root->left, word, mean);
    }
    else if (word.compare(root->keyword) > 0)
    {
        root->right = insert(root->right, word, mean);
    }
    else
    {
        cout << "\"" << word << "\" is already present in dictionary." << endl;
        return root;
    }

    return root;
}

void Dictionary::search(node *root, string word)
{

    if (root == NULL)
    {
        cout << "\"" << word << "\" not present in dictionary." << endl;
        return;
    }

    if (word.compare(root->keyword) == 0)
    {
        cout << root->keyword << " : " << root->meaning << endl;
    }
    else if (word.compare(root->keyword) == -1)
    {
        search(root->left, word);
    }
    else
    {
        search(root->right, word);
    }
}

node *Dictionary ::update(string keyword)
{
    root = remove(root, keyword);
    string updatedValue;
    cout << "Enter new meaning :";
    cin.get();
    getline(cin, updatedValue);
    root = insert(root, keyword, updatedValue);
    return root;
}

node *Dictionary ::remove(node *root, string word)
{
    if (root == NULL)
    {
        cout << "\"" << word << "\" not present in dictionary." << endl;
        return NULL;
    }

    if (word.compare(root->keyword) == -1)
    {
        root->left = remove(root->left, word);
    }
    else if (word.compare(root->keyword) == 1)
    {
        root->right = remove(root->right, word);
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
            root->keyword = succ->keyword;
            root->meaning = succ->meaning;

            root->right = remove(root->right, succ->keyword);

            return root;
        }

        return root;
    }
    return root;
}

void Dictionary::display(node *root)
{
    if (root != NULL)
    {
        display(root->left);
        cout << root->keyword << " : " << root->meaning << endl;
        display(root->right);
    }
}
int main()
{
    Dictionary dic;
    int ch;
    string keyword, meaning;
    int n;

    while (1)
    {
        cout << "______________MENU____________" << endl
             << "\t1.Create dictionary" << endl
             << "\t2.Adding new keywords" << endl
             << "\t3.Delete keywords" << endl
             << "\t4.Update" << endl
             << "\t5.Display" << endl
             << "\t6.Search" << endl
             << "\t7.Exit" << endl
             << "Enter choice :";
        cin >> n;

        switch (n)
        {
        case 1:
            cout << "Enter keyword : ";
            cin >> keyword;
            cout << "Enter meaning : ";
            cin.get();
            getline(cin, meaning);
            dic.root = dic.insert(dic.root, keyword, meaning);
            break;

        case 2:
            cout << "Enter number of keys you want to insert : ";
            cin >> n;

            for (int i = 0; i < n; i++)
            {
                cout << "Enter keyword : ";
                cin >> keyword;
                cout << "Enter meaning : ";
                cin.get();
                getline(cin, meaning);
                dic.root = dic.insert(dic.root, keyword, meaning);
            }
            break;

        case 3:
            cout << "Enter keyword : ";
            cin >> keyword;
            dic.root = dic.remove(dic.root, keyword);
            break;

        case 4:
            cout << "Enter keyword you want to update :";
            cin >> keyword;
            dic.root = dic.update(keyword);
            break;

        case 5:
            dic.display(dic.root);
            break;

        case 6:
            cout << "Enter keyword you want to search :";
            cin >> keyword;
            dic.search(dic.root, keyword);
            break;

        case 7:
            cout << "Thanks" << endl;
            return 0;
        default:
            cout << "Entered wrong choice." << endl;
            break;
        }
    }

    return 0;
}