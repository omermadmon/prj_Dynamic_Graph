//
// Created by omerm on 1/1/2020.
//

#ifndef DYNAMIC_GRAPH_VER1_DYNAMIC_GRAPH_H
#define DYNAMIC_GRAPH_VER1_DYNAMIC_GRAPH_H

#define VIRTUAL_SOURCE 0

#include <cstddef>
#include "Graph_Node.h"
#include "Rooted_Tree.h"
#include "Queue.h"
#include "Rooted_Tree.h"

class Dynamic_Graph
{
private:
    Graph_Node *Nodes; //nodes list: each node stores it's in & out edges

public:
    Dynamic_Graph(): Nodes(NULL) { }
    ~Dynamic_Graph();

    Graph_Node* Insert_Node(unsigned node_key);
    void Delete_Node(Graph_Node* node);
    Graph_Edge* Insert_Edge(Graph_Node* from, Graph_Node* to);
    void Delete_Edge(Graph_Edge* edge);
    Rooted_Tree* BFS(Graph_Node* source) const;
    Rooted_Tree* SCC() const;

private:
    void updateNodesQueue(Queue<Graph_Node*> &Q) const; //used by SCC method
    void DFS_visit(Graph_Node* u, Queue<Graph_Node*> &Q) const; //used by SCC method
    void DFS2_visit(Graph_Node* u, Tree_Node* u_tree, Rooted_Tree* T) const; //used by SCC method
};

#endif //DYNAMIC_GRAPH_VER1_DYNAMIC_GRAPH_H
