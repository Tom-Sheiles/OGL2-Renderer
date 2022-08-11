#include <stdio.h>

#include <GLFW/glfw3.h>

int main()
{
	if (!glfwInit())
		return 1;
	GLFWwindow* glWindow = glfwCreateWindow(640, 720, "Donut", NULL, NULL);
	glfwMakeContextCurrent(glWindow);
	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(glWindow))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();


		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_QUADS);

		// red
		glColor3f(1.0, 0.702, 0.702);
		glVertex2f(-1.0, -1.0);
		glVertex2f(1.0, -1.0);

		//blue color
		glColor3f(0.75, 0.937, 1.0);
		glVertex2f(1.0, 1.0);
		glVertex2f(-1.0, 1.0);

		glEnd();

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_QUADS);

		glColor3f(0.0, 0.0, 0.5);

		glVertex3f(-0.5, -0.5, 1.0);
		glVertex3f(0.5, -0.5, 0.0);

		glVertex3f(0.5, 0.5, 0.0);
		glVertex3f(-0.5, 0.5, 0.0);

		glEnd();

		glfwMakeContextCurrent(glWindow);
		glfwSwapBuffers(glWindow);
	}

	glfwDestroyWindow(glWindow);
	glfwTerminate();

	return 0;
}