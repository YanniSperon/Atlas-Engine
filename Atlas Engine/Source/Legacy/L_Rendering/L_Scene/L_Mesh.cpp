#include "L_Mesh.h"
#include "Shared/S_Vendor/S_GLM/gtc/matrix_transform.hpp"
#include "Shared/S_Vendor/S_GLM/gtx/euler_angles.hpp"
#include "Shared/S_Vendor/S_GLM/gtx/quaternion.hpp"
#include "Legacy/L_Rendering/L_Primitives/L_ShapeGenerator.h"
#include "Legacy/L_Global/L_Global.h"
#include "Legacy/L_System/L_System.h"
#include "Legacy/L_Other/L_Convert.h"
#include "Legacy/L_Physics/L_PhysicsEngine.h"
#include <iostream>
#include <unordered_map>
#include <algorithm>


namespace L_Atlas {

	L_Mesh::L_Mesh()
		: directory(""), fileName("Error"), rotation(0.0f, 0.0f, 0.0f), translation(0.0f, 0.0f, 0.0f), shape(), minExtents(0.0f, 0.0f, 0.0f), maxExtents(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f), objectType(L_Type::cubeModel)
	{

	}

	L_Mesh::L_Mesh(L_Type type, std::string dir, std::string name)
		: directory(dir), fileName(name), rotation(0.0f, 0.0f, 0.0f), translation(0.0f, 0.0f, 0.0f), minExtents(-0.5f, -0.5f, -0.5f), maxExtents(0.5f, 0.5f, 0.5f), scale(1.0f, 1.0f, 1.0f), objectType(type)
	{
		if (type == L_Type::cubeModel) {
			if (L_Global::Variables.meshCache.find("default::type::cube") != L_Global::Variables.meshCache.end()) {
				shape = L_Global::Variables.meshCache["default::type::cube"];
			}
			else {
				L_Global::Variables.meshCache["default::type::cube"] = L_ShapeGenerator::makeCube(minExtents, maxExtents);
				shape = L_Global::Variables.meshCache["default::type::cube"];
			}
		}
		else if (type == L_Type::normalModel) {
			try {
				if (L_Global::Variables.meshCache.find(dir + fileName) != L_Global::Variables.meshCache.end()) {
					shape = L_Global::Variables.meshCache[dir + fileName];
				}
				else {
					std::string file = dir + name;
					std::replace(file.begin(), file.end(), '\\', '/');
					std::string physicalLocation = "";

					file = L_System::ConvertFilePathToLocal(file);
					L_Filepath pathtemp = L_System::SeperateFilepath(file);
					std::string meshDirectory = pathtemp.directory;
					std::string meshName = pathtemp.filename;
					physicalLocation = pathtemp.directory + pathtemp.filename;

					L_Global::Variables.loadedL_MeshCache[meshName] = physicalLocation;

					L_Global::Variables.meshCache[meshDirectory + meshName] = L_ShapeGenerator::loadTexturedShape(dir, name);
					shape = L_Global::Variables.meshCache[meshDirectory + meshName];
				}
			}
			catch (const std::exception & e) {
				try {
					if (L_Global::Variables.meshCache.find(dir + fileName) != L_Global::Variables.meshCache.end()) {
						shape = L_Global::Variables.meshCache[dir + fileName];
					}
					else {
						std::string file = dir + name;
						std::replace(file.begin(), file.end(), '\\', '/');
						std::string physicalLocation = "";

						file = L_System::ConvertFilePathToLocal(file);
						L_Filepath pathtemp = L_System::SeperateFilepath(file);
						std::string meshDirectory = pathtemp.directory;
						std::string meshName = pathtemp.filename;
						physicalLocation = pathtemp.directory + pathtemp.filename;

						L_Global::Variables.loadedL_MeshCache[meshName] = physicalLocation;

						L_Global::Variables.meshCache[meshDirectory + meshName] = L_ShapeGenerator::loadShape(meshDirectory + meshName);
						shape = L_Global::Variables.meshCache[meshDirectory + meshName];
					}
				}
				catch (const std::exception & e) {
					L_System::Err("Unrecognized file type, must be wavefront .obj file following the specified format");
				}
			}
		}
		else if (type == L_Type::skyBox) {
			if (L_Global::Variables.meshCache.find("default::type::skyBox") != L_Global::Variables.meshCache.end()) {
				shape = L_Global::Variables.meshCache["default::type::skyBox"];
			}
			else {
				L_Global::Variables.meshCache["default::type::skyBox"] = L_ShapeGenerator::makeSkybox(minExtents, maxExtents);
				shape = L_Global::Variables.meshCache["default::type::skyBox"];
			}
		}
		else if (type == L_Type::cubeInvertedLighting) {
			if (L_Global::Variables.meshCache.find("default::type::cubeInvertedLighting") != L_Global::Variables.meshCache.end()) {
				shape = L_Global::Variables.meshCache["default::type::cubeInvertedLighting"];
			}
			else {
				L_Global::Variables.meshCache["default::type::cubeInvertedLighting"] = L_ShapeGenerator::makeInvertedLightingCube(minExtents, maxExtents);
				shape = L_Global::Variables.meshCache["default::type::cubeInvertedLighting"];
			}
		}

		minExtents = shape.min;
		maxExtents = shape.max;
	}

