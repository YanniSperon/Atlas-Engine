#include "RenderableText.h"

Atlas::RenderableText::RenderableText()
	: text(NULL), finalTranslation(0.0f), finalRotation(0.0f), finalScale(0.0f)
{

}

Atlas::RenderableText::~RenderableText()
{
}

Atlas::Text* Atlas::RenderableText::GetText()
{
	return text;
}
