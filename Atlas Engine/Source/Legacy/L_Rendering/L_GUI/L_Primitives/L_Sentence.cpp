#include "L_Sentence.h"
#include "Legacy/L_System/L_System.h"

namespace L_Atlas {
	L_Sentence::L_Sentence()
		: shader(new L_Shader()), font(new L_Font()), scale(0.0f)
	{
	}

	L_Sentence::L_Sentence(L_Shader* shdr, L_Font* f, std::string t, float s, glm::vec2 pos, glm::vec3 col)
		: shader(shdr), font(f), text(t), scale(s), position(pos), color(col)
	{

	}

	L_Sentence::~L_Sentence()
	{

	}

	L_Shader* L_Sentence::GetShader()
	{
		return shader;
	}

	void L_Sentence::SetShader(L_Shader* shdr)
	{
		shader = shdr;
	}

	L_Font* L_Sentence::GetFont()
	{
		return font;
	}

	void L_Sentence::SetFont(L_Font* f)
	{
		font = f;
	}

	std::string L_Sentence::GetText()
	{
		return text;
	}

	void L_Sentence::SetText(std::string newText)
	{
		text = newText;
	}

	float L_Sentence::GetScale()
	{
		return scale;
	}

	void L_Sentence::SetScale(float s)
	{
		scale = s;
	}

	glm::vec2 L_Sentence::GetPosition()
	{
		return position;
	}

	void L_Sentence::SetPosition(glm::vec2 newPos)
	{
		position = newPos;
	}

	glm::vec3 L_Sentence::GetColor()
	{
		return color;
	}

	void L_Sentence::SetColor(glm::vec3 newColor)
	{
		color = newColor;
	}
}