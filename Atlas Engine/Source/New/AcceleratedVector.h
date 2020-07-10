#pragma once
#include <stdexcept>
#include <memory>

// T is just the variable name that stores the type that is going to be passed in
// template<typename T>
// template<class T>
// YOU CAN USE TYPENAME OR CLASS
// template<typename variableName>

template<class T>
class AcceleratedVector {
private:
	T* objects;
	int maxElements;
	int indexOfLastElement;
	int amountOfSlotsPerSizeChange;
	std::allocator<T> mem;
public:
	AcceleratedVector();
	AcceleratedVector(const int& slotsPerAllocation);
	~AcceleratedVector();

	int Size();

	void Expand();
	void Shrink();

	void Insert(const int& index, const T& value);
	void Set(const int& index, const T& value);
	T Get(const int& index);
	void Add(const T& object);
	void Remove(const int& index);
	void Destroy();
};

template<class T>
inline AcceleratedVector<T>::AcceleratedVector()
	: objects(NULL), maxElements(2345), indexOfLastElement(-1), amountOfSlotsPerSizeChange(2345), mem()
{
	objects = mem.allocate(amountOfSlotsPerSizeChange);
}

template<class T>
inline AcceleratedVector<T>::AcceleratedVector(const int& slotsPerAllocation)
	: objects(nullptr), maxElements(slotsPerAllocation), indexOfLastElement(-1), amountOfSlotsPerSizeChange(slotsPerAllocation), mem()
{
	if (slotsPerAllocation == 0) {
		amountOfSlotsPerSizeChange = 2345;
		maxElements = 2345;
	}
	objects = mem.allocate(slotsPerAllocation);
}

template<class T>
inline AcceleratedVector<T>::~AcceleratedVector()
{
	mem.deallocate(objects, maxElements);
}

template<class T>
inline int AcceleratedVector<T>::Size()
{
	return indexOfLastElement + 1;
}

template<class T>
inline void AcceleratedVector<T>::Expand()
{
	//T* tempObjects = objects;
	//int originalNumElements = maxElements;
	//maxElements += amountOfSlotsPerSizeChange;
	//objects = new T[maxElements];
	//memcpy(objects, tempObjects, originalNumElements * sizeof(T));
	//delete tempObjects;

	T* tempObjects = objects;
	int originalNumElements = maxElements;
	maxElements += amountOfSlotsPerSizeChange;
	objects = mem.allocate(maxElements);
	memcpy(objects, tempObjects, originalNumElements * sizeof(T));
	mem.deallocate(tempObjects, originalNumElements);

	if (amountOfSlotsPerSizeChange < 500000) {
		amountOfSlotsPerSizeChange *= 2;
	}
}

template<class T>
inline void AcceleratedVector<T>::Shrink()
{
	if (maxElements > amountOfSlotsPerSizeChange && indexOfLastElement < maxElements - amountOfSlotsPerSizeChange) {
		T* tempObjects = objects;
		int originalSize = maxElements;
		maxElements -= amountOfSlotsPerSizeChange;
		objects = mem.allocate(maxElements);
		memcpy(objects, tempObjects, maxElements * sizeof(T));
		mem.deallocate(tempObjects, originalSize);
		if (amountOfSlotsPerSizeChange > 5000) {
			amountOfSlotsPerSizeChange /= 2;
		}
	}
}

template<class T>
inline void AcceleratedVector<T>::Insert(const int& index, const T& value)
{
	if (indexOfLastElement == maxElements - 1) {
		Expand();
	}
	indexOfLastElement++;
	for (int i = indexOfLastElement; i > index; i--) {
		objects[i] = objects[i - 1];
	}
	objects[index] = value;
}

template<class T>
inline void AcceleratedVector<T>::Set(const int& index, const T& value)
{
	if (index >= 0 && index <= indexOfLastElement) {
		objects[index] = value;
	}
	else {
		throw std::out_of_range("Out of bounds");
	}
}

template<class T>
inline T AcceleratedVector<T>::Get(const int& index)
{
	if (index >= 0 && index <= indexOfLastElement) {
		return objects[index];
	}
	else {
		throw std::out_of_range("Out of bounds");
	}
}

template<class T>
inline void AcceleratedVector<T>::Add(const T& object)
{
	if (indexOfLastElement == maxElements - 1) {
		Expand();
	}
	indexOfLastElement++;
	objects[indexOfLastElement] = object;
}

template<class T>
inline void AcceleratedVector<T>::Remove(const int& index)
{
	if (index >= 0 && index < indexOfLastElement) {
		for (int i = index; i < indexOfLastElement; i++) {
			objects[i] = objects[i + 1];
		}
		indexOfLastElement--;
		Shrink();
	}
	else {
		throw std::out_of_range("Out of bounds");
	}
}

template<class T>
inline void AcceleratedVector<T>::Destroy()
{
	for (int i = 0; i < objects.size(); i++) {
		mem.destroy(objects + i);
	}
}
