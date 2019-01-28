#include "Viewport.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>



void Viewport::scale(float s){
  radius = radius * s;
}

void Viewport::transform(float dTheta, float dPhi){
  theta = theta + dTheta;
  if(theta >= 3.14f){
    theta = 3.14f;
  }
  else if(theta <= 0.1f){
    theta = 0.1f;
  }

  theta = theta + dTheta;
  phi = phi + dPhi;
  position = focus + glm::vec3(radius * sin(theta) * sin(phi), radius * cos(theta), radius * sin(theta) * cos(phi));
}


glm::mat4 Viewport::vMat() const{
  return lookAt(position, focus, up);
}
