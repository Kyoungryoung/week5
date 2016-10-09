#include <GLFW/glfw3.h>
#include<iostream>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"

const int width = 1000;
const int height = 500;

float* pixels = new float[width*height * 3];

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue);
void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue);
void circle(const int& i, const int& j, const int& r, const float& red, const float& green, const float& blue);
void drawOnPixelBuffer();

class GeometricObject {
public:
	virtual void draw() {

	}
};

class Line : public GeometricObject {
public:
	int i0,j0;
	int i1,j1;
public:
	Line(const int& start_x, const int& start_y,
		const int& end_x, const int& end_y) {
		initalize(start_x, start_y, end_x, end_y);
	}
	void initalize(const int& start_x, const int& start_y,
		const int& end_x, const int& end_y) {
		i0 = start_x;
		j0 = start_y;
		i1 = end_x;
		j1 = end_y;
	}
	void draw() {
		drawLine(i0, j0, i1, j1, 1.0f, 0.0f, 0.0f);
	}
};

class Box : public GeometricObject {
public:
	int i0, j0;
	int i1, j1;

public:
	Box(){}
	Box(const int& start_x, const int& start_y,
		const int& end_x, const int& end_y) {
		initalize(start_x, start_y, end_x, end_y);
	}
	void initalize(const int& start_x, const int& start_y,
		const int& end_x, const int& end_y) {
		i0 = start_x;
		j0 = start_y;
		i1 = end_x;
		j1 = end_y;
	}

	void draw() {
		drawLine(i0, j0, i1, j0, 1.0f, 0.0f, 0.0f);
		drawLine(i1, j0, i1, j1, 1.0f, 0.0f, 0.0f);
		drawLine(i0, j1, i1, j1, 1.0f, 0.0f, 0.0f);
		drawLine(i0, j0, i0, j1, 1.0f, 0.0f, 0.0f);
	}
};

class Circle : public GeometricObject {
public:
	int i, j, r;

public:
	Circle() {}
	Circle(const int& mid_x, const int& mid_y, const int& rid) {
		initalize(mid_x, mid_y, rid);
	}
	void initalize(const int& mid_x, const int& mid_y, const int& rid) {
		i = mid_x;
		j = mid_y;
		r = rid;
	}
	void draw() {
		circle(i,j,r, 1.0f, 0.0f, 0.0f);
	}
};

class ChangeCircle : public GeometricObject {
public:
	int i, j, r;

public:
	ChangeCircle() {}
	ChangeCircle(const int& mid_x, const int& mid_y, const int& rid) {
		initalize(mid_x, mid_y, rid);
	}
	void initalize(const int& mid_x, const int& mid_y, const int& rid) {
		i = mid_x;
		j = mid_y;
		r = rid;
	}
	void draw() {
		circle(i, j, r, 0.0f, 1.0f, 0.0f);
	}
};

class X : public GeometricObject {
public:
	int i0, j0;
	int i1, j1;
public:
	X(const int& start_x, const int& start_y,
		const int& end_x, const int& end_y) {
		initalize(start_x, start_y, end_x, end_y);
	}
	void initalize(const int& start_x, const int& start_y,
		const int& end_x, const int& end_y) {
		i0 = start_x;
		j0 = start_y;
		i1 = end_x;
		j1 = end_y;
	}
	void draw() {
		drawLine(i0, j0, i1, j1, 1.0f, 0.0f, 0.0f);
		drawLine(i0, j1, i1, j0, 1.0f, 0.0f, 0.0f);
	}
};

class A : public GeometricObject {
public:
	int i0, j0;
	int i1, j1;
public:
	A(const int& start_x, const int& start_y,
		const int& end_x, const int& end_y) {
		initalize(start_x, start_y, end_x, end_y);
	}
	void initalize(const int& start_x, const int& start_y,
		const int& end_x, const int& end_y) {
		i0 = start_x;
		j0 = start_y;
		i1 = end_x;
		j1 = end_y;
	}
	void draw() {
		drawLine(i0, j0, ((i0+i1)/2), j1, 1.0f, 0.0f, 0.0f);
		drawLine(((i0 + i1) / 2), j1, i1, j0, 1.0f, 0.0f, 0.0f);
		drawLine(i0 + 10, ((j0 + j1) / 2), i1 - 10, ((j0 + j1) / 2), 1.0f, 0.0f, 0.0f);
	}
};

class Point : public GeometricObject {
public:
	int i0, j0;
	int i1, j1;
public:
	Point(const int& start_x, const int& start_y,
		const int& end_x, const int& end_y) {
		initalize(start_x, start_y, end_x, end_y);
	}
	void initalize(const int& start_x, const int& start_y,
		const int& end_x, const int& end_y) {
		i0 = start_x;
		j0 = start_y;
		i1 = end_x;
		j1 = end_y;
	}
	void draw() {
		drawLine( i1, j1, i0, j0, 1.0f, 0.0f, 0.0f);
		drawLine( i1, j1, i0+15, j1+15, 1.0f, 0.0f, 0.0f);
		drawLine(i0-15, j1+15, i1, j1, 1.0f, 0.0f, 0.0f);
	}
};

