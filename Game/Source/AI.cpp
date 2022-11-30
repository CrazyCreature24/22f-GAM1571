#include "Framework.h"
#include "GameObject.h"
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
    
}

void AI::Draw(Camera* pCamera)
{

}

void AI::AIStateIdle(float deltaTime)
{
    
}
