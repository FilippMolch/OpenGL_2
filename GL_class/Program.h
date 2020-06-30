#pragma once
#include <g.h>
#include <iostream>
using namespace std;

class Program
{
	private:

		GLuint mProgram;
		GLuint mVertexShader;
		GLuint mFragmentShader;

		GLuint loadShader(const string& path, GLenum ShaderType);
		GLint getLocation(const std::string& name);

	public:
		Program(const string& name);
		~Program();

		void link();
		void bindAttribute(GLuint index, const std::string& name);
		void use();
		void setFloat(const std::string& name, float value);
};

