///////////////////////////////////////////
////Type your name and student ID here/////
////Name: Luk Ming Ho
////Student ID: 115094761

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include <iostream>
#include <fstream>
#include <time.h> 

using namespace std;
using glm::vec3;
using glm::mat4;

mat4 View;
GLuint vao[6];
GLuint vbo[6];
GLuint programID;
float c_time;
float speed = 0.001;
float x_delta = 0.1f;
float y_delta = 0.1f;
int x_press_num = 0;
int y_press_num = 0;
float score = 0;
float crystal_x;
float crystal_y;

float dot(vec3 a, vec3 b) 
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float mag(vec3 a) 
{
	return std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

void randomCrystalLocation() {
	crystal_x = rand() % 17 - 8;
	crystal_y = rand() % 17 - 8;
}

void checkCollision() {
	if ( (x_delta*x_press_num <= crystal_x+0.5f) && (x_delta * x_press_num >= crystal_x - 0.5f) ) {
		if ((y_delta * y_press_num <= crystal_y + 0.5f) && (y_delta * y_press_num >= crystal_y - 0.5f)) {
			randomCrystalLocation();
			score+=0.1;
		}
	}
}

// VAO 0
void draw_triangle()
{
	const GLfloat tri_v[] =
	{
		+0.0f, +1.0f, +0.6f, // Position 0
		-0.2f, +1.0f, +0.0f, // Position 1
		+0.2f, +1.0f, +0.0f, // Position 2
	};
	const GLfloat tri_c[] =
	{
		+1.0f, +1.0f, +0.0f,
		+1.0f, +0.0f, +0.0f,
		+1.0f, +0.0f, +0.0f,
	};

	glBindVertexArray(vao[0]);  //first VAO
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tri_v) + sizeof(tri_c), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(tri_v), tri_v);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(tri_v), sizeof(tri_c), tri_c);
	////vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	////vertex color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (char*)(sizeof(tri_v)));
}

// VAO 1
void draw_rectangle() {
	const GLfloat square[] =
	{
		-0.5f, +0.5f, +0.0f, // Position 0
		+0.5f, +0.5f, +0.0f, // Position 1
		+0.5f, -0.5f, +0.0f, // Position 2
		-0.5f, -0.5f, +0.0f, // Position 3
	};
	const GLfloat sqaure_c[] =
	{
		+1.0f, +0.0f, +0.0f,
		+0.0f, +1.0f, +0.0f,
		+0.0f, +0.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
	};

	GLushort indices[] = 
	{ 
		0,1,2,
		2,3,0 
	};

	glBindVertexArray(vao[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square) + sizeof(sqaure_c), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(square), square);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(square), sizeof(sqaure_c), sqaure_c);
	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	////vertex color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (char*)(sizeof(sqaure_c)));
	GLuint vbo_idx;
	glGenBuffers(1, &vbo_idx);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_idx);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

// VAO 2
void draw_plane() {
	const GLfloat square[] =
	{
		-10.0f,  -0.5f,  10.0f, // Position 0
		10.0f,   -0.5f,  10.0f, // Position 1
		-10.0f,  -0.5f, -10.0f, // Position 2
		10.0f,   -0.5f, -10.0f, // Position 3
	};
	const GLfloat sqaure_c[] =
	{
		+0.5f, +0.5f, +0.0f,
		+0.5f, +0.5f, +0.0f,
		+0.5f, +0.0f, +0.5f,
		+0.5f, +0.0f, +0.5f,
	};

	GLushort indices[] =
	{
		0,1,2,
		1,2,3,
	};

	glBindVertexArray(vao[2]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square) + sizeof(sqaure_c), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(square), square);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(square), sizeof(sqaure_c), sqaure_c);
	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	////vertex color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (char*)(sizeof(sqaure_c)));
	GLuint vbo_idx;
	glGenBuffers(1, &vbo_idx);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_idx);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

