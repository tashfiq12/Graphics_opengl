/**
 *
 *
 * File:	main.cpp
 *
 * Summary:
 *
 * This is a (very) basic program to
 * 1) load shaders from external files, and make a shader program
 * 2) make Vertex Array Object and Vertex Buffer Object for the quad
 *
 **/

#include <iostream>
#include <cmath>
#include <chrono>
#include <limits>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "ShaderTools.h"
#include "Vec3f.h"
#include "Mat4f.h"
#include "OpenGLMatrixTools.h"
#include "Camera.h"

//==================== GLOBAL VARIABLES ====================//
/*	Put here for simplicity. Feel free to restructure into
*	appropriate classes or abstractions.
*/

// Drawing Program
GLuint basicProgramID;
GLuint basicProgramID1;

// Data needed for Cube
GLuint vaoID1;
GLuint vertBufferID1;
Mat4f M1;

// Data needed for Cube
GLuint vaoID;
GLuint vertBufferID;
Mat4f M;

GLuint vaoID2;
GLuint vertBufferID2;
Mat4f M2;

GLuint vaoID3;
GLuint vertBufferID3;
Mat4f M3;

GLuint vaoID4;
GLuint vertBufferID4;
Mat4f M4;

GLuint vaoID5;
GLuint vertBufferID5;
Mat4f M5;

GLuint vaoID6;
GLuint vertBufferID6;
Mat4f M6;



GLuint road_vaoID1;
GLuint road_vertBufferID1;
Mat4f road_M1;




// Only one camera so only one veiw and perspective matrix are needed.
Mat4f V;
Mat4f P;

// Only one thing is rendered at a time, so only need one MVP
// When drawing different objects, update M and MVP = M * V * P
Mat4f MVP;

// Camera and veiwing Stuff
Camera camera;
int g_moveUpDown = 0;
int g_moveLeftRight = 0;
int g_moveBackForward = 0;
int g_rotateLeftRight = 0;
int g_rotateUpDown = 0;
int g_rotateRoll = 0;
float g_rotationSpeed = 0.015625;
float g_panningSpeed = 0.25;
bool g_cursorLocked;
float g_cursorX, g_cursorY;

bool g_play = false;

int WIN_WIDTH = 800, WIN_HEIGHT = 600;
int FB_WIDTH = 800, FB_HEIGHT = 600;
float WIN_FOV = 60;
float WIN_NEAR = 0.01;
float WIN_FAR = 1000;

//==================== FUNCTION DECLARATIONS ====================//
void displayFunc();
void resizeFunc();
void init();
void generateIDs();
void deleteIDs();
void setupVAO();
void loadQuadGeometryToGPU();
void loadPyramidGeometryToGPU();
void loadLineGeometryToGPU();
void reloadProjectionMatrix();
void loadModelViewMatrix();
void setupModelViewProjectionTransform();

void windowSetSizeFunc();
void windowKeyFunc(GLFWwindow *window, int key, int scancode, int action,
                   int mods);
void windowMouseMotionFunc(GLFWwindow *window, double x, double y);
void windowSetSizeFunc(GLFWwindow *window, int width, int height);
void windowSetFramebufferSizeFunc(GLFWwindow *window, int width, int height);
void windowMouseButtonFunc(GLFWwindow *window, int button, int action,
                           int mods);
void windowMouseMotionFunc(GLFWwindow *window, double x, double y);
void windowKeyFunc(GLFWwindow *window, int key, int scancode, int action,
                   int mods);
void animateQuad(float t);
void moveCamera();
void reloadMVPUniform(GLuint ProgramID);
void reloadColorUniform(float r, float g, float b, GLuint ProgramID);
std::string GL_ERROR();
int main(int, char **);

//==================== FUNCTION DEFINITIONS ====================//

void displayFunc() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Use our shader
  glUseProgram(basicProgramID1);

  // ===== DRAW QUAD ====== //
  MVP = P * V * M;
  reloadMVPUniform(basicProgramID1);
  reloadColorUniform(1, 1, 0, basicProgramID1);

  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vaoID);
  // Draw Cube, start at vertex 0, draw 36 of them (for a Cube)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 36);
  // ===== DRAW QUAD ====== //
  MVP = P * V * M1;
  reloadMVPUniform(basicProgramID1);
  reloadColorUniform(1, 1, 0, basicProgramID1);

  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vaoID1);
  // Draw Cube, start at vertex 0, draw 36 of them (for a Cube)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 36);


    MVP = P * V * M2;
  reloadMVPUniform(basicProgramID1);
  reloadColorUniform(0,0,0, basicProgramID1);

  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vaoID2);
  // Draw Cube, start at vertex 0, draw 36 of them (for a Cube)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 36);


    MVP = P * V * M3;
  reloadMVPUniform(basicProgramID1);
  reloadColorUniform(0,0,0, basicProgramID1);

  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vaoID3);
  // Draw Cube, start at vertex 0, draw 36 of them (for a Cube)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 36);



    MVP = P * V * M4;
  reloadMVPUniform(basicProgramID1);
  reloadColorUniform(0,0,0, basicProgramID1);

  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vaoID4);
  // Draw Cube, start at vertex 0, draw 36 of them (for a Cube)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 36);


    MVP = P * V * M5;
  reloadMVPUniform(basicProgramID1);
  reloadColorUniform(0,0,0, basicProgramID1);

  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vaoID5);
  // Draw Cube, start at vertex 0, draw 36 of them (for a Cube)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 36);


    MVP = P * V * M6;
  reloadMVPUniform(basicProgramID1);
  reloadColorUniform(1, 1, 0, basicProgramID1);

  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vaoID6);
  // Draw Cube, start at vertex 0, draw 36 of them (for a Cube)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 36);



    MVP = P * V * road_M1;
  reloadMVPUniform(basicProgramID1);
  reloadColorUniform(.5, .5, 1, basicProgramID1);

  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(road_vaoID1);
  // Draw Cube, start at vertex 0, draw 36 of them (for a Cube)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 36);



  glUseProgram(basicProgramID);


}

