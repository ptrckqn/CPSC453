// ==========================================================================
// Vertex program for barebones GLFW boilerplate
//
// Author:  Sonny Chan, University of Calgary
// Date:    December 2015
// ==========================================================================
#version 410

// location indices for these attributes correspond to those specified in the
// InitializeGeometry() function of the main program
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec2 tC;

// output to be interpolated between vertices and passed to the fragment stage
out vec2 tCo;
out float dNL;
out float dHNPP;
flat out int isNight;

uniform mat4 trans;
uniform mat4 mVP;
uniform float time;
uniform vec3 cPos;
uniform bool earth;

vec2 cOffset(float x){
  return vec2(cos(x), sin(x));
}

void main()
{
    // assign vertex position without modification
    gl_Position = mVP * trans * vec4(VertexPosition, 1.0);

    vec3 o = (trans * vec4(0, 0, 0, 1)).xyz;
    vec3 current = (trans * vec4(VertexPosition, 1.0)).xyz;

    vec3 a = normalize(current - o);
    vec3 b = normalize(vec3(0, 0, 0) - current);
    vec3 c = normalize(cPos - current);
    vec3 d = normalize(b + c);

    dNL = max(0, dot(a, b));
    dHNPP = pow(max(0, dot(d, a)), 4);

    tCo = tC;

    if(earth){
      if(dot(a, b) <= 0){
        isNight = 1;
      }
      else{
        isNight = 0;
      }
    }
    else{
      isNight = 0;
    }
}
