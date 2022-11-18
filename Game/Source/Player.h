#pragma once
#include "DataTypes.h"

struct fw::SpriteInfo;
struct fw::SpriteAnimInfo;
class fw::FlipBook;
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

    std::map<string, SpriteInfo*> m_Sprites;
    SpriteInfo* m_pActiveSprite = nullptr;

    std::map<string, fw::FlipBook*> m_FlipBooks;
    std::vector<fw::SpriteInfo*> m_MoveLeft;
    std::vector<fw::SpriteInfo*> m_MoveRight;
    std::vector<fw::SpriteInfo*> m_MoveUp;
    std::vector<fw::SpriteInfo*> m_MoveDown;

    std::vector<fw::SpriteAnimInfo*> m_MoveLeftAnim;
    std::vector<fw::SpriteAnimInfo*> m_MoveRightAnim;
    std::vector<fw::SpriteAnimInfo*> m_MoveUpAnim;
    std::vector<fw::SpriteAnimInfo*> m_MoveDownAnim;

};