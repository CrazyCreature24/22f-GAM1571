#include "Framework.h"
#include "../GameObject.h"
#include "AI.h"

AI::AI()
{
    m_pMethodPointer = &AI::AIStateIdle;
}

AI::~AI()
{

}

void AI::Update(float deltaTime)
{
    (this->*m_pMethodPointer)(deltaTime);
}

void AI::Draw(Camera* pCamera)
{

}

void AI::AIStateIdle(float deltaTime)
{
    m_IdleTimer += deltaTime;

    if (m_IdleTimer >= 2.0f)
    {
        m_pMethodPointer = &AI::AIStateWalking;
        m_IdleTimer = 0.0f;
    }
}

void AI::AIStateWalking(float deltaTime)
{

}
