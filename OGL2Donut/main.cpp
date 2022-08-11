#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <GLFW/glfw3.h>

// fopen() unsafe
#pragma warning(disable:4996)

struct Vert
{
	Vert(float x, float y, float z) : x(x), y(y), z(z) {}
	float x, y, z;
};

struct Face {
	Face(int a, int b, int c) : a(a), b(b), c(c) {}
	int a, b, c;
};

struct Obj {
	std::vector<Vert> verts;
	std::vector<Face> tris;
};


Vert parseVerts(std::string s)
{
	std::vector<float> v;

	std::istringstream iss(s);
	std::copy(std::istream_iterator<float>(iss),
		std::istream_iterator<float>(),
		std::back_inserter(v));

	return Vert(v[0],v[1],v[2]);
}

Face parseFace(std::string s)
{
	std::vector<int> v;

	std::istringstream iss(s);
	std::copy(std::istream_iterator<int>(iss),
		std::istream_iterator<int>(),
		std::back_inserter(v));

	return Face(v[0], v[1], v[2]);
}

void RotateX3D(Obj* obj, float theta)
{
	float sintheta = sin(theta);
	float costheta = cos(theta);

	for (int i = 0; i < obj->verts.size(); i++)
	{
		float y = obj->verts[i].y;
		float z = obj->verts[i].z;

		obj->verts[i].y = y * costheta - z * sintheta;
		obj->verts[i].z = z * costheta + y * sintheta;
	}
}

void RotateY3D(Obj* obj, float theta)
{
	float sintheta = sin(theta);
	float costheta = cos(theta);

	for (int i = 0; i < obj->verts.size(); i++)
	{
		float x = obj->verts[i].x;
		float z = obj->verts[i].z;

		obj->verts[i].x = x * costheta + z * sintheta;
		obj->verts[i].z = z * costheta - x * sintheta;
	}
}

void RotateZ3D(Obj* obj, float theta)
{
	float sintheta = sin(theta);
	float costheta = cos(theta);

	for (int i = 0; i < obj->verts.size(); i++)
	{
		float x = obj->verts[i].x;
		float y = obj->verts[i].y;

		obj->verts[i].x = x * costheta - y * sintheta;
		obj->verts[i].y = y * costheta + x * sintheta;
	}
}

void Rotate(Obj* obj, float theta)
{
	RotateX3D(obj, theta);
	RotateY3D(obj, theta);
	RotateZ3D(obj, theta);
}

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

	glColor3f(1,1,1);

	for (int i = 0; i < obj->tris.size(); i++)
	{
		Face face = obj->tris[i];

		glVertex3f(obj->verts[face.a - 1].x, obj->verts[face.a - 1].y, obj->verts[face.a - 1].z);
		glVertex3f(obj->verts[face.b - 1].x, obj->verts[face.b - 1].y, obj->verts[face.b - 1].z);
		glVertex3f(obj->verts[face.c - 1].x, obj->verts[face.c - 1].y, obj->verts[face.c - 1].z);
	}

	glEnd();
}

int main()
{
	if (!glfwInit())
		return 1;
	GLFWwindow* glWindow = glfwCreateWindow(640, 640, "Donut", NULL, NULL);
	glfwMakeContextCurrent(glWindow);
	glfwSwapInterval(1);

	char line[256];
	FILE* fObj = fopen("./res/donut.3d", "r");
	if (!fObj)
		return 1;

	Obj obj;
	
	while (fgets(line, sizeof(line), fObj))
	{
		if(line[0] == 'v')
		{
			std::string s(line);
			obj.verts.push_back(parseVerts(s.substr(2)));
		}
		else if (line[0] == 'f')
		{
			std::string s(line);
			obj.tris.push_back(parseFace(s.substr(2)));
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

		Rotate(&obj, 0.01);

		glfwMakeContextCurrent(glWindow);
		glfwSwapBuffers(glWindow);
	}

	glfwDestroyWindow(glWindow);
	glfwTerminate();

	return 0;
}