void animateQuad(float t) {
  M = RotateAboutYMatrix(0);
  M1 = RotateAboutYMatrix(0);
  M2 = RotateAboutYMatrix(0);
  M3 = RotateAboutYMatrix(0);
  M4 = RotateAboutYMatrix(0);
  M5 = RotateAboutYMatrix(0);
  M6 = RotateAboutYMatrix(0);

  float s = (std::sin(t) + 1.f) / 2.f;
  float x = (1 - s) * (20) + s * (-20);

  M = TranslateMatrix(x, 0, 0) * M;
  M1 = TranslateMatrix(x, 0, 0) * M1;
  M2 = TranslateMatrix(x, 0, 0) * M2;
  M3 = TranslateMatrix(x, 0, 0) * M3;
  M4 = TranslateMatrix(x, 0, 0) * M4;
  M5 = TranslateMatrix(x, 0, 0) * M5;
  M6 = TranslateMatrix(x, 0, 0) * M6;

  setupModelViewProjectionTransform();
  reloadMVPUniform(basicProgramID1);
}

void loadQuadGeometryToGPU() {
  // Just basic layout of floats, for a cube
  // 3 floats per vertex, 4 vertices
  std::vector<Vec3f> verts;
verts.push_back(Vec3f(-14.0f,3.0f,0.0f));
verts.push_back(Vec3f(-14.0f,3.0f, 9.0f));
verts.push_back(Vec3f(-13.0f, 5.0f, 9.0f));
verts.push_back(Vec3f(12.0f, 5.0f,0.0f));
verts.push_back(Vec3f(-14.0f,3.0f,0.0f));
verts.push_back(Vec3f(-13.0f, 5.0f,0.0f));
verts.push_back(Vec3f(13.0f,3.0f, 9.0f));
verts.push_back(Vec3f(-14.0f,3.0f,0.0f));
verts.push_back(Vec3f(13.0f,3.0f,0.0f));
verts.push_back(Vec3f(12.0f, 5.0f,0.0f));
verts.push_back(Vec3f(13.0f,3.0f,0.0f));
verts.push_back(Vec3f(-14.0f,3.0f,0.0f));
verts.push_back(Vec3f(-14.0f,3.0f,0.0f));
verts.push_back(Vec3f(-13.0f, 5.0f, 9.0f));
verts.push_back(Vec3f(-13.0f, 5.0f,0.0f));
verts.push_back(Vec3f(13.0f,3.0f, 9.0f));
verts.push_back(Vec3f(-14.0f,3.0f, 9.0f));
verts.push_back(Vec3f(-14.0f,3.0f,0.0f));
verts.push_back(Vec3f(-13.0f, 5.0f, 9.0f));
verts.push_back(Vec3f(-14.0f,3.0f, 9.0f));
verts.push_back(Vec3f(13.0f,3.0f, 9.0f));
verts.push_back(Vec3f(12.0f, 5.0f, 9.0f));
verts.push_back(Vec3f(13.0f,3.0f,0.0f));
verts.push_back(Vec3f(12.0f, 5.0f,0.0f));
verts.push_back(Vec3f(13.0f,3.0f,0.0f));
verts.push_back(Vec3f(12.0f, 5.0f, 9.0f));
verts.push_back(Vec3f(13.0f,3.0f, 9.0f));
verts.push_back(Vec3f(12.0f, 5.0f, 9.0f));
verts.push_back(Vec3f(12.0f, 5.0f,0.0f));
verts.push_back(Vec3f(-13.0f, 5.0f,0.0f));
verts.push_back(Vec3f(12.0f, 5.0f, 9.0f));
verts.push_back(Vec3f(-13.0f, 5.0f,0.0f));
verts.push_back(Vec3f(-13.0f, 5.0f, 9.0f));
verts.push_back(Vec3f(12.0f, 5.0f, 9.0f));
verts.push_back(Vec3f(-13.0f, 5.0f, 9.0f));
verts.push_back(Vec3f(13.0f,3.0f, 9.0f));
  glBindBuffer(GL_ARRAY_BUFFER, vertBufferID);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 36, // byte size of Vec3f, 4 of them
               verts.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}

