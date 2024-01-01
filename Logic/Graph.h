#ifndef PROJETO_2_GRAPH_H
#define PROJETO_2_GRAPH_H


#include <cstddef>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <limits>
#include "Airline.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


/****************** Provided structures  ********************/
/**
 * @brief Represents a vertex in a graph.
 * @tparam T The type of information stored in the vertex.
 */
template <class T>
class Vertex {
    T info;                // contents
    vector<Edge<T> > adj;  // list of outgoing edges
    bool visited;          // auxiliary field
    bool processing;       // auxiliary field
    int low;               // auxiliary field
    int indegree;          // auxiliary field
    int num;               // auxiliary field
    Vertex<T>* parent;

    void addEdge(Vertex<T> *dest, double w, string airline);
    bool removeEdgeTo(Vertex<T> *d);
public:
    Vertex(T in);
    T getInfo() const;
    void setInfo(T in);
    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);
    const vector<Edge<T>> &getAdj() const;
    void setAdj(const vector<Edge<T>> &adj);
    void setParent(Vertex<T>* parent);

    int getIndegree() const;

    void setIndegree(int indegree);

    int getNum() const;

    void setNum(int num);

    int getLow() const;

    void setLow(int low);

    friend class Graph<T>;

    Vertex<T>* getParent();
};

template<class T>
Vertex<T>* Vertex<T>::getParent() {
    return parent;
}

template<class T>
void Vertex<T>::setParent(Vertex<T>* parent) {
    this->parent = parent;
}

/**
 * @brief Represents an edge in a graph.
 * @tparam T The type of information stored in the vertices.
 */
template <class T>
class Edge {
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight
    string airline;        // airline code
public:
    Edge(Vertex<T> *d, double w,string airline);
    Vertex<T> *getDest() const;
    void setDest(Vertex<T> *dest);
    double getweight() const;
    void setweight(double weight);
    std::string getAirline()const ;
    void setAirline(string airline);
    friend class Graph<T>;
    friend class Vertex<T>;
};

/**
 * @brief Represents a graph using an adjacency list.
 * @tparam T The type of information stored in the vertices.
 */
template <class T>
class Graph {
    vector<Vertex<T> *> vertexSet;  // vertex set
    stack<Vertex<T>> stack_;        // auxiliary field
    list<list<T>> list_sccs;        // auxiliary field

    void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
    bool dfsIsDAG(Vertex<T> *v) const;
public:
    Vertex<T> *findVertex(const T &in) const;
    int getNumVertex() const;
    int calculateDiameter() const;
    bool addVertex(const T &in);
    bool removeVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w,string airline);
    bool removeEdge(const T &sourc, const T &dest);
    vector<Vertex<T> * > getVertexSet() const;
    vector<T> dfs() const;
    vector<T> dfs(const T & source) const;
    vector<T> bfs(const T &source) const;
    void bfsDifferent(T &source) const;
    vector<T> topsort() const;
    bool isDAG() const;
    void calculateIndegrees() const;
};

/**
 * @brief Calculates the diameter of the graph using BFS.
 * @details The diameter of a graph is the length of the longest shortest path
 *          between any two vertices.
 * @return The diameter of the graph.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(V^2 + V*E)
 *   - V is the number of vertices in the graph.
 *   - E is the number of edges in the graph.
 *   - The function consists of two nested loops, where the outer loop runs V times
 *     (once for each vertex) and the inner loop runs BFS, which takes O(V + E) time.
 *   - The overall complexity is O(V^2 + V*E).
 */
template<class T>
int Graph<T>::calculateDiameter() const {
    int max_diameter = 0;
    for(auto a : getVertexSet())
    {
        a->setVisited(false);
        a->setParent(nullptr);
        a->setNum(0);
    }
    for (auto a : getVertexSet()){
        T airport = a->getInfo();
        this->bfsDifferent(airport);
        for (Vertex<T>* b : getVertexSet()){
            if (b->getNum() > max_diameter)
            {
                max_diameter = b->getNum();
            }
        }
    }

    return max_diameter;
}

/****************** Provided constructors and functions ********************/
/**
 * @brief Vertex class constructor.
 * @details Initializes a vertex with the given information.
 * @param in The information to be stored in the vertex.
 * @tparam T The type of information stored in the vertex.
 *
 * Time Complexity: O(1)
 *   - The constructor has constant time complexity as it performs basic assignment.
 */
