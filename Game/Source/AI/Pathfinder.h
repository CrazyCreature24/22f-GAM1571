#pragma once

struct PathNode
{
    enum class PathNodeStatus
    {
        Unchecked,
        Open,
        Closed
    };

    int index;
    
    int parentNodeIndex;
    PathNodeStatus status;

    float totalCost; //Cost to get to the node
    float heuristic; //Heuristic: Manhatten distance to the destiation
    float finalCost; //Sum of 2 values above.

};

class Pathfinder
{
protected:




};