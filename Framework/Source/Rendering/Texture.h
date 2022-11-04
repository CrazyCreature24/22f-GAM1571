#pragma once


namespace fw 
{

    class Texture
    {
    public:
        Texture();
        Texture(const char* filename);
        ~Texture();

        GLuint GetTextureID() { return m_TextureID; }

    protected:
        GLuint m_TextureID = 0;


    };


}