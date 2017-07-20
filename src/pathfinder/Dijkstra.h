//
// Created by Tamas Szenczi on 7/20/2017.
//

#ifndef PATHFINDER_DIJKSTRA_H
#define PATHFINDER_DIJKSTRA_H

#include <vector>
#include <map>
#include <string>
#include "Edge.h"
#include "Node.h"

using namespace std;

class CDijkstra {
public:
    CDijkstra(const vector<CEdge> &edges, const vector<CNode> &nodes);

    void calculateDistance(const CNode &start);

private:
    const vector<CEdge> _edges;
    const vector<CNode> _nodes;
    const vector<CNode> _basis;

    const map<string, double> _dist;
    const map<string, CNode> _previous;
};


#endif //PATHFINDER_DIJKSTRA_H
