// -----------------------------------------------------------
// Kevin Trinh
// Summer CMPS 101 2019
// kevatrin
// Graph.h
// Contains function prototypes for Graph.c
// -----------------------------------------------------------

 #ifndef _GRAPH_H_INCLUDE
 #define _GRAPH_H_INCLUDE
 #include"List.h"
 static const int UNDEF = -1;
 static const int NIL = -2;

 typedef struct GraphObj* Graph;
 enum color{white, gray, black};

 // newGraph
 // Constructor
 // Creates new Graph and returns a Graph pointing to newly
 // created GraphObj representing a graph having n vertices and no edges
 Graph newGraph(int n);

 // freeGraph
 // Destructor
 // Frees and deallocates all dynamic memory of Graph *pG
 void freeGraph(Graph *pG);

 /*** Access functions ***/
 // getOrder
 // Returns the cardinality of the vertex set of the Graph
 int getOrder(Graph G);

 // getSize
 // returns the cardinality of the edge set of the Graph
 int getSize(Graph G);

 // getParent
 // Returns the parent of the vertex u in the 
 // Breadth First tree created by BFS() or NIL if 
 // BFS() has not been called
 // Pre: 1<=u<=getOrder(G)
 int getParent(Graph G, int u);

 // getDiscover
 // Returns the discover time of the vertex
 // Pre: 1<=u<=getOrder(G)
 int getDiscover(Graph G, int u);

 // getFinish
 // Returns the finish time of the vertex
 // Pre: 1<=u<=getOrder(G)
 int getFinish(Graph G, int u);

 /*** Manipulation ***/

 // addEdge
 // Inserts a new edge joining u to v
 // Pre: 1<=u<=getOrder(G); 1<=v<=getOrder(G)
 void addEdge(Graph G, int u, int v);

 // addArc
 // Inserts a new directional edge from u to v
 // Pre: 1<=u<=getOrder(G); 1<=v<=getOrder(G)
 void addArc(Graph G, int u, int v);

 // DFS
 // Runs the DFS algorithm on Graph G on source S,
 // setting color, discover, finsih, and parent fields
 // of G accordingly 
 void DFS(Graph G, List S);

 // visit
 // Helper Function
 // Recursive algorithm that visits all the vertices in the Graph
 // and populates the data fields of Graph G respectively
 void visit(int u, int *time, Graph *G, List *L);
 
 /*** Other ***/

 // transpose
 // Returns the transpose of the digraph
 Graph transpose(Graph G);

 // copyGraph
 // Returns a reference to a new graph that is a copy of G
 Graph copyGraph(Graph G);

 // printGraph
 // Prints the Adjacency List Representation
 void printGraph(FILE* out, Graph G);

#endif