template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/**
 * @brief Edge class constructor.
 * @details Initializes an edge with the given destination vertex, weight, and airline code.
 * @param d The destination vertex of the edge.
 * @param w The weight of the edge.
 * @param airline The airline code associated with the edge.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(1)
 *   - The constructor has constant time complexity as it performs basic assignments.
 */
template <class T>
Edge<T>::Edge(Vertex<T> *d, double w,string airline): dest(d), weight(w),airline(airline) {}

/**
 * @brief Gets the number of vertices in the graph.
 * @return The number of vertices in the graph.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(1)
 *   - The function has constant time complexity as it retrieves the size of the vertex set.
 */
template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}
/**
 * @brief Gets the vector of vertices in the graph.
 * @return A vector containing pointers to all vertices in the graph.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(1)
 *   - The function has constant time complexity as it returns a reference to the vertex set.
 */
template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
    return vertexSet;
}

/**
 * @brief Gets the information stored in the vertex.
 * @return The information stored in the vertex.
 * @tparam T The type of information stored in the vertex.
 *
 * Time Complexity: O(1)
 *   - The function has constant time complexity as it retrieves the information of the vertex.
 */
template<class T>
T Vertex<T>::getInfo() const {
    return info;
}

/**
 * @brief Sets the information stored in the vertex.
 * @param in The new information to be stored in the vertex.
 * @tparam T The type of information stored in the vertex.
 *
 * Time Complexity: O(1)
 *   - The function has constant time complexity as it performs a basic assignment.
 */
template<class T>
void Vertex<T>::setInfo(T in) {
    Vertex::info = in;
}

/**
 * @brief Checks if the vertex is being processed.
 * @return True if the vertex is being processed, false otherwise.
 * @tparam T The type of information stored in the vertex.
 *
 * Time Complexity: O(1)
 *   - The function has constant time complexity as it retrieves the processing status of the vertex.
 */
template<class T>
bool Vertex<T>::isProcessing() const {
    return processing;
}

/**
 * @brief Sets the processing status of the vertex.
 * @param p The new processing status.
 * @tparam T The type of information stored in the vertex.
 *
 * Time Complexity: O(1)
 *   - The function has constant time complexity as it performs a basic assignment.
 */
template<class T>
void Vertex<T>::setProcessing(bool p) {
    Vertex::processing = p;
}

/**
 * @brief Gets the destination vertex of the edge.
 * @return A pointer to the destination vertex.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(1)
 *   - The function has constant time complexity as it retrieves the destination vertex.
 */
template<class T>
Vertex<T> *Edge<T>::getDest() const {
    return dest;
}

/**
 * @brief Sets the destination vertex of the edge.
 * @param d A pointer to the new destination vertex.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(1)
 *   - The function has constant time complexity as it performs a basic assignment.
 */
template<class T>
void Edge<T>::setDest(Vertex<T> *d) {
    Edge::dest = d;
}

/**
 * @brief Gets the weight of the edge.
 * @return The weight of the edge.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(1)
 *   - The function has constant time complexity as it retrieves the weight of the edge.
 */
template<class T>
double Edge<T>::getweight() const {
    return weight;
}

/**
 * @brief Sets the weight of the edge.
 * @param weight The new weight of the edge.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(1)
 *   - The function has constant time complexity as it performs a basic assignment.
 */
template<class T>
void Edge<T>::setweight(double weight) {
    Edge::weight = weight;
}

/**
 * @brief Sets the airline code associated with the edge.
 * @param airline The new airline code.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(1)
 *   - The function has constant time complexity as it performs a basic assignment.
 */
template<class T>
void Edge<T>::setAirline(std::string airline) {
    Edge::airline = airline;
}

/**
 * @brief Gets the airline code associated with the edge.
 * @return The airline code.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(1)
 *   - The function has constant time complexity as it retrieves the airline code.
 */
