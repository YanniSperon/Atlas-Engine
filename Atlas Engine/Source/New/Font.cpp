#include "Font.h"

Atlas::Font::Font()
{
	texture = NULL;
	characters = std::vector<Object2D*>();
}

Atlas::Font::~Font()
{

}

void Atlas::Font::LoadFontSheet()
{
	// create mesh2d's and do not load them into vram but add them to the list of characters as object2d's from loading in a file that stores coordinates for each letter.
}

void Atlas::Font::LoadIntoVRAM()
{

}

void Atlas::Font::UnloadFromVRAM()
{

}
