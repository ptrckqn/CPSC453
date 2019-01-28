/*
* Program.cpp
*
*  Created on: Sep 10, 2018
*      Author: John Hall
*/

#include "Program.h"

#include <iostream>
#include <string>

//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imagebuffer.h"
Program::Program() {
  setupWindow();
}

Program::~Program() {

}

void Program::start() {

  image.Initialize();
  // for (unsigned int i = 0; i < image.Width(); i++) {
  //   for (unsigned int j = 0; j < image.Height(); j++) {
  //     //set pixel colors here
  //     image.SetPixel(i, j, glm::vec3(1.0, 0.0, 0.0));
  //   }
  // }
  //Main render loop
  while(!glfwWindowShouldClose(window)) {
    // image.Render();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

}


void Program::setupWindow() {
  //Initialize the GLFW windowing system
  if (!glfwInit()) {
    std::cout << "ERROR: GLFW failed to initialize, TERMINATING" << std::endl;
    return;
  }

  //Set the custom error callback function
  //Errors will be printed to the console
  glfwSetErrorCallback(ErrorCallback);

  //Attempt to create a window with an OpenGL 4.1 core profile context
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  int width = 512;
  int height = 512;
  window = glfwCreateWindow(width, height, "CPSC 453 OpenGL Boilerplate", 0, 0);
  if (!window) {
    std::cout << "Program failed to create GLFW window, TERMINATING" << std::endl;
    glfwTerminate();
    return;
  }

  //Set the custom function that tracks key presses
  glfwSetKeyCallback(window, KeyCallback);

  //Bring the new window to the foreground (not strictly necessary but convenient)
  glfwMakeContextCurrent(window);

  //Intialize GLAD (finds appropriate OpenGL configuration for your system)
  if (!gladLoadGL()) {
    std::cout << "GLAD init failed" << std::endl;
    return;
  }

  //Query and print out information about our OpenGL environment
  QueryGLVersion();
}



void Program::QueryGLVersion() {
  // query opengl version and renderer information
  std::string version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
  std::string glslver = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));
  std::string renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));

  std::cout << "OpenGL [ " << version << " ] "
  << "with GLSL [ " << glslver << " ] "
  << "on renderer [ " << renderer << " ]" << std::endl;
}

void ErrorCallback(int error, const char* description) {
  std::cout << "GLFW ERROR " << error << ":" << std::endl;
  std::cout << description << std::endl;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  //Key codes are often prefixed with GLFW_KEY_ and can be found on the GLFW website
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
  if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
    image.Destroy();
    rayScene("scene1.txt");
  }
  if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
    image.Destroy();
    rayScene("scene2.txt");
  }
  if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
    image.Destroy();
    rayScene("scene3.txt");
  }
}

struct Ray{
  glm::vec3 o;
  glm::vec3 d;
  float length;
};

struct Light{
  glm::vec3 o;
  glm::vec3 c;
};

struct Shape{
  int shape;
  std::vector<glm::vec3> data;
  float add = 0.0f;
  glm::vec3 c;
  glm::vec3 sC;
  glm::vec3 sH;
  float p;
};

struct Intersection{
  float t;
  Shape shape;
};

std::vector<Shape> shapes;

Ray makeRay(int x, int y, int w, int h, glm::vec3 o, float d){
  Ray tempRay;

  tempRay.o = o;
  tempRay.length = d;
  tempRay.d.x = (float) x / (w / 2) - 1.0f - o.x;
  tempRay.d.y = (float) y / (h / 2) - 1.0f - o.y;
  tempRay.d.z = -d;

  return tempRay;
}

