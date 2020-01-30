cmake_minimum_required(VERSION 3.15)
project(dynamic_graph_ver1)

set(CMAKE_CXX_STANDARD 14)

add_executable(dynamic_graph_ver1 main.cpp Graph_Node.cpp Graph_Node.h Graph_Edge.cpp Graph_Edge.h Dynamic_Graph.cpp Dynamic_Graph.h Queue.cpp Queue.h QueueItem.cpp QueueItem.h Rooted_Tree.cpp Rooted_Tree.h Tree_Node.cpp Tree_Node.h)