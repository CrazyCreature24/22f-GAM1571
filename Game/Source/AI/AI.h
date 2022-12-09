#pragma once

struct fw::SpriteInfo;
class Tilemap;
struct TileProperties;

class AI : public GameObject
{
public:
    typedef void (AI::*AIStateFunction)(float deltaTime);


    AI(fw::Mesh* pMesh, fw::ShaderProgram* pShaderProgram, fw::Texture* pTexture, SpriteSheet* pSpriteSheet, Tilemap* pTilemap);
    virtual ~AI();

    virtual void Update(float deltaTime);
    virtual void Draw(Camera* pCamera);

    void AIStateIdle(float deltaTime);
    void AIStateWalking(float deltaTime);

protected:

    Tilemap* m_pTilemap;
    fw::SpriteInfo* m_pActiveSprite = nullptr;

    AIStateFunction m_pMethodPointer;
    
    float m_IdleTimer = 0.0f;
    float m_Speed = 5.0f;

    iVec2 m_NextTileLocation = { 0, 0 };
    Vec2 m_NextWorldPosition = { 0, 0 };

    iVec2 m_NextDestination = { 0, 0 };
    iVec2 m_Destination1 = { 1, 8 };
    iVec2 m_Destination2 = { 3, 8 };
    iVec2 m_Destination3 = { 3, 1 };
    iVec2 m_Destination4 = { 2, 2 };


};