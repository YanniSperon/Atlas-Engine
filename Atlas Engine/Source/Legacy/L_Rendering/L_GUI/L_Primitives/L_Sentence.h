#pragma once

#include "L_Font.h"

namespace L_Atlas {

	class L_Sentence {
	private:
		L_Shader* shader;
		L_Font* font;
		std::string text;
		float scale;
		glm::vec2 position;
		glm::vec3 color;
	public:
		L_Sentence();
		L_Sentence(L_Shader* shdr, L_Font* f, std::string t, float s, glm::vec2 pos, glm::vec3 col);
		~L_Sentence();

		L_Shader* GetShader();
		void SetShader(L_Shader* shdr);

		L_Font* GetFont();
		void SetFont(L_Font* f);

		std::string GetText();
		void SetText(std::string newText);

		float GetScale();
		void SetScale(float s);

		glm::vec2 GetPosition();
		void SetPosition(glm::vec2 newPos);

		glm::vec3 GetColor();
		void SetColor(glm::vec3 newColor);
	};
}