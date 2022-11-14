#include "Framework.h"
#include "SpriteSheet.h"
#include "GameObject.h"

GameObject::GameObject(fw::Mesh* pMesh, fw::ShaderProgram* pShaderProgram, float timeElapsed, fw::Vec2 resolution, fw::Texture* pTexture, SpriteSheet* pSpriteSheet)
{
	
	m_pMesh = pMesh;
	m_pShaderProgram = pShaderProgram;
	m_TimeElapsed = timeElapsed;
	m_Resolution = resolution;
	m_pTexture = pTexture;
	m_pSpriteSheet = pSpriteSheet;


	m_pSpriteInfo = new SpriteInfo("WalkLeft1", pSpriteSheet->GetUVScale("WalkLeft1"), pSpriteSheet->GetUVOffset("WalkLeft1"));

}

GameObject::~GameObject()
{
	delete m_pSpriteInfo;
}

void GameObject::Update()
{

}

void GameObject::Draw(float color[])
{
	m_pMesh->Draw(m_pShaderProgram, m_Scale, m_Angle, m_Position, m_TimeElapsed, m_Resolution, color, m_pTexture);
}


//TODO: Find out how to deal with TimeElapsed and Resolution better //Camera does this