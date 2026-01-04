//
// Created by Clef on 12/27/25.
//

#include "Texture.h"
#include <glad/glad.h>
#include "stb_image.h"


void Texture::loadTexture(int index, std::string path, unsigned int format, bool shouldFlip)
{
    int width, height, nrChannels;
    unsigned char * data;
    glGenTextures(1, &TextureIDs[index]);
    glActiveTexture(GL_TEXTURE0 +index);
    glBindTexture(GL_TEXTURE_2D, TextureIDs[index]);

    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(shouldFlip);
    data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}


void Texture::use()
{
    for (int i = 0; auto const id : TextureIDs)
    {
        glActiveTexture(GL_TEXTURE0+i);
        glBindTexture(GL_TEXTURE_2D, id);
        i++;
    }
}

