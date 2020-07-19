#include "Text.h"

Atlas::Text::Text()
	: text(), font(nullptr), finalTransformation(1.0f)
{

}

Atlas::Text::~Text()
{

}

void Atlas::Text::Update(float deltaTime)
{

}

void Atlas::Text::SetFinalTransformation(glm::mat4 trans)
{
	finalTransformation = trans;
}
