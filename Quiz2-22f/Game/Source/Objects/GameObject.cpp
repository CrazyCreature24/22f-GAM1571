#include "Framework.h"
#include "GameObject.h"

GameObject::GameObject(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, float angle, vec2 scale)
    : m_Mesh( pMesh )
    , m_Shader( pShader )
    , m_Texture( pTexture )
    , m_Pos( pos )
    , m_Angle( angle )
    , m_Scale( scale )
{
}

GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::Draw()
{
    m_Mesh->Draw( m_Shader, m_Texture, m_Pos, m_Angle, m_Scale, 1 );
}
