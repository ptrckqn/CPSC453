#version 410

layout(isolines) in;

in vec3 teColour[];
uniform int quadBez;
vec2 position, pointOne, pointTwo, pointThree, pointFour;
float x1, x2, x3, x4;

out vec3 color;

#define PI 3.14159265359

void main()
{
	float u = gl_TessCoord.x;

	vec3 startColour = teColour[0];
	vec3 endColour = teColour[1];

	// vec2 p0 = vec2(0, 0);
	// vec2 p1 = vec2(1, 0);

	//vec2 p0 = gl_in[0].gl_Position.xy;
	//vec2 p1 = gl_in[1].gl_Position.xy;


	if (quadBez == 1){
		 pointOne = gl_in[0].gl_Position.xy;
		 pointTwo = gl_in[1].gl_Position.xy;
		 pointThree = gl_in[2].gl_Position.xy;

		 x1 = (1 - u) * (1 - u);
		 x2 = 2 * (1 - u) * u;
		 x3 = u * u;

		position = x1 * pointOne + x2 * pointTwo + x3 * pointThree;
	}

	else if(quadBez == 0){
		 pointOne = gl_in[0].gl_Position.xy;
		 pointTwo = gl_in[1].gl_Position.xy;
		 pointThree = gl_in[2].gl_Position.xy;
		 pointFour = gl_in[3].gl_Position.xy;

		 x1 = (1 - u) * (1 - u) * (1 - u);
		 x2 = 3 * u * (1 - u) * (1 - u);
		 x3 = 3 * u * u * (1 - u);
		 x4 = u * u * u;

		position = x1 * pointOne + x2 * pointTwo + x3 * pointThree + x4 * pointFour;
	}

	gl_Position = vec4(position, 0, 1);

	color = (1 - u) * startColour + u * endColour;

}
