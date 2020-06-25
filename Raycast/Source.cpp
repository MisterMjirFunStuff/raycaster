#include <iostream>
#include <math.h>
#include "Player.h"
#include "Level.h"
#include "Constants.h"
#include"Caster.h"

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 512;
const int TARGET_FPS = 60;
Player player(240, 256);
Level level;
Caster caster(&level, &player);

void framebuffer_size_callback(GLFWwindow* window, int w, int h);
void input(GLFWwindow* window);
void draw();

int main(int argc, char* args[])
{
	/* Initialize GLFW and GLEW */
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Raycaster", nullptr, nullptr);
	if (!window)
	{
		std::cout << "Could not create the window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (GLEW_OK != glewInit())
	{
		std::cout << "GLEW could not initialize" << std::endl;
		return -1;
	}

	/* Set stuff up for the window */
	glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1, 1);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/* Object Stuff */
	if (level.load("lvl_2.rdata"))
	{
		std::cout << "The level couldn't be loaded" << std::endl;
		return -1;
	}

	/* Framerate capping (that's cap) */
	const double limitFPS = 1.0 / TARGET_FPS;
	double lastTime = glfwGetTime(), timer = lastTime;
	double deltaTime = 0, nowTime = 0;
	int frames = 0, updates = 0;

	while (!glfwWindowShouldClose(window))
	{
		nowTime = glfwGetTime();
		deltaTime += (nowTime - lastTime) / limitFPS;
		lastTime = nowTime;

		// Input
		glfwPollEvents();

		// Update
		while (deltaTime >= 1.0)
		{
			input(window);
			updates++;
			deltaTime--;
		}
		

		// Draw
		draw();

		frames++;

		// Events / Buffer swap
		glfwSwapBuffers(window);
		
		
	}

	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	//glViewport(0, 0, w, h);
}

void input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		player.moveX(player.getDeltaPos().x);
		player.moveY(player.getDeltaPos().y);
	}

	if (glfwGetKey(window, GLFW_KEY_S))
	{
		player.moveX(-player.getDeltaPos().x);
		player.moveY(-player.getDeltaPos().y);
	}

	if (glfwGetKey(window, GLFW_KEY_A))
		player.turn(-0.1);

	if (glfwGetKey(window, GLFW_KEY_D))
		player.turn(0.1);
}

void draw()
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	level.draw();
	player.draw();
	caster.draw();
}