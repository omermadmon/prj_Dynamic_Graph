//
// Created by omerm on 1/4/2020.
//

#ifndef DYNAMIC_GRAPH_VER1_QUEUEITEM_H
#define DYNAMIC_GRAPH_VER1_QUEUEITEM_H

#include <cstddef>

template <class Type> class Queue;
template <class Type> class QueueItem
{
    friend class Queue<Type>;

private:
    QueueItem (const Type &t) : item(t), next(0) { }
    Type item;
    QueueItem *next;
};

#endif //DYNAMIC_GRAPH_VER1_QUEUEITEM_H
