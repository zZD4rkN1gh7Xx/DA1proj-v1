 /*
 * Graph.h
 */

 /**
*@file Graph.h
*@brief Header file for the Graph class
*/


#ifndef GRAPH_H_
#define GRAPH_H_

#include <cstddef>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>

 using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#include "Pipes.h"


/****************** Provided structures  ********************/

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // list of outgoing edges
    vector<Edge<T>> ingoing; // list of ingoing edges
	bool visited;          // auxiliary field
    bool processing;       // auxiliary field
    int indegree;          // auxiliary field
    int num;               // auxiliary field
    int low;               // auxiliary field

    void addEdge(Vertex<T> *dest, Pipe w);
	bool removeEdgeTo(Vertex<T> *d);

public:
	Vertex(T in);
    T getInfo() const;
    void setInfo(T in);
    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);
    int getIndegree() const;
    void setIndegree(int indegree);
    void setLow(int low);
    void setNum(int num);
    int getNum() const;
    int getLow() const;

    vector<Edge<T>> &getAdj();
    const vector<Edge<T>> &getingoing() const;
    void setAdj(const vector<Edge<T>> &adj);
    void setIngoing(const vector<Edge<T>> &ingoing);
    friend class Graph<T>;

    void sortAdjByCapacity();
};

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	Pipe weight;// edge weight

public:
	Edge(Vertex<T> *d, Pipe w);
    Vertex<T> *getDest() const;
    void setDest(Vertex<T> *dest);
    Pipe getWeight() const;
    void setWeight(Pipe weight);
    friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set
    void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
public:
    Vertex<T> *findVertex(const T &in) const;
    int getNumVertex() const;
	bool addVertex( T &in);
	bool removeVertex(T &in);
	bool addEdge(const T &sourc, const T &dest, Pipe w);
	bool removeEdge(const T &sourc, const T &dest);
    vector<Vertex<T> * > getVertexSet() const;
    void setVertexSet(vector<Vertex<T> * >);
	vector<T> dfs() const;
	vector<T> dfs(const T & source) const;
	vector<T> bfs(const T &source) const;
    void emitDOTFile(string gname);
    Edge<T>* findEdge(const T& source_info, const T& dest_info) const;

};

template<class T>
void Graph<T>::setVertexSet(vector<Vertex<T> * > vertexes) {
     this->vertexSet = vertexes;
 }

 template <class T>
 void Vertex<T>::sortAdjByCapacity() {
     // Define a custom comparison function for sorting
     auto compareByCapacity = [](const Edge<T>& a, const Edge<T>& b) {
         return a.getWeight().get_capacity() < b.getWeight().get_capacity();
     };

     // Sort the adj vector using the custom comparison function
     std::sort(adj.begin(), adj.end(), compareByCapacity);
 }

/****************** Provided constructors and functions ********************/

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, Pipe w): dest(d), weight(w) {}


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
    return vertexSet;
}

template<class T>
T Vertex<T>::getInfo() const {
    return info;
}

template<class T>
void Vertex<T>::setInfo(T in) {
    Vertex::info = in;
}

template<class T>
bool Vertex<T>::isProcessing() const {
    return processing;
}
template<class T>
void Vertex<T>::setNum(int num) {
    Vertex::num = num;
}

template<class T>
void Vertex<T>::setLow(int low) {
    Vertex::low = low;
}

template<class T>
int Vertex<T>::getNum() const {
    return num;
}

template<class T>
int Vertex<T>::getLow() const {
    return low;
}

template<class T>
void Vertex<T>::setProcessing(bool p) {
    Vertex::processing = p;
}

template<class T>
Vertex<T> *Edge<T>::getDest() const {
    return dest;
}

template<class T>
void Edge<T>::setDest(Vertex<T> *d) {
    Edge::dest = d;
}

template<class T>
Pipe Edge<T>::getWeight() const {
    return weight;
}

