#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "GL/gl3w.h"
#include "GLFW/glfw3.h"
#include "GL/gl.h"

static void glfw_error_handler(int error, const char* message);
static void glfw_key_handler(GLFWwindow*, int, int, int, int);

int main(void){
	
	if (!glfwInit()){
		fprintf(stderr, "Failed to initialize glfw!\n");
		exit(1);
	}
	glfwSetErrorCallback(&glfw_error_handler);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, 1);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);
	GLFWwindow* window = glfwCreateWindow(640, 480, "Minimal Triangle", NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "Failed to create glfw window!\n");
		exit(1);
	}
	glfwSetKeyCallback(window, &glfw_key_handler);
	
	glfwMakeContextCurrent(window);
	

	if(gl3wInit()){
		fprintf(stderr, "Gl3w function loading failed!\n");
	}
	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(window))
	{
		glfwSetWindowOpacity( window, 0.1);
		/* Set background color. */
		glClearColor(0, 0, 0, 0.1);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwDestroyWindow(window);
	glfwTerminate();

	printf("Hello there!\n");

	return EXIT_SUCCESS;
}

static void glfw_error_handler(int error, const char* message){
	fprintf(stderr, "Glfw error number %d has appeared - %s\n", error, message);
}

static void glfw_key_handler(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}
