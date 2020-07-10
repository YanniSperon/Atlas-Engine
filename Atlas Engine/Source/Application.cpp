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
// temp
//#include "New/AcceleratedVector.h"
//#include <vector>
//#include <chrono>
//#include <iostream>

int main(void)
{
	if (Atlas::AtlasEngine::Start()) {
		Atlas::AtlasEngine::Cleanup();
		return 0;
	}
	return -1;



	/*

	AcceleratedVector<int> av = AcceleratedVector<int>(1000000);
	AcceleratedVector<int>* avHA = new AcceleratedVector<int>();
	std::vector<int> v = std::vector<int>();
	std::vector<int>* vHA = new std::vector<int>();

	auto startAV = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 100000000; i++) {
		av.Add(i);
	}
	auto endAV = std::chrono::high_resolution_clock::now();



	auto startV = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 100000000; i++) {
		v.push_back(i);
	}
	auto endV = std::chrono::high_resolution_clock::now();


	auto durationAV = std::chrono::duration_cast<std::chrono::microseconds>(endAV - startAV);
	auto durationV = std::chrono::duration_cast<std::chrono::microseconds>(endV - startV);
	std::cout << "Stack allocated: " << std::endl;
	std::cout << durationAV.count() << std::endl;
	std::cout << durationV.count() << std::endl;

	auto startAVHA = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000000; i++) {
		avHA->Add(i);
	}
	auto endAVHA = std::chrono::high_resolution_clock::now();



	auto startVHA = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000000; i++) {
		vHA->push_back(i);
	}
	auto endVHA = std::chrono::high_resolution_clock::now();


	auto durationAVHA = std::chrono::duration_cast<std::chrono::microseconds>(endAVHA - startAVHA);
	auto durationVHA = std::chrono::duration_cast<std::chrono::microseconds>(endVHA - startVHA);
	std::cout << "Heap allocated: " << std::endl;
	std::cout << durationAVHA.count() << std::endl;
	std::cout << durationVHA.count() << std::endl;


	system("pause");*/
}
#endif