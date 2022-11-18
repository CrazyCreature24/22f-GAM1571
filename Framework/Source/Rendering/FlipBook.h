#pragma once


namespace fw
{
    struct SpriteInfo;

    struct SpriteAnimInfo
    {

        SpriteInfo* sprite = nullptr;
        float timePerFrame = 0.0f;

        SpriteAnimInfo(SpriteInfo* spriteInfo, float nTimePerFrame) : sprite(spriteInfo), timePerFrame(nTimePerFrame) {}
    };


    class FlipBook
    {
    public:
        FlipBook(const std::vector<SpriteAnimInfo*>& sprites);
        ~FlipBook();

        void Update(float deltaTime);

        void Animation();

        void SetTimer(float timer) { m_Timer = timer; }
        void ResetElapsed() { m_Elapsed = 0.0f; }

        SpriteInfo* GetActiveSprite() { return m_ActiveSprite; }

    protected:

        std::vector<SpriteAnimInfo*> m_pSprites;



        std::map<std::string, SpriteInfo*> m_Sprites;
        SpriteInfo* m_ActiveSprite = nullptr;

        float m_Timer = 0.3f; 
        float m_Elapsed = 0.0f;
        int m_Index = 0;

    };
}