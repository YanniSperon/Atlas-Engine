#pragma once

#include "GL/glew.h"
#include "Shared/S_Vendor/S_GLM/glm.hpp"
#include "Legacy/L_Rendering/L_Scene/L_Shader.h"
#include <map>

namespace L_Atlas {

	struct L_Character {
		GLuint     TextureID;  // ID handle of the glyph texture
		glm::ivec2 Size;       // Size of glyph
		glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
		GLuint     Advance;    // Offset to advance to next glyph
	};

	class L_Font {
	private:
		std::map<GLchar, L_Character> Characters;
		GLuint VAO;
		GLuint VBO;
	public:
		L_Font();
		L_Font(std::string fontDirectory, std::string fontName, GLuint characterSize);
		~L_Font();

		void RenderText(L_Shader* s, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, glm::mat4 projection);

		std::map<GLchar, L_Character> GetGlyphs();
	};
}