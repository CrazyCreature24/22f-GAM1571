#include "CoreHeaders.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Libraries/stb/stb_image.h"

namespace fw {

    Texture::Texture()
    {
        const int w = 8;
        const int h = 8;
        unsigned char pixels[w * h * 4] = {0};

        pixels[4 * 4] = 255;

        glGenTextures(1, &m_TextureID);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }

    Texture::Texture(const char* filename)
    {
        int x,y,n;
        stbi_set_flip_vertically_on_load( true );
        unsigned char* data = stbi_load( filename, &x, &y, &n, 4 );
        assert( data != nullptr );

        glGenTextures( 1, &m_TextureID );

        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, m_TextureID );

        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

        stbi_image_free( data );
    }

    Texture::~Texture()
    {
    }

}
