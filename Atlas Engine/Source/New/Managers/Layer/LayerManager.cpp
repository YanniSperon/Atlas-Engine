#include "LayerManager.h"

Atlas::LayerManager::LayerManager()
	: layers()
{

}

Atlas::LayerManager::~LayerManager()
{
	for (int i = 0; i < layers.size(); i++) {
		delete layers.at(i);
	}
	layers.clear();
}

void Atlas::LayerManager::AddLayer(Layer* layer)
{
	layers.push_back(layer);
}

void Atlas::LayerManager::Draw(Renderer* renderer)
{
	for (int i = 0; i < layers.size(); i++) {
		layers.at(i)->Draw(renderer);
	}
}

void Atlas::LayerManager::Update(float deltaTime)
{
	for (int i = 0; i < layers.size(); i++) {
		layers.at(i)->Update(deltaTime);
	}
}