void loadQuadGeometryToGPU1() {
  // Just basic layout of floats, for a cube
  // 3 floats per vertex, 4 vertices
  std::vector<Vec3f> verts;
verts.push_back(Vec3f(-11.0f,3.0f,0.0f));
verts.push_back(Vec3f(-11.0f,3.0f, 9.0f));
verts.push_back(Vec3f(-9.0f, 9.0f, 9.0f));
verts.push_back(Vec3f(9.0f, 9.0f,0.0f));
verts.push_back(Vec3f(-11.0f,3.0f,0.0f));
verts.push_back(Vec3f(-9.0f, 9.0f,0.0f));
verts.push_back(Vec3f(11.0f,3.0f, 9.0f));
verts.push_back(Vec3f(-11.0f,3.0f,0.0f));
verts.push_back(Vec3f(11.0f,3.0f,0.0f));
verts.push_back(Vec3f(9.0f, 9.0f,0.0f));
verts.push_back(Vec3f(11.0f,3.0f,0.0f));
verts.push_back(Vec3f(-11.0f,3.0f,0.0f));
verts.push_back(Vec3f(-11.0f,3.0f,0.0f));
verts.push_back(Vec3f(-9.0f, 9.0f, 9.0f));
verts.push_back(Vec3f(-9.0f, 9.0f,0.0f));
verts.push_back(Vec3f(11.0f,3.0f, 9.0f));
verts.push_back(Vec3f(-11.0f,3.0f, 9.0f));
verts.push_back(Vec3f(-11.0f,3.0f,0.0f));
verts.push_back(Vec3f(-9.0f, 9.0f, 9.0f));
verts.push_back(Vec3f(-11.0f,3.0f, 9.0f));
verts.push_back(Vec3f(11.0f,3.0f, 9.0f));
verts.push_back(Vec3f(9.0f, 9.0f, 9.0f));
verts.push_back(Vec3f(11.0f,3.0f,0.0f));
verts.push_back(Vec3f(9.0f, 9.0f,0.0f));
verts.push_back(Vec3f(11.0f,3.0f,0.0f));
verts.push_back(Vec3f(9.0f, 9.0f, 9.0f));
verts.push_back(Vec3f(11.0f,3.0f, 9.0f));
verts.push_back(Vec3f(9.0f, 9.0f, 9.0f));
verts.push_back(Vec3f(9.0f, 9.0f,0.0f));
verts.push_back(Vec3f(-9.0f, 9.0f,0.0f));
verts.push_back(Vec3f(9.0f, 9.0f, 9.0f));
verts.push_back(Vec3f(-9.0f, 9.0f,0.0f));
verts.push_back(Vec3f(-9.0f, 9.0f, 9.0f));
verts.push_back(Vec3f(9.0f, 9.0f, 9.0f));
verts.push_back(Vec3f(-9.0f, 9.0f, 9.0f));
verts.push_back(Vec3f(11.0f,3.0f, 9.0f));
  glBindBuffer(GL_ARRAY_BUFFER, vertBufferID1);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 36, // byte size of Vec3f, 4 of them
               verts.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}

void loadQuadGeometryToGPU2() {
  // Just basic layout of floats, for a cube
  // 3 floats per vertex, 4 vertices
  std::vector<Vec3f> verts;
verts.push_back(Vec3f(-7.0f,0.5f,0.0f));
verts.push_back(Vec3f(-7.0f,0.5f, 2.0f));
verts.push_back(Vec3f(-7.0f, 3.0f, 2.0f));
verts.push_back(Vec3f(-3.0f, 3.0f,0.0f));
verts.push_back(Vec3f(-7.0f,0.5f,0.0f));
verts.push_back(Vec3f(-7.0f, 3.0f,0.0f));
verts.push_back(Vec3f(-3.0f,0.5f, 2.0f));
verts.push_back(Vec3f(-7.0f,0.5f,0.0f));
verts.push_back(Vec3f(-3.0f,0.5f,0.0f));
verts.push_back(Vec3f(-3.0f, 3.0f,0.0f));
verts.push_back(Vec3f(-3.0f,0.5f,0.0f));
verts.push_back(Vec3f(-7.0f,0.5f,0.0f));
verts.push_back(Vec3f(-7.0f,0.5f,0.0f));
verts.push_back(Vec3f(-7.0f, 3.0f, 2.0f));
verts.push_back(Vec3f(-7.0f, 3.0f,0.0f));
verts.push_back(Vec3f(-3.0f,0.5f, 2.0f));
verts.push_back(Vec3f(-7.0f,0.5f, 2.0f));
verts.push_back(Vec3f(-7.0f,0.5f,0.0f));
verts.push_back(Vec3f(-7.0f, 3.0f, 2.0f));
verts.push_back(Vec3f(-7.0f,0.5f, 2.0f));
verts.push_back(Vec3f(-3.0f,0.5f, 2.0f));
verts.push_back(Vec3f(-3.0f, 3.0f, 2.0f));
verts.push_back(Vec3f(-3.0f,0.5f,0.0f));
verts.push_back(Vec3f(-3.0f, 3.0f,0.0f));
verts.push_back(Vec3f(-3.0f,0.5f,0.0f));
verts.push_back(Vec3f(-3.0f, 3.0f, 2.0f));
verts.push_back(Vec3f(-3.0f,0.5f, 2.0f));
verts.push_back(Vec3f(-3.0f, 3.0f, 2.0f));
verts.push_back(Vec3f(-3.0f, 3.0f,0.0f));
verts.push_back(Vec3f(-7.0f, 3.0f,0.0f));
verts.push_back(Vec3f(-3.0f, 3.0f, 2.0f));
verts.push_back(Vec3f(-7.0f, 3.0f,0.0f));
verts.push_back(Vec3f(-7.0f, 3.0f, 2.0f));
verts.push_back(Vec3f(-3.0f, 3.0f, 2.0f));
verts.push_back(Vec3f(-7.0f, 3.0f, 2.0f));
verts.push_back(Vec3f(-3.0f,0.5f, 2.0f));
  glBindBuffer(GL_ARRAY_BUFFER, vertBufferID2);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 36, // byte size of Vec3f, 4 of them
               verts.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}

