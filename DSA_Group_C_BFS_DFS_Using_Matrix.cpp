#include <bits/stdc++.h>
using namespace std;

// class to create graph using adjacency matrix
class Graph
{
    int n;                         // no. of vertices in graph
    int e;                         // no. of edges
    int src, dist;                 // source and distination for edge
    vector<vector<int>> adjMatrix; // adjacency matrix for graph representation
    vector<bool> visited;          // visited vector for DFS

public:
    Graph()
    {
        n = 0;
        e = 0;
        src = dist = 0;
    }

    void create()
    {
        cout << "Enter the number of vertices in graph : ";
        cin >> n;

        adjMatrix.resize(n);      // resizing rows adjacency matrix
        visited.resize(n, false); // resizing visited vector
        for (int i = 0; i < n; i++)
        {
            // resizing columns in adjacency matrix and intializing with zero
            adjMatrix[i].resize(n, 0);
        }

        cout << "Enter the number of Edges in graph : ";
        cin >> e;

        for (int i = 0; i < e; i++)
        {
            cout << "Enter source and distination for edge " << i + 1 << " : ";
            cin >> src >> dist;

            // undirected graph
            adjMatrix[src][dist] = 1; // connecting edge in adjacency matrix
            adjMatrix[dist][src] = 1; // connecting edge in adjacency matrix
        }
    }

    void display()
    {
        cout << "The adjacency matrix representaion of given graph :" << endl;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << " " << adjMatrix[i][j];
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
            cout << vert << " ";
            visited[vert] = true;

            for (int i = 0; i < n; i++)
            {
                if (adjMatrix[vert][i] != 0 && visited[i] == false)
                {
                    q.push(i);
                    visited[i] = true;
                }
            }
        }
    }

    void DFS(int source)
    {
        cout << source << " ";  // print the vertex
        visited[source] = true; // mark the vertex as visited

        // relaxing the adjacent vertices
        for (int i = 0; i < n; i++)
        {
            if (adjMatrix[source][i] != 0 && visited[i] == false)
            {
                DFS(i);
            }
        }
    }

    void clearVisited()
    {
        for (int i = 0; i < n; i++)
        {
            visited[i] = false;
        }
    }
};

int main()
{
    int ch;
    Graph g;
    int src;
    cout << "\n*****  Graph Creation,BFS and DFS Using Matrix *****" << endl
         << endl;
    while (1)
    {

        cout << "______________MENU______________" << endl
             << "\t1. Create Graph" << endl
             << "\t2. Display Matrix" << endl
             << "\t3. BFS" << endl
             << "\t4. DFS" << endl
             << "\t5. Exit" << endl
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
            cout << "Enter source vertex for BFS : ";
            cin >> src;
            cout << "The BFS traversal of graph : ";
            g.BFS(src);
            cout << endl;
            g.clearVisited();
            break;
        case 4:
            cout << "Enter source vertex for DFS : ";
            cin >> src;
            cout << "The DFS traversal of graph : ";
            g.DFS(src);
            cout << endl;
            g.clearVisited();
            break;
        case 5:
            cout << "Thanks" << endl;
            return 0;
            break;

        default:
            cout << "Entered wrong choice" << endl;
            break;
        }
    }

    return 0;
}