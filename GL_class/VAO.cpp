#include "VAO.h"
#include "g.h"
#include <glm/glm.hpp>

VAO::VAO()
{
	glGenVertexArrays(1, &mVAO);
	bind();
}

void VAO::addVBO(const std::vector<glm::vec3>& data)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(mBuffers.size(), 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	mBuffers.push_back(vbo);
}

void VAO::addVBO(const std::vector<glm::vec4>& data)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec4), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(mBuffers.size(), 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	mBuffers.push_back(vbo);
}

void VAO::bind()
{
	glBindVertexArray(VAO::mVAO);
}

void VAO::addIndices(const std::vector<unsigned>& data)
{
	assert(mIndicesBuffer == 0);

	mIndicesCount = data.size();

	glGenBuffers(1, &mIndicesBuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned), data.data(), GL_STATIC_DRAW);
}

VAO::~VAO()
{
	glDeleteBuffers(VAO::mBuffers.size(), VAO::mBuffers.data());
	glDeleteVertexArrays(1, &mVAO);
}