template<class T>
std::string Edge<T>::getAirline() const{
    return airline;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
/**
 * @brief Finds a vertex with a given content.
 * @param in The content to search for in the vertices.
 * @return A pointer to the vertex if found, or nullptr if not found.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(V)
 *   - The function has linear time complexity as it iterates through the vertex set to find the desired vertex.
 *     (V is the number of vertices in the graph.)
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

/**
 * @brief Checks if the vertex has been visited.
 * @return True if the vertex has been visited, false otherwise.
 * @tparam T The type of information stored in the vertex.
 *
 * Time Complexity: O(1)
 *   - The function has constant time complexity as it retrieves the visited status of the vertex.
 */
template <class T>
bool Vertex<T>::isVisited() const {
    return visited;
}

/**
 * @brief Gets the indegree of the vertex.
 * @return The indegree of the vertex.
 * @tparam T The type of information stored in the vertex.
 *
 * Time Complexity: O(1)
 *   - The function has constant time complexity as it retrieves the indegree of the vertex.
 */
template<class T>
int Vertex<T>::getIndegree() const {
    return indegree;
}

/**
 * @brief Sets the indegree of the vertex.
 * @param indegree The new indegree of the vertex.
 * @tparam T The type of information stored in the vertex.
 *
 * Time Complexity: O(1)
 *   - The function has constant time complexity as it performs a basic assignment.
 */
template<class T>
void Vertex<T>::setIndegree(int indegree) {
    Vertex::indegree = indegree;
}

/**
 * @brief Gets the auxiliary field "num" of the vertex.
 * @return The value of the "num" field.
 * @tparam T The type of information stored in the vertex.
 *
 * Time Complexity: O(1)
 *   - The function has constant time complexity as it retrieves the "num" field of the vertex.
 */
template<class T>
int Vertex<T>::getNum() const {
    return num;
}

/**
 * @brief Sets the auxiliary field "num" of the vertex.
 * @param num The new value for the "num" field.
 * @tparam T The type of information stored in the vertex.
 *
 * Time Complexity: O(1)
 *   - The function has constant time complexity as it performs a basic assignment.
 */
template<class T>
void Vertex<T>::setNum(int num) {
    Vertex::num = num;
}

/**
 * @brief Gets the auxiliary field "low" of the vertex.
 * @return The value of the "low" field.
 * @tparam T The type of information stored in the vertex.
 *
 * Time Complexity: O(1)
 *   - The function has constant time complexity as it retrieves the "low" field of the vertex.
 */
template<class T>
int Vertex<T>::getLow() const {
    return low;
}

/**
 * @brief Sets the auxiliary field "low" of the vertex.
 * @param low The new value for the "low" field.
 * @tparam T The type of information stored in the vertex.
 *
 * Time Complexity: O(1)
 *   - The function has constant time complexity as it performs a basic assignment.
 */
template<class T>
void Vertex<T>::setLow(int low) {
    Vertex::low = low;
}

/**
 * @brief Sets the visited status of the vertex.
 * @param v The new visited status.
 * @tparam T The type of information stored in the vertex.
 *
 * Time Complexity: O(1)
 *   - The function has constant time complexity as it performs a basic assignment.
 */
template <class T>
void Vertex<T>::setVisited(bool v) {
    Vertex::visited = v;
}

/**
 * @brief Gets the list of outgoing edges from the vertex.
 * @return A reference to the vector of outgoing edges.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(1)
 *   - The function has constant time complexity as it returns a reference to the outgoing edges of the vertex.
 */
template<class T>
const vector<Edge<T>> &Vertex<T>::getAdj() const {
    return adj;
}

/**
 * @brief Sets the list of outgoing edges from the vertex.
 * @param adj A reference to the vector of outgoing edges.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(1)
 *   - The function has constant time complexity as it performs a basic assignment.
 */
template <class T>
void Vertex<T>::setAdj(const vector<Edge<T>> &adj) {
    Vertex::adj = adj;
}


/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
/**
 * @brief Adds a vertex with a given content to the graph.
 * @param in The content of the new vertex.
 * @return True if the addition is successful, false if a vertex with the same content already exists.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(V)
 *   - The function calls the findVertex method, which has a linear time complexity.
 *     (V is the number of vertices in the graph.)
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if (findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}


/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
/**
 * @brief Adds an edge to the graph, given the contents of the source and destination vertices and the edge weight.
 * @param sourc The content of the source vertex.
 * @param dest The content of the destination vertex.
 * @param w The weight of the edge.
 * @param airline The airline code associated with the edge.
 * @return True if the addition is successful, false if the source or destination vertex does not exist.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(V)
 *   - The function calls the findVertex method twice, each with linear time complexity.
 *     Additionally, the Vertex<T>::addEdge method is called, which has a constant time complexity.
 *     (V is the number of vertices in the graph.)
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w,string airline) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w,airline);
    return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
/**
 * @brief Adds an outgoing edge to the vertex with a given destination vertex and edge weight.
 * @param d The destination vertex.
 * @param w The weight of the edge.
 * @param airline The airline code associated with the edge.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(1)
 *   - The function has constant time complexity as it appends an edge to the vector of outgoing edges.
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w,string airline) {
    adj.push_back(Edge<T>(d, w,airline));
}


/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
/**
 * @brief Removes an edge from the graph, identified by the source and destination contents.
 * @param sourc The content of the source vertex.
 * @param dest The content of the destination vertex.
 * @return True if the removal is successful, false if such an edge does not exist.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(V)
 *   - The function calls the findVertex method twice, each with linear time complexity.
 *     Additionally, the Vertex<T>::removeEdgeTo method is called, which has linear time complexity.
 *     (V is the number of vertices in the graph.)
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    return v1->removeEdgeTo(v2);
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
/**
 * @brief Removes an outgoing edge (with a given destination) from the vertex.
 * @param d The destination vertex.
 * @return True if the removal is successful, false if such an edge does not exist.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(E)
 *   - The function iterates through the vector of outgoing edges, where E is the number of edges.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    for (auto it = adj.begin(); it != adj.end(); it++)
        if (it->dest  == d) {
            adj.erase(it);
            return true;
        }
    return false;
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
/**
 * @brief Removes a vertex with a given content from the graph, along with all outgoing and incoming edges.
 * @param in The content of the vertex to be removed.
 * @return True if the removal is successful, false if such a vertex does not exist.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(V + E)
 *   - The function has linear time complexity as it iterates through the vertex set to find and remove the desired vertex,
 *     and then iterates through the remaining vertices to remove edges pointing to the deleted vertex.
 *     (V is the number of vertices, and E is the number of edges in the graph.)
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
        if ((*it)->info  == in) {
            auto v = *it;
            vertexSet.erase(it);
            for (auto u : vertexSet)
                u->removeEdgeTo(v);
            delete v;
            return true;
        }
    return false;
}


/****************** DFS ********************/
/*
 * Performs a depth-first search (dfs) traversal in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
/**
 * @brief Performs a depth-first search (dfs) traversal in the graph.
 * @return A vector with the contents of the vertices in dfs order.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(V + E)
 *   - The function iterates through all vertices, calling the dfsVisit method for each unvisited vertex.
 *     The dfsVisit method, in turn, traverses all adjacent vertices.
 *     (V is the number of vertices, and E is the number of edges in the graph.)
 */
template <class T>
vector<T> Graph<T>::dfs() const {
    vector<T> res;
    for (auto v : vertexSet)
        v->visited = false;
    for (auto v : vertexSet)
        if (! v->visited)
            dfsVisit(v, res);
    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */
/**
 * @brief Auxiliary function that visits a vertex and its adjacent, recursively.
 * @param v The vertex to visit.
 * @param res A vector to store the contents of visited nodes.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(E)
 *   - The function recursively traverses all adjacent vertices of the given vertex.
 *     (E is the number of edges in the graph.)
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
    v->visited = true;
    res.push_back(v->info);
    for (auto & e : v->adj) {
        auto w = e.dest;
        if ( ! w->visited)
            dfsVisit(w, res);
    }
}


/****************** BFS ********************/
/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 */
/**
 * @brief Performs a breadth-first search (bfs) in the graph, starting from the vertex with the given source contents.
 * @param source The content of the source vertex.
 * @return A vector with the contents of the vertices in bfs order.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(V + E)
 *   - The function iterates through all vertices, calling the bfsDifferent method, which traverses all adjacent vertices in bfs order.
 *     (V is the number of vertices, and E is the number of edges in the graph.)
 */
template <class T>
vector<T> Graph<T>::bfs(const T & source) const {
    vector<T> res;
    auto s = findVertex(source);
    if (s == NULL)
        return res;
    queue<Vertex<T> *> q;
    for (auto v : vertexSet)
        v->visited = false;
    q.push(s);
    s->visited = true;
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->info);
        for (auto & e : v->adj) {
            auto w = e.dest;
            if ( ! w->visited ) {
                q.push(w);
                w->visited = true;
            }
        }
    }
}
/**
 * @brief Performs a breadth-first search (bfs) in the graph, starting from the vertex with the given source contents.
 * @param source The content of the source vertex.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(V + E)
 *   - The function iterates through all vertices, calling the setVisited and setNum methods, and traverses all adjacent vertices in bfs order.
 *     (V is the number of vertices, and E is the number of edges in the graph.)
 */
