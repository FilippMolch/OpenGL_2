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
	// ��������� ������ � ����������
	glAttachShader(mProgram, mVertexShader);
	glAttachShader(mProgram, mFragmentShader);

	// �������
	glLinkProgram(mProgram);
}

GLuint Program::loadShader(const string& path, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	// �������� ���� �������
	// �������� �������, �� ��� �����, �������
	std::ifstream fis(path);
	// �� ��������, ��� ��� �������� ������� (����� ������), ������� ����������� ����� ����� {}
	std::string shaderCode = { std::istreambuf_iterator<char>(fis), std::istreambuf_iterator<char>() };

	// �������� ���� ������� � OpenGL
	const char* c = shaderCode.c_str();
	// ��, ��� ������ ��������� �� ���������, char**
	glShaderSource(shader, 1, &c, nullptr);

	// �������� ��������� ���������� (�������/���������)
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