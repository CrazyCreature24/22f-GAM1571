#include "Tilemap.h"
#include "Pathfinder.h"

Pathfinder::Pathfinder(Tilemap* pTilemap)
{
    m_pTilemap = pTilemap;
    m_MapWidth = pTilemap->GetWidth();
    m_MapHeight = pTilemap->GetHeight();

    m_Nodes.resize(m_MapWidth * m_MapHeight);
}

Pathfinder::~Pathfinder()
{

}

PathNode* Pathfinder::FindLowestSomething()
{
    PathNode* currentNode = nullptr;

    float temp = FLT_MAX;

    for (int i = 0; i < m_Nodes.size(); i++)
    {
        if (m_Nodes[i].status == PathNode::PathNodeStatus::Open)
        {
            if (m_Nodes[i].finalCost < temp)
            {
                currentNode = &m_Nodes[i];
                temp = m_Nodes[i].finalCost;
            }
        }
    }
    return currentNode;
}

bool Pathfinder::FindPath(int sx, int sy, int ex, int ey)
{
    for (auto& i : m_Nodes)
    {
        i.cost = FLT_MAX;
        i.finalCost = FLT_MAX;
        i.heuristic = FLT_MAX;
        i.parentNodeIndex = -1;
        i.status = PathNode::PathNodeStatus::Unchecked;
    }


    int startIndex = sy * m_MapWidth + sx;
    int endIndex = ey * m_MapWidth + ex;

    m_Nodes[startIndex].cost = 0.0f;
    m_Nodes[startIndex].finalCost = 0.0f;
    m_Nodes[startIndex].status = PathNode::PathNodeStatus::Open;

    while (true)
    {
        PathNode* currentNode = FindLowestSomething();

        if (currentNode == nullptr || currentNode == &m_Nodes[endIndex])
        {
            return;
        }



    }

   /* m_Nodes[i].status = PathNode::PathNodeStatus::Unchecked;

    if (i == endIndex)
    {
        return true;
    }

    m_Nodes[i].status = PathNode::PathNodeStatus::Closed;

    PathNode neighbors[4] = {
        {m_Nodes[i + m_MapWidth]},
        {m_Nodes[i - m_MapWidth]},
        {m_Nodes[i + 1]},
        {m_Nodes[i + -1]}
    };

    for (int j = 0; j < 4; j++)
    {


        if (neighbors[j].status != PathNode::PathNodeStatus::Open)
        {
            neighbors[j].status = PathNode::PathNodeStatus::Open;
        }

        float tempCost = m_Nodes[i].cost + 1;

        if (tempCost < neighbors[j].cost)
        {
            neighbors[j].parentNodeIndex = currentNode.parentNodeIndex;

        }
    }

    continue;

}
        }
    }


    return false;*/
}

std::vector<int> Pathfinder::GetPath(int ex, int ey)
{
    std::vector<int> path;

    return path;
}