template<class T>
void Graph<T>::bfsDifferent(T &source) const {
    auto s = findVertex(source);
    if (s == NULL)
        return ;
    queue<Vertex<T> *> q;
    for (auto v : vertexSet)
        v->setVisited(false);
    q.push(s);
    s->setVisited(true);
    s->setNum(0);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        for (const Edge<T> & e : v->getAdj()) {
            Vertex<T>* w = e.getDest();
            if (!w->isVisited()) {
                q.push(w);
                w->setVisited(true);
                w->setNum(v->getNum() + 1);
            }
        }
    }
}

/****************** isDAG  ********************/
/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template <class T>
bool Graph<T>::isDAG() const {
    for (auto v : vertexSet) {
        v->visited = false;
        v->processing = false;
    }
    for (auto v : vertexSet)
        if (! v->visited)
            if ( ! dfsIsDAG(v) )
                return false;
    return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template <class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
    v->visited = true;
    v->processing = true;
    for (auto & e : v->adj) {
        auto w = e.dest;
        if (w->processing)
            return false;
        if (! w->visited)
            if (! dfsIsDAG(w))
                return false;
    }
    v->processing = false;
    return true;
}


/****************** toposort ********************/

/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */
/**
 * @brief Performs a topological sort auxiliary function.
 * @param vertex The current vertex being visited.
 * @param s The stack to store vertices in topological order.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(V + E)
 *   - The function traverses all vertices and edges in the graph, performing a depth-first search.
 *     (V is the number of vertices, and E is the number of edges in the graph.)
 */
