#include "texture_manager.h"
#include <SOIL/SOIL.h>
#include <exception>
void TextureManager::loadTexture(std::string path, std::string name){
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int width, height, channels;
    unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, &channels, SOIL_LOAD_RGBA);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    SOIL_free_image_data(image);

    glBindTexture(GL_TEXTURE_2D, 0);
    this->textures[name]= texture; 
}

GLuint TextureManager::getTexture(std::string name){
    return this->textures[name];
}

void TextureManager::bindTexture(std::string name){
}

TextureManager::TextureManager(){
    loadTexture("assets/sprites/mage.png", "enemy");
    loadTexture("assets/sprites/player.png", "player");
}



TextureManager *texture_manager;