// BOUHENAF Irfan IP TP3
#include <iostream>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#ifndef GRAPH_HPP
#define GRAPH_HPP
class Graph
{
    private:
        std::unordered_map<int, std::unordered_set<int>> map; 
    public:
        Graph();
        ~Graph();
        void addVertex(int);
        void addEdge(int,int);
        bool containsVertex(int) const;
        bool containsEdge(int,int) const;
        int degree(int) const;
        int maxDegree() const;
        int countVertices() const;
        int countEdges() const;
        void removeEdge(int,int);
        void removeVertex(int);
        void contract(int,int);
        std::vector<int> neighbors(int) const;
        std::vector<int> commonNeighbors(int,int) const;
        std::vector<int> dfs(int) const;
        void searchdfs(std::vector<int> &,std::map<int,bool>&,int) const;
        std::vector<int> bfs(int) const;
        void searchbfs(std::vector<int> &,std::map<int,bool>&,int) const;
        

};
#endif