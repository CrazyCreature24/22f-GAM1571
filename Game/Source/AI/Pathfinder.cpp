#include "Framework.h"
#include "../Tilemap.h"
#include "Pathfinder.h"

Pathfinder::Pathfinder(Tilemap* pTilemap)
{
    m_pTilemap = pTilemap;
    m_MapWidth = pTilemap->GetMapWidth();
    m_MapHeight = pTilemap->GetMapHeight();

    m_Nodes.resize(m_MapWidth * m_MapHeight);
}

Pathfinder::~Pathfinder()
{

}

int Pathfinder::FindLowestFScore()
{
    float temp = FLT_MAX;

    int index = -1;

    for (int i = 0; i < m_Nodes.size(); i++)
    {
        if (m_Nodes[i].status == PathNode::PathNodeStatus::Open)
        {
            if (m_Nodes[i].finalCost < temp)
            {
                temp = m_Nodes[i].finalCost;
                index = i;
            }
        }
    }
    return index;
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
        int currentNodeIndex = FindLowestFScore();

        if (currentNodeIndex == -1)
        {
            return false;
        }

        PathNode* currentNode = &m_Nodes[currentNodeIndex];

        if (currentNodeIndex == endIndex)
        {
            return true;
        }

        currentNode->status = PathNode::PathNodeStatus::Closed;

        //Make neighbor array
        std::vector<int> neighbors;

        if ((currentNodeIndex) % m_MapWidth != 0 && currentNodeIndex < m_Nodes.size() - 2)
        {
            neighbors.push_back(currentNodeIndex + 1);
        }

        if ((currentNodeIndex) % m_MapWidth != m_MapWidth && currentNodeIndex > 0)
        {
            neighbors.push_back(currentNodeIndex - 1);
        }

        if (currentNodeIndex + m_MapWidth < m_MapWidth * m_MapHeight)
        {
            neighbors.push_back(currentNodeIndex + m_MapWidth);
        }

        if ((currentNodeIndex - m_MapWidth) > 0)
        {
            neighbors.push_back(currentNodeIndex - m_MapWidth);
        }

        for (auto& i : neighbors)
        {
            int neighborNodeIndex = i;


            int x = neighborNodeIndex % m_MapWidth;
            int y = neighborNodeIndex / m_MapWidth;
            if (m_Nodes[i].status != PathNode::PathNodeStatus::Closed && m_pTilemap->GetTilePropertiesAtTilePosition(iVec2(x, y)).m_Walkable)
            {
                if (m_Nodes[i].status != PathNode::PathNodeStatus::Open)
                {
                    m_Nodes[i].status = PathNode::PathNodeStatus::Open;
                }

                if (currentNode->cost + 1 < m_Nodes[i].cost)
                {

                    m_Nodes[i].parentNodeIndex = currentNodeIndex;

                    m_Nodes[i].cost = currentNode->cost + 1;
                    m_Nodes[i].heuristic = (float)(abs(ex - x) + abs(ey - y));
                    m_Nodes[i].finalCost = m_Nodes[i].cost + m_Nodes[i].heuristic;
                }
            }
        }

        
    }
}

std::vector<int> Pathfinder::GetPath(int ex, int ey)
{
    std::vector<int> path;
    int endIndex = ey * m_MapWidth + ex;

    int tempParentIndex = endIndex;

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