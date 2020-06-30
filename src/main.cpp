#include <Windows.h>
#include "../GL_class/VAO.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include "../GL_class/Program.h"
using namespace std;

void Size(GLFWwindow* window, int wi, int he);
void Input(GLFWwindow* window);
int i = 0;

int main() 
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	if (!glfwInit())
	{
		cout << "GLFW Error" << endl;
		glfwTerminate();
		return 1;
	}
	
	GLFWwindow* window = glfwCreateWindow(800, 640, "OpenGL", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, Size);
	glfwMakeContextCurrent(window);
	
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		cout << "GLEW NOT INIT" << endl;
		return -1;
	}
	
	VAO vao;

	// 3х компонентный массив
	// неявно задаём трёхкомпонетные векторы
	// вершины
	vao.addVBO({
		{-0.5f, 0.5f, 0.f},
		{-0.5f, -0.5f, 0.f},
		{0.5f, 0.5f, 0.f},
		{0.5f, -0.5f, 0.f},
		});

	// 3х компонентный массив
	// неявно задаём трёхкомпонетные векторы
	// цвета
	vao.addVBO({
		{1, 0, 0}, // красный
		{0, 0, 1}, // синий
		{0, 1, 0}, // зелёный
		{1, 0, 0}, // красный
		});

	// индексы (см. 4 туториал)
	vao.addIndices({
		0, 1, 2,
		2, 1, 3
		});

	Program first("first");
	// название атрибута здесь должно совпадать с шейдером
	first.bindAttribute(0, "position");
	first.bindAttribute(1, "color");
	first.link();

	first.use();

	float anim = 0;
	while (!glfwWindowShouldClose(window))
	{
		Input(window);

		anim += 0.01;
		first.setFloat("animation", glm::sin(anim) * 0.5f + 0.5f);

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		vao.Draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void Input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_0))
	{
		cout << "Press: " << i << endl;
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void Size(GLFWwindow* window, int wi, int he)
{
	glViewport(0, 0, wi, he);
}