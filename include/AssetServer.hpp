#ifndef ASSET_SERVER_H
#define ASSET_SERVER_H

#include <map>
#include "raylib.h"
#include <iostream>
using namespace std;

class AssetServer {
private:
    const static string texturePath;
    map<string, Texture2D> textures;
public:
    AssetServer();
    ~AssetServer();
    Texture2D load_texture(string name);
};

#endif