void loadQuadGeometryToGPU3() {
  // Just basic layout of floats, for a cube
  // 3 floats per vertex, 4 vertices
  std::vector<Vec3f> verts;
verts.push_back(Vec3f(-7.0f,0.5f,7.0f));
verts.push_back(Vec3f(-7.0f,0.5f, 9.0f));
verts.push_back(Vec3f(-7.0f, 3.0f, 9.0f));
verts.push_back(Vec3f(-3.0f, 3.0f,7.0f));
verts.push_back(Vec3f(-7.0f,0.5f,7.0f));
verts.push_back(Vec3f(-7.0f, 3.0f,7.0f));
verts.push_back(Vec3f(-3.0f,0.5f, 9.0f));
verts.push_back(Vec3f(-7.0f,0.5f,7.0f));
verts.push_back(Vec3f(-3.0f,0.5f,7.0f));
verts.push_back(Vec3f(-3.0f, 3.0f,7.0f));
verts.push_back(Vec3f(-3.0f,0.5f,7.0f));
verts.push_back(Vec3f(-7.0f,0.5f,7.0f));
verts.push_back(Vec3f(-7.0f,0.5f,7.0f));
verts.push_back(Vec3f(-7.0f, 3.0f, 9.0f));
verts.push_back(Vec3f(-7.0f, 3.0f,7.0f));
verts.push_back(Vec3f(-3.0f,0.5f, 9.0f));
verts.push_back(Vec3f(-7.0f,0.5f, 9.0f));
verts.push_back(Vec3f(-7.0f,0.5f,7.0f));
verts.push_back(Vec3f(-7.0f, 3.0f, 9.0f));
verts.push_back(Vec3f(-7.0f,0.5f, 9.0f));
verts.push_back(Vec3f(-3.0f,0.5f, 9.0f));
verts.push_back(Vec3f(-3.0f, 3.0f, 9.0f));
verts.push_back(Vec3f(-3.0f,0.5f,7.0f));
verts.push_back(Vec3f(-3.0f, 3.0f,7.0f));
verts.push_back(Vec3f(-3.0f,0.5f,7.0f));
verts.push_back(Vec3f(-3.0f, 3.0f, 9.0f));
verts.push_back(Vec3f(-3.0f,0.5f, 9.0f));
verts.push_back(Vec3f(-3.0f, 3.0f, 9.0f));
verts.push_back(Vec3f(-3.0f, 3.0f,7.0f));
verts.push_back(Vec3f(-7.0f, 3.0f,7.0f));
verts.push_back(Vec3f(-3.0f, 3.0f, 9.0f));
verts.push_back(Vec3f(-7.0f, 3.0f,7.0f));
verts.push_back(Vec3f(-7.0f, 3.0f, 9.0f));
verts.push_back(Vec3f(-3.0f, 3.0f, 9.0f));
verts.push_back(Vec3f(-7.0f, 3.0f, 9.0f));
verts.push_back(Vec3f(-3.0f,0.5f, 9.0f));

  glBindBuffer(GL_ARRAY_BUFFER, vertBufferID3);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 36, // byte size of Vec3f, 4 of them
               verts.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}


void loadQuadGeometryToGPU4() {
  // Just basic layout of floats, for a cube
  // 3 floats per vertex, 4 vertices
  std::vector<Vec3f> verts;
verts.push_back(Vec3f(3.0f,0.5f,0.0f));
verts.push_back(Vec3f(3.0f,0.5f, 2.0f));
verts.push_back(Vec3f(3.0f, 3.0f, 2.0f));
verts.push_back(Vec3f(7.0f, 3.0f,0.0f));
verts.push_back(Vec3f(3.0f,0.5f,0.0f));
verts.push_back(Vec3f(3.0f, 3.0f,0.0f));
verts.push_back(Vec3f(7.0f,0.5f, 2.0f));
verts.push_back(Vec3f(3.0f,0.5f,0.0f));
verts.push_back(Vec3f(7.0f,0.5f,0.0f));
verts.push_back(Vec3f(7.0f, 3.0f,0.0f));
verts.push_back(Vec3f(7.0f,0.5f,0.0f));
verts.push_back(Vec3f(3.0f,0.5f,0.0f));
verts.push_back(Vec3f(3.0f,0.5f,0.0f));
verts.push_back(Vec3f(3.0f, 3.0f, 2.0f));
verts.push_back(Vec3f(3.0f, 3.0f,0.0f));
verts.push_back(Vec3f(7.0f,0.5f, 2.0f));
verts.push_back(Vec3f(3.0f,0.5f, 2.0f));
verts.push_back(Vec3f(3.0f,0.5f,0.0f));
verts.push_back(Vec3f(3.0f, 3.0f, 2.0f));
verts.push_back(Vec3f(3.0f,0.5f, 2.0f));
verts.push_back(Vec3f(7.0f,0.5f, 2.0f));
verts.push_back(Vec3f(7.0f, 3.0f, 2.0f));
verts.push_back(Vec3f(7.0f,0.5f,0.0f));
verts.push_back(Vec3f(7.0f, 3.0f,0.0f));
verts.push_back(Vec3f(7.0f,0.5f,0.0f));
verts.push_back(Vec3f(7.0f, 3.0f, 2.0f));
verts.push_back(Vec3f(7.0f,0.5f, 2.0f));
verts.push_back(Vec3f(7.0f, 3.0f, 2.0f));
verts.push_back(Vec3f(7.0f, 3.0f,0.0f));
verts.push_back(Vec3f(3.0f, 3.0f,0.0f));
verts.push_back(Vec3f(7.0f, 3.0f, 2.0f));
verts.push_back(Vec3f(3.0f, 3.0f,0.0f));
verts.push_back(Vec3f(3.0f, 3.0f, 2.0f));
verts.push_back(Vec3f(7.0f, 3.0f, 2.0f));
verts.push_back(Vec3f(3.0f, 3.0f, 2.0f));
verts.push_back(Vec3f(7.0f,0.5f, 2.0f));

  glBindBuffer(GL_ARRAY_BUFFER, vertBufferID4);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 36, // byte size of Vec3f, 4 of them
               verts.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}