template<class T>
void Edge<T>::setWeight(Pipe weight) {
    Edge::weight = weight;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

template <class T>
bool Vertex<T>::isVisited() const {
    return visited;
}

template <class T>
void Vertex<T>::setVisited(bool v) {
    Vertex::visited = v;
}
template<class T>
int Vertex<T>::getIndegree() const {
    return indegree;
}

template<class T>
void Vertex<T>::setIndegree(int indegree) {
    Vertex::indegree = indegree;
}

template<class T>
vector<Edge<T>> &Vertex<T>::getAdj()  {
    return adj;
}

template <class T>
void Vertex<T>::setAdj(const vector<Edge<T>> &adj) {
    Vertex::adj = adj;
}


/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex( T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}


/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, Pipe w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, Pipe w) {
	adj.push_back(Edge<T>(d, w));
    sortAdjByCapacity();
}


/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;

	return v1->removeEdgeTo(v2); //&& v2->removeEdgeFrom(v1);
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
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
template <class T>
bool Graph<T>::removeVertex( T &in) {
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

 template <class T>
 Edge<T>* Graph<T>::findEdge(const T& source_info, const T& dest_info) const {
     for (auto& vertex : vertexSet) {
         if (vertex->getInfo() == source_info) {
             for (auto& edge : vertex->getAdj()) {
                 if (edge.getDest()->getInfo() == dest_info) {
                     return &edge;
                 }
             }
             break; // Break loop if source vertex found
         }
     }
     return nullptr; // Edge not found
 }

//=============================================================================
// Exercise 1.1: Depth First Search
//=============================================================================
// Subexercise 1.1.1: Depth First Search (Graph Traversal)
//=============================================================================
/*
 * Performs a depth-first search (dfs) traversal in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 */
// TODO
template <class T>
vector<T> Graph<T>::dfs() const {
    vector<T> res;
    //starting the process, mark each vertex has non visited
    for(auto v : vertexSet){
        v->visited = false;
    }
    for(auto v: vertexSet){
        if(!v->visited){
            dfsVisit(v, res);
        }
    }

    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */
// TODO
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {

    // mark as visited
    v->visited = true;
    for(auto e : v->adj){
       auto w =  e.dest;
       if(!w->visited){
           dfsVisit(w, res);
       }
    }
    res.push_back(v->info);
}

//=============================================================================
// Subexercise 1.1.2: Depth First Search (From a source node)
//=============================================================================
/*
 *
 *
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order,
 * from the source node.
 */
// TODO
template <class T>
vector<T> Graph<T>::dfs(const T & source) const {
    vector<T> res;

    auto vbegin = findVertex(source);

    // not exist in the graph

    if(vbegin == nullptr){
        return res;
    }

    for(auto v : vertexSet){
        v->visited = false;
    }
    dfsVisit(vbegin, res);

    return res;
}


//=============================================================================
// Exercise 2: Breadth-First Search
//=============================================================================
/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 */
// TODO
template <class T>
vector<T> Graph<T>::bfs(const T & source) const {
    // HINT: Use the flag "visited".
    vector<T> res;
    auto b = findVertex(source);
    queue <Vertex <T> * >  myqueue;

    if(b == nullptr){
        return res;
    }
    for(auto v : vertexSet){
        v->visited = false;
    }
    b->visited = true;
    myqueue.push(b);

    while(!myqueue.empty()){
        auto v = myqueue.front();
        myqueue.pop();

        res.push_back(v->info);
        for(auto b : v->adj){
            auto next_node = b.dest;
            if(!next_node->visited){
                myqueue.push(next_node);
                next_node->visited = true;
            }

        }

    }

    // HINT: Use the "queue" class to temporarily store the vertices.

	return res;
}


template <class T>
inline void  Graph<T>::emitDOTFile(string gname) {
    ofstream g_dot_file;

    g_dot_file.open (gname+".gv");
    g_dot_file << "digraph { \n";


    g_dot_file << "labelloc  = top;\n";
    g_dot_file << "labeljust = left;\n";
    g_dot_file << "fontname  = calibri;\n";
    g_dot_file << "fontsize  = 16;\n";
    g_dot_file << "\n";

    for (auto v : vertexSet) {
        g_dot_file << "  " << v->getInfo() << ";\n";  // Print isolated node
        for (auto & e : v->getAdj()) {
            auto w = e.getDest();
            g_dot_file << "  " << v->getInfo() << " -> " << w->getInfo() << ";\n";
        }
    }

    g_dot_file << "}\n";
    g_dot_file.close();
}

#endif /* GRAPH_H_ */