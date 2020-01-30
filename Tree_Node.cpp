//
// Created by omerm on 1/4/2020.
//

#include "Tree_Node.h"

Tree_Node* Tree_Node::addChild(unsigned key)
{
    Tree_Node* newChild = new Tree_Node(key);
    newChild->sibling = child;
    child = newChild;
    newChild->parent = this;
    return child;
}
