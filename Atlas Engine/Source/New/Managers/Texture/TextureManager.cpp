#include "TextureManager.h"
#include "Shared/S_Vendor/S_STB_Image/stb_image.h"
#include "New/System/Console/Console.h"
#include "New/Rendering/3D/Object/Object3D.h"
#include "New/Rendering/2D/Object/Object2D.h"

Atlas::TextureManager::ImageData& Atlas::TextureManager::ReadTexture(const std::string& filepath)
{
	stbi_set_flip_vertically_on_load(1);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);

	return ImageData(width, height, nrChannels, data, filepath);
}

GLuint Atlas::TextureManager::LoadTexture(ImageData& data)
{
	GLuint texID = 0;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (data.data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, data.width, data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		Console::Error("Failed to load texture \"" + data.filepath + "\"");
	}
	return texID;
}

Atlas::TextureManager::TextureManager()
	: Updatable(60), loadedTextures()
{

}

Atlas::TextureManager::~TextureManager()
{
	for (auto it : loadedTextures) {
		delete it.second;
	}
	loadedTextures.clear();
}

void Atlas::TextureManager::Update(float deltaTime)
{
	Updatable::Update(deltaTime);
	if (Updatable::ShouldUpdate()) {
		for (auto it = loadedTextures.begin(); it != loadedTextures.end();) {
			Texture* tex = it->second;
			if (tex->GetReferencingObjects().size() == 0) {
				tex->Unbind();
				it = loadedTextures.erase(it);
				delete tex;
			}
			else {
				it++;
			}
		}
	}
}

Atlas::Texture* Atlas::TextureManager::LoadTexture(const std::string& filepath)
{
	Texture* tempTexture = nullptr;
	for (auto it : loadedTextures) {
		if (it.second->GetFilepath() == filepath) {
			tempTexture = it.second;
		}
	}
	if (tempTexture) {
		return tempTexture;
	}
	else {
		return GetTexture(new Texture(LoadTexture(ReadTexture(filepath)), filepath, "texture"));
	}
}

Atlas::Texture* Atlas::TextureManager::GetTexture(Texture* tex)
{
	if (loadedTextures.find(tex->GetName()) == loadedTextures.end()) {
		// doesnt exist
		loadedTextures[tex->GetName()] = tex;
	}
	else {
		// does exist
		int count = 0;
		while (loadedTextures.find(tex->GetName() + std::to_string(count)) != loadedTextures.end()) {
			count++;
		}
		std::string newName = tex->GetName() + std::to_string(count);
		tex->SetName(newName);
		loadedTextures[newName] = tex;
	}
	return tex;
}

void Atlas::TextureManager::DeleteReference(Object* obj)
{
	for (auto it : loadedTextures) {
		switch (obj->GetType()) {
		case Object::E_ObjectType::THREEDIMENSIONAL:
			Object3D* obj3d = (Object3D*)obj;
			if (it.second == obj3d->GetTexture()) {
				it.second->GetReferencingObjects().erase(obj);
			}
		case Object::E_ObjectType::TWODIMENSIONAL:
			Object2D* obj2d = (Object2D*)obj;
			if (it.second == obj2d->GetTexture()) {
				it.second->GetReferencingObjects().erase(obj);
			}
		}
	}
}

void Atlas::TextureManager::AddReference(Object* obj)
{
	switch (obj->GetType()) {
	case Object::E_ObjectType::THREEDIMENSIONAL:
		Object3D* obj3d = (Object3D*)obj;
		obj3d->GetTexture()->GetReferencingObjects().insert(obj);
	case Object::E_ObjectType::TWODIMENSIONAL:
		Object2D* obj2d = (Object2D*)obj;
		obj2d->GetTexture()->GetReferencingObjects().insert(obj);
	}
}

void Atlas::TextureManager::DeleteTexture(const std::string& name)
{
	if (loadedTextures.find(name) == loadedTextures.end()) {
		// doesnt exist
		// do nothing
		Console::Warning("Attempting to delete texture that does not exist");
	}
	else {
		Texture* tex = loadedTextures[name];
		loadedTextures.erase(tex->GetName());
		delete tex;
	}
}

void Atlas::TextureManager::DeleteTexture(Texture* tex)
{
	if (loadedTextures.find(tex->GetName()) == loadedTextures.end()) {
		Console::Warning("Attempting to delete unloaded texture");
	}
	else {
		Texture* tempTex = loadedTextures[tempTex->GetName()];
		loadedTextures.erase(tempTex->GetName());
		delete tempTex;
	}
}

void Atlas::TextureManager::SetTexture(Texture* newTex)
{
	int count = 0;
	while (loadedTextures.find(newTex->GetName() + std::to_string(count)) != loadedTextures.end()) {
		count++;
	}
	std::string newName = newTex->GetName() + std::to_string(count);
	newTex->SetName(newName);
	loadedTextures[newName] = newTex;
}

void Atlas::TextureManager::ReplaceTexture(Texture* newTex)
{
	if (loadedTextures.find(newTex->GetName()) == loadedTextures.end()) {
		// Does not exist
		loadedTextures[newTex->GetName()] = newTex;
	}
	else {
		// Does exist
		Texture* tempTex = loadedTextures[newTex->GetName()];
		std::set<Object*> referencingObjects = std::set<Object*>(tempTex->GetReferencingObjects());
		loadedTextures.erase(tempTex->GetName());
		delete tempTex;

		loadedTextures[newTex->GetName()] = newTex;
		newTex->SetReferencingObjects(referencingObjects);
		for (auto obj : newTex->GetReferencingObjects()) {
			switch (obj->GetType()) {
			case Object::E_ObjectType::THREEDIMENSIONAL:
				Object3D* obj3d = (Object3D*)obj;
				obj3d->SetTexture(newTex);
			case Object::E_ObjectType::TWODIMENSIONAL:
				Object2D* obj2d = (Object2D*)obj;
				obj2d->SetTexture(newTex);
			}
		}
	}
}
