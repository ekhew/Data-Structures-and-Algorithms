/*
Title: Undirected Graph (Adjacency Matrix) Vertex
Author: Edwin Khew
Description: Undirected graph (adjacency matrix) vertex class declaration.
Date Created: 7/16/2021
*/

#ifndef VERTEX_H_
#define VERTEX_H_

template <class ItemType>
class Vertex
{
public:
    /*
        default constructor
    */
    Vertex();

    /*
        parameterized constructor
    */
    Vertex(ItemType item);

    /*
        sets the item in the vertex to the specified item
        @param item, item to be set in the vertex
    */
    void setItem(ItemType item);

    /*
        returns the item of the calling vertex
        @return 'item_'
    */
    ItemType getItem() const;

    /*
        operator overload of '<'; needed for maps
        @param v, vertex to compare with the calling vertex
        @return true if the parameter vertex is less than the calling vertex, and false otherwise
    */
    bool operator < (const Vertex& v) const;

    /*
        operator overload of '=='; needed for maps
        @param v, vertex to compare with the calling vertex
        @return true if the parameter vertex is equal to the calling vertex, and false otherwise
    */
    bool operator == (const Vertex& v) const;
private:
    ItemType item_; //item that is stored in the vertex
};

#include "Vertex.cpp"
#endif
