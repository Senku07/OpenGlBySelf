#include <glad/glad.h>
#include <glfw3.h>
#include "glad.c"

#include <iostream>


int main()
{
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
			"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 u_Color;\n"
		"void main()\n"
		"{\n"
			"FragColor = u_Color;\n"
		"}\0";

	//std::cout << fragmentShaderSource << std::endl;

	glfwInit();
	if (!glfwInit())
	{
		std::cout << "glfw not work proplery";
	};

	GLFWwindow* window = glfwCreateWindow(600, 400, "For fun", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (!window)
	{
		std::cout << "fails to show window";
	};

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to intitalize glad" << std::endl;
	};

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int Vsuccess;
	char log[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &Vsuccess);

	if (!Vsuccess)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, log);
		std::cout << "Failed to Load Vertex Shader" << log << std::endl;
	};

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	int Fsuccess;
	char loginfo[1000];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &Fsuccess);

	if (!Fsuccess)
	{
		glGetShaderInfoLog(fragmentShader,1000, NULL, loginfo);
		std::cout << "Error in Fragment Shader" << loginfo << std::endl;
	};

	GLuint Program = glCreateProgram();
	glAttachShader(Program, vertexShader);
	glAttachShader(Program, fragmentShader);
	glLinkProgram(Program);
	glUseProgram(Program);

	int Psuccess;
	glGetProgramiv(Program, GL_CURRENT_PROGRAM, &Psuccess);
	char plog[512];

	if (!Psuccess)
	{
		glGetProgramInfoLog(Program, 512, NULL, plog);
		std::cout << "Error in Program" << plog << std::endl;
	};

	float vertices[9] =
	{
		0.0f,0.5f,0.0f,
       -0.5f,0.0f,0.0f,
		0.5f,0.0f,0.0f	
	};

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float),vertices, GL_STATIC_DRAW);	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(Program);
	int UniformLocation = glGetUniformLocation(Program, "u_Color");
	glUniform4f(UniformLocation,1.0f, 0.0f, 0.0f, 1.0f);

	while (!glfwWindowShouldClose(window))
	{	
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	};

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(Program);

	glfwTerminate();
}