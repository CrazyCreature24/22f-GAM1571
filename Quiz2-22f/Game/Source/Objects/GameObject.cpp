#include "Framework.h"
#include "GameObject.h"

GameObject::GameObject(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, float angle, vec2 scale)
    : m_Mesh( pMesh )
    , m_Shader( pShader )
    , m_Texture( pTexture )
{
    m_pComponents.push_back(new fw::Transform(pos, scale, angle));
    m_pComponents.push_back(new fw::Renderable(pMesh, pTexture, pShader));

}

GameObject::~GameObject()
{
    for (auto& i : m_pComponents)
    {
        delete i;
    }
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::Draw()
{
    fw::Transform* transform = nullptr;
    fw::Renderable* renderable = nullptr;

    for (auto i : m_pComponents)
    {
        if (dynamic_cast<fw::Transform*>(i) != nullptr)
        {
            transform = dynamic_cast<fw::Transform*>(i);
        }
        else if (dynamic_cast<fw::Renderable*>(i) != nullptr)
        {
            renderable = dynamic_cast<fw::Renderable*>(i);
        }
    }

    if (transform != nullptr && renderable != nullptr)
    {
        renderable->pMesh->Draw(renderable->pShaderProgram, renderable->pTexture, transform, 1);
    }
}
