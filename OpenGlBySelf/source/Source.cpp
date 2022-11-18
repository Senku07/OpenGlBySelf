#include <glad/glad.h>
#include <glfw3.h>
#include "glad.c"
#include "shader.h"

#include <iostream>



int main()
{
	//std::cout << fragmentShaderSource << std::endl;
	glfwInit();
	if (!glfwInit())
	{
		std::cout << "glfw not work proplery";
	};

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//std::cout << VER_MAJORVERSION << "," << VER_MINORVERSION << std::endl;

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

	
	std::cout <<glGetString(GL_VERSION);

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

	float position1[18] =
	{
		0.0f,0.90f,0.0f,	1.0f,0.0f,0.0f,
	   -0.75f,-0.75f,0.0f,  0.0f,1.0f,0.0f,
		0.75f,-0.75f,0.0f,  0.0f,0.0f,1.0f
	};

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint buffer; //index;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), position1, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 6 * sizeof(float) ,(void*)12);
	
	//glGenBuffers(1, &index);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint),indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(Program);


	//float r = 0.0f;
	//int UniformLocation = glGetUniformLocation(Program, "u_Color");
	//glUniform4f(UniformLocation, r, 0.0f, 0.0f, 1.0f);

	while (!glfwWindowShouldClose(window))
	{	
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0,3);


		glfwSwapBuffers(window);
		glfwPollEvents();

	};

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(Program);

	glfwTerminate();
}