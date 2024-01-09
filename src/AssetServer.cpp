#include "AssetServer.hpp"
#include <cstring>

const string AssetServer::texturePath = "assets/textures/";
const string AssetServer::soundPath = "assets/soundfx/";

AssetServer::AssetServer(){ }

AssetServer::~AssetServer(){
    
}

Texture2D AssetServer::load_texture(string filename){
    if(textures.count(filename) == 0){
        textures[filename] = LoadTexture((texturePath + filename).c_str());
    }
    return textures[filename];
}

Sound AssetServer::load_sound(string filename){
    if(sounds.count(filename) == 0){
        sounds[filename] = LoadSound((soundPath + filename).c_str());
    }
    return sounds[filename];
}