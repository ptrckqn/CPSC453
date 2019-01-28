// ==========================================================================
// Vertex program for barebones GLFW boilerplate
//
// Author:  Sonny Chan, University of Calgary
// Date:    December 2015
// ==========================================================================
#version 410

// interpolated colour received from vertex stage
in vec2 uv;

// first output is mapped to the framebuffer's colour index by default
out vec4 FragmentColour;

uniform sampler2DRect imageTexture;
uniform sampler2DRect imageTextureTwo;

uniform int gs;
uniform int sobelNum;
uniform int gaussian;

void main(void)
{
    // write colour output without modification
    //FragmentColour = vec4(Colour, 0);
	FragmentColour = texture(imageTexture, uv);

  float R = FragmentColour[0];
  float G = FragmentColour[1];
  float B = FragmentColour[2];
  float alpha = FragmentColour[3];
  float lValue;

  float outR = R;
  float outG = G;
  float outB = B;

	float sobelMatrix[9];
	float sobelR = 0.0;
	float sobelG = 0.0;
	float sobelB = 0.0;

	float gausR = 0.0;
	float gausG = 0.0;
	float gausB = 0.0;

  if (gs == 1) {
    lValue = 0.333 * (R + B + G);
    outR = lValue;
    outG = lValue;
    outB = lValue;
  }
  else if (gs == 2) {
    lValue = 0.299 * R + 0.587 * G + 0.114 * B;
    outR = lValue;
    outG = lValue;
    outB = lValue;
  }
  else if (gs == 3) {
    lValue = 0.213 * R + 0.715 * G + 0.072 * B;
    outR = lValue;
    outG = lValue;
    outB = lValue;
  }

	else if(sobelNum == 1){
		int row = 0;
		int c = 0;
		sobelMatrix = float[](
			1, 0, -1,
			2, 0, -2,
			1, 0, -1
		);

		for(int i = -1; i < 2; i++){
			c = 0;
			for(int j = 1; j > -2; j--){
				vec2 pixel = uv;
				pixel[0] = pixel[0] + j;
				pixel[1] = pixel[1] + i;
				vec4 colour = texture(imageTexture, pixel);
				sobelR = sobelR + sobelMatrix[c + row] * colour[0];
				sobelG = sobelG + sobelMatrix[c + row] * colour[1];
				sobelB = sobelB + sobelMatrix[c + row] * colour[2];
				c++;
			}
			row = row + 3;
		}
		outR = sobelR;
		outG = sobelG;
		outB = sobelB;
	}

	else if(sobelNum == 2){
		int row = 0;
		int c = 0;
		sobelMatrix = float[](
			-1, -2, -1,
			0, 0, 0,
			1, 2, 1
		);

		for(int i = -1; i < 2; i++){
			c = 0;
			for(int j = 1; j > -2; j--){
				vec2 pixel = uv;
				pixel[0] = pixel[0] + j;
				pixel[1] = pixel[1] + i;
				vec4 colour = texture(imageTexture, pixel);
				sobelR = sobelR + sobelMatrix[c + row] * colour[0];
				sobelG = sobelG + sobelMatrix[c + row] * colour[1];
				sobelB = sobelB + sobelMatrix[c + row] * colour[2];
				c++;
			}
			row = row + 3;
		}
		outR = sobelR;
		outG = sobelG;
		outB = sobelB;
	}

	else if(sobelNum == 3){
		int row = 0;
		int c = 0;
		sobelMatrix = float[](
			0, -1, 0,
			-1, 5, -1,
			0, -1, 0
		);

		for(int i = -1; i < 2; i++){
			c = 0;
			for(int j = 1; j > -2; j--){
				vec2 pixel = uv;
				pixel[0] = pixel[0] + j;
				pixel[1] = pixel[1] + i;
				vec4 colour = texture(imageTexture, pixel);
				sobelR = sobelR + sobelMatrix[c + row] * colour[0];
				sobelG = sobelG + sobelMatrix[c + row] * colour[1];
				sobelB = sobelB + sobelMatrix[c + row] * colour[2];
				c++;
			}
			row = row + 3;
		}
		outR = sobelR;
		outG = sobelG;
		outB = sobelB;
	}

	else if(gaussian == 1){
		int row = 0;
		int c = 0;
		float gausMatrix[9] = float[](
			0.04, 0.12, 0.04,
			0.12, 0.36, 0.12,
			0.04, 0.12, 0.04
		);

		for(int i = -1; i < 2; i++){
			c = 0;
			for(int j = 1; j > -2; j--){
				vec2 pixel = uv;
				pixel[0] = pixel[0] + j;
				pixel[1] = pixel[1] + i;
				vec4 colour = texture(imageTexture, pixel);
				gausR = gausR + gausMatrix[c + row] * colour[0];
				gausG = gausG + gausMatrix[c + row] * colour[1];
				gausB = gausB + gausMatrix[c + row] * colour[2];
				c++;
			}
			row = row + 3;
		}
		outR = gausR;
		outG = gausG;
		outB = gausB;
	}

	else if(gaussian == 2){
		int row = 0;
		int c = 0;
		float gausMatrix[25] = float[](
			0.010534,	0.02453,	0.032508,	0.02453,	0.010534,
			0.02453,	0.05712,	0.075698,	0.05712,	0.02453,
			0.032508,	0.075698,	0.100318,	0.075698,	0.032508,
			0.02453,	0.05712,	0.075698,	0.05712,	0.02453,
			0.010534,	0.02453,	0.032508,	0.02453,	0.010534
		);

		for(int i = -2; i < 3; i++){
			c = 0;
			for(int j = 2; j > -3; j--){
				vec2 pixel = uv;
				pixel[0] = pixel[0] + j;
				pixel[1] = pixel[1] + i;
				vec4 colour = texture(imageTexture, pixel);
				gausR = gausR + gausMatrix[c + row] * colour[0];
				gausG = gausG + gausMatrix[c + row] * colour[1];
				gausB = gausB + gausMatrix[c + row] * colour[2];
				c++;
			}
			row = row + 5;
		}
		outR = gausR;
		outG = gausG;
		outB = gausB;
	}

	else if(gaussian == 3){
		int row = 0;
		int c = 0;
		float gausMatrix[49] = float[](
			0.000569,	0.002332,	0.00543,	0.007196,	0.00543,	0.002332,	0.000569,
			0.002332,	0.009553,	0.022245,	0.02948,	0.022245,	0.009553,	0.002332,
			0.00543,	0.022245,	0.051799,	0.068647,	0.051799,	0.022245,	0.00543,
			0.007196,	0.02948,	0.068647,	0.090973,	0.068647,	0.02948,	0.007196,
			0.00543,	0.022245,	0.051799,	0.068647,	0.051799,	0.022245,	0.00543,
			0.002332,	0.009553,	0.022245,	0.02948,	0.022245,	0.009553,	0.002332,
			0.000569,	0.002332,	0.00543,	0.007196,	0.00543,	0.002332,	0.000569
		);

		for(int i = -3; i < 4; i++){
			c = 0;
			for(int j = 3; j > -4; j--){
				vec2 pixel = uv;
				pixel[0] = pixel[0] + j;
				pixel[1] = pixel[1] + i;
				vec4 colour = texture(imageTexture, pixel);
				gausR = gausR + gausMatrix[c + row] * colour[0];
				gausG = gausG + gausMatrix[c + row] * colour[1];
				gausB = gausB + gausMatrix[c + row] * colour[2];
				c++;
			}
			row = row + 7;
		}
		outR = gausR;
		outG = gausG;
		outB = gausB;
	}

	FragmentColour = vec4(outR, outG, outB, alpha);

}
