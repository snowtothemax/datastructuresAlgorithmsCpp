#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>

#define MAX_GRAPH_VERTICES 100
#define MAX_NODE_VERTICES 10
#define ARR_CAPACITY 100

/// @brief Declaration of the Node Class, later implemented
class Node;

/// @brief Utility to double an arrays size
/// @tparam T The type of element in the array
/// @param arr The array to double
/// @param size The size of an array
/// @return A pointer to an array that is double the input size of type T
template <typename T>
T *douleArraySize(T *arr, int size)
{
    T *newArr = new T[size * 2];
    for (int i = 0; i < size; i++)
    {
        newArr[i] = arr[i];
    }
}

/// @brief A class declaration of a Queue that will be used in implementation of BFS
/// @tparam T The type of element in the queue
template <typename T>
class Queue
{
private:
    /// @brief Head element index
    int head;
    /// @brief Tail element index
    int tail;
    /// @brief Capacity of the queue
    int capacity;
    /// @brief The array to use in the queue
    T **arr;

public:
    /// @brief Constructor
    Queue();
    /// @brief Push a value to the end of the queue
    /// @param val The value to add
    void push(T *val);
    /// @brief Pop a value from the front of the queue
    /// @return A pointer to that value
    T *pop();
    /// @brief Whether or not the queue is empty
    /// @return True if the queue is empty, false otherwise
    bool isEmpty();
};

/// @brief An edge in a graph
class Edge
{
public:
    /// @brief The node this goes from
    Node *from;

    /// @brief The node this edge goes to
    Node *to;

    /// @brief Constructor
    Edge()
    {
        from = nullptr;
        to = nullptr;
    }

    /// @brief Constructor
    /// @param fromNode The from node to initialize
    /// @param toNode The to node to initialize
    Edge(Node *fromNode, Node *toNode)
    {
        from = fromNode;
        to = toNode;
    }

    /// @brief Checks if this node is equivalent by checking node values of the input values
    /// @param val1 The first val to check
    /// @param val2 The second val to check
    /// @return True if equal
    bool equals(int val1, int val2);

    /// @brief Checks if the edge contains the former node, and returns the latter (other)
    /// @param former The node to check for
    /// @param latter The node to get out
    /// @return true if the edge contains the former node
    bool containsNode(Node *former, Node *latter);

    /// @brief 
    /// @param val 
    /// @param out 
    /// @return 
    bool containsValue(int val, Node *out);
};

/// @brief A node in a graph
class Node
{
public:
    /// @brief The data in the node
    int val;

    /// @brief The list of edges
    Edge **edges;
    /// @brief The number of edges
    int numEdges;

    /// @brief Constructor
    /// @param value The value to store in the node
    Node(int value)
    {
        val = value;
        numEdges = 0;
        edges = new Edge *[MAX_NODE_VERTICES];
    }

    /// @brief Constructor
    Node()
    {
        Node(-1);
    }

    /// @brief
    /// @param to
    void addEdge(Node *to);

    /// @brief
    /// @param edge The edge to add
    void addEdge(Edge *edge);

    /// @brief
    /// @return
    bool hasNoNeighbors();

    /// @brief Takes advantage of the call stack to perform DFS recursively
    /// @param valToFind
    /// @return
    Node *findNodeDfs(int valToFind);

    /// @brief 
    /// @param valToFind 
    /// @param nodesToVisit 
    /// @param visitedNodes 
    /// @return 
    Node *findNodeBfs(int valToFind, Queue<Node *> *nodesToVisit, std::vector<Node *> visitedNodes);
};

/// @brief
/// @param fromVal
/// @param toVal
/// @param edges
/// @param size
/// @return
bool edgeExists(int fromVal, int toVal, Edge **edges, int size)
{
    for (int i = 0; i < size; i++)
    {
        Edge *edge = edges[i];
        if (edge->equals(fromVal, toVal))
        {
            return true;
        }
    }
    return false;
}

/// @brief
/// @param nodes
/// @param val
/// @param size
/// @return
Node *valExists(Node **nodes, int val, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (nodes[i]->val == val)
        {
            return nodes[i];
        }
    }
    return nullptr;
}
/// @brief
/// @param node
/// @param nodes
/// @return
bool nodeExists(Node *node, std::vector<Node *> nodes)
{
    for (auto it = nodes.begin(); it != nodes.end(); ++it)
    {
        if (*it == node)
        {
            return true;
            ;
        }
    }
    return false;
}

enum SearchMethod
{
    DFS = 1,
    BFS = 2
};

/// @brief
class Graph
{
private:
    /// @brief
    int numEdges;

    Node *dfs(int val)
    {
        Node *first = nodes[0];
        return first->findNodeDfs(val);
    }

    Node *bfs(int val)
    {
        Queue<Node> *queue = new Queue<Node>();
        queue->push(nodes[0]);
        std::vector<Edge *> *visitedEdges = new std::vector<Edge *>();

        while (!queue->isEmpty())
        {
            Node *node = queue->pop();

            if (node->val == val)
            {
                return node;
            }

            for (int i = 0; i < node->numEdges; i++)
            {
                if (std::find(visitedEdges->begin(), visitedEdges->end(), node->edges[i]) == visitedEdges->end())
                {
                    queue->push(node->edges[i]->to);
                    visitedEdges->push_back(node->edges[i]);
                }
            }
        }
        return nullptr;
    }

public:
    /// @brief
    Edge **edges;

