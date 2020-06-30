#include "Program.h"
#include <iterator>
#include <fstream>
#include <iostream>
#include "VAO.h"



Program::Program(const string& name) 
{
	mProgram = glCreateProgram();
	mVertexShader = loadShader("res/glsl/" + name + ".vert", GL_VERTEX_SHADER);
	mFragmentShader = loadShader("res/glsl/" + name + ".frag", GL_FRAGMENT_SHADER);
}

Program::~Program()
{
	glDetachShader(mProgram, mVertexShader);
	glDetachShader(mProgram, mFragmentShader);
	glDeleteShader(mVertexShader);
	glDeleteShader(mFragmentShader);
	glDeleteProgram(mProgram);
}

void Program::link()
{
	// св€зываем шейдеы с программой
	glAttachShader(mProgram, mVertexShader);
	glAttachShader(mProgram, mFragmentShader);

	// линкуем
	glLinkProgram(mProgram);
}

GLuint Program::loadShader(const string& path, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	// загрузка кода шейдера
	// выгл€дит страшно, но так проще, отвечаю
	std::ifstream fis(path);
	// он посчитал, что это прототип функции (идиот просто), поэтому конструктор будет таким {}
	std::string shaderCode = { std::istreambuf_iterator<char>(fis), std::istreambuf_iterator<char>() };

	// загрузка кода шейдера в OpenGL
	const char* c = shaderCode.c_str();
	// да, тут именно указатель на указатель, char**
	glShaderSource(shader, 1, &c, nullptr);

	// получить результат компил€ции (успешно/неуспешно)
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	char buf[0x1000];
	GLsizei len;
	glGetShaderInfoLog(shader, sizeof(buf), &len, buf);
	if (len > 0)
	{
		std::cout << "Failed to compile shader " << path << ":" << std::endl << buf;
	}

	return shader;
}

GLint Program::getLocation(const std::string& name)
{
	return glGetUniformLocation(mProgram, name.c_str());
}

void Program::setFloat(const std::string& name, float value)
{
	glUniform1f(getLocation(name), value);
}

void Program::use()
{
	glUseProgram(mProgram);
}

void Program::bindAttribute(GLuint index, const std::string& name)
{
	glBindAttribLocation(mProgram, index, name.c_str());
}