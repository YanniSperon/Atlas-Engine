#include "L_Mesh2D.h"
#include "Legacy/L_Rendering/L_Primitives/L_ShapeGenerator.h"
#include "Shared/S_Vendor/S_GLM/gtc/matrix_transform.hpp"
#include "Shared/S_Vendor/S_GLM/gtx/euler_angles.hpp"

namespace L_Atlas {
	L_Mesh2D::L_Mesh2D()
		: rotation(0.0f), translation(0.0f, 0.0f), scale(0.0f, 0.0f), minExtents(0.0f, 0.0f), maxExtents(0.0f, 0.0f), minTexCoords(0.0f, 0.0f), maxTexCoords(1.0f, 1.0f)
	{
	}

	L_Mesh2D::L_Mesh2D(glm::vec2 min, glm::vec2 max, float rot, glm::vec2 trans, glm::vec2 s, glm::vec2 minTex, glm::vec2 maxTex)
		: rotation(rot), translation(trans), scale(s), minExtents(min), maxExtents(max), minTexCoords(minTex), maxTexCoords(maxTex)
	{
		shape = L_ShapeGenerator::makeSquare(min, max, minTex, maxTex);
	}

	L_Mesh2D::~L_Mesh2D()
	{

	}

	glm::mat4 L_Mesh2D::GetModelTransformMatrix()
	{
		return (glm::translate(glm::mat4(), glm::vec3(translation, 0.0f)) * glm::yawPitchRoll(glm::radians(0.0f), glm::radians(0.0f), glm::radians(rotation)) * glm::scale(glm::mat4(), glm::vec3(scale, 1.0f)));
	}

	void L_Mesh2D::Rotate1f(float x)
	{
		rotation = x;
	}

	void L_Mesh2D::RotateAdd1f(float x)
	{
		rotation += x;
	}

	void L_Mesh2D::TranslateX(float x)
	{
		translation.x = x;
	}

	void L_Mesh2D::TranslateY(float y)
	{
		translation.y = y;
	}

	void L_Mesh2D::Translate2f(float x, float y)
	{
		translation.x = x;
		translation.y = y;
	}

	void L_Mesh2D::TranslateVec2(glm::vec2 trans)
	{
		translation = trans;
	}

	void L_Mesh2D::TranslateAdd2f(float x, float y)
	{
		translation.x += x;
		translation.y += y;
	}

	void L_Mesh2D::TranslateAddVec2(glm::vec2 trans)
	{
		translation += trans;
	}

	void L_Mesh2D::ScaleX(float x)
	{
		scale.x = x;
	}

	void L_Mesh2D::ScaleY(float y)
	{
		scale.y = y;
	}

	void L_Mesh2D::Scale2f(float x, float y)
	{
		scale.x = x;
		scale.y = y;
	}

	void L_Mesh2D::ScaleVec2(glm::vec2 s)
	{
		scale = s;
	}

	void L_Mesh2D::ScaleAdd2f(float x, float y)
	{
		scale.x += x;
		scale.y += y;
	}

	void L_Mesh2D::ScaleAddVec2(glm::vec2 s)
	{
		scale += s;
	}

	glm::vec2 L_Mesh2D::GetTranslation()
	{
		return translation;
	}

	float L_Mesh2D::GetRotation()
	{
		return rotation;
	}

	glm::vec2 L_Mesh2D::GetScale()
	{
		return scale;
	}

	L_ShapeData2D L_Mesh2D::GetShape()
	{
		return shape;
	}

	glm::vec2 L_Mesh2D::GetMinExtents()
	{
		return minExtents;
	}

	glm::vec2 L_Mesh2D::GetMaxExtents()
	{
		return maxExtents;
	}

	glm::vec2 L_Mesh2D::GetMinTexCoords()
	{
		return minTexCoords;
	}

	glm::vec2 L_Mesh2D::GetMaxTexCoords()
	{
		return maxTexCoords;
	}

	void L_Mesh2D::SetShape(L_ShapeData2D newShape)
	{
		shape = newShape;
	}

	std::string L_Mesh2D::GetType()
	{
		return "L_Mesh2D";
	}
}