	L_Mesh::L_Mesh(L_Type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, glm::vec3 s)
		: directory(dir), fileName(name), rotation(rot), translation(trans), minExtents(-0.5f, -0.5f, -0.5f), maxExtents(0.5f, 0.5f, 0.5f), scale(s), objectType(type)
	{
		if (type == L_Type::cubeModel) {
			if (L_Global::Variables.meshCache.find("default::type::cube") != L_Global::Variables.meshCache.end()) {
				shape = L_Global::Variables.meshCache["default::type::cube"];
			}
			else {
				L_Global::Variables.meshCache["default::type::cube"] = L_ShapeGenerator::makeCube(minExtents, maxExtents);
				shape = L_Global::Variables.meshCache["default::type::cube"];
			}
		}
		else if (type == L_Type::normalModel) {
			try {
				if (L_Global::Variables.meshCache.find(dir + fileName) != L_Global::Variables.meshCache.end()) {
					shape = L_Global::Variables.meshCache[dir + fileName];
				}
				else {
					std::string file = dir + name;
					std::replace(file.begin(), file.end(), '\\', '/');
					std::string physicalLocation = "";

					file = L_System::ConvertFilePathToLocal(file);
					L_Filepath pathtemp = L_System::SeperateFilepath(file);
					std::string meshDirectory = pathtemp.directory;
					std::string meshName = pathtemp.filename;
					physicalLocation = pathtemp.directory + pathtemp.filename;

					L_Global::Variables.loadedL_MeshCache[meshName] = physicalLocation;

					L_Global::Variables.meshCache[meshDirectory + meshName] = L_ShapeGenerator::loadTexturedShape(dir, name);
					shape = L_Global::Variables.meshCache[meshDirectory + meshName];
				}
			}
			catch (const std::exception & e) {
				try {
					if (L_Global::Variables.meshCache.find(dir + fileName) != L_Global::Variables.meshCache.end()) {
						shape = L_Global::Variables.meshCache[dir + fileName];
					}
					else {
						std::string file = dir + name;
						std::replace(file.begin(), file.end(), '\\', '/');
						std::string physicalLocation = "";

						file = L_System::ConvertFilePathToLocal(file);
						L_Filepath pathtemp = L_System::SeperateFilepath(file);
						std::string meshDirectory = pathtemp.directory;
						std::string meshName = pathtemp.filename;
						physicalLocation = pathtemp.directory + pathtemp.filename;

						L_Global::Variables.loadedL_MeshCache[meshName] = physicalLocation;

						L_Global::Variables.meshCache[meshDirectory + meshName] = L_ShapeGenerator::loadShape(meshDirectory + meshName);
						shape = L_Global::Variables.meshCache[meshDirectory + meshName];
					}
				}
				catch (const std::exception & e) {
					L_System::Err("Unrecognized file type, must be wavefront .obj file following the specified format");
				}
			}
		}
		else if (type == L_Type::skyBox) {
			if (L_Global::Variables.meshCache.find("default::type::skyBox") != L_Global::Variables.meshCache.end()) {
				shape = L_Global::Variables.meshCache["default::type::skyBox"];
			}
			else {
				L_Global::Variables.meshCache["default::type::skyBox"] = L_ShapeGenerator::makeSkybox(minExtents, maxExtents);
				shape = L_Global::Variables.meshCache["default::type::skyBox"];
			}
		}
		else if (type == L_Type::cubeInvertedLighting) {
			if (L_Global::Variables.meshCache.find("default::type::cubeInvertedLighting") != L_Global::Variables.meshCache.end()) {
				shape = L_Global::Variables.meshCache["default::type::cubeInvertedLighting"];
			}
			else {
				L_Global::Variables.meshCache["default::type::cubeInvertedLighting"] = L_ShapeGenerator::makeInvertedLightingCube(minExtents, maxExtents);
				shape = L_Global::Variables.meshCache["default::type::cubeInvertedLighting"];
			}
		}

		minExtents = shape.min;
		maxExtents = shape.max;
	}

	L_Mesh::~L_Mesh()
	{
		
	}

