#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 10

struct node
{
    int key; // to store the index
    string keyword;
    string meaning;
    int nextIdx; // to point next index in chain;

    node(int key, string keyword, string meaning)
    {
        this->key = key;
        this->keyword = keyword;
        this->meaning = meaning;
        nextIdx = -1;
    }
};

class Hash
{
    int getKey(string keyword);
    int HashFunction(int key);
    node *HashTable[MAX_SIZE];
    int current_size;

public:
    Hash()
    {
        current_size = 0;
        for (int i = 0; i < MAX_SIZE; i++)
        {
            HashTable[i] = NULL;
        }
    }

    void insert(string keyword, string meaning);
    void find(string keyword);
    void remove(string keyword);
    void display();
};

int Hash::getKey(string keyword)
{
    int key = 0;

    for (int i = 0; i < keyword.length(); i++)
    {
        key += (int)(keyword[i]);
    }
    return key;
}

int Hash::HashFunction(int key)
{
    return key % MAX_SIZE;
}

void Hash ::insert(string keyword, string meaning)
{
    if (current_size == MAX_SIZE)
    {
        cout << "Overflow" << endl;
        return;
    }

    int key = getKey(keyword);
    int idx = HashFunction(key);
    int prevIdx = idx;
    bool flag = false; // true if find starting of chain

    // find the starting of chain
    for (int i = 0; i < MAX_SIZE; i++)
    {

        if (HashTable[idx] != NULL)
        {
            if (HashFunction(HashTable[idx]->key) == HashFunction(key))
            {
                flag = true;
                break;
            }
        }

        idx = HashFunction(idx + 1);
    }

    // if we can't find the starting of chain
    if (!flag)
    {
        while (HashTable[idx] != NULL)
        {
            idx = HashFunction(idx + 1);
        }
    }

    if (HashTable[idx] != NULL)
    {
        if (HashTable[idx]->keyword == keyword)
        {
            cout << keyword << " is already present in dictionary" << endl;
            return;
        }
        // go to end of chain
        while (HashTable[idx]->nextIdx != -1)
        {
            if (HashTable[idx]->keyword == keyword)
            {
                cout << keyword << " is already present in dictionary" << endl;
                return;
            }

            idx = HashTable[idx]->nextIdx;
            prevIdx = idx;
        }

        if (HashTable[idx]->keyword == keyword)
        {
            cout << keyword << " is already present in dictionary" << endl;
            return;
        }

        // go to empty space after the end of chain
        while (HashTable[idx] != NULL)
        {
            idx = HashFunction(idx + 1);
        }

        HashTable[prevIdx]->nextIdx = idx;
        HashTable[idx] = new node(key, keyword, meaning);
        current_size++;
        cout << "inserted successfully" << endl;
    }
    else
    {
        HashTable[idx] = new node(key, keyword, meaning);
        current_size++;
        cout << "inserted successfully." << endl;
    }

    return;
}

void Hash::find(string keyword)
{
    int key = getKey(keyword);
    int idx = HashFunction(key);
    bool flag = false;

    for (int i = 0; i < MAX_SIZE; i++)
    {

        if (HashTable[idx] != NULL)
        {
            if (HashFunction(HashTable[idx]->key) == HashFunction(key))
            {
                flag = true;
                break;
            }
        }

        idx = HashFunction(idx + 1);
    }

    // if we can't find starting of chain
    if (!flag)
    {
        cout << keyword << " not present in dictionary." << endl;
        return;
    }

    // for first element in chain
    if (HashTable[idx]->keyword == keyword)
    {
        cout << HashTable[idx]->keyword << " : " << HashTable[idx]->meaning << endl;
        return;
    }

    // traverse through chain
    while (HashTable[idx]->nextIdx != -1)
    {
        if (HashTable[idx]->keyword == keyword)
        {
            cout << HashTable[idx]->keyword << " : " << HashTable[idx]->meaning << endl;
            return;
        }
        idx = HashTable[idx]->nextIdx;
    }

    // for last element in chain
    if (HashTable[idx]->keyword == keyword)
    {
        cout << HashTable[idx]->keyword << " : " << HashTable[idx]->meaning << endl;
    }
    else
    {
        cout << keyword << " not present in dictionary." << endl;
    }
    return;
}

void Hash::remove(string keyword)
{
    if (current_size == 0)
    {
        cout << "underflow" << endl;
        return;
    }
    int key = getKey(keyword);
    int idx = HashFunction(key);
    int prevIdx = idx;
    bool flag = false;

    // find the strating of chain
    for (int i = 0; i < MAX_SIZE; i++)
    {

        if (HashTable[idx] != NULL)
        {
            if (HashFunction(HashTable[idx]->key) == HashFunction(key))
            {
                flag = true;
                break;
            }
        }

        idx = HashFunction(idx + 1);
    }

    // if we can't find starting of chain
    if (!flag)
    {
        cout << keyword << " not present in dictionary." << endl;
        return;
    }

    // for first element in chain
    if (HashTable[idx]->keyword == keyword)
    {
        delete HashTable[idx];
        HashTable[idx] = NULL;
        current_size--;
        cout << "Deleted successfully." << endl;
        return;
    }

    // traverse though chain

    while (HashTable[idx]->nextIdx != -1)
    {
        if (HashTable[idx]->keyword == keyword)
        {
            HashTable[prevIdx]->nextIdx = HashTable[idx]->nextIdx;
            delete HashTable[idx];
            HashTable[idx] = NULL;
            current_size--;
            cout << "Deleted successfully." << endl;
            return;
        }
        prevIdx = idx;
        idx = HashTable[idx]->nextIdx;
    }

    // checking for last element of chain
    if (HashTable[idx]->keyword == keyword)
    {
        HashTable[prevIdx]->nextIdx = HashTable[idx]->nextIdx;
        delete HashTable[idx];
        HashTable[idx] = NULL;
        current_size--;
        cout << "Deleted successfully." << endl;
    }
    else
    {
        cout << keyword << " not present in dictionary." << endl;
    }
    return;
}

void Hash::display()
{
    cout << "key\tkeyword\t\tmeaning\t\tnextIdx" << endl;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (HashTable[i] == NULL)
        {
            cout << "---------------------EMPTY---------------------" << endl;
        }
        else
        {
            cout << HashTable[i]->key << setw(10) << HashTable[i]->keyword << setw(20) << HashTable[i]->meaning << setw(10) << HashTable[i]->nextIdx << endl;
        }
    }
}

int main()
{
    Hash h1;
    string keyword;
    string meaning;
    int ch;
    int n;

    cout << "+++----Dictionary ADT using Hashing----+++" << endl;
    while (1)
    {
        cout << "___________MENU____________" << endl
             << "\t1.Insert" << endl
             << "\t2.Find" << endl
             << "\t3.Remove" << endl
             << "\t4.Display" << endl
             << "\t5.Exit" << endl
             << "Enter your choice : ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "Enter number of words you wan't to insert : ";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                cout << "Enter word " << i + 1 << " : ";
                cin >> keyword;
                cout << "Enter meaning  : ";
                cin.get();
                getline(cin, meaning);
                h1.insert(keyword, meaning);
            }
            break;
        case 2:
            cout << "Enter the word : ";
            cin >> keyword;
            h1.find(keyword);
            break;
        case 3:
            cout << "Enter the word : ";
            cin >> keyword;
            h1.remove(keyword);
            break;
        case 4:
            h1.display();
            break;
        case 5:
            cout << "Thanks" << endl;
            return 0;

        default:
            cout << "Entered wrong choice" << endl;
            break;
        }
    }
    return 0;
}