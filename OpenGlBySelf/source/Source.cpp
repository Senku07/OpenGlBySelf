#include <glad/glad.h>
#include <glfw3.h>
#include "glad.c"
#include "shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "image.h"

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

	
	
	float position1[32] =
	{
		 1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-1.0f,  1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	int indices[6] =
	{
		0,1,2,
		0,2,3
	};

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//buffer of position..
	GLuint buffer,index;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 32 * sizeof(float), position1, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 8 * sizeof(float) ,(void*)(3*sizeof(float)));
	
	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint),indices, GL_STATIC_DRAW);

	//texture area
	stbi_set_flip_vertically_on_load(true);

	int width, height, channels;
	unsigned char* data = stbi_load("res/scene.png", &width, &height, &channels, 0);

	unsigned int texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (!data)
	{
		std::cout << "Failed to Initialize Texture" << std::endl;
	}
	else
	{
		std::cout << "Good Texture" << std::endl;
		std::cout << channels << std::endl;
		std::cout << width << "," << height << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	};

	stbi_image_free(data);
	
	//second texutre...
	stbi_set_flip_vertically_on_load(true);
	unsigned char* byte = stbi_load("res/komi2.png", &width, &height, &channels, 0);

	unsigned int texture1;
	glGenTextures(2, &texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (!byte)
	{
		std::cout << "Failed to Initialize Texture" << std::endl;
	}
	else
	{
		std::cout << "Good Texture" << std::endl;
		std::cout << channels << std::endl;
		std::cout << width << "," << height << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,width,height,0,GL_RGBA, GL_UNSIGNED_BYTE, byte);
	};
	
	glGenerateMipmap(GL_TEXTURE_2D);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));


	//unbind buffer area..
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);


	stbi_image_free(byte);
	//Area for uniform..
	
	//float r = 0.0f;
	//int UniformLocation = glGetUniformLocation(Program, "u_Color");
	//glUniform4f(UniformLocation, r, 0.0f, 0.0f, 1.0f);
	glUseProgram(Program);

	unsigned int texUni = glGetUniformLocation(Program, "ourTexture0");
	glUniform1i(texUni, 0);
	unsigned int textUni1 = glGetUniformLocation(Program, "ourTexture1");
	glUniform1i(textUni1,1);
	
	while (!glfwWindowShouldClose(window))
	{	
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.50f, 0.0f, 0.0f, 1.0f);
		//glDrawArrays(GL_TRIANGLES, 0,3);
		glUseProgram(Program);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);

		//glBindTexture(GL_TEXTURE_2D, texture);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
		
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);


		glfwSwapBuffers(window);
		glfwPollEvents();

	};

	//buffer dleteing area...
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(Program);
	glDeleteTextures(1, &texture);
	glDeleteTextures(2, &texture1);

	glfwTerminate();
}