const int num_lines = 40;
Line **my_lines = new Line*[num_lines];

const int num_boxes = 20;
Box **my_boxes = new Box*[num_boxes];

const int num_circles = 21;
Circle **my_circles = new Circle*[num_circles];

const int num_ch_circles = 21;
ChangeCircle **my_ch_circles = new ChangeCircle*[num_ch_circles];

const int num_x = 2;
X **my_x = new X*[num_x];

const int num_point = 8;
Point **my_point = new Point*[num_point];

const int num_a = 2;
A **my_a = new A*[num_a];

GeometricObject **my_object = new GeometricObject*[50];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	if (i0 == i1)
	{
		for (int j = j0; j < j1; j++)
			drawPixel(i0, j, red, green, blue);
		return;
	}

	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}

void circle(const int& i, const int& j, const int& r, const float& red, const float& green, const float& blue)
{
	double d = 0.0;
	float angle = 360.0;
	int x = 0, y = 0;

	for (angle = 0; angle < 360; angle++)
	{
		d = angle*(3.14 / 180);
		x = i + r*sin(d);
		y = j + r*cos(d);
		drawPixel(x, y, red, green, blue);
		drawPixel(x + 1, y, red, green, blue);
		drawPixel(x, y - 1, red, green, blue);
	}

}

void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

	for (int i = 0; i<width*height; i++) {
		pixels[i * 3 + 0] = 1.0f; // red 
		pixels[i * 3 + 1] = 1.0f; // green
		pixels[i * 3 + 2] = 1.0f; // blue
	}

	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);
}

int main(void)
{
	GeometricObject *my_geo = new GeometricObject;
	my_geo->draw();

	int count = 0;
	
		for (int i = 0; i < 5; i++) 
			my_object[i] = new Circle(50 + 100 * i, 50, 40);
		for (int i = 5; i < 10; i++)
			my_object[i] = new Circle(50 + 100 * (i-5), 150, 40);
		for (int i = 10; i < 15; i++)
			my_object[i] = new Circle(50 + 100 * (i-10), 300, 40);
		for (int i = 15; i < 20; i++)
			my_object[i] = new Circle(50 + 100 * (i-15), 400, 40);

		count = 20;

		// 1_1 ~ 2_5
		my_object[count] = new Line(30, 380, 70, 420); count++;
		my_object[count] = new Circle(150, 400, 15); count++;
		my_object[count] = new Box(230, 380, 270, 420); count++;
		my_object[count] = new X(330,380,370,420); count++;
		my_object[count] = new Point(450, 420, 450, 380); count++;

		my_object[count] = new Line(30, 300, 70, 300); count++;
		my_object[count] = new Line(60, 310, 70, 300); count++;
		my_object[count] = new Line(60, 290, 70, 300); count++;
		my_object[count] = new A(125, 280, 175, 320); count++;
		my_object[count] = new Line(250, 280, 250, 320); count++;

		my_object[count] = new Line(330, 300, 370, 300); count++;
		my_object[count] = new Line(330, 300, 340, 310); count++;
		my_object[count] = new Line(330, 300, 340, 290); count++;

		my_object[count] = new Line(450, 280, 450, 320); count++;
		my_object[count] = new Line(440, 310, 450, 320); count++;
		my_object[count] = new Line(450, 320, 460, 310); count++;

		// 3_1 ~ 4_5
		my_object[count] = new Line(30, 130, 70, 170); count++;
		my_object[count] = new Circle(150, 150, 15); count++;
		my_object[count] = new Box(230, 130, 270, 170); count++;
		my_object[count] = new X(330, 130, 370, 170); count++;
		my_object[count] = new Point(450, 170, 450, 130); count++;

		my_object[count] = new Line(30, 50, 70, 50); count++;
		my_object[count] = new Line(60, 60, 70, 50); count++;
		my_object[count] = new Line(60, 40, 70, 50); count++;
		my_object[count] = new A(125, 30, 175, 70); count++;
		my_object[count] = new Line(250, 30, 250, 70); count++;

		my_object[count] = new Line(330, 50, 370, 50); count++;
		my_object[count] = new Line(330, 50, 340, 60); count++;
		my_object[count] = new Line(330, 50, 340, 40); count++;

		my_object[count] = new Line(450, 30, 450, 70); count++;
		my_object[count] = new Line(440, 60, 450, 70); count++;
		my_object[count] = new Line(450, 70, 460, 60); count++;

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

		drawOnPixelBuffer();

		double xpos, ypos;
		double dist;

		for (int i = 0; i < count; i++) {
			my_object[i]->draw();
		}

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);



		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}