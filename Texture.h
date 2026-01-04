//
// Created by Clef on 12/27/25.
//

#ifndef OPENGLSETUP_TEXTURE_H
#define OPENGLSETUP_TEXTURE_H

#include <string>
#include <vector>


class Texture
{
public:
    Texture() : TextureIDs(16) {}
    void loadTexture(int index, std::string path, unsigned int format, bool shouldFlip);
    void use();
    std::vector<unsigned int> TextureIDs;
};


#endif //OPENGLSETUP_TEXTURE_H