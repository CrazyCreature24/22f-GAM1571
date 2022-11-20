#include "CoreHeaders.h"
#include "SpriteSheet.h"
#include "FlipBook.h"

namespace fw
{
    FlipBook::FlipBook(const std::vector<SpriteAnimInfo*>& sprites) :
        m_pSprites(sprites)
    {
        //Sets Default Sprite and FrameTime
        m_ActiveSprite = m_pSprites[m_Index]->sprite;
        m_FrameTime = m_pSprites[m_Index]->timePerFrame;
    }

    FlipBook::~FlipBook()
    {

    }

    void FlipBook::Update(float deltaTime)
    {
        m_Elapsed += deltaTime;
    }

    void FlipBook::Animation()
    {
        if (m_Elapsed >= m_FrameTime)
        {
            if (m_ActiveSprite != m_pSprites[m_pSprites.size() - 1]->sprite)
            {
                m_Index++;
            }
            else
            {
                m_Index = 0;
            }
            m_ActiveSprite = m_pSprites[m_Index]->sprite;
            m_FrameTime = m_pSprites[m_Index]->timePerFrame;

            m_Elapsed = 0.0f;
        }
    }
}