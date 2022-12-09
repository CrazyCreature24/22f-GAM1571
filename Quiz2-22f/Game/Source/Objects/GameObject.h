#pragma once

#include "../DataTypes.h"

class fw::BaseComponent;

class GameObject
{
public:
    GameObject(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, float angle, vec2 scale);
    virtual ~GameObject();

    virtual void Update(float deltaTime);
    virtual void Draw();

protected:

    std::vector<fw::BaseComponent*> m_pComponents;

    fw::Mesh* m_Mesh = nullptr;
    fw::ShaderProgram* m_Shader = nullptr;
    fw::Texture* m_Texture = nullptr;
};
