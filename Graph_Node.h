//
// Created by omerm on 1/1/2020.
//

#ifndef DYNAMIC_GRAPH_VER1_GRAPH_NODE_H
#define DYNAMIC_GRAPH_VER1_GRAPH_NODE_H

#define WHITE 1
#define GRAY 2
#define BLACK 3

#include "Graph_Edge.h"
#include <cstddef>

class Dynamic_Graph;
class Graph_Node
{
    //allowing Dynamic_Graph access to Graph_Node private data members:
    friend class Dynamic_Graph;
private:
    unsigned key;
    Graph_Node* prev; //graph nodes list prev
    Graph_Node* next; //graph nodes list next
    unsigned degIn;
    unsigned degOut;
    Graph_Edge* edgeIn; //list of in edges
    Graph_Edge* edgeOut; //list of out edges
    unsigned color; //BFS/DFS status

public:
    Graph_Node(unsigned key, Graph_Node* p, Graph_Node* n): key(key), prev(p), next(n),
                              degIn(0), degOut(0), edgeIn(NULL), edgeOut(NULL), color(WHITE) {}
    unsigned Get_out_Degree() const { return degOut; }
    unsigned Get_in_Degree() const { return degIn; }
    unsigned Get_key() const { return key; }
};

#endif //DYNAMIC_GRAPH_VER1_GRAPH_NODE_H