void loadQuadGeometryToGPU5() {
  // Just basic layout of floats, for a cube
  // 3 floats per vertex, 4 vertices
  std::vector<Vec3f> verts;
verts.push_back(Vec3f(3.0f,0.5f,7.0f));
verts.push_back(Vec3f(3.0f,0.5f, 9.0f));
verts.push_back(Vec3f(3.0f, 3.0f, 9.0f));
verts.push_back(Vec3f(7.0f, 3.0f,7.0f));
verts.push_back(Vec3f(3.0f,0.5f,7.0f));
verts.push_back(Vec3f(3.0f, 3.0f,7.0f));
verts.push_back(Vec3f(7.0f,0.5f, 9.0f));
verts.push_back(Vec3f(3.0f,0.5f,7.0f));
verts.push_back(Vec3f(7.0f,0.5f,7.0f));
verts.push_back(Vec3f(7.0f, 3.0f,7.0f));
verts.push_back(Vec3f(7.0f,0.5f,7.0f));
verts.push_back(Vec3f(3.0f,0.5f,7.0f));
verts.push_back(Vec3f(3.0f,0.5f,7.0f));
verts.push_back(Vec3f(3.0f, 3.0f, 9.0f));
verts.push_back(Vec3f(3.0f, 3.0f,7.0f));
verts.push_back(Vec3f(7.0f,0.5f, 9.0f));
verts.push_back(Vec3f(3.0f,0.5f, 9.0f));
verts.push_back(Vec3f(3.0f,0.5f,7.0f));
verts.push_back(Vec3f(3.0f, 3.0f, 9.0f));
verts.push_back(Vec3f(3.0f,0.5f, 9.0f));
verts.push_back(Vec3f(7.0f,0.5f, 9.0f));
verts.push_back(Vec3f(7.0f, 3.0f, 9.0f));
verts.push_back(Vec3f(7.0f,0.5f,7.0f));
verts.push_back(Vec3f(7.0f, 3.0f,7.0f));
verts.push_back(Vec3f(7.0f,0.5f,7.0f));
verts.push_back(Vec3f(7.0f, 3.0f, 9.0f));
verts.push_back(Vec3f(7.0f,0.5f, 9.0f));
verts.push_back(Vec3f(7.0f, 3.0f, 9.0f));
verts.push_back(Vec3f(7.0f, 3.0f,7.0f));
verts.push_back(Vec3f(3.0f, 3.0f,7.0f));
verts.push_back(Vec3f(7.0f, 3.0f, 9.0f));
verts.push_back(Vec3f(3.0f, 3.0f,7.0f));
verts.push_back(Vec3f(3.0f, 3.0f, 9.0f));
verts.push_back(Vec3f(7.0f, 3.0f, 9.0f));
verts.push_back(Vec3f(3.0f, 3.0f, 9.0f));
verts.push_back(Vec3f(7.0f,0.5f, 9.0f));
  glBindBuffer(GL_ARRAY_BUFFER, vertBufferID5);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 36, // byte size of Vec3f, 4 of them
               verts.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}


void loadQuadGeometryToGPU6() {
  // Just basic layout of floats, for a cube
  // 3 floats per vertex, 4 vertices
  std::vector<Vec3f> verts;
verts.push_back(Vec3f(-9.0f,9.0f,0.0f));
verts.push_back(Vec3f(-9.0f,9.0f, 9.0f));
verts.push_back(Vec3f(-7.0f, 12.0f, 9.0f));
verts.push_back(Vec3f(7.0f, 12.0f,0.0f));
verts.push_back(Vec3f(-9.0f,9.0f,0.0f));
verts.push_back(Vec3f(-7.0f, 12.0f,0.0f));
verts.push_back(Vec3f(9.0f,9.0f, 9.0f));
verts.push_back(Vec3f(-9.0f,9.0f,0.0f));
verts.push_back(Vec3f(9.0f,9.0f,0.0f));
verts.push_back(Vec3f(7.0f, 12.0f,0.0f));
verts.push_back(Vec3f(9.0f,9.0f,0.0f));
verts.push_back(Vec3f(-9.0f,9.0f,0.0f));
verts.push_back(Vec3f(-9.0f,9.0f,0.0f));
verts.push_back(Vec3f(-7.0f, 12.0f, 9.0f));
verts.push_back(Vec3f(-7.0f, 12.0f,0.0f));
verts.push_back(Vec3f(9.0f,9.0f, 9.0f));
verts.push_back(Vec3f(-9.0f,9.0f, 9.0f));
verts.push_back(Vec3f(-9.0f,9.0f,0.0f));
verts.push_back(Vec3f(-7.0f, 12.0f, 9.0f));
verts.push_back(Vec3f(-9.0f,9.0f, 9.0f));
verts.push_back(Vec3f(9.0f,9.0f, 9.0f));
verts.push_back(Vec3f(7.0f, 12.0f, 9.0f));
verts.push_back(Vec3f(9.0f,9.0f,0.0f));
verts.push_back(Vec3f(7.0f, 12.0f,0.0f));
verts.push_back(Vec3f(9.0f,9.0f,0.0f));
verts.push_back(Vec3f(7.0f, 12.0f, 9.0f));
verts.push_back(Vec3f(9.0f,9.0f, 9.0f));
verts.push_back(Vec3f(7.0f, 12.0f, 9.0f));
verts.push_back(Vec3f(7.0f, 12.0f,0.0f));
verts.push_back(Vec3f(-7.0f, 12.0f,0.0f));
verts.push_back(Vec3f(7.0f, 12.0f, 9.0f));
verts.push_back(Vec3f(-7.0f, 12.0f,0.0f));
verts.push_back(Vec3f(-7.0f, 12.0f, 9.0f));
verts.push_back(Vec3f(7.0f, 12.0f, 9.0f));
verts.push_back(Vec3f(-7.0f, 12.0f, 9.0f));
verts.push_back(Vec3f(9.0f,9.0f, 9.0f));
  glBindBuffer(GL_ARRAY_BUFFER, vertBufferID6);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 36, // byte size of Vec3f, 4 of them
               verts.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}




