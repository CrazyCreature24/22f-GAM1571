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

PathNode* Pathfinder::FindLowestFScore()
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
        PathNode* currentNode = FindLowestFScore();

        //Find the index of current node
        int currentNodeIndex = 0;
        for (int i = 0; i < m_Nodes.size(); i++)
        {
            if (currentNode == &m_Nodes[currentNodeIndex])
            {
                break;
            }
            currentNodeIndex++;
        }

        if (currentNode == nullptr)
        {
            return false;
        }

        currentNode->status = PathNode::PathNodeStatus::Closed;

        if (currentNode == &m_Nodes[endIndex])
        {
            return true;
        }
        
        //Make neighbor array
        std::vector<PathNode*> neighbors;

        if ((currentNodeIndex) % m_MapWidth != 0)
        {
            neighbors.push_back(&m_Nodes[currentNodeIndex + 1]);
        }

        if ((currentNodeIndex) % m_MapWidth != m_MapWidth)
        {
            neighbors.push_back(&m_Nodes[currentNodeIndex - 1]);
        }

        if (currentNodeIndex + m_MapWidth < m_MapWidth * m_MapHeight)
        {
            neighbors.push_back(&m_Nodes[currentNodeIndex + m_MapWidth]);
        }

        if ((currentNodeIndex - m_MapWidth) > 0)
        {
            neighbors.push_back(&m_Nodes[currentNodeIndex - m_MapWidth]);
        }

        for (auto& i : neighbors)
        {
            int neighborNodeIndex = 0;
            for (int j = 0; j < m_Nodes.size(); j++)
            {
                if (i == &m_Nodes[neighborNodeIndex])
                {
                    break;
                }
                neighborNodeIndex++;
            }

            int x = neighborNodeIndex % m_MapWidth;
            int y = neighborNodeIndex / m_MapWidth;
            if (i->status != PathNode::PathNodeStatus::Closed && m_pTilemap->IsTileWalkableAtTilePos(x, y))
            {
                if (i->status != PathNode::PathNodeStatus::Open)
                {
                    i->status = PathNode::PathNodeStatus::Open;
                }

                if (currentNode->cost + 1 < i->cost)
                {

                    i->parentNodeIndex = currentNodeIndex;

                    i->cost = currentNode->cost + 1;
                    i->heuristic = abs(ex - x) + abs(ey- y);
                    i->finalCost = i->cost + i->heuristic;
                }
            }
        }

    }
}

std::vector<int> Pathfinder::GetPath(int ex, int ey)
{
    std::vector<int> path;
    int endIndex = ey * m_MapWidth + ex;

    int tempParentIndex = m_Nodes[endIndex].parentNodeIndex;

    path.push_back(tempParentIndex);

    while (tempParentIndex != -1)
    {
        if (m_Nodes[tempParentIndex].parentNodeIndex != -1)
        {
            path.push_back(m_Nodes[tempParentIndex].parentNodeIndex);
        }


        tempParentIndex = m_Nodes[tempParentIndex].parentNodeIndex;
    }

    return path;
}
