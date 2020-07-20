#pragma once

#include "New/Mesh/Shared/VRAM/VRAMHandle.h"

namespace Atlas {
	class Object {
	public:
		enum class E_ObjectType {
			NONE = 0,
			THREEDIMENSIONAL, TWODIMENSIONAL
		};

		Object(E_ObjectType objectType);
		Object(const Object& obj2);
		virtual ~Object();

		E_ObjectType GetType();
	protected:
		E_ObjectType type;
	};
}