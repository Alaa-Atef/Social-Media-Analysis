#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <queue>
#include <iomanip>
using namespace std;


#ifndef GRAPH_H
#define GRAPH_H


#define INFINITY 1000



typedef struct element
{
    int Distance;
    int Node;
    int Parent;
    int Table;


}PriorityElement;



class myComparator
{
public:
    int operator() (const PriorityElement& p1, const PriorityElement& p2)
    {
        return p1.Distance > p2.Distance;
    }
};

class Graph
{

private:

    vector<list<pair<int,int> > > adj_list;
    vector<int> nodes_edges;




public:

    Graph();
    Graph(int);
    int number_nodes();
    int number_edges();
    void set_numberNode(int);
    void read_File(ifstream&,vector<pair<int,int> >&);
    void read_File(int,vector<pair<int,int> >&);
    void degree_printAll(vector<int>&);
    void print_adjacencyList();
    void shortest_Path(int,vector<int>&,vector<int>&);
	void shortest_Path(int source, vector<vector<int> >&, vector<vector<int> >&,vector<int>&);
    void closenessCentrality_printAll(vector<float>&);
    void betwenessCentrality_printAll();


};






#endif // GRAPH_H
