#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <GLFW/glfw3.h>

// fopen() unsafe
#pragma warning(disable:4996)

struct Vert
{
	Vert(float x, float y, float z) : x(x), y(y), z(z) {}
	float x, y, z;
};

struct Obj {
	std::vector<Vert> verts;
	std::vector<int> tris;
};

void DrawBackground()
{
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
}


void DrawObject(Obj *obj)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_TRIANGLES);

	glColor3f(0.0, 0.0, 0.5);

	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);

	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);


	glEnd();
}

int main()
{
	if (!glfwInit())
		return 1;
	GLFWwindow* glWindow = glfwCreateWindow(640, 720, "Donut", NULL, NULL);
	glfwMakeContextCurrent(glWindow);
	glfwSwapInterval(1);

	char line[256];
	FILE* fObj = fopen("./res/cube.3d", "r");
	if (!fObj)
		return 1;

	Obj obj;
	
	while (fgets(line, sizeof(line), fObj))
	{
		if(line[0] == 'v')
		{
			std::string s(line);
			std::string temp = s.substr(1, s.find(" "));
			int a = 1;
		}
		else if (line[0] == 'f')
		{

		}
	}
	fclose(fObj);

	while (!glfwWindowShouldClose(glWindow))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Draw Scene
		DrawBackground();
		DrawObject(&obj);


		glfwMakeContextCurrent(glWindow);
		glfwSwapBuffers(glWindow);
	}

	glfwDestroyWindow(glWindow);
	glfwTerminate();

	return 0;
}