#include "ErrorHandler.h"

#include <iostream>



void GLClearError() {
	while (glGetError());
}

bool GLLogCall() {

	while (GLenum error = glGetError()) {
		std::cout << "OpengGL Error: [" << error << "]" << std::endl;
		return false;
	}
	return true;

}
