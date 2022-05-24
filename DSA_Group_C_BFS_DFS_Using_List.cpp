#include <bits/stdc++.h>
using namespace std;

class Graph
{
    int v;                       // no. of vertices
    int e;                       // no. of edges
    vector<vector<int>> adjList; // adjacency list representation of graph
    int src, dist;
    vector<bool> visited;

public:
    Graph()
    {
        v = e = src = dist = 0;
    }

    void create()
    {
        cout << "Enter the number of vertices in graph : ";
        cin >> v;
        adjList.resize(v);
        visited.resize(v, false);

        cout << "Enter the number of edges in graph : ";
        cin >> e;

        for (int i = 0; i < e; i++)
        {
            cout << "Enter source and distination for edge " << i + 1 << " : ";
            cin >> src >> dist;

            // undirecred graph
            adjList[src].push_back(dist);
            adjList[dist].push_back(src);
        }
    }

    void display()
    {
        for (int i = 0; i < v; i++)
        {
            cout << i;
            for (int j : adjList[i])
            {
                cout << " -> " << j;
            }
            cout << endl;
        }
    }

    void BFS(int source)
    {
        queue<int> q;
        q.push(source);

        int vert;

        while (!q.empty())
        {
            vert = q.front();
            q.pop();
            visited[vert] = true;
            cout << vert << " ";
            for (int i : adjList[vert])
            {
                if (visited[i] == false)
                {
                    q.push(i);
                    visited[i] = true;
                }
            }
        }
    }

    void DFS(int source)
    {
        cout << source << " ";
        visited[source] = true;
        for (int i : adjList[source])
        {
            if (visited[i] == false)
            {
                DFS(i);
            }
        }
    }

    void clearVisited()
    {
        for (int i = 0; i < v; i++)
        {
            visited[i] = false;
        }
    }
};

int main()
{
    int ch;
    int n, src;
    Graph g;
    cout << "***** Graph representaion using adjacency list & BFS, DFS *****" << endl
         << endl;
    while (1)
    {
        cout << "____________MENU_____________" << endl
             << "\t1.Create Graph" << endl
             << "\t2.Display Graph" << endl
             << "\t3.BFS" << endl
             << "\t4.DFS" << endl
             << "\t5.Exit" << endl
             << "Enter your choice : ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            g.create();
            break;

        case 2:
            g.display();
            break;

        case 3:
            cout << "Enter source for BFS traversal : ";
            cin >> src;
            cout << "BFS traversal of graph : ";
            g.BFS(src);
            cout << endl;
            g.clearVisited();
            break;

        case 4:
            cout << "Enter source for DFS traversal : ";
            cin >> src;
            cout << "DFS traversal of graph : ";
            g.DFS(src);
            cout << endl;
            g.clearVisited();
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