void loadRoadGeometryToGPU1() {
  // Just basic layout of floats, for a quad
  // 3 floats per vertex, 4 vertices
  std::vector<Vec3f> verts;

verts.push_back(Vec3f(-100.0f,-1.0f,-20.0f));
verts.push_back(Vec3f(-100.0f,-1.0f, 10.0f));
verts.push_back(Vec3f(-100.0f, 0.5f, 10.0f));
verts.push_back(Vec3f(100.0f, 0.5f,-10.0f));
verts.push_back(Vec3f(-100.0f,-1.0f,-10.0f));
verts.push_back(Vec3f(-100.0f, 0.5f,-10.0f));
verts.push_back(Vec3f(100.0f,-1.0f, 10.0f));
verts.push_back(Vec3f(-100.0f,-1.0f,-10.0f));
verts.push_back(Vec3f(100.0f,-1.0f,-10.0f));
verts.push_back(Vec3f(100.0f, 0.5f,-10.0f));
verts.push_back(Vec3f(100.0f,-1.0f,-10.0f));
verts.push_back(Vec3f(-100.0f,-1.0f,-10.0f));
verts.push_back(Vec3f(-100.0f,-1.0f,-10.0f));
verts.push_back(Vec3f(-100.0f, 0.5f, 10.0f));
verts.push_back(Vec3f(-100.0f, 0.5f,-10.0f));
verts.push_back(Vec3f(100.0f,-1.0f, 10.0f));
verts.push_back(Vec3f(-100.0f,-1.0f, 10.0f));
verts.push_back(Vec3f(-100.0f,-1.0f,-10.0f));
verts.push_back(Vec3f(-100.0f, 0.5f, 10.0f));
verts.push_back(Vec3f(-100.0f,-1.0f, 10.0f));
verts.push_back(Vec3f(100.0f,-1.0f, 10.0f));
verts.push_back(Vec3f(100.0f, 0.5f, 10.0f));
verts.push_back(Vec3f(100.0f,-1.0f,-10.0f));
verts.push_back(Vec3f(100.0f, 0.5f,-10.0f));
verts.push_back(Vec3f(100.0f,-1.0f,-10.0f));
verts.push_back(Vec3f(100.0f, 0.5f, 10.0f));
verts.push_back(Vec3f(100.0f,-1.0f, 10.0f));
verts.push_back(Vec3f(100.0f, 0.5f, 10.0f));
verts.push_back(Vec3f(100.0f, 0.5f,-10.0f));
verts.push_back(Vec3f(-100.0f, 0.5f,-10.0f));
verts.push_back(Vec3f(100.0f, 0.5f, 10.0f));
verts.push_back(Vec3f(-100.0f, 0.5f,-10.0f));
verts.push_back(Vec3f(-100.0f, 0.5f, 10.0f));
verts.push_back(Vec3f(100.0f, 0.5f, 10.0f));
verts.push_back(Vec3f(-100.0f, 0.5f, 10.0f));
verts.push_back(Vec3f(100.0f,-1.0f, 10.0f));


  glBindBuffer(GL_ARRAY_BUFFER, road_vertBufferID1);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 36, // byte size of Vec3f, 4 of them
               verts.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}

void setupVAO() {
  glBindVertexArray(vaoID);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBufferID);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );

  glBindVertexArray(vaoID1);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBufferID1);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );

    glBindVertexArray(vaoID2);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBufferID2);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );

  glBindVertexArray(vaoID3);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBufferID3);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );


  glBindVertexArray(vaoID4);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBufferID4);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );


  glBindVertexArray(vaoID5);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBufferID5);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );


  glBindVertexArray(vaoID6);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBufferID6);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );



  glBindVertexArray(road_vaoID1);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER,road_vertBufferID1);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );



  glBindVertexArray(0); // reset to default

}

void reloadProjectionMatrix() {
  // Perspective Only

  // field of view angle 60 degrees
  // window aspect ratio
  // near Z plane > 0
  // far Z plane

  P = PerspectiveProjection(WIN_FOV, // FOV
                            static_cast<float>(WIN_WIDTH) /
                                WIN_HEIGHT, // Aspect
                            WIN_NEAR,       // near plane
                            WIN_FAR);       // far plane depth
}

void loadModelViewMatrix() {
  M = IdentityMatrix();
  M1 = IdentityMatrix();
  M2 = IdentityMatrix();
  M3 = IdentityMatrix();
  M4 = IdentityMatrix();
  M5 = IdentityMatrix();
  M6 = IdentityMatrix();

  road_M1 = IdentityMatrix();
   // view doesn't change, but if it did you would use this
  V = camera.lookatMatrix();
}

void reloadViewMatrix() { V = camera.lookatMatrix(); }

