#pragma once
#include "DataTypes.h"

struct fw::SpriteInfo;
struct fw::SpriteAnimInfo;
class fw::FlipBook;
class VirtualController;
class Tilemap;
struct TileProperties;

class Player : public GameObject
{
public:
    Player(fw::Mesh* pMesh, fw::ShaderProgram* pShaderProgram, fw::Texture* pTexture, SpriteSheet* pSpriteSheet, Tilemap* pTilemap);
    ~Player();

    virtual void Update(float deltaTime) override;
    virtual void Draw(Camera* pCamera) override;

    void OnKeyEvent(VirtualController* controller, float deltaTime);

protected:
    SpriteInfo* m_pActiveSprite = nullptr;

    std::map<string, fw::FlipBook*> m_Animations;

    std::vector<fw::SpriteAnimInfo*> m_MoveLeftAnim;
    std::vector<fw::SpriteAnimInfo*> m_MoveRightAnim;
    std::vector<fw::SpriteAnimInfo*> m_MoveUpAnim;
    std::vector<fw::SpriteAnimInfo*> m_MoveDownAnim;

    Tilemap* m_pTilemap = nullptr;
    TileProperties* m_pTileProperties = nullptr;

};