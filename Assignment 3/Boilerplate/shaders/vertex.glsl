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
layout(location = 1) in vec3 VertexColor;


// output to be interpolated between vertices and passed to the fragment stage
out vec3 color;
uniform int quadBez;
float scale;

void main()
{
    if(quadBez == 0){
      scale = 0.1;
    }

    else if (quadBez == 1){
      scale = 0.3;
    }
    mat3x3 x = mat3x3(scale, 0.0, 0.0,
                      0.0, scale, 0.0,
                      0.0, 0.0, scale);
    vec3 newPoint = x * VertexPosition;

    mat4x4 scroll = mat4x4(1.0, 0.0, 0.0, 100.0,
                      0.0, 1.0, 0.0, 0.0,
                      0.0, 0.0, 1.0, 0.0,
                      0.0, 0.0, 0.0, 1.0);

    // assign vertex position without modification
    gl_Position = scroll * vec4(newPoint.xy, 0.0, 1.0);

    // assign output colour to be interpolated
    color = VertexColor;
}