void setupModelViewProjectionTransform() {
  MVP = P * V * M; // transforms vertices from right to left (odd huh?)
  MVP = P * V * M1; // transforms vertices from right to left (odd huh?)
  MVP = P * V * M2; // transforms vertices from right to left (odd huh?)
  MVP = P * V * M3; // transforms vertices from right to left (odd huh?)
  MVP = P * V * M4; // transforms vertices from right to left (odd huh?)
  MVP = P * V * M5; // transforms vertices from right to left (odd huh?)
  MVP = P * V * M6; // transforms vertices from right to left (odd huh?)
  MVP = P * V * road_M1; // transforms vertices from right to left (odd huh?)

}

void reloadMVPUniform(GLuint ProgramID) {
  GLint id = glGetUniformLocation(ProgramID, "MVP");

  glUseProgram(ProgramID);
  glUniformMatrix4fv(id,        // ID
                     1,         // only 1 matrix
                     GL_TRUE,   // transpose matrix, Mat4f is row major
                     MVP.data() // pointer to data in Mat4f
                     );
}

void reloadColorUniform(float r, float g, float b, GLuint ProgramID) {
  GLint id = glGetUniformLocation(ProgramID, "inputColor");

  glUseProgram(ProgramID);
  glUniform3f(id, // ID in basic_vs.glsl
              r, g, b);
}

void generateIDs() {
  // shader ID from OpenGL
  std::string vsSource = loadShaderStringfromFile("./shaders/basic.vert");
  std::string fsSource = loadShaderStringfromFile("./shaders/basic.frag");
  basicProgramID = CreateShaderProgram(vsSource, fsSource);

  std::string vsSource1 = loadShaderStringfromFile("./shaders/cube.vert");
  std::string fsSource1 = loadShaderStringfromFile("./shaders/cube.frag");
  basicProgramID1 = CreateShaderProgram(vsSource1, fsSource1);

  // VAO and buffer IDs given from OpenGL
  glGenVertexArrays(1, &vaoID);
  glGenBuffers(1, &vertBufferID);
  glGenVertexArrays(1, &vaoID1);
  glGenBuffers(1, &vertBufferID1);
  glGenVertexArrays(1, &vaoID2);
  glGenBuffers(1, &vertBufferID2);
  glGenVertexArrays(1, &vaoID3);
  glGenBuffers(1, &vertBufferID3);
  glGenVertexArrays(1, &vaoID4);
  glGenBuffers(1, &vertBufferID4);
  glGenVertexArrays(1, &vaoID5);
  glGenBuffers(1, &vertBufferID5);

  glGenVertexArrays(1, &vaoID6);
  glGenBuffers(1, &vertBufferID6);

  glGenVertexArrays(1, &road_vaoID1);
  glGenBuffers(1, &road_vertBufferID1);

}

void deleteIDs() {
  glDeleteProgram(basicProgramID);
  glDeleteProgram(basicProgramID1);

  glDeleteVertexArrays(1, &vaoID);
  glDeleteBuffers(1, &vertBufferID);
  glDeleteVertexArrays(1, &vaoID1);
  glDeleteBuffers(1, &vertBufferID1);
  glDeleteVertexArrays(1, &road_vaoID1);
  glDeleteBuffers(1, &road_vertBufferID1);
  glDeleteVertexArrays(1, &vaoID2);
  glDeleteBuffers(1, &vertBufferID2);
  glDeleteVertexArrays(1, &vaoID3);
  glDeleteBuffers(1, &vertBufferID3);
  glDeleteVertexArrays(1, &vaoID4);
  glDeleteBuffers(1, &vertBufferID4);
  glDeleteVertexArrays(1, &vaoID5);
  glDeleteBuffers(1, &vertBufferID5);

  glDeleteVertexArrays(1, &vaoID6);
  glDeleteBuffers(1, &vertBufferID6);


}

void init() {
  glEnable(GL_DEPTH_TEST);
  glPointSize(50);

  camera = Camera(Vec3f{0, 30, 100}, Vec3f{0, 0, -5}, Vec3f{0, 1, 0});

  // SETUP SHADERS, BUFFERS, VAOs

  generateIDs();
  setupVAO();
  loadQuadGeometryToGPU();
  loadQuadGeometryToGPU1();
  loadQuadGeometryToGPU2();
  loadQuadGeometryToGPU3();
  loadQuadGeometryToGPU4();
  loadQuadGeometryToGPU5();
  loadQuadGeometryToGPU6();


  loadRoadGeometryToGPU1();

  loadModelViewMatrix();
  reloadProjectionMatrix();
  setupModelViewProjectionTransform();
  reloadMVPUniform(basicProgramID);
}

int main(int argc, char **argv) {
  GLFWwindow *window;

  if (!glfwInit()) {
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window =
      glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "CSE414 Project 1", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  glfwSetWindowSizeCallback(window, windowSetSizeFunc);
  glfwSetFramebufferSizeCallback(window, windowSetFramebufferSizeFunc);
  glfwSetKeyCallback(window, windowKeyFunc);
  glfwSetCursorPosCallback(window, windowMouseMotionFunc);
  glfwSetMouseButtonCallback(window, windowMouseButtonFunc);

  glfwGetFramebufferSize(window, &WIN_WIDTH, &WIN_HEIGHT);

  // Initialize glad
  if (!gladLoadGL()) {
    std::cerr << "Failed to initialise GLAD" << std::endl;
    return -1;
  }

  std::cout << "GL Version: :" << glGetString(GL_VERSION) << std::endl;
  std::cout << GL_ERROR() << std::endl;

  // Initialize all the geometry, and load it once to the GPU
  init(); // our own initialize stuff func

  float t = 0;
  float dt = 0.01;

  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         !glfwWindowShouldClose(window)) {

    if (g_play) {
      t += dt;
      animateQuad(t);
    }

    displayFunc();
    moveCamera();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // clean up after loop
  deleteIDs();

  return 0;
}

//==================== CALLBACK FUNCTIONS ====================//

void windowSetSizeFunc(GLFWwindow *window, int width, int height) {
  WIN_WIDTH = width;
  WIN_HEIGHT = height;

  reloadProjectionMatrix();
  setupModelViewProjectionTransform();
  reloadMVPUniform(basicProgramID);
}

void windowSetFramebufferSizeFunc(GLFWwindow *window, int width, int height) {
  FB_WIDTH = width;
  FB_HEIGHT = height;

  glViewport(0, 0, FB_WIDTH, FB_HEIGHT);
}

void windowMouseButtonFunc(GLFWwindow *window, int button, int action,
                           int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT) {
    if (action == GLFW_PRESS) {
      g_cursorLocked = GL_TRUE;
    } else {
      g_cursorLocked = GL_FALSE;
    }
  }
}

