#include "ShaderManager.h"
#include "New/System/Console/Console.h"
#include "New/Rendering/3D/Object/Object3D.h"
#include "New/Rendering/2D/Object/Object2D.h"
#include <fstream>
#include <sstream>

Atlas::ShaderProgramSource& Atlas::ShaderManager::ReadShader(const std::string filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	if (!stream.is_open()) {
		printf("Error parsing shader, invalid file!\n");
	}

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			try {
				ss[(int)type] << line << '\n';
			}
			catch (std::exception) {
				Console::Error("Failed to load shader at \"" + filepath + "\"");
			}
		}
	}

	return { ss[0].str(), ss[1].str() };
}

GLuint Atlas::ShaderManager::LoadShader(ShaderProgramSource source)
{
	GLuint program = glCreateProgram();
	GLuint vs = CompileShader(GL_VERTEX_SHADER, source.VertexSource);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, source.FragmentSource);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

GLuint Atlas::ShaderManager::CompileShader(GLuint type, const std::string& source)
{
	GLuint id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message;
		try {
			message = (char*)alloca(length * sizeof(char));
		}
		catch (std::exception) {
			message = "FAILED";
		}
		glGetShaderInfoLog(id, length, &length, message);
		Console::Error("Failed to compile shader!");
		Console::Info(source);
		Console::Error(message);
		glDeleteShader(id);
		return 0;
	}

	return id;
}

Atlas::ShaderManager::ShaderManager()
	: Updatable(60), loadedShaders()
{

}

Atlas::ShaderManager::~ShaderManager()
{
	for (auto it : loadedShaders) {
		delete it.second;
	}
	loadedShaders.clear();
}

void Atlas::ShaderManager::Update(float deltaTime)
{
	Updatable::Update(deltaTime);
	if (Updatable::ShouldUpdate()) {
		for (auto it = loadedShaders.begin(); it != loadedShaders.end();) {
			Shader* shdr = it->second;
			if (shdr->GetReferencingObjects().size() == 0) {
				shdr->Unbind();
				it = loadedShaders.erase(it);
				delete shdr;
			}
			else {
				it++;
			}
		}
	}
}

Atlas::Shader* Atlas::ShaderManager::LoadShader(const std::string& filepath)
{
	Shader* tempShader = nullptr;
	for (auto it : loadedShaders) {
		if (it.second->GetFilepath() == filepath) {
			tempShader = it.second;
		}
	}
	if (tempShader) {
		return tempShader;
	}
	else {
		ShaderProgramSource src = ReadShader(filepath);
		return GetShader(src, filepath);
	}
}

Atlas::Shader* Atlas::ShaderManager::GetShader(Shader* shdr)
{
	if (loadedShaders.find(shdr->GetName()) == loadedShaders.end()) {
		// doesnt exist
		loadedShaders[shdr->GetName()] = shdr;
	}
	else {
		// does exist
		int count = 0;
		while (loadedShaders.find(shdr->GetName() + std::to_string(count)) != loadedShaders.end()) {
			count++;
		}
		std::string newName = shdr->GetName() + std::to_string(count);
		shdr->SetName(newName);
		loadedShaders[newName] = shdr;
	}
	return shdr;
}

Atlas::Shader* Atlas::ShaderManager::GetShader(ShaderProgramSource& src, const std::string& filepath)
{
	Shader* shdr = new Shader(src, filepath);
	if (loadedShaders.find(shdr->GetName()) == loadedShaders.end()) {
		// doesnt exist
		loadedShaders[shdr->GetName()] = shdr;
	}
	else {
		// does exist
		int count = 0;
		while (loadedShaders.find(shdr->GetName() + std::to_string(count)) != loadedShaders.end()) {
			count++;
		}
		std::string newName = shdr->GetName() + std::to_string(count);
		shdr->SetName(newName);
		loadedShaders[newName] = shdr;
	}
	return shdr;
}

void Atlas::ShaderManager::DeleteReference(Object* obj)
{
	for (auto it : loadedShaders) {
		switch (obj->GetType()) {
		case Object::E_ObjectType::THREEDIMENSIONAL:
			Object3D* obj3d = (Object3D*)obj;
			if (it.second == obj3d->GetShader()) {
				it.second->GetReferencingObjects().erase(obj);
			}
		case Object::E_ObjectType::TWODIMENSIONAL:
			Object2D* obj2d = (Object2D*)obj;
			if (it.second == obj2d->GetShader()) {
				it.second->GetReferencingObjects().erase(obj);
			}
		}
	}
}

void Atlas::ShaderManager::AddReference(Object* obj)
{
	switch (obj->GetType()) {
	case Object::E_ObjectType::THREEDIMENSIONAL:
		Object3D* obj3d = (Object3D*)obj;
		obj3d->GetShader()->GetReferencingObjects().insert(obj);
	case Object::E_ObjectType::TWODIMENSIONAL:
		Object2D* obj2d = (Object2D*)obj;
		obj2d->GetShader()->GetReferencingObjects().insert(obj);
	}
}

void Atlas::ShaderManager::DeleteShader(const std::string& name)
{
	if (loadedShaders.find(name) == loadedShaders.end()) {
		// doesnt exist
		// do nothing
		Console::Warning("Attempting to delete shader that does not exist");
	}
	else {
		Shader* shdr = loadedShaders[name];
		loadedShaders.erase(shdr->GetName());
		delete shdr;
	}
}

void Atlas::ShaderManager::DeleteShader(Shader* shdr)
{
	if (loadedShaders.find(shdr->GetName()) == loadedShaders.end()) {
		Console::Warning("Attempting to delete unloaded shader");
	}
	else {
		Shader* shdr = loadedShaders[shdr->GetName()];
		loadedShaders.erase(shdr->GetName());
		delete shdr;
	}
}

void Atlas::ShaderManager::SetShader(Shader* newShdr)
{
	int count = 0;
	while (loadedShaders.find(newShdr->GetName() + std::to_string(count)) != loadedShaders.end()) {
		count++;
	}
	std::string newName = newShdr->GetName() + std::to_string(count);
	newShdr->SetName(newName);
	loadedShaders[newName] = newShdr;
}

void Atlas::ShaderManager::ReplaceShader(Shader* newShdr)
{
	if (loadedShaders.find(newShdr->GetName()) == loadedShaders.end()) {
		// Does not exist
		loadedShaders[newShdr->GetName()] = newShdr;
	}
	else {
		// Does exist
		Shader* shdr = loadedShaders[newShdr->GetName()];
		std::set<Object*> referencingObjects = std::set<Object*>(shdr->GetReferencingObjects());
		loadedShaders.erase(newShdr->GetName());
		delete shdr;

		loadedShaders[newShdr->GetName()] = newShdr;
		newShdr->SetReferencingObjects(referencingObjects);
		for (auto obj : newShdr->GetReferencingObjects()) {
			switch (obj->GetType()) {
			case Object::E_ObjectType::THREEDIMENSIONAL:
				Object3D* obj3d = (Object3D*)obj;
				obj3d->SetShader(newShdr);
			case Object::E_ObjectType::TWODIMENSIONAL:
				Object2D* obj2d = (Object2D*)obj;
				obj2d->SetShader(newShdr);
			}
		}
	}
}
