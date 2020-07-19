#include "ShaderManager.h"

Atlas::ShaderManager::ShaderManager()
	: loadedShaders()
{

}

Atlas::ShaderManager::~ShaderManager()
{
	for (auto it : loadedShaders) {
		delete it.second;
	}
	loadedShaders.clear();
}
