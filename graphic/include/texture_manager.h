#ifndef GRAYVE_TEXTURE_MANAGER_H
#define GRAYVE_TEXTURE_MANAGER_H

#include "GL/glut.h"
#include <map>
#include <string>

class TextureManager {
    std::map<std::string, GLuint> textures;
    public:
    TextureManager();
    void loadTexture(std::string path, std::string name);
    void bindTexture(std::string name);
    GLuint getTexture(const std::string& name);
};
extern TextureManager *texture_manager;
#endif //GRAYVE_TEXTURE_MANAGER_H