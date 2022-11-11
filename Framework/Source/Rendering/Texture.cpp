#include "CoreHeaders.h"
#include "Rendering/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Libraries/stb/stb_image.h"

namespace fw
{

    Texture::Texture()
    {
        const int width = 8;
        const int height = 8;
        unsigned char temp[(width * height) * 4];
        int index = 0;
        bool colorChange = true;

        for (int i = 0; i < height; i++)
        {
            colorChange = !colorChange;
            for (int j = 0; j < width; j++)
            {
                if (colorChange)
                {
                    temp[index] = 255;
                    temp[index + 1] = 255;
                    temp[index + 2] = 255;
                    temp[index + 3] = 255;

                    colorChange = !colorChange;
                }
                else if (!colorChange)
                {
                    temp[index] = 0;
                    temp[index + 1] = 0;
                    temp[index + 2] = 0;
                    temp[index + 3] = 0;

                    colorChange = !colorChange;
                }
                index += 4;

                
            }
        }

        glGenTextures(1, &m_TextureID);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, temp);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    }

    Texture::Texture(const char* filename)
    {
            int x, y, n;
            stbi_set_flip_vertically_on_load(true);
            unsigned char *data = stbi_load(filename, &x, &y, &n, 4);
            
            if (data == nullptr)
            {
                Texture();
                return;
            }

            assert( data != nullptr );

            glGenTextures(1, &m_TextureID);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_TextureID);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
     
            stbi_image_free(data);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_TextureID);
    }


}