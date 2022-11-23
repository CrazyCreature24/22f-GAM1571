#include "Framework.h"
#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::GameObject(fw::Mesh* pMesh, fw::ShaderProgram* pShaderProgram, float timeElapsed, fw::Texture* pTexture, SpriteSheet* pSpriteSheet)
{
	
	m_pMesh = pMesh;
	m_pShaderProgram = pShaderProgram;
	m_TimeElapsed = timeElapsed;
	m_pTexture = pTexture;
	m_pSpriteSheet = pSpriteSheet;


	m_pSpriteInfo = new SpriteInfo("LinkWalkLeft1", pSpriteSheet->GetUVScale("LinkWalkLeft1") / pSpriteSheet->GetSizePicture(), pSpriteSheet->GetUVOffset("LinkWalkLeft1") / pSpriteSheet->GetSizePicture());

}

GameObject::~GameObject()
{
	delete m_pSpriteInfo;
}

void GameObject::Update(float deltaTime)
{

}

void GameObject::Draw(Camera* pCamera)
{
	m_pMesh->Draw(m_pShaderProgram, m_Scale, m_Angle, m_Position, m_TimeElapsed, m_pTexture, pCamera, m_pSpriteInfo->UVScale, m_pSpriteInfo->UVOffset);
}