// VAO 3
void draw_pyramid_1() {
	const GLfloat py[] =
	{
		+0.0f, +0.5f, +0.0f, // Position 0
		+0.5f, -0.5f, +0.5f, // Position 1
		-0.5f, -0.5f, +0.5f, // Position 2
		+0.5f, -0.5f, -0.5f, // Position 3
		-0.5f, -0.5f, -0.5f, // Position 4

	};
	const GLfloat py_c[] =
	{
		+1.0f, +1.0f, +1.0f,
		+1.0f, +0.3f, +0.8f,
		+0.3f, +0.5f, +1.0f,
		+0.3f, +1.0f, +0.5f,
		+1.0f, +0.8f, +0.3f,
	};

	GLushort indices[] =
	{
		0,1,2,
		0,1,3,
		0,2,4,
		0,3,4,
		1,2,3,
		2,3,4,
	};

	glBindVertexArray(vao[3]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(py) + sizeof(py_c), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(py), py);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(py), sizeof(py_c), py_c);
	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	////vertex color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (char*)(sizeof(py_c)));
	GLuint vbo_idx;
	glGenBuffers(1, &vbo_idx);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_idx);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

// VAO 4
void draw_pyramid_2() {
	const GLfloat py[] =
	{
		+0.0f, +0.5f, +0.0f, // Position 0
		+0.5f, -0.5f, +0.5f, // Position 1
		-0.5f, -0.5f, +0.5f, // Position 2
		+0.5f, -0.5f, -0.5f, // Position 3
		-0.5f, -0.5f, -0.5f, // Position 4

	};
	const GLfloat py_c[] =
	{
		+1.0f, +1.0f, +1.0f,
		+1.0f, +0.3f, +0.8f,
		+0.3f, +0.5f, +1.0f,
		+0.3f, +1.0f, +0.5f,
		+1.0f, +0.8f, +0.3f,
	};

	GLushort indices[] =
	{
		0,1,2,
		0,1,3,
		0,2,4,
		0,3,4,
		1,2,3,
		2,3,4,
	};

	glBindVertexArray(vao[4]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(py) + sizeof(py_c), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(py), py);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(py), sizeof(py_c), py_c);
	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	////vertex color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (char*)(sizeof(py_c)));
	GLuint vbo_idx;
	glGenBuffers(1, &vbo_idx);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_idx);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

// VAO 5
void draw_crystal() {
	const GLfloat py[] =
	{
		+0.0f, +1.1f, +0.0f, // Position 0
		-0.2f, +0.8f, +0.2f, // Position 1
		+0.2f, +0.8f, +0.2f, // Position 2
		+0.2f, +0.8f, -0.2f, // Position 3
		-0.2f, +0.8f, -0.2f, // Position 4
		-0.2f, +0.3f, +0.2f, // Position 5
		+0.2f, +0.3f, +0.2f, // Position 6
		+0.2f, +0.3f, -0.2f, // Position 7
		-0.2f, +0.3f, -0.2f, // Position 8
		+0.0f, +0.0f, +0.0f, // Position 9

	};
	const GLfloat py_c[] =
	{
		+1.0f, +0.3f, +0.3f,
		+1.0f, +0.5f, +0.5f,
		+1.0f, +0.5f, +0.5f,
		+1.0f, +0.5f, +0.5f,
		+1.0f, +0.5f, +0.5f,
		+1.0f, +0.7f, +0.7f,
		+1.0f, +0.7f, +0.7f,
		+1.0f, +0.7f, +0.7f,
		+1.0f, +0.7f, +0.7f,
		+1.0f, +1.0f, +1.0f,
	};

	GLushort indices[] =
	{
		0,1,2,
		0,1,4,
		0,2,3,
		0,3,4,
		1,4,5,
		4,5,8,
		3,4,8,
		3,7,8,
		2,3,7,
		2,6,7,
		1,2,5,
		2,5,6,
		5,6,9,
		5,8,9,
		7,8,9,
		6,7,9,
	};

	glBindVertexArray(vao[5]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(py) + sizeof(py_c), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(py), py);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(py), sizeof(py_c), py_c);
	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	////vertex color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (char*)(sizeof(py_c)));
	GLuint vbo_idx;
	glGenBuffers(1, &vbo_idx);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_idx);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}


