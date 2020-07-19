#include "TextureManager.h"

Atlas::TextureManager::TextureManager()
	: loadedTextures()
{

}

Atlas::TextureManager::~TextureManager()
{
	for (auto it : loadedTextures) {
		delete it.second;
	}
	loadedTextures.clear();
}
