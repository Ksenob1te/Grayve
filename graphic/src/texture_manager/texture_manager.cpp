#include "texture_manager.h"
#include <SOIL/SOIL.h>
#include <exception>
void TextureManager::loadTexture(std::string path, std::string name){
    GLuint texture;
    texture = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if(texture == 0)
        throw std::exception();
    this->textures[name]= texture; 
}

GLuint TextureManager::getTexture(std::string name){
    return this->textures[name];
}

TextureManager::TextureManager(){
    loadTexture("assets/sprites/mage.png", "enemy");
    loadTexture("assets/sprites/player.png", "player");
}

TextureManager *texture_manager;