void readScene(std::vector<Shape> &shapes, Light *light, const char* fileName){
  std::ifstream f (fileName);

  const int bSize = 256;
  char buffer[bSize];

  while(f){
    std::string line;

    f >> line;

    if(line.compare("#") == 0){
      f.getline(buffer, bSize);
    }
    else if(line.compare("light") == 0){
      f.getline(buffer, bSize);
      f.getline(buffer, bSize);
      float x, y, z;

      if(sscanf(buffer, "%f %f %f", &x, &y, &z) == 3){
        light -> o = glm::vec3(x, y, z);
      }

      f.getline(buffer,bSize);
      if(sscanf(buffer, "%f %f %f", &x, &y, &z) == 3){
        light -> c = glm::vec3(x, y, z);
      }
    }

    else if(line.compare("sphere") == 0){
      Shape sphere;
      sphere.shape = 0;
      f.getline(buffer, bSize);
      f.getline(buffer, bSize);
      float x, y, z;

      if(sscanf(buffer,"%f %f %f", &x, &y, &z)==3){
        sphere.data.push_back(glm::vec3(x, y, z));
      }

      float r;
      f >> r;
      sphere.add = r;
      f.getline(buffer, bSize);
      f.getline(buffer, bSize);

      if(sscanf(buffer,"%f %f %f", &x, &y, &z) == 3){
        sphere.c = glm::vec3(x, y, z);
      }

      f.getline(buffer,bSize);

      if(sscanf(buffer,"%f %f %f", &x, &y, &z) == 3){
        sphere.sC = glm::vec3(x, y, z);
      }

      f.getline(buffer,bSize);

      if(sscanf(buffer,"%f %f %f", &x, &y, &z) == 3){
        sphere.sH = glm::vec3(x, y, z);
      }

      f.getline(buffer,bSize);

      if(sscanf(buffer,"%f", &x) == 1){
        sphere.p = x;
      }

      shapes.push_back(sphere);
    }

    else if(line.compare("plane") == 0){
      Shape plane;
      plane.shape = 1;
      f.getline(buffer, bSize);
      f.getline(buffer, bSize);
      float x, y, z;

      if(sscanf(buffer,"%f %f %f", &x, &y, &z) == 3){
        plane.data.push_back(glm::vec3(x, y, z));
      }

      f.getline(buffer, bSize);

      if(sscanf(buffer,"%f %f %f", &x, &y, &z) == 3){
        plane.data.push_back(glm::vec3(x, y, z));
      }

      f.getline(buffer,bSize);

      if(sscanf(buffer,"%f %f %f", &x, &y, &z) == 3){
        plane.c = glm::vec3(x, y, z);
      }

      f.getline(buffer,bSize);

      if(sscanf(buffer,"%f %f %f", &x, &y, &z) == 3){
        plane.sC = glm::vec3(x, y, z);
      }

      f.getline(buffer,bSize);

      if(sscanf(buffer,"%f %f %f", &x, &y, &z) == 3){
        plane.sH = glm::vec3(x, y, z);
      }

      f.getline(buffer,bSize);

      if(sscanf(buffer,"%f", &x) == 1){
        plane.p = x;
      }

      shapes.push_back(plane);
    }

    else if(line.compare("triangle") == 0){
      Shape triangle;
      triangle.shape = 2;
      f.getline(buffer, bSize);
      f.getline(buffer, bSize);
      float x, y, z;

      if(sscanf(buffer,"%f %f %f", &x, &y, &z) == 3){
        triangle.data.push_back(glm::vec3(x, y, z));
      }

      f.getline(buffer,bSize);

      if(sscanf(buffer,"%f %f %f", &x, &y, &z) == 3){
        triangle.data.push_back(glm::vec3(x, y, z));
      }

      f.getline(buffer,bSize);

      if(sscanf(buffer,"%f %f %f", &x, &y, &z) == 3){
        triangle.data.push_back(glm::vec3(x, y, z));
      }

      f.getline(buffer,bSize);

      if(sscanf(buffer,"%f %f %f", &x, &y, &z) == 3){
        triangle.c= glm::vec3(x, y, z);
      }

      f.getline(buffer,bSize);

      if(sscanf(buffer,"%f %f %f", &x, &y, &z) == 3){
        triangle.sC = glm::vec3(x, y, z);
      }

      f.getline(buffer,bSize);

      if(sscanf(buffer,"%f %f %f", &x, &y, &z) == 3){
        triangle.sH = glm::vec3(x, y, z);
      }

      f.getline(buffer,bSize);

      if(sscanf(buffer,"%f", &x) == 1){
        triangle.p = x;
      }

      shapes.push_back(triangle);
    }
  }

  f.close();
}

bool sphereRay(Ray r, Shape s, Intersection *i){
  bool intersected = false;
  glm::vec3 o = r.o;
  glm::vec3 d = r.d;
  glm::vec3 data = s.data[0];
  float a = s.add;

  float disc = pow(dot(d, o - data), 2) - dot(d, d) * (dot(o - data, o - data) - pow(a, 2));

  if(disc >= 0){
    intersected = true;
    float t = (-(dot(d, o - data)) - sqrt(disc)) / dot(d, d);
    i -> t = t;
    i -> shape = s;
  }

  return intersected;
}

bool planeRay(Ray r, Shape s, Intersection *i){
  bool intersected = false;
  glm::vec3 o = r.o;
  glm::vec3 d = r.d;
  glm::vec3 dataOne = s.data[0];
  glm::vec3 dataTwo = s.data[1];

  if(abs(dot(d, dataOne)) >= 0.0001){
    intersected = true;
    float t = dot((dataTwo - o), dataOne) / dot(d, dataOne);
    i -> t = t;
    i -> shape = s;
  }
  return intersected;
}

