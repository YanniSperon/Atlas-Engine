#include "Renderable3D.h"

#include "Shared/S_Vendor/S_GLM/gtc/matrix_transform.hpp"
#include "Shared/S_Vendor/S_GLM/gtx/euler_angles.hpp"
#include "Shared/S_Vendor/S_GLM/gtx/quaternion.hpp"

Atlas::Renderable3D::Renderable3D(Object3D* object)
	: objectBeingRendered(object), finalTransformation(object->GetTransformationMatrix())
{
	
}

Atlas::Renderable3D::Renderable3D(Object3D* object, glm::mat4 transformationMatrix)
	: objectBeingRendered(object), finalTransformation(transformationMatrix)
{

}

Atlas::Renderable3D::Renderable3D(Object3D* object, glm::mat4 translation, glm::mat4 rotation, glm::mat4 scale)
	: objectBeingRendered(object), finalTransformation(translation * rotation * scale)
{

}

Atlas::Renderable3D::~Renderable3D()
{

}

Atlas::Object3D* Atlas::Renderable3D::GetObject()
{
	return objectBeingRendered;
}

glm::mat4 Atlas::Renderable3D::GetTransformMatrix()
{
	return finalTransformation;
}
