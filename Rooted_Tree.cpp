//
// Created by omerm on 1/4/2020.
//

#include "Rooted_Tree.h"

Rooted_Tree::~Rooted_Tree()
{
    deleteAux(root);
}

void Rooted_Tree::deleteAux(Tree_Node* node)
{
    if (node == NULL)
        return;
    deleteAux(node->child);
    deleteAux(node->sibling);
    delete node;
}

void Rooted_Tree::Preorder_Print(std::ostream &stream) const
{
    if (root == NULL) return;
    Queue<Tree_Node*> Q;
    preOrderAux(root, Q);
    while(Q.getSize() > 1)
    {
        stream << Q.front()->key << ",";
        Q.pop();
    }
    stream << Q.front()->key;
}

void Rooted_Tree::preOrderAux(Tree_Node* x, Queue<Tree_Node*> &Q) const
{
    if(x == NULL) return;
    Q.push(x);
    preOrderAux(x->child, Q);
    preOrderAux(x->sibling, Q);
}

void Rooted_Tree::Print_By_Layer(std::ostream & stream) const
{
    Queue<Tree_Node*> Q; //left child queue
    Tree_Node* x = root;
    Q.push(x);
    while (Q.getSize() > 0)
    {
        unsigned n = Q.getSize(); //number of left children of current level
        for (unsigned int i = 0; i < n; ++i) //iterating over all left children of current level
        {
            if(i) stream << ",";
            Tree_Node* temp = Q.front(); Q.pop();
            stream << temp->key;
            if (temp->child) Q.push(temp->child); //if temp has a left child - push into Q
            while (temp->sibling) //print all of temp's siblings:
            {
                stream << ",";
                temp = temp->sibling;
                if (temp->child) Q.push(temp->child);
                stream << temp->key;
            }
        }
        if(!Q.empty()) stream << "\n"; //start a new line only after printing current level
    }
}
