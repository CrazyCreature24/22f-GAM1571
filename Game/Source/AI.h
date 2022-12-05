#pragma once



class AI : public GameObject
{
public:
    typedef void (AI::*AIStateFunction)(float deltaTime);


    AI();
    virtual ~AI();

    virtual void Update(float deltaTime);
    virtual void Draw(Camera* pCamera);

    void AIStateIdle(float deltaTime);

protected:
    AIStateFunction m_pMethodPointer;
    

};