//
// Created by omerm on 1/4/2020.
//

#ifndef DYNAMIC_GRAPH_VER1_QUEUE_H
#define DYNAMIC_GRAPH_VER1_QUEUE_H

#include "QueueItem.h"

template <class Type> class Queue
{
    //generic Queue, is also being used as a Stack in Dynamic_Graph::SCC
private:
    QueueItem<Type>  *head;
    QueueItem<Type>  *tail;
    unsigned int size;

    void destroy ();
    void copy_elems (const Queue&);
public:
    Queue (): head(0), tail (0), size(0) {}
    Queue (const Queue &Q): head (0), tail (0) {copy_elems(Q);}
    Queue& operator=(const Queue&);
    ~Queue () {destroy ();}
    Type& front ()  {return head->item;}
    const Type &front () const {return head->item;}
    void push (const Type &);
    void pushFront (const Type &);
    void pop ();
    unsigned int getSize() const;
    bool empty () const {return head == 0;}
};

template <class Type> unsigned int Queue<Type>::getSize() const { return size; }
template <class Type> void Queue<Type>::destroy () {
    while (!empty ())
        pop ();
}
template <class Type> void Queue<Type>::pop () {

    QueueItem<Type>* p = head;
    head = head -> next;
    size--;
    delete p;
}
template <class Type> void Queue<Type>::push (const Type &val)
{
    QueueItem<Type> *pt = new QueueItem<Type>(val);
    if (empty ())
        head = tail = pt;
    else {
        tail -> next = pt;
        tail = pt;
    }
    size++;
}
template <class Type> void Queue<Type>::pushFront (const Type &val)
{
    QueueItem<Type> *pt = new QueueItem<Type>(val);
    if (empty ())
        tail = head = pt;
    else {
        pt -> next = head;
        head = pt;
    }
    size++;
}
template <class Type> void Queue<Type>::copy_elems(const Queue &orig)
{

    for (QueueItem<Type> *pt = orig.head; pt !=0; pt=pt->next)
        push(pt->item);
}

#endif //DYNAMIC_GRAPH_VER1_QUEUE_H
