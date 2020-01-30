//
// Created by omerm on 1/1/2020.
//

#ifndef DYNAMIC_GRAPH_VER1_GRAPH_EDGE_H
#define DYNAMIC_GRAPH_VER1_GRAPH_EDGE_H

#include <cstddef>

class Graph_Node;
class Dynamic_Graph;
class Graph_Edge
{
    //allowing Graph_Node and Dynamic_Graph access to Graph_Edge private data members:
    friend class Graph_Node;
    friend class Dynamic_Graph;
private:
    Graph_Node* from;
    Graph_Node* to;
    Graph_Edge* inPrev; //graph in edges list prev
    Graph_Edge* inNext; //graph in edges list next
    Graph_Edge* outPrev; //graph out edges list prev
    Graph_Edge* outNext; //graph out edges list next

public:
    Graph_Edge(Graph_Node* From, Graph_Node* To): from(From), to(To),
                                                  inPrev(NULL), inNext(NULL), outPrev(NULL), outNext(NULL) {}
};

#endif //DYNAMIC_GRAPH_VER1_GRAPH_EDGE_H
