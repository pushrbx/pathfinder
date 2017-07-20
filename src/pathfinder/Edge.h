#ifndef PATHFINDINDER_EDGE_H
#define PATHFINDINDER_EDGE_H

class CNode;

class CEdge {
public:
    CEdge(const CNode& origin, const CNode& destination, double distance);

    const CNode &getOrigin() const;

    const CNode &getDestination() const;

    double getDistance();

private:
    const CNode *_origin;
    const CNode *_destination;
    double _distance;
};


#endif //PATHFINDINDER_EDGE_H
