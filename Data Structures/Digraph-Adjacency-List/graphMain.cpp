/*
Title: Digraph (Adjacency List)
Author: Edwin Khew
Description: Digraph (adjacency list) test file.
Date Created: 7/16/2021
*/

#include <iostream>
#include "Vertex.hpp"
#include "Graph.hpp"

using namespace std;

int main()
{
    Graph<string> myGraph;

    myGraph.addVertex("Aa");
    myGraph.addVertex("Bb");
    myGraph.addVertex("Cc");
    myGraph.addVertex("Dd");
    myGraph.addVertex("Ee");

    myGraph.addEdge("Bb", "Aa");
    myGraph.addEdge("Aa", "Cc");
    myGraph.addEdge("Aa", "Dd");
    myGraph.addEdge("Bb", "Cc");
    myGraph.addEdge("Ee", "Cc");
    myGraph.addEdge("Yy", "Zz"); //vertices do not exists

    //myGraph.removeVertex("Cc");
    //myGraph.removeVertex("Zz"); //vertex does not exists

    //myGraph.removeEdge("Cc", "Dd");
    //myGraph.removeEdge("Aa", "Cc"); //edge does not exist
    //myGraph.removeEdge("Yy", "Zz"); //vertices do not exists

    cout << "Is Empty: " << myGraph.isEmpty() << endl;
    cout << "Check Adjacency: " << myGraph.checkAdj("Dd", "Aa") << endl;
    cout << "Adjacent Vertices: ";
    myGraph.printAdjVertices("Aa");
    cout << endl << "BFS: ";
    myGraph.BFS("Aa");
    cout << endl << "DFS (Iterative): ";
    myGraph.iterativeDFS("Aa");
    cout << endl << "DFS (Recursive): ";
    myGraph.recursiveDFS("Aa");
    cout << endl << "Display: " << endl << endl;

    myGraph.display();
}
