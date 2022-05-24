#include <bits/stdc++.h>
using namespace std;

const int TABLE_SIZE = 5;

class data
{

public:
    int ID;
    string number;
    data() // this default constructor is required while creating array of objects
    {
        ID = -1;
        number = "";
    }

    data(int ID, string number)
    {
        this->ID = ID;
        this->number = number;
    }
};

class TelephoneBook
{
    int current_size;
    data **HashTable;
    int hashFunc(int ID);

public:
    TelephoneBook()
    {
        // array of pointers
        HashTable = new data *[TABLE_SIZE];
        current_size = 0;

        for (int i = 0; i < TABLE_SIZE; i++)
        {
            HashTable[i] = NULL;
        }
    }

    void insert(int ID, string number);
    void remove(int ID);
    void search(int ID);
    void display();

    // distructor to free the allocated memory
    ~TelephoneBook()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            if (HashTable[i] != NULL)
            {
                delete[] HashTable[i];
            }

            delete[] HashTable;
        }
    }
};

int TelephoneBook ::hashFunc(int ID)
{
    return ID % TABLE_SIZE;
}

void TelephoneBook ::insert(int ID, string number)
{
    if (current_size == TABLE_SIZE)
    {
        cout << "Overflow" << endl;
        return;
    }

    int idx = hashFunc(ID);
    int prob_count = 0;
    while (HashTable[idx] != NULL && prob_count != TABLE_SIZE)
    {
        prob_count++;
        idx = hashFunc(idx + 1);
    }

    if (HashTable[idx] == NULL)
    {
        current_size++;
        HashTable[idx] = new data(ID, number);
        cout << "Data inserted successfully" << endl;
    }
    return;
}

void TelephoneBook ::search(int ID)
{
    if (current_size == 0)
    {
        cout << "no data exist currently" << endl;
        return;
    }

    int prob_count = 0;
    int idx = hashFunc(ID);
    while (HashTable[idx] != NULL && HashTable[idx]->ID != ID && prob_count < TABLE_SIZE)
    {
        prob_count++;
        idx = hashFunc(idx + 1);
    }

    if (HashTable[idx] == NULL || HashTable[idx]->ID != ID)
    {
        cout << "No data exist for ID " << ID << endl;
    }
    else
    {
        cout << "Value at ID " << ID << " : " << HashTable[idx]->number << endl;
    }
}

void TelephoneBook ::remove(int ID)
{

    if (current_size == 0)
    {
        cout << "Underflow" << endl;
        return;
    }
    int prob_count = 0;

    int idx = hashFunc(ID);

    while (prob_count <= TABLE_SIZE)
    {
        if (HashTable[idx] != NULL)
        {
            if (HashTable[idx]->ID == ID)
            {
                break;
            }
        }
        prob_count++;
        idx = hashFunc(idx + 1);
    }

    if (HashTable[idx] == NULL || HashTable[idx]->ID != ID)
    {
        cout << "No data exist for ID " << ID << endl;
    }
    else
    {
        delete HashTable[idx];
        HashTable[idx] = NULL;
        current_size--;
        cout << "Data deleted successfully" << endl;
    }
}

void TelephoneBook ::display()
{

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (HashTable[i] != NULL)
        {
            cout << setw(3) << i << ". " << HashTable[i]->ID << " : " << HashTable[i]->number << endl;
        }
        else
        {
            cout << setw(3) << i << ". NULL" << endl;
        }
    }
}
int main()
{
    int ID;
    string number;
    int ch;
    TelephoneBook B;

    while (1)
    {
        cout << "_______TELEPHONE BOOK DATABASE_______" << endl
             << "\t1.Insert number" << endl
             << "\t2.Search number" << endl
             << "\t3.Delete number" << endl
             << "\t4.Display Book" << endl
             << "\t5.Exit" << endl
             << "Enter your choice : ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            cout << "Enter the ID at which you want to insert number : ";
            cin >> ID;
            cout << "Enter the phone number : ";
            cin >> number;
            B.insert(ID, number);
            break;

        case 2:
            cout << "Enter the ID for which you want to search data : ";
            cin >> ID;
            B.search(ID);
            break;

        case 3:
            cout << "Enter the ID for which you want to delete data : ";
            cin >> ID;
            B.remove(ID);
            break;

        case 4:
            B.display();
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