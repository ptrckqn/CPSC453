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
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "texture.h"
#include "Viewport.h"

Program::Program() {
  setupWindow();
}

Program::~Program() {

}

void Program::start() {

  drawSolarSystem(0);

  //Main render loop
  // while(!glfwWindowShouldClose(window)) {
  // 	glfwSwapBuffers(window);
  // 	glfwPollEvents();
  // }

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
  int width = 1024;
  int height = 1024;
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
    drawSolarSystem(0);
  }
  if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
    drawSolarSystem(1);
  }
  if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
    drawSolarSystem(2);
  }
  if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
    drawSolarSystem(3);
  }
  if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
    drawSolarSystem(4);
  }
  if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
    drawSolarSystem(5);
  }
  if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
    drawSolarSystem(6);
  }
  if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
    drawSolarSystem(7);
  }
  if (key == GLFW_KEY_9 && action == GLFW_PRESS) {
    drawSolarSystem(8);
  }

}

std::string LoadSource(const std::string &filename)
{
  std::string source;

  std::ifstream input(filename.c_str());
  if (input) {
    copy(std::istreambuf_iterator<char>(input),
    std::istreambuf_iterator<char>(),
    back_inserter(source));
    input.close();
  }
  else {
    std::cout << "ERROR: Could not load shader source from file "
    << filename << std::endl;
  }

  return source;
}

// creates and returns a shader object compiled from the given source
GLuint CompileShader(GLenum shaderType, const std::string &source)
{
  // allocate shader object name
  GLuint shaderObject = glCreateShader(shaderType);

  // try compiling the source as a shader of the given type
  const GLchar *source_ptr = source.c_str();
  glShaderSource(shaderObject, 1, &source_ptr, 0);
  glCompileShader(shaderObject);

  // retrieve compile status
  GLint status;
  glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE)
  {
    GLint length;
    glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &length);
    std::string info(length, ' ');
    glGetShaderInfoLog(shaderObject, info.length(), &length, &info[0]);
    std::cout << "ERROR compiling shader:" << std::endl << std::endl;
    std::cout << source << std::endl;
    std::cout << info << std::endl;
  }

  return shaderObject;
}

// creates and returns a program object linked from vertex and fragment shaders
GLuint LinkProgram(GLuint vertexShader, GLuint fragmentShader)
{
  // allocate program object name
  GLuint programObject = glCreateProgram();

  // attach provided shader objects to this program
  if (vertexShader)   glAttachShader(programObject, vertexShader);
  if (fragmentShader) glAttachShader(programObject, fragmentShader);

  // try linking the program with given attachments
  glLinkProgram(programObject);

  // retrieve link status
  GLint status;
  glGetProgramiv(programObject, GL_LINK_STATUS, &status);
  if (status == GL_FALSE)
  {
    GLint length;
    glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &length);
    std::string info(length, ' ');
    glGetProgramInfoLog(programObject, info.length(), &length, &info[0]);
    std::cout << "ERROR linking shader program:" << std::endl;
    std::cout << info << std::endl;
  }

  return programObject;
}

// load, compile, and link shaders, returning true if successful
GLuint InitializeShaders()
{
  // load shader source from files
  std::string vertexSource = LoadSource("shaders/vertex.glsl");
  std::string fragmentSource = LoadSource("shaders/fragment.glsl");
  if (vertexSource.empty() || fragmentSource.empty()) return false;

  // compile shader source into shader objects
  GLuint vertex = CompileShader(GL_VERTEX_SHADER, vertexSource);
  GLuint fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

  // link shader program
  GLuint program = LinkProgram(vertex, fragment);

  glDeleteShader(vertex);
  glDeleteShader(fragment);

  // check for OpenGL errors and return false if error occurred
  return program;
}

