#define DGPU

#ifdef DGPU
extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}
#endif


//#define ATLAS_LEGACY

#ifdef ATLAS_LEGACY
#include "Legacy/L_AtlasEngine.h"
int main(void)
{
	if (L_Atlas::AtlasEngine::Start()) {
		L_Atlas::AtlasEngine::Cleanup();
		return 0;
	}
	return -1;
}
#else
#include "New/AtlasEngine.h"

int main(void)
{
	if (Atlas::AtlasEngine::Start()) {
		Atlas::AtlasEngine::Cleanup();
		return 0;
	}
	return -1;
}
#endif