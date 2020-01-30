//
// Created by omerm on 1/4/2020.
//

#ifndef DYNAMIC_GRAPH_VER1_TREE_NODE_H
#define DYNAMIC_GRAPH_VER1_TREE_NODE_H

#include <cstddef>

class Rooted_Tree;
class Dynamic_Graph;
class Tree_Node
{
    //allowing Rooted_Tree and Dynamic_Graph access to Tree_Node private data members:
    friend class Rooted_Tree;
    friend class Dynamic_Graph;

private:
    Tree_Node* child;
    Tree_Node* sibling;
    Tree_Node* parent;
    unsigned key;

    Tree_Node(unsigned key): parent(NULL), child(NULL), sibling(NULL), key(key) {}
    Tree_Node* addChild(unsigned key);
};

#endif //DYNAMIC_GRAPH_VER1_TREE_NODE_H
