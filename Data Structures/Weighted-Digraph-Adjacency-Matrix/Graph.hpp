/*
Title: Weighted Digraph (Adjacency Matrix)
Author: Edwin Khew
Description: Weighted digraph (adjacency matrix) class declaration.
Date Created: 7/20/2021
*/

#ifndef GRAPH_H_
#define GRAPH_H_

#include <map>
#include <climits>

template <class ItemType>
class Graph
{
public:
    /*
        default constructor
    */
    Graph();

    /*
        adds a new vertex into the graph
        @param item, the new vertex to add into the graph
    */
    void addVertex(ItemType item);

    /*
        removes a vertex from the graph
        @param item, vertex to remove from the graph
    */
    void removeVertex(ItemType item);

    /*
        adds an edge connecting two specified vertices
        @param item1, first vertex
        @param item2, second vertex
    */
    void addEdge(ItemType item1, ItemType item2, int weight);

    /*
        removes an edge connecting two specified vertices
        @param item1, first vertex
        @param item2, second vertex
    */
    void removeEdge(ItemType item1, ItemType item2);

    /*
        checks if the graph is currently empty
        @return true if the graph is empty, and false otherwise
    */
    bool isEmpty() const;

    /*
        checks if two specified vertices are adjacent
        @param item1, first vertex
        @param item2, second vertex
        @return true if the vertices are adjacent, and false otherwise
    */
    bool checkAdj(ItemType item1, ItemType item2) const;

    /*
        prints every adjacent vertex of the specified vertex
        @param item, the vertex to print every adjacent vertex of
    */
    void printAdjVertices(ItemType item) const;

    /*
        traverses the graph using BFS and prints every vertex
        @param start, the vertex to start the traversal from
    */
    void BFS(ItemType start) const;

    /*
        traverses the graph using DFS and prints every vertex; iterative approach
        @param start, the vertex to start the traversal from
    */
    void iterativeDFS(ItemType start) const;

    /*
        traverses the graph using DFS and prints every vertex; recursive approach
        @param start, the vertex to start the traversal from
    */
    void recursiveDFS(ItemType start) const;

    /*
        performs Dijkstra's shortest path algorithm using the specified source vertex
        @param source, the vertex to start the algorithm from
    */
    void dijkstra(ItemType source) const;

    /*
        returns the current vertex count
        @return 'vertex_count_'
    */
    int getVertexCount() const;

    /*
        prints out every adjacency list that makes up the graph
    */
    void display() const;
private:
    int vertex_count_; //current number of vertices in the graph
    int matrix_size_; //size of the matrix; number of rows and columns
    int **matrix_; //adjacency matrix; dynamic 2D array
    static const int NULL_EDGE_ = INT_MAX; //for indices where an edge does not exist
    std::map<Vertex<ItemType>, int> vertex_map_; //map that associates a vertex with an index; key = vertex, value = index
    int next_index_; //the next available index; used for inserting and removing vertices

    /*
        traverses the graph using DFS and prints every vertex; recursive approach
        @param curr_vertex, the current vertex being visited
        @param visited_map, map used to keep track of visited vertices; key = vertex and value = 'true'
    */
    void recursiveDFSHelper(ItemType curr_vertex, std::map<Vertex<ItemType>, bool> *visited_map) const;

    /*
        increases the size of the matrix to accommodate for more new vertices
    */
    void expandMatrix();

    /*
        Dijkstra's algorithm helper; finds the unvisited vertex with the smallest current path and returns its index
        @param paths[], array of shortest paths
        @param visited[], array used to keep track of visited vertices
        @return index of the unvisited vertex with the shortest path
    */
    int minDistance(int paths[], bool visited[]) const;

    /*
        displays the resulting shortest paths of Dijkstra's algorithm
        @param paths[], array of shortest paths
    */
    void dijkstraDisplay(int paths[]) const;
};

#include "Graph.cpp"
#endif
