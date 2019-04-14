#include <iostream>
#include <fstream>
#include <queue>
#include <list>
#define INF 99999

using namespace std;

struct Node
{
    int val;
    Node *next;
};

struct Edge
{
    int src, dest;
};

class Graph
{
    int N;
    Node *createNode(int dest, Node *head)
    {
        Node *newNode = new Node;
        newNode->val = dest;

        newNode->next = head;

        return newNode;
    }

    void removeDuplicateNodes(Node *start)
    {
        struct Node *ptr1, *ptr2, *dup;
        ptr1 = start;

        while (ptr1 != NULL && ptr1->next != NULL)
        {
            ptr2 = ptr1;

            while (ptr2->next != NULL)
            {

                if (ptr1->val == ptr2->next->val)
                {

                    dup = ptr2->next;
                    ptr2->next = ptr2->next->next;
                    delete (dup);
                }
                else
                    ptr2 = ptr2->next;
            }
            ptr1 = ptr1->next;
        }
    }

    void copyAdjList(Graph graph);

  public:
    Node **head;

    friend istream &operator>>(istream &, Graph &);
    friend ostream &operator<<(ostream &, Graph &);
    friend Graph operator+(Graph &, Graph &);

    int **generateAdjacencyMatrix();

    void DFSHelper(int v, int visited[], int component);
    void DFSHelper(int v, bool visited[]);
    void DFS(int v);

    void BFS(int s);

    vector<list<int>> connectedComponents();
    void printConnectedComponents();
    bool isConnected();

    void printPathMatrix(int **dist);
    int **generatePathMatrix();
    void pathMatrix();

    Graph()
    {
        this->N = 0;
    }

    ~Graph()
    {
        for (int i = 0; i < N; i++)
            delete[] head[i];

        delete[] head;
    }
};

void Graph::printPathMatrix(int **dist)
{
    cout << "Path Matrix:" << endl
         << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        cout << endl;
        cout << endl;
    }
}

int **Graph::generateAdjacencyMatrix()
{
    int **graph = new int *[N];

    for (int i = 0; i < N; ++i)
        graph[i] = new int[N]();

    for (int i = 0; i < N; i++)
    {
        Node *ptr = this->head[i];
        while (ptr != nullptr)
        {
            graph[i][ptr->val] = 1;
            ptr = ptr->next;
        }
    }

    return graph;
}

