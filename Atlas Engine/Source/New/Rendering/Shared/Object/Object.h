#pragma once

#include "New/Mesh/Shared/VRAM/VRAMHandle.h"

namespace Atlas {
	class Object {
	protected:
		enum class E_ObjectType {
			NONE = 0,
			THREEDIMENSIONAL, TWODIMENSIONAL
		};
		E_ObjectType type;
	public:
		Object(E_ObjectType objectType);
		Object(const Object& obj2);
		virtual ~Object();
	};
}