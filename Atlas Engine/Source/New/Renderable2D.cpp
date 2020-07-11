#include "Renderable2D.h"

#include "Shared/S_Vendor/S_GLM/gtc/matrix_transform.hpp"
#include "Shared/S_Vendor/S_GLM/gtx/euler_angles.hpp"
#include "Shared/S_Vendor/S_GLM/gtx/quaternion.hpp"

Atlas::Renderable2D::Renderable2D(Object2D* object)
	: objectBeingRendered(object), finalTransformation(object->GetTransformationMatrix())
{

}

Atlas::Renderable2D::Renderable2D(Object2D* object, glm::mat4 transformationMatrix)
	: objectBeingRendered(object), finalTransformation(transformationMatrix)
{

}

Atlas::Renderable2D::Renderable2D(Object2D* object, glm::mat4 translation, glm::mat4 rotation, glm::mat4 scale)
	: objectBeingRendered(object), finalTransformation(translation* rotation* scale)
{

}

Atlas::Renderable2D::~Renderable2D()
{

}

Atlas::Object2D* Atlas::Renderable2D::GetObject()
{
	return objectBeingRendered;
}

glm::mat4 Atlas::Renderable2D::GetTransformMatrix()
{
	return finalTransformation;
}
