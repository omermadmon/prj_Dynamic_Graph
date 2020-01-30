//
// Created by omerm on 1/1/2020.
//

#include "Dynamic_Graph.h"

Graph_Node* Dynamic_Graph::Insert_Node(unsigned node_key)
{
    //assumption: node_key does not appear in the graph.
    //create new node and add it to be the first node in Nodes:
    Graph_Node* newNode = new Graph_Node(node_key, NULL, Nodes);
    if (newNode->next != NULL) (newNode->next)->prev = newNode; //if the inserted node is not the first
    Nodes = newNode;
    return Nodes;
}

void Dynamic_Graph::Delete_Node(Graph_Node *node)
{
    //if node has some in or out edges - do nothing:
    if(node->degIn != 0 || node->degOut != 0) return;

    //else - delete node:
    if(node->prev == NULL) //if node is the first in Nodes list:
    {
        Nodes = node->next; //set node->next to be the first node in Nodes
        if(node->next != NULL) (node->next)->prev = NULL; //node->next points to node->prev
        //make sure node doesn't point anywhere while being deleted:
        node->next = NULL;
        delete node;
    }
    else
    {
        (node->prev)->next = node->next; //node->prev points to node->next
        if(node->next != NULL) (node->next)->prev = node->prev; //node->next points to node->prev
        //make sure node doesn't point anywhere while being deleted:
        node->prev = NULL;
        node->next = NULL;
        //delete:
        delete node;
    }
}

Graph_Edge* Dynamic_Graph::Insert_Edge(Graph_Node* from, Graph_Node* to)
{
    //1st assumption: from != to
    //2nd assumption: from and to both appear in the graph

    //create new edge:
    Graph_Edge* e = new Graph_Edge(from, to);
    //update degIn & degOut:
    from->degOut++;
    to->degIn++;
    //add e to the beginning of from's edgeOut list:
    if(from->edgeOut == NULL) from->edgeOut = e; //if e is the first out edge of from
    else
    {
        (from->edgeOut)->outPrev = e;
        e->outNext = from->edgeOut;
        from->edgeOut = e;
    }
    //add e to the beginning of to's edgeIn list:
    if(to->edgeIn == NULL) to->edgeIn = e; //if e is the first in edge into to
    else
    {
      (to->edgeIn)->inPrev = e;
      e->inNext = to->edgeIn;
      to->edgeIn = e;
    }

    return e;
}

void Dynamic_Graph::Delete_Edge(Graph_Edge* edge)
{
    //assumption: edge exists in the graph

    //FIRST STEP: update degIn & degOut:
    (edge->from)->degOut--;
    (edge->to)->degIn--;

    //SECOND STEP: remove edge from from->edgeOut list:
    //if edge is the first edge in from->edgeOut list:
    if(edge->outPrev == NULL)
    {
        edge->from->edgeOut = edge->outNext;
        if(edge->outNext != NULL) (edge->outNext)->outPrev = NULL;
        //make sure edge does not point anyone before being deleted:
        edge->outNext = NULL;

    }
    else
    {
        //edge->outPrev is surely not NULL
        (edge->outPrev)->outNext = edge->outNext;
        if(edge->outNext != NULL) (edge->outNext)->outPrev = edge->outPrev;
        //make sure edge does not point anyone before being deleted:
        edge->outPrev = NULL;
        edge->outNext = NULL;

    }

    //THIRD STEP: remove edge from to->edgeIn list:
    //if edge is the first edge in to->edgeIn list:
    if(edge->inPrev == NULL)
    {
        edge->to->edgeIn = edge->inNext;
        if(edge->inNext != NULL) (edge->inNext)->inPrev = NULL;
        //make sure edge does not point anyone before being deleted:
        edge->inNext = NULL;

    }
    else
    {
        //edge->outPrev is surely not NULL
        (edge->inPrev)->inNext = edge->inNext;
        if(edge->inNext != NULL) (edge->inNext)->inPrev = edge->inPrev;
        //make sure edge does not point anyone before being deleted:
        edge->inPrev = NULL;
        edge->inNext = NULL;

    }

    delete edge;
}

Dynamic_Graph::~Dynamic_Graph()
{
    Graph_Node *n = Nodes;
    while(n != NULL)
    {
        Graph_Edge* e1 = n->edgeOut;
        Graph_Edge* e2 = n->edgeIn;
        Graph_Edge* tmpEdge = NULL;
        while (e1 != NULL) //delete all on n's out edges
        {
            tmpEdge = e1->outNext;
            this->Delete_Edge(e1);
            e1 = tmpEdge;
        }
        while(e2 != NULL) //delete all on n's in edges
        {
            tmpEdge = e2->inNext;
            this->Delete_Edge(e2);
            e2 = tmpEdge;
        }

        //when code reaches here, n->degIn = n->degOut = 0, so it can be deleted:
        Graph_Node * toDelete = n;
        n = n->next;
        this->Delete_Node(toDelete);
    }
}

