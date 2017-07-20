#ifndef PATHFINDINDER_CNODE_H
#define PATHFINDINDER_CNODE_H

#include <string>
using namespace std;

class CNode {
public:
    CNode(const string &name);

    const string& getName() const;
private:
    string _name;
};


#endif //PATHFINDINDER_CNODE_H
