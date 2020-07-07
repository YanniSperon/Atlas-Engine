#include "L_Search.h"

GLuint L_Search::LinearSearchVector(std::vector<GLuint>& vec, GLuint value)
{
	for (unsigned int i = 0; i < vec.size(); i++) {
		if (vec[i] == value) {
			return i;
		}
	}
	return 0;
}