    /// @brief
    Node **nodes;

    /// @brief
    int numNodes;

    /// @brief
    Graph()
    {
        numEdges = 0;
        numNodes = 0;
        edges = new Edge *[MAX_GRAPH_VERTICES]();
        nodes = new Node *[2 * MAX_GRAPH_VERTICES]();
    }

    /// @brief
    /// @param fromVal
    /// @param toVal
    void addEdge(int fromVal, int toVal)
    {
        if (!edgeExists(fromVal, toVal, edges, numEdges))
        {
            Node *from = valExists(nodes, fromVal, numNodes);
            if (!from)
            {
                from = new Node(fromVal);
                nodes[numNodes] = from;
                numNodes++;
            }
            Node *to = valExists(nodes, toVal, numNodes);
            if (!to)
            {
                to = new Node(toVal);
                nodes[numNodes] = to;
                numNodes++;
            }
            Edge *edge = new Edge(from, to);
            from->addEdge(to);
            to->addEdge(from);
            edges[numEdges] = edge;
            numEdges++;
        }
    }

    /// @brief
    /// @param val
    /// @return
    Node *findNode(int val, SearchMethod method)
    {
        if (isEmpty())
        {
            return nullptr;
        }

        if (method == DFS)
        {
            return dfs(val);
        }
        // BFS
        else
        {
            return bfs(val);
        }
    }

    bool isEmpty()
    {
        return numNodes == 0;
    }
};

#pragma region Implementations

#pragma region Node
void Node::addEdge(Node *to)
{
    if (!edgeExists(val, to->val, edges, numEdges))
    {
        Edge *edge = new Edge(this, to);
        edges[numEdges] = edge;
        numEdges++;
    }
}
void Node::addEdge(Edge *edge)
{
    if (!edgeExists(val, edge->to->val, edges, numEdges))
    {
        edges[numEdges] = edge;
        numEdges++;
    }
}
bool Node::hasNoNeighbors()
{
    return numEdges == 0;
}

/// @brief Takes advantage of the call stack to perform DFS recursively
/// @param valToFind
/// @return
Node *Node::findNodeDfs(int valToFind)
{
    if (val == valToFind)
    {
        return this;
    }
    if (hasNoNeighbors())
    {
        return nullptr;
    }
    Node *foundNode = nullptr;
    for (int i = 0; i < numEdges; i++)
    {
        Edge *edge = edges[i];
        Node *otherNode = edge->to;
        foundNode = otherNode->findNodeDfs(valToFind);
        if (foundNode)
        {
            return foundNode;
        }
    }
    return nullptr;
}
#pragma endregion Node

#pragma region Edge
/// @brief
/// @param val1
/// @param val2
/// @return
bool Edge::equals(int val1, int val2)
{
    return ((from->val == val1 && to->val == val2) || (from->val == val2 && to->val == val1));
}

/// @brief
/// @param former
/// @param latter
/// @return
bool Edge::containsNode(Node *former, Node *latter)
{
    if (!former || !latter)
    {
        return false;
    }
    if (to == former)
    {
        latter = from;
        return true;
    }
    if (from == former)
    {
        latter = to;
        return true;
    }

    return false;
}

/// @brief
/// @param val
/// @param out
/// @return
bool Edge::containsValue(int val, Node *out)
{
    if (to->val == val)
    {
        out = to;
        return true;
    }
    if (from->val == val)
    {
        out = from;
        return true;
    }
    return false;
}
#pragma endregion Edge

#pragma region Queue
template <typename T>
Queue<T>::Queue()
{
    head = 0;
    tail = 0;
    capacity = 0;
    arr = new T *[ARR_CAPACITY]();
}

template <typename T>
void Queue<T>::push(T *val)
{
    if (capacity < ARR_CAPACITY)
    {
        arr[head] = val;
        capacity++;
        head++;
        head = head % ARR_CAPACITY;
    }
}

template <typename T>
T *Queue<T>::pop()
{
    if (capacity > 0)
    {
        T *retval = arr[tail];
        tail++;
        capacity--;
        tail = tail % ARR_CAPACITY;
        return retval;
    }
    else
        return nullptr;
}

template <typename T>
bool Queue<T>::isEmpty()
{
    return capacity == 0;
}
#pragma endregion Queue

#pragma endregion

int main()
{
    Graph *graph = new Graph();
    graph->addEdge(1, 2);

    std::cout << graph->numNodes << "\n";

    Node *node = nullptr;

    node = graph->findNode(2, DFS);

    if (!node)
    {
        std::cout << "Not found! \n";
    }
    std::cout << node->val << "\n";

    node = graph->findNode(2, BFS);
    if (!node)
    {
        std::cout << "Not found! \n";
    }
    std::cout << node->val << "\n";
}
