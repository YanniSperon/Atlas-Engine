#pragma once

#include <vector>
#include <string>
#include "Legacy/L_Rendering/L_Scene/L_Object.h"
#include "Legacy/L_Rendering/L_GUI/L_Primitives/L_Object2D.h"
#include "Legacy/L_Rendering/L_GUI/L_Primitives/L_Sentence.h"

namespace L_Atlas {

	class L_IO {
	public:

		static void LoadFile(std::vector<L_Object*>& vec, const std::string dir, const std::string fileName);
		static void SaveToFile(std::vector<L_Object*>& vec, const std::string dir, const std::string fileName);

		static void LoadFile(std::vector<L_Object2D*>& vec, const std::string dir, const std::string fileName);
		static void SaveToFile(std::vector<L_Object2D*>& vec, const std::string dir, const std::string fileName);

		static void LoadFile(std::vector<L_Sentence*>& vec, const std::string dir, const std::string fileName);
		static void SaveToFile(std::vector<L_Sentence*>& vec, const std::string dir, const std::string fileName);
	};
}