template<class T>
void topsortAux(Vertex<T>* vertex, stack<Vertex<T>*> & s) {
    vertex->setVisited(true);
    for (Edge<T> edge : vertex->getAdj()) {
        auto neighbor = edge.getDest();
        if (!neighbor->isVisited()) {
            topsortAux(neighbor, s);
        }
    }
    s.push(vertex);
}

/**
 * @brief Performs a topological sort of the graph.
 * @return A vector with the contents of the vertices in topological order.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(V + E)
 *   - The function iterates through all vertices, calling the topsortAux method for each unvisited vertex.
 *     The topsortAux method, in turn, traverses all adjacent vertices in a depth-first search.
 *     (V is the number of vertices, and E is the number of edges in the graph.)
 */
template<class T>
vector<T> Graph<T>::topsort() const {
    vector<T> res;
    stack<Vertex<T>*> s;
    for (Vertex<T> * vertex : this->vertexSet) {
        vertex->setVisited(false);
    }
    for (Vertex<T>* vertex : this->vertexSet) {
        if (!vertex->isVisited())
            topsortAux(vertex, s);
    }

    while (!s.empty()) {
        res.push_back(s.top()->getInfo());
        s.pop();
    }
    return res;
}

/**
 * @brief Calculates the indegree of each vertex in the graph.
 * @tparam T The type of information stored in the vertices.
 *
 * Time Complexity: O(V + E)
 *   - The function iterates through all vertices and edges in the graph, updating the indegree of each vertex.
 *     (V is the number of vertices, and E is the number of edges in the graph.)
 */
template <class T>
void Graph<T>::calculateIndegrees() const {
    for (auto v : vertexSet) {
        v->setIndegree(0);
    }

    for (auto v : vertexSet) {
        for (auto &e : v->getAdj()) {
            auto w = e.getDest();
            w->setIndegree(w->getIndegree() + 1);
        }
    }
}

#endif //PROJETO_2_GRAPH_H