void sendDataToOpenGL()
{

	glGenVertexArrays(6, vao);
	glGenBuffers(6, vbo);
	draw_plane();
	draw_rectangle();
	draw_triangle();
	draw_pyramid_1();
	draw_pyramid_2();
	draw_crystal();
}

bool checkStatus(
	GLuint objectID,
	PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
	PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
	GLenum statusType)
{
	GLint status;
	objectPropertyGetterFunc(objectID, statusType, &status);
	if (status != GL_TRUE)
	{
		GLint infoLogLength;
		objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);
		cout << buffer << endl;

		delete[] buffer;
		return false;
	}
	return true;
}

bool checkShaderStatus(GLuint shaderID)
{
	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool checkProgramStatus(GLuint programID)
{
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

string readShaderCode(const char* fileName)
{
	ifstream meInput(fileName);
	if (!meInput.good())
	{
		cout << "File failed to load..." << fileName;
		exit(1);
	}
	return std::string(
		std::istreambuf_iterator<char>(meInput),
		std::istreambuf_iterator<char>()
	);
}

void installShaders()
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* adapter[1];
	//adapter[0] = vertexShaderCode;
	string temp = readShaderCode("VertexShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);
	//adapter[0] = fragmentShaderCode;
	temp = readShaderCode("FragmentShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if (!checkShaderStatus(vertexShaderID) || !checkShaderStatus(fragmentShaderID))
		return;

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	if (!checkProgramStatus(programID))
		return;
	glUseProgram(programID);

}

void initializedGL(void) //run only once
{
	sendDataToOpenGL();
	installShaders();
}

void paintGL(void)  //always run
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.56f, 0.894f, 1.0f, 1.0f); //specify the background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	c_time = glutGet(GLUT_ELAPSED_TIME);
	//Define useful items
	mat4 modelTransformMatrix;
	GLint modelTransformMatrixUniformLocation = glGetUniformLocation(programID, "modelTransformMatrix");
	
	//Define camera
	View = glm::lookAt(
		//vec3(sin(x_delta * x_press_num)*3.0f, 0.0f , cos(x_delta * x_press_num)*3.0f),  // Rotate Camera
		vec3(x_delta * x_press_num, 5.0f , y_delta * y_press_num + 10.0f),
		vec3(x_delta * x_press_num, -1.0f, y_delta * y_press_num),
		vec3(0.0f, 1.0f, 0.0f)   // Head is up (set to 0,-1,0 to look upside-down)
	);
	mat4 projectionMatrix;
	projectionMatrix = glm::perspective(0.78f, 1.0f, 1.0f, 100.0f) * View * mat4(1.0f);
	GLint projectionMatrixUniformLocation = glGetUniformLocation(programID, "projectionMatrix");
	glUniformMatrix4fv(projectionMatrixUniformLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

	// ********************************
	//Bind plane to be transformed
	glBindVertexArray(vao[2]);
	//Define transform
	modelTransformMatrix = mat4(1.0f);
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1, GL_FALSE, &modelTransformMatrix[0][0]);
	//Draw object
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	// ********************************

	// ********************************
	//Bind rectangle to be transformed
	glBindVertexArray(vao[1]);
	//Define transform
	//modelTransformMatrix = mat4(1.0f);
	modelTransformMatrix = glm::translate(mat4(), vec3((float)sin(c_time * speed), (float)cos(c_time * speed)-0.5f, -10.0f));;
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1, GL_FALSE, &modelTransformMatrix[0][0]);
	//Draw object
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	// ********************************

	// ********************************
	//Bind triangle to be transformed
	glBindVertexArray(vao[0]);
	//Define transform
	//modelTransformMatrix = mat4(1.0f);
	vec3 dirVec = vec3(x_delta * x_press_num, 0.0f, y_delta * y_press_num) - vec3(crystal_x, 0.0f, crystal_y);
	vec3 zVec = vec3(0.0f, 0.0f, 0.01f);
	float angle = std::acos(dot(dirVec, zVec) / (mag(dirVec) * mag(zVec)));
	if (x_delta * x_press_num > crystal_x) {
		angle = -angle;
	}
	mat4 rotateMatrix = glm::rotate(mat4(), -angle + 3.142f, vec3(0.0f, 1.0f, 0.0f));;
	modelTransformMatrix = glm::translate(mat4(), vec3(x_delta * x_press_num, 0.0f, y_delta * y_press_num))* rotateMatrix;;
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1, GL_FALSE, &modelTransformMatrix[0][0]);
	//Draw object
	glDrawArrays(GL_TRIANGLES, 0, 3); //render primitives from array data
	// ********************************

	float rotate_speed = c_time * 0.001f;

	// ********************************
	//Bind pyramid to be transformed
	glBindVertexArray(vao[3]);
	//Define transform
	mat4 scaleMatrix = glm::scale(mat4(), vec3(0.5f + score, 0.5f + score, 0.5f + score));;
	rotateMatrix = glm::rotate(mat4(), rotate_speed, vec3(0.0f, 1.0f, 0.0f));;
	modelTransformMatrix = glm::translate(mat4(), vec3(x_delta * x_press_num, 0.0f, y_delta * y_press_num))*rotateMatrix*scaleMatrix;;
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1, GL_FALSE, &modelTransformMatrix[0][0]);
	//Draw object
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(vao[4]);
	//Define transform
	rotateMatrix = glm::rotate(mat4(), 2.34f+rotate_speed, vec3(0.0f, 1.0f, 0.0f));;
	modelTransformMatrix = glm::translate(mat4(), vec3(x_delta * x_press_num, 0.0f, y_delta * y_press_num)) * rotateMatrix*scaleMatrix;;
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1, GL_FALSE, &modelTransformMatrix[0][0]);
	//Draw object
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, 0);
	// ********************************
	
	checkCollision();

	// ********************************
	//Bind crystal to be transformed
	glBindVertexArray(vao[5]);
	//Define transform
	rotateMatrix = glm::rotate(mat4(), rotate_speed, vec3(0.0f, 1.0f, 0.0f));;
	modelTransformMatrix = glm::translate(mat4(), vec3(crystal_x, 0.0f, crystal_y)) * rotateMatrix;
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1, GL_FALSE, &modelTransformMatrix[0][0]);
	//Draw object
	glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_SHORT, 0);
	// ********************************

	glFlush(); //force execution of GL commands
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 'a') { x_press_num -= 1; }
	if (key == 'd') { x_press_num += 1; }
	if (key == 'w') { y_press_num -= 1; }
	if (key == 's') { y_press_num += 1; }
	//printf("[%c] key is down.\n", key);
}

int main(int argc, char* argv[])
{
	/*Initialization*/
	glutInit(&argc, argv); 
	/*
	glEnable(GL_MULTISAMPLE);
	glutSetOption(GLUT_MULTISAMPLE, 4);
	glutInitDisplayMode(GLUT_MULTISAMPLE);*/
	glutInitWindowSize(512, 512);
	glutCreateWindow("Assignment 1");
	glewInit();
	srand(time(NULL));
	randomCrystalLocation();

	/*Register different CALLBACK function for GLUT to response
	with different events, e.g. window sizing, mouse click or
	keyboard stroke */
	initializedGL();
	glutDisplayFunc(paintGL);
	glutKeyboardFunc(keyboard);

	/*Enter the GLUT event processing loop which never returns.
	it will call different registered CALLBACK according
	to different events. */
	glutMainLoop();

	return 0;
}
