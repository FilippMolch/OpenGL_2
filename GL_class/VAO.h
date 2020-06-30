#pragma once
#include <g.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
using namespace std;

class VAO
{
	private:
		unsigned int mVAO;
		std::vector<unsigned int> mBuffers;
		unsigned mIndicesBuffer = 0;
		size_t mIndicesCount = 0;
	public:
		VAO();
		VAO(const VAO&) = delete;
		void bind();
		void Draw(unsigned type = 0x0004)
		{
			assert(mIndicesBuffer != 0);
			bind();
			for (size_t i = 0; i < mBuffers.size(); ++i)
			{
				glEnableVertexAttribArray(i);
			}

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndicesBuffer);
			glDrawElements(type, mIndicesCount, GL_UNSIGNED_INT, nullptr);

			for (size_t i = 0; i < mBuffers.size(); ++i)
			{
				glDisableVertexAttribArray(i);
			}
		}
		void addVBO(const std::vector<float>& data);
		void addVBO(const std::vector<glm::vec2>& data);
		void addVBO(const std::vector<glm::vec3>& data);
		void addVBO(const std::vector<glm::vec4>& data);
		void addIndices(const std::vector<unsigned>& data);
		~VAO();
};

