/*
Read the marks obtained by students of second year in an online examination of
particular subject. Find out maximum and minimum marks obtained in that subject. Use
heap data structure. Analyze the algorithm.

time complexity -> log(n)-> insertion and deletion
*/

#include <bits/stdc++.h>
using namespace std;

const int capacity = 20;

class MAX_HEAP
{
    int size;
    int arr[capacity];
    void Heapify(int i);

public:
    MAX_HEAP()
    {
        size = 0;
    }

    void insert(int key);
    void pop();
    int top();
};

void MAX_HEAP::Heapify(int i)
{
    // find the maximum element between left child,right child and parent(element at i)
    // and if parent(element at i) is maximum then heap is build else swap parent
    // element with element at max_idx and call Heapify at index max_idx
    int left_idx = 2 * i + 1;
    int right_idx = 2 * i + 2;
    int max_idx = i;

    if (left_idx < size && arr[left_idx] > arr[max_idx])
    {
        max_idx = left_idx;
    }

    if (right_idx < size && arr[right_idx] > arr[max_idx])
    {
        max_idx = right_idx;
    }

    if (max_idx != i)
    {
        swap(arr[max_idx], arr[i]);
        Heapify(max_idx);
    }
}

void MAX_HEAP ::insert(int key)
{
    if (size == capacity)
    {
        cout << "overflow" << endl;
        return;
    }

    arr[size] = key;
    int child_idx = size;
    size++;
    int parent_idx = (child_idx - 1) / 2;

    while (child_idx > 0 && arr[parent_idx] < arr[child_idx])
    {
        swap(arr[parent_idx], arr[child_idx]);
        child_idx = parent_idx;
        parent_idx = (child_idx - 1) / 2;
    }
}

int MAX_HEAP ::top()
{
    if (size == 0)
    {
        cout << "underflow" << endl;
        return -1;
    }
    return arr[0];
}

void MAX_HEAP ::pop()
{
    if (size == 0)
    {
        return;
    }
    arr[0] = arr[size - 1];
    size--;
    Heapify(0);
}

class MIN_HEAP
{
    int size;
    int arr[capacity];
    void Heapify(int i);

public:
    MIN_HEAP()
    {
        size = 0;
    }

    void insert(int key);
    void pop();
    int top();
};

void MIN_HEAP::Heapify(int i)
{
    int left_idx = 2 * i + 1;
    int right_idx = 2 * i + 2;
    int min_idx = i;

    if (left_idx < size && arr[left_idx] > arr[min_idx])
    {
        min_idx = left_idx;
    }

    if (right_idx < size && arr[right_idx] > arr[min_idx])
    {
        min_idx = right_idx;
    }

    if (min_idx != i)
    {
        swap(arr[min_idx], arr[i]);
        Heapify(min_idx);
    }
}

void MIN_HEAP ::insert(int key)
{
    if (size == capacity)
    {
        cout << "overflow" << endl;
        return;
    }

    arr[size] = key;
    int child_idx = size;
    size++;
    int parent_idx = (child_idx - 1) / 2;

    while (child_idx > 0 && arr[parent_idx] > arr[child_idx])
    {
        swap(arr[parent_idx], arr[child_idx]);
        child_idx = parent_idx;
        parent_idx = (child_idx - 1) / 2;
    }
}

int MIN_HEAP ::top()
{
    if (size == 0)
    {
        cout << "underflow" << endl;
        return -1;
    }
    return arr[0];
}

void MIN_HEAP ::pop()
{
    if (size == 0)
    {
        return;
    }
    arr[0] = arr[size - 1];
    size--;
    Heapify(0);
}
int main()
{
    int n;
    int ch;
    MAX_HEAP maxHeap;
    MIN_HEAP minHeap;
    int ele;
    while (1)
    {
        cout << "________________MENU________________" << endl
             << "1.Insert data" << endl
             << "2.Maximum mark" << endl
             << "3.Minimum mark" << endl
             << "4.Exit" << endl
             << "Enter choice : ";
        cin >> n;

        switch (n)
        {
        case 1:
            cout << "Enter number of elements :" << endl;
            cin >> n;

            for (int i = 0; i < n; i++)
            {
                cout << "Enter " << i + 1 << " element : ";
                cin >> ele;
                maxHeap.insert(ele);
                minHeap.insert(ele);
            }
            break;
        case 2:
            cout << "Maximum mark : " << maxHeap.top() << endl;
            break;

        case 3:
            cout << "Minimum mark : " << minHeap.top() << endl;
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