void windowMouseMotionFunc(GLFWwindow *window, double x, double y) {
  if (g_cursorLocked) {
    float deltaX = (x - g_cursorX) * 0.01;
    float deltaY = (y - g_cursorY) * 0.01;
    camera.rotateAroundFocus(deltaX, deltaY);

    reloadViewMatrix();
    setupModelViewProjectionTransform();
    reloadMVPUniform(basicProgramID);
  }

  g_cursorX = x;
  g_cursorY = y;
}

void windowKeyFunc(GLFWwindow *window, int key, int scancode, int action,
                   int mods) {
  bool set = action != GLFW_RELEASE && GLFW_REPEAT;
  switch (key) {
  case GLFW_KEY_ESCAPE:
    glfwSetWindowShouldClose(window, GL_TRUE);
    break;
  case GLFW_KEY_W:
    g_moveBackForward = set ? 1 : 0;
    break;
  case GLFW_KEY_S:
    g_moveBackForward = set ? -1 : 0;
    break;
  case GLFW_KEY_A:
    g_moveLeftRight = set ? 1 : 0;
    break;
  case GLFW_KEY_D:
    g_moveLeftRight = set ? -1 : 0;
    break;
  case GLFW_KEY_Q:
    g_moveUpDown = set ? -1 : 0;
    break;
  case GLFW_KEY_E:
    g_moveUpDown = set ? 1 : 0;
    break;
  case GLFW_KEY_UP:
    g_rotateUpDown = set ? -1 : 0;
    break;
  case GLFW_KEY_DOWN:
    g_rotateUpDown = set ? 1 : 0;
    break;
  case GLFW_KEY_LEFT:
    if (mods == GLFW_MOD_SHIFT)
      g_rotateRoll = set ? -1 : 0;
    else
      g_rotateLeftRight = set ? 1 : 0;
    break;
  case GLFW_KEY_RIGHT:
    if (mods == GLFW_MOD_SHIFT)
      g_rotateRoll = set ? 1 : 0;
    else
      g_rotateLeftRight = set ? -1 : 0;
    break;
  case GLFW_KEY_SPACE:
    g_play = set ? !g_play : g_play;
    break;
  case GLFW_KEY_LEFT_BRACKET:
    if (mods == GLFW_MOD_SHIFT) {
      g_rotationSpeed *= 0.5;
    } else {
      g_panningSpeed *= 0.5;
    }
    break;
  case GLFW_KEY_RIGHT_BRACKET:
    if (mods == GLFW_MOD_SHIFT) {
      g_rotationSpeed *= 1.5;
    } else {
      g_panningSpeed *= 1.5;
    }
    break;
  default:
    break;
  }
}

//==================== OPENGL HELPER FUNCTIONS ====================//

void moveCamera() {
  Vec3f dir;

  if (g_moveBackForward) {
    dir += Vec3f(0, 0, g_moveBackForward * g_panningSpeed);
  }
  if (g_moveLeftRight) {
    dir += Vec3f(g_moveLeftRight * g_panningSpeed, 0, 0);
  }
  if (g_moveUpDown) {
    dir += Vec3f(0, g_moveUpDown * g_panningSpeed, 0);
  }

  if (g_rotateUpDown) {
    camera.rotateUpDown(g_rotateUpDown * g_rotationSpeed);
  }
  if (g_rotateLeftRight) {
    camera.rotateLeftRight(g_rotateLeftRight * g_rotationSpeed);
  }
  if (g_rotateRoll) {
    camera.rotateRoll(g_rotateRoll * g_rotationSpeed);
  }

  if (g_moveUpDown || g_moveLeftRight || g_moveBackForward ||
      g_rotateLeftRight || g_rotateUpDown || g_rotateRoll) {
    camera.move(dir);
    reloadViewMatrix();
    setupModelViewProjectionTransform();
    reloadMVPUniform(basicProgramID1);
  }
}

std::string GL_ERROR() {
  GLenum code = glGetError();

  switch (code) {
  case GL_NO_ERROR:
    return "GL_NO_ERROR";
  case GL_INVALID_ENUM:
    return "GL_INVALID_ENUM";
  case GL_INVALID_VALUE:
    return "GL_INVALID_VALUE";
  case GL_INVALID_OPERATION:
    return "GL_INVALID_OPERATION";
  case GL_INVALID_FRAMEBUFFER_OPERATION:
    return "GL_INVALID_FRAMEBUFFER_OPERATION";
  case GL_OUT_OF_MEMORY:
    return "GL_OUT_OF_MEMORY";
  default:
    return "Non Valid Error Code";
  }
}
