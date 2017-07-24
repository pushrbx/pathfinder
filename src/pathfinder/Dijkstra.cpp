#include "Dijkstra.h"
#include <boost/foreach.hpp>
#include <boost/range/algorithm_ext/erase.hpp>
#include <float.h>

CDijkstra::CDijkstra(const vector<std::shared_ptr<CEdge>> &edges, const vector<std::shared_ptr<CNode>> &nodes)
{
    _edges = edges;
    _nodes = nodes;

    for (vector<std::shared_ptr<CNode>>::iterator it; it != _nodes.end(); ++it)
    {
        shared_ptr<CNode> n = *it;
        _previous.emplace(n->getName(), nullptr);
        _basis.push_back(n);
        _dist.emplace(n->getName(), DBL_MAX);
    }
}

void CDijkstra::calculateDistance(const CNode &start)
{
    _dist[start.getName()] = 0;

    while (_basis.size() > 0)
    {
        shared_ptr<CNode> u = getNodeWithSmallestDistance();

        if (u == nullptr)
            _basis.clear();
        else
        {
            const CNode nodeWithSmallestDistance = *u;
            const vector<CNode> neighbours = getNeighbours(nodeWithSmallestDistance);
            BOOST_FOREACH(CNode v, neighbours)
            {
                double alt = _dist[u->getName()] + getDistanceBetween(nodeWithSmallestDistance, v);
                if (alt < _dist[v.getName()])
                {
                    _dist[v.getName()] = alt;
                    _previous[v.getName()] = u;
                }
            }

            boost::remove_erase(_basis, nodeWithSmallestDistance);
        }
    }
}

const vector<std::shared_ptr<CNode>> CDijkstra::getPathTo(CNode &destination)
{
    vector<std::shared_ptr<CNode>> path;
    std::shared_ptr<CNode> d = make_shared<CNode>(destination.getName());
    path.push_back(d);

    while (_previous[d->getName()] != nullptr)
    {
        d = _previous[d->getName()];
        path.insert(path.begin(), d);
    }

    return path;
}

std::shared_ptr<CNode> CDijkstra::getNodeWithSmallestDistance()
{
    double distance = DBL_MAX;
    shared_ptr<CNode> psmallest(nullptr);

    for (auto it = _basis.begin(); it != _basis.end(); ++it)
    {
        shared_ptr<CNode> n = *it;

        if (_dist[n->getName()] < distance)
        {
            distance = _dist[n->getName()];
            psmallest = n;
        }
    }

    return psmallest;
}

const vector<CNode> CDijkstra::getNeighbours(const CNode &n)
{
    vector<CNode> neighbours;

    for (auto it = _edges.begin(); it != _edges.end(); ++it)
    {
        shared_ptr<CEdge> e = *it;
        if (e->getOrigin().getName() == n.getName()
            && std::find(_basis.begin(), _basis.end(), n) != _basis.end())
        {
            neighbours.push_back(e->getDestination());
        }
    }

    return neighbours;
}

double CDijkstra::getDistanceBetween(const CNode &o, const CNode &d)
{
    for (auto it = _edges.begin(); it != _edges.end(); ++it)
    {
        shared_ptr<CEdge> e = *it;
        // note: the comparison can be done through reference address comparison, it might be quicker
        if (e->getOrigin().getName() == o.getName()
                && e->getDestination().getName() == d.getName())
        {
            return e->getDistance();
        }
    }

    return 0;
}

const vector<std::shared_ptr<CNode>> &CDijkstra::getNodes() const
{
    return _nodes;
}

const vector<std::shared_ptr<CEdge>> &CDijkstra::getEdges() const
{
    return _edges;
}

const vector<std::shared_ptr<CNode>> &CDijkstra::getBasis() const
{
    return _basis;
}

const map<string, double> &CDijkstra::getDistances() const
{
    return _dist;
}

const map<string, std::shared_ptr<CNode>> &CDijkstra::getPreviousNodes()
{
    return _previous;
}
