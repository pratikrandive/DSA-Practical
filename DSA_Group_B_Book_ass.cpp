/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>

using namespace std;

struct node
{
  string title;
  int ch;
  node* child;
  
  node()
  {
      child = NULL;
  }
};


class book
{
  node* root;
  
  public :
    book()
    {
        root = NULL;
    }
    
    void InsertData();
    void displayData();
    
};


void book :: InsertData()
{   
    string title;
    int NoOfChapter;
    int NoOfSection;
    cout<<"Enter book title : ";
    cin>>title;
    root = new node;
    root->title = title;
    
    cout<<"Enter no. of chapters : ";
    cin>>NoOfChapter;
    root-> ch = NoOfChapter;
    
    root->child = new node[NoOfChapter];
    
    for(int i =0;i < NoOfChapter;i++)
    {
        cout<<"Enter title of chapter "<<i+1<<" : ";
        cin>>title;
        root->child[i].title = title;
        cout<<"Enter no. of sections in chapter "<<i+1<<" : ";
        cin>>NoOfSection;
        root->child[i].child = new node[NoOfSection];
        root->child[i].ch = NoOfSection;
        for(int j =0;j < NoOfSection;j++ )
        {
            cout<<"Enter title of section "<<j+1<<" :";
            cin>>title;
            root->child[i].child[j].title = title;
        }
    }
}

void book :: displayData()
{
    cout<<"Book title : "<<root->title <<endl;
    cout<<"No of chapters in book : "<<root->ch<<endl;
    
    for(int i = 0;i < root->ch;i++)
    {
        cout<<"Name of Chapter "<<i+1<<" : "<<root->child[i].title<<endl;
        cout<<"No. of sections in chapter "<<i+1<<" : "<<root->child[i].ch <<endl;
        cout<<"Name of sections"<<endl;
        for(int j=0;j < root->child[i].ch;j++)
        {
            cout<<root->child[i].child[j].title<<endl;
        }
    }
}
int main()
{
    book b1;
    int n;
    while(1)
    {
        cout<<"\t1.Create book"<<endl
            <<"\t2.Display book"<<endl
            <<"\t3.Exit"<<endl;
        cout<<"Enter your choice : ";
            cin>>n;
            
        switch(n)
        {
            case 1:
                b1.InsertData();
                break;
            case 2:
                b1.displayData();
                break;
            case 3:
                return 0;
                break;
            default:
                cout<<"Wrong choice"<<endl;
                break;
        }
    }
    
    return 0;
}

