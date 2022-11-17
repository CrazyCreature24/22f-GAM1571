#pragma once
#include "DataTypes.h"

struct fw::SpriteInfo;
class VirtualController;

class Player : public GameObject
{
public:
    Player(fw::Mesh* pMesh, fw::ShaderProgram* pShaderProgram, fw::Texture* pTexture, SpriteSheet* pSpriteSheet);
    ~Player();

    virtual void Update(float deltaTime) override;
    virtual void Draw(Camera* pCamera) override;

    void OnKeyEvent(VirtualController* controller, float deltaTime);

protected:
    Vec2 m_UVScale = { 1, 1 };
    Vec2 m_UVOffset = { 0, 0 };


    std::map<string, SpriteInfo*> m_Sprites;
    SpriteInfo* m_pActiveSprite = nullptr;

};