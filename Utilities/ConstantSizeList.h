//============================================================================
// Name        : ConstantSizeList.h
// Author      : Michal Marcinkowski
// Description : Simple constant size list (for extended euklides algorithm purposes)
//============================================================================

#ifndef CONSTANTSIZELIST_H_
#define CONSTANTSIZELIST_H_

#include <stdexcept>

template<class T>
class ConstantSizeList {
public:
	ConstantSizeList(const int& pSize) {
		maxSize = pSize;
		list = new T[maxSize];
		insertIndex = 0;
		firstValueIndex = 0;
		lastValueIndex = 0;
		size = 0;
	}

	bool isEmpty() {
		return (size == 0);
	}

	void pushFront(const T& x) {
		list[insertIndex] = x;
		firstValueIndex = insertIndex++;
		if (insertIndex >= maxSize) {
			insertIndex %= maxSize;
		}
		if (size != maxSize) {
			size++;
		} else {
			lastValueIndex = insertIndex;
		}
	}

	T& operator[](size_t pIndex) {
		int index;
		if (pIndex < size) {
			index = (firstValueIndex - pIndex);
			if (index < 0) {
				index = maxSize + index;
			}
			return list[index];
		}
		throw new std::out_of_range("Index out of range!");
	}

	const T& operator[](size_t pIndex) const {
		int index;
		if (pIndex < size) {
			index = (firstValueIndex - pIndex);
			if (index < 0) {
				index = maxSize + index;
			}
			return list[index];
		}
		throw new std::out_of_range("Index out of range!");
	}

	T& operator=(const T& other) {
		if (this != &other) {
			T * new_list = new T[other.maxSize];
			std::copy(other.list, other.maxSize, new_list);

			delete[] list;

			list = new_list;
			maxSize = other.maxSize;
			size = other.size;
			insertIndex = other.insertIndex;
			firstValueIndex = other.firstValueIndex;
			lastValueIndex = other.lastValueIndex;
		}
		return *this;
	}

	~ConstantSizeList() {
		delete[] list;
	}

private:
	T* list;
	size_t maxSize, size, insertIndex, firstValueIndex, lastValueIndex;
};

#endif /* CONSTANTSIZELIST_H_ */
