//
// Created by omerm on 1/4/2020.
//

#ifndef DYNAMIC_GRAPH_VER1_ROOTED_TREE_H
#define DYNAMIC_GRAPH_VER1_ROOTED_TREE_H

#include "Tree_Node.h"
#include "Queue.h"
#include <cstddef>
#include <ostream>

class Rooted_Tree
{
private:
    Tree_Node* root;

    void preOrderAux(Tree_Node* x, Queue<Tree_Node*> &Q) const;
    static void deleteAux(Tree_Node* root);

public:
    Rooted_Tree(): root(NULL) { }
    Rooted_Tree(Tree_Node* r): root(r) { }
    ~Rooted_Tree();
    void Print_By_Layer(std::ostream& stream) const;
    void Preorder_Print(std::ostream& stream) const;
};

#endif //DYNAMIC_GRAPH_VER1_ROOTED_TREE_H
