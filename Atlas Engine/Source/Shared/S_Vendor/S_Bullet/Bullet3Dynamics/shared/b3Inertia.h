

#ifndef B3_INERTIA_H
#define B3_INERTIA_H

#include "Shared/S_Vendor/S_Bullet/Bullet3Common/Shared/b3Mat3x3.h"

struct b3Inertia
{
	b3Mat3x3 m_invInertiaWorld;
	b3Mat3x3 m_initInvInertia;
};

#endif  //B3_INERTIA_H