	glm::mat4 L_Mesh::GetModelTransformMatrix()
	{
		return (glm::translate(glm::mat4(), translation) * glm::yawPitchRoll(glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z)) * glm::scale(glm::mat4(), scale));
	}

	glm::mat4 L_Mesh::GetModelTransRotMatrix()
	{
		return (glm::translate(glm::mat4(), translation) * glm::yawPitchRoll(glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z)));
	}

	

	void L_Mesh::RotateX(float x)
	{
		rotation.x = x;
	}

	void L_Mesh::RotateY(float y)
	{
		rotation.y = y;
	}

	void L_Mesh::RotateZ(float z)
	{
		rotation.z = z;
	}

	void L_Mesh::Rotate3f(float x, float y, float z)
	{
		rotation.x = x;
		rotation.y = y;
		rotation.z = z;
	}

	void L_Mesh::RotateVec3(glm::vec3 rot) {
		rotation = rot;
	}

	void L_Mesh::RotateAdd3f(float x, float y, float z)
	{
		rotation.x += x;
		rotation.y += y;
		rotation.z += z;
	}

	void L_Mesh::RotateAddVec3(glm::vec3 rot)
	{
		rotation += rot;
	}

	void L_Mesh::TranslateX(float x)
	{
		translation.x = x;
	}

	void L_Mesh::TranslateY(float y)
	{
		translation.y = y;
	}

	void L_Mesh::TranslateZ(float z)
	{
		translation.z = z;
	}

	void L_Mesh::Translate3f(float x, float y, float z)
	{
		translation.x = x;
		translation.y = y;
		translation.z = z;
	}

	void L_Mesh::TranslateVec3(glm::vec3 trans) {
		translation = trans;
	}

	void L_Mesh::TranslateAdd3f(float x, float y, float z)
	{
		translation.x += x;
		translation.y += y;
		translation.z += z;
	}

	void L_Mesh::TranslateAddVec3(glm::vec3 trans)
	{
		translation += trans;
	}

	void L_Mesh::ScaleX(float x)
	{
		scale.x = x;
	}

	void L_Mesh::ScaleY(float y)
	{
		scale.y = y;
	}

	void L_Mesh::ScaleZ(float z)
	{
		scale.z = z;
	}

	void L_Mesh::Scale3f(float x, float y, float z)
	{
		if (scale.x > 0) {
			scale.x = x;
		}
		if (scale.y > 0) {
			scale.y = y;
		}
		if (scale.z > 0) {
			scale.z = z;
		}
	}

	void L_Mesh::ScaleVec3(glm::vec3 s)
	{
		if (s.x > 0) {
			scale.x = s.x;
		}
		if (s.y > 0) {
			scale.y = s.y;
		}
		if (s.z > 0) {
			scale.z = s.z;
		}
	}

	void L_Mesh::ScaleAdd3f(float x, float y, float z)
	{
		if (scale.x + x > 0) {
			scale.x += x;
		}
		if (scale.y + y > 0) {
			scale.y += y;
		}
		if (scale.z + z > 0) {
			scale.z += z;
		}
	}

	void L_Mesh::ScaleAddVec3(glm::vec3 s)
	{
		if (scale.x + s.x > 0) {
			scale.x += s.x;
		}
		if (scale.y + s.y > 0) {
			scale.y += s.y;
		}
		if (scale.z + s.z > 0) {
			scale.z += s.z;
		}
	}

	glm::vec3 L_Mesh::GetTranslation()
	{
		return translation;
	}

	glm::vec3 L_Mesh::GetRotation()
	{
		return rotation;
	}

	glm::vec3 L_Mesh::GetScale()
	{
		return scale;
	}

	L_ShapeData L_Mesh::GetShape()
	{
		return shape;
	}

	std::string L_Mesh::GetModelFileName()
	{
		return fileName;
	}

	std::string L_Mesh::GetModelFileDirectory()
	{
		return directory;
	}

	void L_Mesh::SetShape(L_ShapeData newShape)
	{
		shape = newShape;
	}

	std::string L_Mesh::GetModelType()
	{
		if (objectType == L_Type::cubeModel) {
			return "cubeModel";
		}
		else if (objectType == L_Type::cubeInvertedLighting) {
			return "cubeInvertedLighting";
		}
		else if (objectType == L_Type::skyBox) {
			return "skyBox";
		}
		else if (objectType == L_Type::normalModel) {
			return "normalModel";
		}
		else {
			return "INVALID";
		}
	}

	std::string L_Mesh::GetType()
	{
		return "L_Mesh";
	}

	L_Type L_Mesh::GetTypeEnum()
	{
		return objectType;
	}

	void L_Mesh::FlushCache()
	{
		for (auto it : L_Global::Variables.meshCache) {
			it.second.cleanUp();
		}
		L_Global::Variables.meshCache.erase(L_Global::Variables.meshCache.begin(), L_Global::Variables.meshCache.end());
	}
}