void InitializeVAO(Geometry *geometry){

  const GLuint VERTEX_INDEX = 0;
  const GLuint TEXT_INDEX = 1;

  //Generate Vertex Buffer Objects
  // create an array buffer object for storing our vertices
  glGenBuffers(1, &geometry->vertexBuffer);

  glGenBuffers(1, &geometry->textureBuffer);

  //Set up Vertex Array Object
  // create a vertex array object encapsulating all our vertex attributes
  glGenVertexArrays(1, &geometry->vertexArray);
  glBindVertexArray(geometry->vertexArray);

  // associate the position array with the vertex array object
  glBindBuffer(GL_ARRAY_BUFFER, geometry->vertexBuffer);
  glVertexAttribPointer(
    VERTEX_INDEX,		//Attribute index
    3, 					//# of components
    GL_FLOAT, 			//Type of component
    GL_FALSE, 			//Should be normalized?
    sizeof(glm::vec3),		//Stride - can use 0 if tightly packed
    0);					//Offset to first element
    glEnableVertexAttribArray(VERTEX_INDEX);

    glBindBuffer(GL_ARRAY_BUFFER, geometry->textureBuffer);
    glVertexAttribPointer(
      TEXT_INDEX,		//Attribute index
      2, 					//# of components
      GL_FLOAT, 			//Type of component
      GL_FALSE, 			//Should be normalized?
      sizeof(glm::vec2), 		//Stride - can use 0 if tightly packed
      0);					//Offset to first element
      glEnableVertexAttribArray(TEXT_INDEX);

      // unbind our buffers, resetting to default state
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);

      return;
    }

    void LoadGeometry(Geometry *geometry, glm::vec3 *vertices, glm::vec2* texCoord, int elementCount)
    {
      geometry->elementCount = elementCount;

      // create an array buffer object for storing our vertices
      glBindBuffer(GL_ARRAY_BUFFER, geometry->vertexBuffer);
      glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*geometry->elementCount, vertices, GL_STATIC_DRAW);

      glBindBuffer(GL_ARRAY_BUFFER, geometry->textureBuffer);
      glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*geometry->elementCount, texCoord, GL_STATIC_DRAW);
      //Unbind buffer to reset to default state
      glBindBuffer(GL_ARRAY_BUFFER, 0);

      // check for OpenGL errors and return false if error occurred
      return;
    }

    // deallocate geometry-related objects
    void DestroyGeometry(Geometry *geometry)
    {
      // unbind and destroy our vertex array object and associated buffers
      glBindVertexArray(0);
      glDeleteVertexArrays(1, &geometry->vertexArray);
      glDeleteBuffers(1, &geometry->vertexBuffer);
    }

    glm::vec3 sphere(float t, float p, float r){
      return glm::vec3(r * sin(t) * cos(p), r * cos(t), r * sin(t) * sin(p));
    }

    void sphereLocation(glm::vec3 o, float r, std::vector<glm::vec3>* data, std::vector<glm::vec2>* tC){
      float ittPhi = 2 * 3.14 / 999;
      float ittTheta = 3.14 / 999;

      for(float theta = 0; theta < 3.14; theta += ittTheta){
        for(float phi = 0; phi < 2 * 3.14; phi += ittPhi){

          data -> push_back(o + sphere(theta, phi, r));
          tC -> push_back(glm::vec2(1 - phi / (2 * 3.14), 1 - theta / 3.14));

          data->push_back(o + sphere(theta, phi + ittPhi, r));
          tC->push_back(glm::vec2(1 - (phi + ittPhi) / (2 * 3.14),1 - theta / 3.14));

          data->push_back(o + sphere(theta + ittTheta, phi, r));
          tC->push_back(glm::vec2(1 - phi / (2 * 3.14),1 - (theta + ittTheta) / 3.14));

          data->push_back(o + sphere(theta, phi + ittPhi, r));
          tC->push_back(glm::vec2(1 - (phi + ittPhi) / (2 * 3.14), 1 - theta / 3.14));

          data->push_back(o + sphere(theta + ittTheta, phi, r));
          tC->push_back(glm::vec2(1 - phi / ( 2* 3.14),1 - (theta + ittTheta) / 3.14));

          data->push_back(o + sphere(theta + ittTheta, phi + ittPhi, r));
          tC->push_back(glm::vec2(1 - (phi + ittPhi) / (2 * 3.14), 1 - (theta + ittTheta) / 3.14));
        }
      }
    }

    glm::mat4 calcTrans(float distance, float inc, float phi){
      glm::vec3 p = glm::vec3(distance * sin(phi), 0, distance * cos(phi));
      glm::vec3 z = glm::vec3(0, 0, 1);

      glm::mat4 result;

      glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), inc, z);
      glm::mat4 tMat = glm::translate(glm::mat4(1.0f), p);

      result = tMat * rMat;

      return result;
    }

    glm::mat4 calcAniTrans(float time, float f){
      glm::vec3 y = glm::vec3(0, 1, 0);

      return glm::rotate(glm::mat4(1.f), f * time, y);
    }

    void drawScene(Geometry *geometry, GLuint program, glm::vec3 colour, Viewport* vp, glm::mat4 pMat, glm::mat4 trans, GLenum rMode){
      glUseProgram(program);

      int tempVP [4];
      glGetIntegerv(GL_VIEWPORT, tempVP);
      int width = tempVP[2];
      int height = tempVP[3];

      GLint uniformLocation = glGetUniformLocation(program, "Colour");
      glUniform3f(uniformLocation, colour.r, colour.g, colour.b);

      glm::mat4 mVP = pMat * vp -> vMat();
      uniformLocation = glGetUniformLocation(program, "mVP");
      glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(mVP));

      uniformLocation = glGetUniformLocation(program, "trans");
      glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(trans));

      glBindVertexArray(geometry -> vertexArray);
      glDrawArrays(rMode, 0, geometry -> elementCount);

      glBindVertexArray(0);
      glUseProgram(0);

    }

    void drawSolarSystem(int planetFocus){

      GLuint program = InitializeShaders();

      glEnable(GL_DEPTH_TEST);
      glDepthFunc(GL_LEQUAL);

      planet sun;
      sun.radius = 8.0f;
      sun.tex = 0;

      planet mercury;
      mercury.radius = 0.2f;
      mercury.tex = 5;
      mercury.axialT = 0;
      mercury.inc = 7;
      mercury.distance = 13;

      planet venus;
      venus.radius = 0.3f;
      venus.tex = 6;
      venus.axialT = 177.3;
      venus.inc = 3.39;
      venus.distance = 16;

      planet earth;
      earth.radius = 0.5f;
      earth.tex = 1;
      earth.axialT = 23.44;
      earth.inc = 0;
      earth.distance = 19;

      planet moon;
      moon.parent = &earth;
      moon.radius = 0.1f;
      moon.tex = 0.7f;
      moon.axialT = 6.68;
      moon.inc = 18.29;
      moon.distance = 2;

      planet mars;
      mars.radius = 0.46f;
      mars.tex = 7;
      mars.axialT = 25.19;
      mars.inc = 1.85;
      mars.distance = 21;

      planet jupiter;
      jupiter.radius = 2.0f;
      jupiter.tex = 8;
      jupiter.axialT = 3.12;
      jupiter.inc = 1.31;
      jupiter.distance = 25;

      planet saturn;
      saturn.radius = 1.0f;
      saturn.tex = 9;
      saturn.axialT = 3.12;
      saturn.inc = 2.48;
      saturn.distance = 30;

      planet uranus;
      uranus.radius = 1.35f;
      uranus.tex = 10;
      uranus.axialT = 97.86;
      uranus.inc = 0.76;
      uranus.distance = 35;

      planet neptune;
      neptune.radius = 1.45f;
      neptune.tex = 11;
      neptune.axialT = 29.58;
      neptune.inc = 1.77;
      neptune.distance = 39;

      std::vector<glm::vec2> tCs;
      std::vector<glm::vec3> testS;

      std::vector<glm::vec3> sunS;
      std::vector<glm::vec3> earthS;
      std::vector<glm::vec3> moonS;
      std::vector<glm::vec3> star;

      std::vector<glm::vec3> mercuryS;
      std::vector<glm::vec3> venusS;
      std::vector<glm::vec3> marsS;
      std::vector<glm::vec3> jupiterS;
      std::vector<glm::vec3> saturnS;
      std::vector<glm::vec3> uranusS;
      std::vector<glm::vec3> neptuneS;

      std::vector<glm::vec3> saturnRing;
      std::vector<glm::vec2> ringTC;
      Geometry saturnR;

      float itt = 0.01f * 2 * 3.14;
      for(float i = 0; i < 2 * 3.14; i += itt){
        saturnRing.push_back(glm::vec3(2 * sin(i), 0, 2 * cos(i)));
        saturnRing.push_back(glm::vec3(2 * sin(i + itt), 0, 2 * cos(i + itt)));
        saturnRing.push_back(glm::vec3(0, 0, 0));
        ringTC.push_back(glm::vec2(0.8, i / 2 * 3.14));
        ringTC.push_back(glm::vec2(0.8, i + itt / 2 * 3.14));
        ringTC.push_back(glm::vec2(0, 0.5));
      }

      InitializeVAO(&saturnR);

      LoadGeometry(&saturnR, saturnRing.data(), ringTC.data(), saturnRing.size());

      sphereLocation(glm::vec3(0,0,0),0.5f,&testS, &tCs);
      sphereLocation(sun.o, sun.radius, &sunS, &tCs);
      sphereLocation(earth.o, earth.radius, &earthS, &tCs);
      sphereLocation(moon.o, moon.radius, &moonS, &tCs);
      sphereLocation(glm::vec3(0, 0, 0), 500, &star, &tCs);

      sphereLocation(mercury.o, mercury.radius, &mercuryS, &tCs);
      sphereLocation(venus.o, venus.radius, &venusS, &tCs);
      sphereLocation(mars.o, mars.radius, &marsS, &tCs);
      sphereLocation(jupiter.o, jupiter.radius, &jupiterS, &tCs);
      sphereLocation(saturn.o, saturn.radius, &saturnS, &tCs);
      sphereLocation(uranus.o, uranus.radius, &uranusS, &tCs);
      sphereLocation(neptune.o, neptune.radius, &neptuneS, &tCs);

      glm::mat4 pMat = glm::perspective(3.14f * 0.4f, 1.0f, 0.1f, 1000.0f);

      Geometry geometry;
      Geometry testG;

      Geometry sunG;
      Geometry earthG;
      Geometry moonG;
      Geometry starG;

      Geometry mercuryG;
      Geometry venusG;
      Geometry marsG;
      Geometry jupiterG;
      Geometry saturnG;
      Geometry uranusG;
      Geometry neptuneG;

      InitializeVAO(&testG);
      LoadGeometry(&testG, testS.data(), tCs.data(), testS.size());

      InitializeVAO(&sunG);
      LoadGeometry(&sunG, sunS.data(), tCs.data(), sunS.size());

      InitializeVAO(&earthG);
      LoadGeometry(&earthG, earthS.data(), tCs.data(), earthS.size());

      InitializeVAO(&moonG);
      LoadGeometry(&moonG, moonS.data(), tCs.data(), moonS.size());

      InitializeVAO(&starG);
      LoadGeometry(&starG, star.data(), tCs.data(), star.size());

      InitializeVAO(&mercuryG);
      LoadGeometry(&mercuryG, mercuryS.data(), tCs.data(), mercuryS.size());

      InitializeVAO(&venusG);
      LoadGeometry(&venusG, venusS.data(), tCs.data(), venusS.size());

      InitializeVAO(&marsG);
      LoadGeometry(&marsG, marsS.data(), tCs.data(), marsS.size());

      InitializeVAO(&jupiterG);
      LoadGeometry(&jupiterG, jupiterS.data(), tCs.data(), jupiterS.size());

      InitializeVAO(&saturnG);
      LoadGeometry(&saturnG, saturnS.data(), tCs.data(), saturnS.size());

      InitializeVAO(&uranusG);
      LoadGeometry(&uranusG, uranusS.data(), tCs.data(), uranusS.size());

      InitializeVAO(&neptuneG);
      LoadGeometry(&neptuneG, neptuneS.data(), tCs.data(), neptuneS.size());

      glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

      MyTexture image = MyTexture();
      std::vector<MyTexture> images;
      InitializeTexture(&image, "sun.jpg", GL_TEXTURE_2D);
      images.push_back(image);

      InitializeTexture(&image, "earthDay.jpg", GL_TEXTURE_2D);
      images.push_back(image);

      InitializeTexture(&image, "earthNight.jpg", GL_TEXTURE_2D);
      images.push_back(image);

      InitializeTexture(&image, "moon.jpg", GL_TEXTURE_2D);
      images.push_back(image);

      InitializeTexture(&image, "starsMilkyWay.jpg", GL_TEXTURE_2D);
      images.push_back(image);

      InitializeTexture(&image, "mercury.jpg", GL_TEXTURE_2D);
      images.push_back(image);

      InitializeTexture(&image, "venus.jpg", GL_TEXTURE_2D);
      images.push_back(image);

      InitializeTexture(&image, "mars.jpg", GL_TEXTURE_2D);
      images.push_back(image);

      InitializeTexture(&image, "jupiter.jpg", GL_TEXTURE_2D);
      images.push_back(image);

      InitializeTexture(&image, "saturn.jpg", GL_TEXTURE_2D);
      images.push_back(image);

      InitializeTexture(&image, "uranus.jpg", GL_TEXTURE_2D);
      images.push_back(image);

      InitializeTexture(&image, "neptune.jpg", GL_TEXTURE_2D);
      images.push_back(image);

      InitializeTexture(&image, "saturnRing.png", GL_TEXTURE_2D);
      images.push_back(image);

      glUseProgram(program);
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D,images[1].textureID);

      GLint loc = glGetUniformLocation(program,"imageT");
      glUniform1i(loc,0);

      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D,images[2].textureID);

      GLint loc2 = glGetUniformLocation(program, "eNight");
      glUniform1i(loc2,1);

      glActiveTexture(GL_TEXTURE0);
      float timeE = 0.0f;
      GLint timeL = glGetUniformLocation(program, "time");

      Viewport vp;

      glm::vec2 mouseLoc;

      float mouseSen = 3.14 / 150.0f;


      while(!glfwWindowShouldClose(window)) {
        glUseProgram(program);
        glUniform1f(timeL, timeE);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 tMatSun = calcTrans(0, 0, 0);
        glm::mat4 tMatEarth = calcTrans(earth.distance, -(earth.axialT / 360.0f) * 2 * 3.14f, timeE * 0.5f);
        glm::mat4 tMatMoon = calcTrans(moon.parent -> distance, -(moon.inc / 360.0f) * 2 * 3.14f, timeE * 0.5f) * calcTrans(moon.distance, -(moon.axialT / 360.0f) * 2 * 3.14f, 2.0f * timeE);

        glm::mat4 tMatMercury = calcTrans(0, -(mercury.inc / 360.0f) * 2 * 3.14f, 0) * calcTrans(mercury.distance, -(mercury.axialT / 360.0f) * 2 * 3.14f, timeE * 1.5f);
        glm::mat4 tMatVenus = calcTrans(0, -(venus.inc / 360.0f) * 2 * 3.14f, 0) * calcTrans(venus.distance, -(venus.axialT / 360.0f) * 2 * 3.14f, timeE * 1.2f);
        glm::mat4 tMatMars = calcTrans(0, -(mars.inc / 360.0f) * 2 * 3.14f, 0) * calcTrans(mars.distance, -(mars.axialT / 360.0f) * 2 * 3.14f, timeE * 0.6f);
        glm::mat4 tMatJupiter = calcTrans(0, -(jupiter.inc / 360.0f) * 2 * 3.14f,0) * calcTrans(jupiter.distance, -(jupiter.axialT / 360.0f) * 2 * 3.14f, timeE * 0.16f);
        glm::mat4 tMatSaturn = calcTrans(0, -(saturn.inc / 360.0f) * 2 * 3.14f, 0) * calcTrans(saturn.distance, -(saturn.axialT / 360.0f) * 2 * 3.14f, timeE * 0.4f);
        glm::mat4 tMatUranus = calcTrans(0, -(uranus.inc / 360.0f) * 2 * 3.14f, 0) * calcTrans(uranus.distance, -(uranus.axialT / 360.0f) * 2 * 3.14f, timeE * 0.2f);
        glm::mat4 tMatNeptune = calcTrans(0, -(neptune.inc / 360.0f) * 2 * 3.14f, 0) * calcTrans(neptune.distance, -(neptune.axialT / 360.0f) * 2 * 3.14f, timeE * 0.25f);

        glm::mat4 aMatSun = calcAniTrans(timeE, 1.0f);
        glm::mat4 aMatEarth = calcAniTrans(timeE, 2.0f);
        glm::mat4 aMatMoon = calcAniTrans(timeE, 3.0f);

        glm::mat4 aMatMercury = calcAniTrans(timeE, 4.0f);
        glm::mat4 aMatVenus = calcAniTrans(timeE, 3.0f);
        glm::mat4 aMatMars = calcAniTrans(timeE, 2.0f);
        glm::mat4 aMatJupiter = calcAniTrans(timeE, 0.5f);
        glm::mat4 aMatSaturn = calcAniTrans(timeE, 0.7f);
        glm::mat4 aMatUranus = calcAniTrans(timeE, 0.65f);
        glm::mat4 aMatNeptune = calcAniTrans(timeE, 0.63f);

        GLint cPLoc = glGetUniformLocation(program, "cPos");
        GLint sLoc = glGetUniformLocation(program, "shading");
        GLint eLoc = glGetUniformLocation(program, "earth");

        switch(planetFocus){
          case 0:
          vp.focus = glm::vec3(0, 0, 0.0f);
          vp.radius = sun.radius * 5;
          break;

          case 1:
          vp.focus = glm::vec3(tMatMercury*aMatMercury*glm::vec4(0,0,0,1));
          vp.radius = mercury.radius*2;
          break;

          case 2:
          vp.focus = glm::vec3(tMatVenus*aMatVenus*glm::vec4(0,0,0,1));
          vp.radius = venus.radius*2;
          break;

          case 3:
          vp.focus = glm::vec3(tMatEarth*aMatEarth*glm::vec4(0,0,0,1));
          vp.radius = earth.radius*2;
          break;

          case 4:
          vp.focus = glm::vec3(tMatMars*aMatMars*glm::vec4(0,0,0,1));
          vp.radius = mars.radius*2;
          break;

          case 5:
          vp.focus = glm::vec3(tMatJupiter*aMatJupiter*glm::vec4(0,0,0,1));
          vp.radius = jupiter.radius*2;
          break;

          case 6:
          vp.focus = glm::vec3(tMatSaturn*aMatSaturn*glm::vec4(0,0,0,1));
          vp.radius = saturn.radius*2;
          break;

          case 7:
          vp.focus = glm::vec3(tMatUranus*aMatUranus*glm::vec4(0,0,0,1));
          vp.radius = uranus.radius*2;
          break;

          case 8:
          vp.focus = glm::vec3(tMatNeptune*aMatNeptune*glm::vec4(0,0,0,1));
          vp.radius = neptune.radius*2;
          break;
        }

        double xP, yP;
        glfwGetCursorPos(window, &xP, &yP);
        glm::vec2 mousePos(xP, yP);
        glm::vec2 moveMouse = mousePos - mouseLoc;

        if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
          vp.transform(-moveMouse.y * mouseSen, -moveMouse.x * mouseSen);
        }

        vp.transform(-0.0001, -0.0001);

        vp.scale(scale);

        mouseLoc = mousePos;

        glUniform3f(cPLoc, vp.position.x, vp.position.y, vp.position.z);
        glUniform1i(eLoc, false);

        glBindTexture(GL_TEXTURE_2D,images[0].textureID);
        glUniform1i(sLoc,false);
        drawScene(&sunG, program, glm::vec3(0.6, 0.7, 0.8), &vp, pMat, tMatSun * aMatSun, GL_TRIANGLES);

        glBindTexture(GL_TEXTURE_2D,images[1].textureID);

        glUseProgram(program);
        glUniform1i(eLoc,true);
        glUniform1i(sLoc,true);
        drawScene(&earthG, program, glm::vec3(0.6, 0.7, 0.8), &vp, pMat, tMatEarth * aMatEarth, GL_TRIANGLES);

        glUseProgram(program);
        glUniform1i(eLoc,false);

        glBindTexture(GL_TEXTURE_2D,images[3].textureID);

        glUseProgram(program);
        glUniform1i(sLoc,true);
        drawScene(&moonG, program, glm::vec3(0.6, 0.7, 0.8), &vp, pMat, tMatMoon * aMatMoon, GL_TRIANGLES);

        glBindTexture(GL_TEXTURE_2D,images[5].textureID);

        glUseProgram(program);
        glUniform1i(sLoc,true);
        drawScene(&mercuryG, program, glm::vec3(0.6, 0.7, 0.8), &vp, pMat, tMatMercury * aMatMercury, GL_TRIANGLES);

        glBindTexture(GL_TEXTURE_2D,images[6].textureID);

        glUseProgram(program);
        glUniform1i(sLoc,true);
        drawScene(&venusG, program, glm::vec3(0.6, 0.7, 0.8), &vp, pMat, tMatVenus * aMatVenus, GL_TRIANGLES);

        glBindTexture(GL_TEXTURE_2D,images[6].textureID);

        glUseProgram(program);
        glUniform1i(sLoc,true);
        drawScene(&venusG, program, glm::vec3(0.6, 0.7, 0.8), &vp, pMat, tMatVenus * aMatVenus, GL_TRIANGLES);

        glBindTexture(GL_TEXTURE_2D,images[7].textureID);

        glUseProgram(program);
        glUniform1i(sLoc,true);
        drawScene(&marsG, program, glm::vec3(0.6, 0.7, 0.8), &vp, pMat, tMatMars * aMatMars, GL_TRIANGLES);

        glBindTexture(GL_TEXTURE_2D,images[8].textureID);

        glUseProgram(program);
        glUniform1i(sLoc,true);
        drawScene(&jupiterG, program, glm::vec3(0.6, 0.7, 0.8), &vp, pMat, tMatJupiter * aMatJupiter, GL_TRIANGLES);

        glBindTexture(GL_TEXTURE_2D,images[9].textureID);

        glUseProgram(program);
        glUniform1i(sLoc,true);
        drawScene(&saturnG, program, glm::vec3(0.6, 0.7, 0.8), &vp, pMat, tMatSaturn * aMatSaturn, GL_TRIANGLES);

        glBindTexture(GL_TEXTURE_2D,images[12].textureID);

        glUseProgram(program);
        glUniform1i(sLoc,true);
        drawScene(&saturnR, program, glm::vec3(0.6, 0.7, 0.8), &vp, pMat, tMatSaturn * aMatSaturn, GL_TRIANGLES);

        glBindTexture(GL_TEXTURE_2D,images[10].textureID);

        glUseProgram(program);
        glUniform1i(sLoc,true);
        drawScene(&uranusG, program, glm::vec3(0.6, 0.7, 0.8), &vp, pMat, tMatUranus * aMatUranus, GL_TRIANGLES);

        glBindTexture(GL_TEXTURE_2D,images[11].textureID);

        glUseProgram(program);
        glUniform1i(sLoc,true);
        drawScene(&neptuneG, program, glm::vec3(0.6, 0.7, 0.8), &vp, pMat, tMatNeptune * aMatNeptune, GL_TRIANGLES);

        glBindTexture(GL_TEXTURE_2D,images[4].textureID);

        glUseProgram(program);
        glUniform1i(sLoc,false);

        drawScene(&starG, program, glm::vec3(0.6, 0.7, 0.8), &vp, pMat, tMatSun, GL_TRIANGLES);


        timeE += 0.01f;

        glfwSwapBuffers(window);
        glfwPollEvents();
      }

    }