int **Graph::generatePathMatrix()
{
    int i, j, k;

    int **dist = new int *[N];
    int **graph = generateAdjacencyMatrix();

    for (int i = 0; i < N; ++i)
        dist[i] = new int[N];

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            dist[i][j] = graph[i][j] == 0 ? INF : 1;

    for (k = 0; k < N; k++)
    {

        for (i = 0; i < N; i++)
        {

            for (j = 0; j < N; j++)
            {

                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    for (int i = 0; i < N; i++)
        delete[] graph[i];
    delete[] graph;

    return dist;
}

void Graph::pathMatrix()
{
    int **pathMatrix = generatePathMatrix();
    printPathMatrix(pathMatrix);
    for (int i = 0; i < N; i++)
        delete[] pathMatrix[i];
    delete[] pathMatrix;
}

void Graph::DFSHelper(int v, bool visited[])
{
    visited[v] = true;
    cout << v << " ";

    Node *ptr = this->head[v];

    while (ptr != nullptr)
    {
        if (!visited[ptr->val])
            DFSHelper(ptr->val, visited);
        ptr = ptr->next;
    }
}

void Graph::DFSHelper(int v, int visited[], int curr_component)
{
    visited[v] = curr_component;

    Node *ptr = this->head[v];

    while (ptr != nullptr)
    {
        if (visited[ptr->val] == 0)
            DFSHelper(ptr->val, visited, curr_component);
        ptr = ptr->next;
    }
}

void Graph::DFS(int v)
{
    bool *visited = new bool[N];
    for (int i = 0; i < N; i++)
        visited[i] = false;

    DFSHelper(v, visited);
}

void Graph::BFS(int v)
{
    bool *visited = new bool[N];
    for (int i = 0; i < N; i++)
        visited[i] = false;

    queue<int> queue;

    visited[v] = true;
    queue.push(v);

    while (!queue.empty())
    {
        v = queue.front();
        cout << v << " ";
        queue.pop();

        Node *ptr = this->head[v];

        while (ptr != nullptr)
        {
            if (!visited[ptr->val])
            {
                visited[ptr->val] = true;
                queue.push(ptr->val);
            }
            ptr = ptr->next;
        }
    }
}

void Graph::copyAdjList(Graph graph)
{

    if (this->head == nullptr)
    {

        this->N = graph.N;
        this->head = new Node *[this->N]();

        for (int i = 0; i < graph.N; i++)
            this->head[i] = nullptr;
    }

    for (int i = 0; i < graph.N; i++)
    {

        Node *ptr = graph.head[i];

        while (ptr != nullptr)
        {

            Node *newNode = createNode(ptr->val, this->head[i]);
            this->head[i] = newNode;
            ptr = ptr->next;
        }
    }
}

Graph operator+(Graph &a, Graph &b)
{
    Graph result;
    result.N = a.N;
    result.head = new Node *[result.N]();

    // initialize head pointer for all vertices
    for (int i = 0; i < result.N; i++)
        result.head[i] = nullptr;

    result.copyAdjList(a);
    result.copyAdjList(b);

    for (int i = 0; i < result.N; i++)
        result.removeDuplicateNodes(result.head[i]);

    return result;
}

istream &operator>>(istream &input, Graph &graph)
{
    int n;

    input >> n;

    graph.head = new Node *[n]();
    graph.N = n;

    for (int i = 0; i < n; i++)
        graph.head[i] = nullptr;

    int src, dest;

    while (input >> src >> dest)
    {
        Node *newNode = graph.createNode(dest, graph.head[src]);
        graph.head[src] = newNode;
        newNode = graph.createNode(src, graph.head[dest]);
        graph.head[dest] = newNode;
    }
    return input;
}

ostream &operator<<(ostream &output, Graph &graph)
{
    cout << graph.N << endl;

    for (int i = 0; i < graph.N; i++)
    {
        Node *ptr = graph.head[i];

        while (ptr != nullptr)
        {
            if (ptr->val > i)
                output << i << " " << ptr->val << endl;

            ptr = ptr->next;
        }
    }

    return output;
}

vector<list<int>> Graph::connectedComponents()
{
    // Mark all the vertices as not visited
    int *visited = new int[N];
    for (int v = 0; v < N; v++)
        visited[v] = 0;

    int k = 0;

    for (int v = 0; v < N; v++)
    {
        if (visited[v] == 0)
        {
            DFSHelper(v, visited, ++k);
        }
    }

    vector<list<int>> components(k);

    for (int i = 0; i < N; i++)
    {
        components[visited[i] - 1].push_back(i);
    }

    return components;
}

void Graph::printConnectedComponents()
{
    vector<list<int>> components = connectedComponents();

    for (auto component : components)
    {
        for (auto nod : component)
        {
            cout << nod << " ";
        }
        cout << endl;
    }
}

bool Graph::isConnected()
{
    if (connectedComponents().size() == 1)
        return true;
    return false;
}

int main()
{
    Graph A, B;

    ifstream in("date.in");
    ifstream in2("date2.in");

    // n
    // src dest
    // ...

    in >> A;
    in2 >> B;

    cout << "Connected components: " << endl
         << endl;
    A.printConnectedComponents();
    cout << endl;
    cout << "Is connected: " << (A.isConnected() ? "true" : "false") << endl
         << endl;
    A.pathMatrix();

    Graph C = A + B;

    cout << C;

    return 0;
}
