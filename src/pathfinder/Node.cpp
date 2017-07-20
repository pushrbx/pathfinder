#include "Node.h"

CNode::CNode(const string &name)
{
    _name = name;
}

const string& CNode::getName() const
{
    return _name;
}