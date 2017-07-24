#ifndef PATHFINDER_DIJKSTRA_H
#define PATHFINDER_DIJKSTRA_H

#include <vector>
#include <map>
#include <string>
#include "Edge.h"
#include "Node.h"
#include <memory>

using namespace std;

class CDijkstra {
public:
    CDijkstra(const vector<std::shared_ptr<CEdge>> &edges, const vector<std::shared_ptr<CNode>> &nodes);

    void calculateDistance(const CNode &start);

    const vector<std::shared_ptr<CNode>> getPathTo(CNode &destination);

    std::shared_ptr<CNode> getNodeWithSmallestDistance();

    const vector<CNode> getNeighbours(const CNode &n);

    double getDistanceBetween(const CNode &o, const CNode &d);

    const vector<std::shared_ptr<CNode>>& getNodes() const;

    const vector<std::shared_ptr<CEdge>>& getEdges() const;

    const vector<std::shared_ptr<CNode>>& getBasis() const;

    const map<string, double>& getDistances() const;

    const map<string, std::shared_ptr<CNode>>& getPreviousNodes();

private:
    vector<std::shared_ptr<CEdge>> _edges;
    vector<std::shared_ptr<CNode>> _nodes;
    vector<std::shared_ptr<CNode>> _basis;

    map<string, double> _dist;
    map<string, std::shared_ptr<CNode>> _previous;
};


#endif //PATHFINDER_DIJKSTRA_H
