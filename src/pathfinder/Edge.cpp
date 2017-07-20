//
// Created by Tamas Szenczi on 7/20/2017.
//

#include "Edge.h"
#include "Node.h"

CEdge::CEdge(const CNode &origin, const CNode &destination, double distance) {
    _origin = &origin;
    _destination = &destination;
    _distance = distance;
}

const CNode &CEdge::getOrigin() const {
    return *_origin;
}

const CNode &CEdge::getDestination() const {
    return *_destination;
}

double CEdge::getDistance() {
    return _distance;
}
