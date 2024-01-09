#ifndef ASSET_SERVER_H
#define ASSET_SERVER_H

#include <map>
#include "raylib.h"
#include <iostream>
using namespace std;

class AssetServer {
private:
    const static string texturePath;
    const static string soundPath;
    map<string, Texture2D> textures;
    map<string, Sound> sounds;

public:
    AssetServer();
    ~AssetServer();
    Texture2D load_texture(string name);
    Sound load_sound(string name);
};

#endif