bool triangleRay(Ray r, Shape s, Intersection *i){
  bool intersected = false;
  glm::vec3 o = r.o;
  glm::vec3 d = r.d;
  glm::vec3 dataOne = s.data[0];
  glm::vec3 dataTwo = s.data[1];
  glm::vec3 dataThree = s.data[2];

  float A, B, C, D, E, F, G, H, I, J, K, L;
  A = dataOne.x - dataTwo.x;
  B = dataOne.y - dataTwo.y;
  C = dataOne.z - dataTwo.z;
  D = dataOne.x - dataThree.x;
  E = dataOne.y - dataThree.y;
  F = dataOne.z - dataThree.z;
  G = d.x;
  H = d.y;
  I = d.z;
  J = dataOne.x - o.x;
  K = dataOne.y - o.y;
  L = dataOne.z - o.z;

  float x = A * (E * I - H * F) + B * (G * F - D * I)+ C * (D * H - E * G);

  float y = (J * (E * I - H * F) + K * (G * F - D * I) + L * (D * H - E * G)) / x;
  float z = (I * (A * K - J * B) + H * (J * C - A * L) + G * (B * L - K * C)) / x;

  float t = -(F * (A * K - J * B) + E * (J * C - A * L) + D * (B * L - K * C)) / x;

  if((x != 0) && (z >= 0) && (z <= 1) && (y >= 0) && (y <= 1 - z)) {
    intersected = true;
    i -> t = t;
    i -> shape = s;
  }
  return intersected;
}

bool traceRay(Ray r, Shape s, Intersection *i){
  bool intersected = false;
  if(s.shape == 0){
    intersected = sphereRay(r, s, i);
  }
  else if(s.shape == 1){
    intersected = planeRay(r, s, i);
  }
  else if(s.shape == 2){
    intersected = triangleRay(r, s, i);
  }
  return intersected;
}

bool rayIntersection(Ray r, std::vector<Shape> sList, Intersection *i, float min, float max){
  bool intersected = false;
  float t = max;
  for(int j = 0; j < sList.size(); j++){
    Intersection tempI;
    if(traceRay(r, sList[j], &tempI)){
      if(tempI.t >= min && tempI.t < t){
        intersected = true;
        t = tempI.t;
        i -> t = t;
        i -> shape = tempI.shape;
      }
    }
  }
  return intersected;
}


glm::vec3 sNormVec(Ray r, Intersection i){
  glm::vec3 result;
  if (i.shape.shape == 0){
    result = (r.o + i.t * r.d) - i.shape.data[0];
  }

  else if(i.shape.shape == 1){
    result = i.shape.data[0];
  }

  else if(i.shape.shape == 2){
    result = cross(i.shape.data[1] - i.shape.data[0], i.shape.data[2] - i.shape.data[0]);
  }

  return normalize(result);
}

glm::vec3 rayColour(Ray ra, float min, float max, Light li, int count){
  Intersection tempI;
  if(rayIntersection(ra, shapes, &tempI, min, max)){
    glm::vec3 d = ra.d;
    glm::vec3 c = glm::vec3(0, 0, 0);
    glm::vec3 sNV = sNormVec(ra, tempI);
    glm::vec3 v = normalize(-d);
    glm::vec3 point = ra.o + tempI.t * d;
    c = tempI.shape.c * glm::vec3(0.4f, 0.4f, 0.4f);

    Ray shadow;
    shadow.o = point;
    shadow.d = (li.o - shadow.o);
    Intersection tempITwo;
    if(!rayIntersection(shadow, shapes, &tempITwo, 0.0001f, 1.0f)){
      glm::vec3 l = normalize(li.o - point);
      glm::vec3 kd = tempI.shape.c;
      glm::vec3 I = li.c;
      glm::vec3 ks = tempI.shape.sH;
      glm::vec3 h = normalize(v + l);
      c = c + kd * I * glm::max(0.0f, dot(sNV, l)) + ks * I * (float)(pow(glm::max(0.0f, dot(sNV, h)), tempI.shape.p));
    }

    glm::vec3 r = normalize(d) - 2 * dot(normalize(d), sNV) * sNV;
    glm::vec3 km = tempI.shape.sC;

    Ray reflected;
    reflected.o = point;
    reflected.d = r;

    if(tempI.shape.sC == glm::vec3(0, 0, 0)){
      count = 0;
    }

    if(count > 0){
      count--;
      return c + km * rayColour(reflected, 0.0001f, 99999.9f, li, count);
    }
    else{
      return c;
    }
  }

  else{
    return glm::vec3(0, 0, 0);
  }
}

void rayScene(const char* fileName){
  Light defaultL;
  image.Initialize();
  readScene(shapes, &defaultL, fileName);

  for(int i = 0; i < 512; i++){
    for(int j = 0; j < 512; j++){
      Ray r = makeRay(i, j, 512, 512, glm::vec3(0, 0, 0), 2.0f);
      glm::vec3 c = glm::vec3 (0, 0, 0);

      c = rayColour(r, 0.0f, 9999.9f, defaultL, 10);

      image.SetPixel(i, j, c);
    }
  }

  image.Render();

  image.SaveToFile("outputImage.png");
}
