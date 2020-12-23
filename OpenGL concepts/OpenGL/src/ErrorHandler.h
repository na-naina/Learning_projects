#include <GL/glew.h>



#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall())

    bool GLLogCall();
    void GLClearError();

