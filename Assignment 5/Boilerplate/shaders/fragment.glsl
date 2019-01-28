// ==========================================================================
// Vertex program for barebones GLFW boilerplate
//
// Author:  Sonny Chan, University of Calgary
// Date:    December 2015
// ==========================================================================
#version 410

// interpolated colour received from vertex stage
uniform vec3 Colour;

// first output is mapped to the framebuffer's colour index by default
out vec4 FragmentColour;
in vec2 tCo;
in float dNL;
flat in int isNight;

uniform sampler2D imageT;
uniform sampler2D eNight;
uniform bool shading;

void main(void){
  vec4 a = texture(imageT, tCo);
  vec4 b = vec4(0.5f, 0.5f, 0.5f, 0);
  vec4 c = vec4(1, 1, 1, 0);
  vec4 d = vec4(0.7f, 0.7f, 0.7f, 0);

  if(shading){
    FragmentColour = a * (b + c *dNL);
  }
  else{
    FragmentColour = texture(imageT, tCo);
  }

  if(isNight == 1){
    FragmentColour = texture(eNight, tCo);
  }
}
