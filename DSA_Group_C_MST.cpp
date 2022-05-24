/*You have a business with several offices; you want to lease phone lines to connect them
up with each other; and the phone company charges different amounts of money to
connect different pairs of cities. You want a set of lines that connects all your offices
with a minimum total cost. Solve the problem by suggesting appropriate data structures. */
#include <bits/stdc++.h>
using namespace std;

class Graph
{
    vector<vector<int>> adjMatrix;
    int v, e, src, dist, wt;
    int minCost;

    // function to return minimum weight vertex from weight vector
    int getMinWeightVertex(vector<bool> &setMST, vector<int> &weight);

public:
    Graph()
    {
        v = e = src = dist = 0;
    }

    Graph(int v)
    {
        this->v = v;
        adjMatrix.resize(v);

        for (int i = 0; i < v; i++)
        {
            adjMatrix[i].resize(v, 0);
        }
    }

    void addEdge(int source, int distination, int weight)
    {
        adjMatrix[source][distination] = weight;
        adjMatrix[distination][source] = weight;
    }

    void create()
    {
        cout << "Enter the number of vertices in graph : ";
        cin >> v;
        adjMatrix.resize(v);

        for (int i = 0; i < v; i++)
        {
            adjMatrix[i].resize(v, 0);
        }

        cout << "Enter the number of edges in graph : ";
        cin >> e;

        for (int i = 0; i < e; i++)
        {
            cout << "Enter source, distination and weight for edge " << i + 1 << " : ";
            cin >> src >> dist >> wt;
            addEdge(src, dist, wt);
        }
    }

    void display()
    {
        for (int i = 0; i < v; i++)
        {
            for (int j = 0; j < v; j++)
            {
                cout << " " << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void primsMST()
    {
        Graph MST(v);
        vector<bool> setMST(v, false);  // show that is vetex is present in MST or not
        vector<int> weight(v, INT_MAX); // store the minimum weight required to reach vertex
        vector<int> parent(v, -1);      // store parent vertex of vertex i
        minCost = 0;
        int vert;

        // we consider source as vertex 0 hence assigned weight for it as zero
        weight[0] = 0;
        // as there is v-1 edges in MST so loop will run for v-1 times
        for (int i = 0; i < v - 1; i++)
        {
            // choice vertex with minimum edge and it should not present in setMST
            vert = getMinWeightVertex(setMST, weight);
            setMST[vert] = true; // include selected vertex in setMST

            // relax the adjacent vertex of source vertex
            for (int j = 0; j < v; j++)
            {
                /*
                    if there edge present between source to j and weight from
                    source to j is less than previous weight at j and j is not
                    included in mst then update weight at j. Make source as new
                    parent of j
                */
                if (adjMatrix[vert][j] > 0 && adjMatrix[vert][j] < weight[j] && setMST[j] == false)
                {
                    weight[j] = adjMatrix[vert][j];
                    parent[j] = vert;
                }
            }
        }

        // loop for adding edge in MST graph and calculating cost of MST
        // we should start from 1 because parent of source is -1 i.e. no parent
        for (int i = 1; i < v; i++)
        {
            MST.addEdge(i, parent[i], weight[i]);
            minCost += weight[i];
        }

        MST.display();
    }

    // function to return minimum cost
    int getMinimumCost()
    {
        return minCost;
    }
};

int Graph ::getMinWeightVertex(vector<bool> &setMST, vector<int> &weight)
{
    int minWeightVertex;     // store vertex with minimum weight from weight
    int minWeight = INT_MAX; // store minimum weight

    for (int i = 0; i < v; i++)
    {
        // if weight to reach at vertex i is less than minWeight and i is not included
        // in MST then update minWeightVertex and minWeight
        if (minWeight > weight[i] && setMST[i] == false)
        {
            minWeightVertex = i;
            minWeight = weight[i];
        }
    }

    return minWeightVertex;
}

int main()
{
    int ch;
    int src, dist;
    int n;
    Graph g;
    cout << "*****   Prim's algorithm for finding MST   *****" << endl
         << endl;
    while (1)
    {
        cout << "______________MENU______________" << endl
             << "\t1.Create" << endl
             << "\t2.Get MST" << endl
             << "\t3.Get minimum cost" << endl
             << "\t4.Exit" << endl
             << "Enter your choice : ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            g.create();
            break;

        case 2:
            g.primsMST();
            break;

        case 3:
            cout << "Cost of MST : " << g.getMinimumCost() << endl;
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