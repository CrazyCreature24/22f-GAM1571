#pragma once

#include "../DataTypes.h"

class GameObject
{
public:
    GameObject(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, float angle, vec2 scale);
    virtual ~GameObject();

    virtual void Update(float deltaTime);
    virtual void Draw();

protected:
    fw::Mesh* m_Mesh = nullptr;
    fw::ShaderProgram* m_Shader = nullptr;
    fw::Texture* m_Texture = nullptr;
    vec2 m_Pos = vec2(0,0);
    float m_Angle = 0;
    vec2 m_Scale = vec2(1,1);
};
