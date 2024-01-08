#include "AssetServer.hpp"
#include <cstring>

const string AssetServer::texturePath = "assets/textures/";

AssetServer::AssetServer(){ }

AssetServer::~AssetServer(){
    
}

Texture2D AssetServer::load_texture(string filename){
    if(textures.count(filename) == 0){
        textures[filename] = LoadTexture((texturePath + filename).c_str());
    }
    return textures[filename];
}