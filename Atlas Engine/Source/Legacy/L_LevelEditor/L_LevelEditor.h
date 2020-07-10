#pragma once

#include <string>

namespace L_LevelEditor {

	enum L_Mode
	{
		scale, translate, rotate, cam, texture
	};

	enum L_EditorType
	{
		Scene, light
	};

	struct L_Texture
	{
		std::string name;
		unsigned int id;
	};
}