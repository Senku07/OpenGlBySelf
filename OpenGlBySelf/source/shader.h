const char* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 aColor;\n"
"layout(location = 2) in vec2 aTexCoord;\n"

"out vec3 ourColor;\n"
"out vec2 TexCoord;\n"

"void main()\n"
"{\n"
"gl_Position = vec4(aPos, 1.0);\n"
"ourColor = aColor;\n"
"TexCoord = aTexCoord;\n"
"}\0";


const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"

"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"

"uniform sampler2D ourTexture0;\n"
"uniform sampler2D ourTexture1;\n"

"void main()\n"
"{\n"
//"FragColor = vec4(ourColor,1.0);\n"
"FragColor = mix(texture(ourTexture0, TexCoord), texture(ourTexture1,TexCoord),0.5);\n"
"}\0";