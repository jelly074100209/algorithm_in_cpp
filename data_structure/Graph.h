#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

#define DefaultVertexes 30
#define maxWeight 9999999

int visited[DefaultVertexes];

template<class T>
class Graph
{
public:
    Graph(int sz = DefaultVertexes);
    ~Graph()
    {
        delete[] vexs;
        delete[] arcs;
    }

    void CreateGraph();
    void PrintGraph();
    bool InsertVex(const T &vex);
    bool InsertEdge(const T &fromVex, const T &endVex, int weight);
    bool RemoveVex(const T &vex);
    bool RemoveEdge(const T & fromVex, const T &endVex);
    bool IsGraphFull()
    {
        if (numVexes == maxVexes || numArcs == numVexes*(numVexes - 1) / 2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool IsGraphEmpty()
    {
        if (numVexes == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int GetLocation(const T &vex)
    {
        int i = 0;
        for (i = 0; i < numVexes; i++)
        {
            if (vex == vexs[i])
            {
                return i;
            }
        }
        return -1;
    }

    T GetValue(int pos)
    {
        if (pos >= 0 && pos < numVexes)
        {
            return vexs[pos];
        }
        return -1;
    }

private:
    T *vexs;
    int **arcs;
    int maxVexes;//最大顶点数
    int numVexes;//顶点数
    int numArcs;//边数
};

template<class T>
bool Graph<T>::InsertVex(const T &vex)
{
    if (IsGraphFull())
    {
        return false;
    }
    vexs[numVexes++] = vex;
    return true;
}

template<class T>
bool Graph<T>::InsertEdge(const T &fromVex, const T &endVex, int cost)
{
    if (IsGraphFull())
    {
        return false;
    }
    int row = GetLocation(fromVex), col = GetLocation(endVex);
    if (row == -1 || col == -1)
    {
        cout << "Failure" << endl;
        return false;
    }
    if (arcs[row][col] < maxWeight)
    {
        arcs[row][col] = arcs[col][row] = cost;
    }
    return true;
}

template<class T>
bool Graph<T>::RemoveVex(const T &vex)
{
    if (IsGraphEmpty())
    {
        return false;
    }
    int pos = GetLocation(vex);
    if (post == -1)
    {
        return false;
    }
    vexs[pos] = vexs[numVexes - 1];
    int i = 0;
    for (i = 0; i < numVexes; i++)
    {
        arcs[pos][i] = arcs[numVexes - 1][i];
    }
    for (i = 0; i < numVexes - 1; i++)
    {
        arcs[i][pos] = arcs[i][numVexes - 1];
    }
    numVexes--;
}

template<class T>
bool Graph<T>::RemoveEdge(const T &fromVex, const T &endVex)
{
    int from = GetLocation(fromVex), end = GetLocation(endVex);
    if (end == -1 || from == -1)
    {
        return false;
    }
    arcs[from][end] = arcs[end][from] = maxWeight;
    return true;
}

template<class T>
Graph<T>::Graph(int sz)
{
    maxVexes = sz;
    numVexes = 0;
    numArcs = 0;
    int i, j;
    vexs = new T[sz];
    arcs = new int*[sz];
    for (i = 0; i < maxVexes; i++)
    {
        arcs[i] = new int[maxVexes];
    }
    for (i = 0; i < maxVexes; i++)
    {
        for (j = i; j < maxVexes; j++)
        {
            if (i == j)
            {
                arcs[i][j] = 0;
                continue;
            }
            arcs[i][j] = arcs[j][i] = maxWeight;
        }
    }
}

template<class T>
void Graph<T>::CreateGraph()
{
    T fromVex, endVex;
    //int weight, n, e;
    //cout << "Please input the number of the vertexes and the edges: " << endl;
    //cin >> n >> e;
    numVexes = 6;
    numArcs = 9;
    //cout << "Please input the vertexes in the graph:" << endl;
    int i = 0;
    for (i = 0; i < numVexes; i++)
    {
        //cin >> vexs[i];
        vexs[i] = i;
    }
    //cout << "Please input the edges: " << endl;
    int data[6][6] = {
        { maxWeight,6,3,maxWeight,maxWeight,maxWeight },
        {6,maxWeight,2,5,maxWeight,maxWeight },
        {3,2,maxWeight,3,4,maxWeight},
        { maxWeight,5,3,maxWeight,2,maxWeight },
        { maxWeight,maxWeight,4,2,maxWeight,5},
        { maxWeight,maxWeight,maxWeight,3,5,maxWeight }
    };
    for (i = 0; i < numVexes; i++)
    {
        //cin >> fromVex >> endVex >> weight;
        for (int j = 0; j < numVexes; j++)
        {
            arcs[i][j] = data[i][j];
            cout << data[i][j] << "\t";
        }
        cout << endl;
        //arcs[GetLocation(fromVex)][GetLocation(endVex)] = arcs[GetLocation(endVex)][GetLocation(fromVex)] = weight;
    }
}

template<class T>
void Graph<T>::PrintGraph()
{
    cout << "The vertexes: " << endl;
    int i = 0, n = numVexes, e = numArcs;
    for (i = 0; i < n; i++)
    {
        cout << vexs[i] << "";
    }
    cout << endl;
    int j = 0;
    for (i = 0; i < n; i++)
    {
        cout << GetValue(i) << "\t:\t";
        for (j = 0; j < n; j++)
        {
            if (arcs[i][j] > 0 && arcs[i][j] < maxWeight)
            {
                cout << "(" << GetValue(j) << " , " << arcs[i][j] << ")\t";
            }
        }
        cout << endl;
    }
}

#endif