Rooted_Tree* Dynamic_Graph::BFS(Graph_Node* source) const
{
    //initialize BFS:
    Graph_Node* n = Nodes;
    while (n != NULL)
    {
        if (n == source) n->color = GRAY;
        else n->color = WHITE;
        n = n->next;
    }
    Queue<Graph_Node*> Q;
    Q.push(source);

    Tree_Node* u_tree = new Tree_Node(source->Get_key());
    Rooted_Tree* T = new Rooted_Tree(u_tree);

    Queue<Tree_Node*> P;
    P.push(u_tree);

    while(!Q.empty())
    {
        Graph_Node* u = Q.front(); Q.pop();
        u_tree = P.front(); P.pop();
        Graph_Edge* edgeOutIter = u->edgeOut; //newest out edge of u
        Tree_Node* u_right_child = NULL;
        while(edgeOutIter != NULL) //iterating u's neighbours
        {
            if(u_right_child == NULL) //u has no children at BFS tree:
            {
                Graph_Node* v = edgeOutIter->to; //v is the newest neighbour of u
                if(v->color == WHITE)
                {
                    v->color = GRAY;
                    u_tree->addChild(v->Get_key());
                    Q.push(v);
                    P.push(u_tree->child);
                    u_right_child = u_tree->child;
                }
                edgeOutIter = edgeOutIter->outNext;
            }
            else //u already has some children at BFS tree:
            {
                Graph_Node* v = edgeOutIter->to; //v is the newest neighbour of u
                if(v->color == WHITE)
                {
                    v->color = GRAY;
                    u_right_child->sibling = new Tree_Node(v->key);
                    Q.push(v);
                    P.push(u_right_child->sibling);
                    u_right_child = u_right_child->sibling;
                    if(u_right_child->sibling != NULL) u_right_child->sibling->parent = u_tree;
                }
                edgeOutIter = edgeOutIter->outNext;
            }
        }
        u->color = BLACK;
    }
    return T;
}

Rooted_Tree* Dynamic_Graph::SCC() const
{
    //STAGE 1: create a queue of graph nodes, ordered by v.f:
    Queue<Graph_Node*> Q; //first node to pop out from Q will be the latest one colored BLACK by DFS
    updateNodesQueue(Q);

    //STAGE 2: performing DFS on G transpose while iterating the nodes in decreasing v.f order, using Q:

    //initialize DFS:
    Graph_Node* n = Nodes;
    while (n != NULL)
    {
        n->color = WHITE;
        n = n->next;
    }

    Tree_Node* source = new Tree_Node(VIRTUAL_SOURCE);
    Rooted_Tree* T = new Rooted_Tree(source);
    Tree_Node* source_right_child = NULL;

    //DFS outer loop over graph nodes:
    while(!Q.empty())
    {
        Graph_Node* u = Q.front();
        Q.pop();
        if (u->color == WHITE)
        {
            //add u as a right child of source:
            if(source_right_child == NULL)
            {
                source->addChild(u->Get_key());
                source_right_child = source->child;
            } else
            {
                source_right_child->sibling = new Tree_Node(u->key);
                source_right_child = source_right_child->sibling;
            }

            //DFS recursive call:
            DFS2_visit(u, source_right_child, T);
        }
    }

    return T;
}

void Dynamic_Graph::DFS2_visit(Graph_Node* u, Tree_Node* u_tree, Rooted_Tree* T) const
{
    u->color = GRAY;
    Tree_Node* u_right_child = NULL;
    Graph_Edge* iter = u->edgeIn; //DFS over G TRANSPOSE!
    while(iter != NULL)
    {
        Graph_Node* v = iter->from;
        if(v->color == WHITE)
        {
            //add v as a right child of u:
            if(u_right_child == NULL)
            {
                u_tree->addChild(v->Get_key());
                u_right_child = u_tree->child;
            } else
            {
                u_right_child->sibling = new Tree_Node(v->key);
                u_right_child = u_right_child->sibling;
                if(u_right_child->sibling != NULL) u_right_child->sibling->parent = u_tree;
            }
            DFS2_visit(v, u_right_child, T);
        }

        iter = iter->inNext;
    }
    u->color = BLACK;
}

void Dynamic_Graph::updateNodesQueue(Queue<Graph_Node*> &Q) const
{
    //performing first DFS of the SCC method.
    //nodes will be pushed to the front of the queue as soon as their v.f field should be updated.

    //initialize DFS:
    Graph_Node* n = Nodes;
    while (n != NULL)
    {
        n->color = WHITE;
        n = n->next;
    }

    n = Nodes;

    //DFS outer loop over graph nodes:
    while(n != NULL)
    {
        if (n->color == WHITE) DFS_visit(n, Q);
        n = n->next;
    }

    //be the end of this loop, Q store pointers to the nodes in increasing order of their v.f fields
}

void Dynamic_Graph::DFS_visit(Graph_Node* u, Queue<Graph_Node*> &Q) const
{
    u->color = GRAY;
    Graph_Edge* iter = u->edgeOut;
    while(iter != NULL)
    {
        Graph_Node* v = iter->to;
        if (v->color == WHITE) DFS_visit(v, Q);
        iter = iter->outNext;
    }
    u->color = BLACK;
    Q.pushFront(u); //when Q is popped, u is the first item to pop out of it
}