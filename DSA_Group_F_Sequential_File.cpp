/*Department maintains a student information. The file contains roll number, name, division
and address. Allow user to add, delete information of student. Display information of
particular employee. If record of student does not exist an appropriate message is displayed.
If it is, then the system displays the student details. Use sequential file to main the data.*/
#include <bits/stdc++.h>
using namespace std;

class Student
{
    char name[20];
    int roll_number;
    char div;
    char address[20];

public:
    Student()
    {
        name[0] = address[0] = '\0';
        roll_number = div = -1;
    }

    void setData()
    {
        cout << "Enter student information" << endl;
        cout << "Name : ";
        cin >> name;
        cout << "Roll Number : ";
        cin >> roll_number;
        cout << "Division : ";
        cin >> div;
        cout << "Address : ";
        cin >> address;
    }

    void getData()
    {
        cout << roll_number << "\t\t   " << div << "\t\t" << name << "\t\t" << address << endl;
    }

    int getRollNo()
    {
        return roll_number;
    }
};

class SequentialFile
{
    char fileName[30];
    ofstream writeToFile;
    ifstream readFromFile;
    Student s;

public:
    void create();
    void addData();
    void display();
    void search(int roll_No);
    void _remove(int roll_No);
    void clear()
    {
        writeToFile.open(fileName, ios ::out);
        writeToFile.close();
    }
};

void SequentialFile ::create()
{
    cout << "Enter the file name (\".txt\" should be there) : ";
    cin >> fileName;
    int n = 0;
    cout << "Enter number of students : ";
    cin >> n;
    writeToFile.open(fileName, ios::app);

    if (writeToFile.is_open())
    {
        for (int i = 0; i < n; i++)
        {
            s.setData();
            writeToFile.write((char *)(&s), sizeof(s));
        }
        writeToFile.close();
    }
    else
    {
        cout << "File opening error" << endl;
    }
}

void SequentialFile ::addData()
{
    writeToFile.open(fileName, ios::app);

    if (writeToFile.is_open())
    {
        s.setData();
        writeToFile.write((char *)(&s), sizeof(s));
    }

    writeToFile.close();
}

void SequentialFile ::display()
{
    readFromFile.open(fileName, ios ::in);

    if (readFromFile.is_open())
    {
        cout << "Roll No.\t Division \t Name \t\tAddress" << endl;

        readFromFile.read((char *)(&s), sizeof(s));
        while (!readFromFile.eof())
        {
            s.getData();
            readFromFile.read((char *)(&s), sizeof(s));
        }

        readFromFile.close();
    }
    else
    {
        cout << "File opening error" << endl;
    }
}

void SequentialFile ::search(int roll_no)
{
    readFromFile.open(fileName, ios ::in);
    bool flag = false;
    if (readFromFile.is_open())
    {
        while (!readFromFile.eof())
        {
            readFromFile.read((char *)(&s), sizeof(s));
            if (s.getRollNo() == roll_no)
            {
                flag = true;
                cout << "Roll No.\t Division \t Name \t\tAddress" << endl;
                s.getData();
                break;
            }
        }

        if (!flag)
        {
            cout << "student information with roll no." << roll_no << " not exist." << endl;
        }
        readFromFile.close();
    }
    else
    {
        cout << "File opening error" << endl;
    }
}

void SequentialFile ::_remove(int roll_no)
{

    readFromFile.open(fileName, ios::in);
    writeToFile.open("temp.txt", ios::out);
    bool flag = false;
    if (readFromFile.is_open() && writeToFile.is_open())
    {
        readFromFile.read((char *)(&s), sizeof(s));

        while (!readFromFile.eof())
        {

            if (s.getRollNo() == roll_no)
            {
                cout << "Data deleted successfully" << endl;
                flag = true;
            }
            else
            {
                writeToFile.write((char *)(&s), sizeof(s));
            }
            readFromFile.read((char *)(&s), sizeof(s));
        }

        if (!flag)
        {
            cout << "student information with roll no." << roll_no << " not exist." << endl;
        }
        readFromFile.close();
        writeToFile.close();
        remove(fileName);
        rename("temp.txt", fileName);
    }
    else
    {
        cout << "File opening error" << endl;
    }
}

int main()
{
    int ch;
    int roll_no;
    SequentialFile sf1;
    cout << "*********    Student data base    **********" << endl;
    while (1)
    {
        cout << "________________MENU_________________" << endl
             << "\t1.Create Database" << endl
             << "\t2.Display Database" << endl
             << "\t3.Add a record" << endl
             << "\t4.Search a record" << endl
             << "\t5.Delete a record" << endl
             << "\t6.Clear Database" << endl
             << "\t7.Exit" << endl
             << "Enter your choice :";
        cin >> ch;

        switch (ch)
        {
        case 1:
            sf1.create();
            break;

        case 2:
            sf1.display();
            break;

        case 3:
            sf1.addData();
            break;

        case 4:
            cout << "Enter roll number of student : ";
            cin >> roll_no;
            sf1.search(roll_no);
            break;

        case 5:
            cout << "Enter roll number of student : ";
            cin >> roll_no;
            sf1._remove(roll_no);
            break;

        case 6:
            sf1.clear();
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