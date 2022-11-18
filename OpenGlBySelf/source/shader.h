const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec4 ourColor;\n"

"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"ourColor = vec4(aColor.x, aColor.y, aColor.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
//"uniform vec4 u_Color;\n"
"in vec4 ourColor;\n"

"void main()\n"
"{\n"
//"FragColor = u_Color;\n"
"FragColor = ourColor;\n"
"}\0";