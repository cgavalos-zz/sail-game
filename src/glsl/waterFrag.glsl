#version 430 core
#include glsl/bigBlock.glsl
#include glsl/shaderUtils.glsl

uniform float unitSize;
uniform bool allBlack;

in vec3 onormal;
out vec4 finalColor;

const float distFactor = -0.7 / (2 * unitSize);

float reflectance(float degrees) {
	degrees = clamp(degrees, 0.0, 90.0);
	float table[10];
	table[0] = 0.025;
	table[1] = 0.025;
	table[2] = 0.025;
	table[3] = 0.025;
	table[4] = 0.025;
	table[5] = 0.033;
	table[6] = 0.060;
	table[7] = 0.133;
	table[8] = 0.35;
	table[9] = 1;

	int lower = int(degrees / 10);
	int upper = lower + 1;
	float quality = (degrees - lower * 10.0) / ((upper - lower) * 10.0);
	return table[lower] + (table[upper] - table[lower]) * quality;
}

const vec4 seaBlue = vec4(vec3(0, 0.412, 0.58) * 0.75, 1);

void main() {

	if (allBlack) {

		float dist = gl_FragCoord.z / gl_FragCoord.w;
		float alpha = clamp(exp(dist * distFactor), 0, 1);
		finalColor = vec4(0, 0, 0, alpha);

	} else {

		vec3 augmentedLookDir = getAugmentedLookDirection(windowSize, fovy, aspectRatio);
		vec3 reflectV = reflect(augmentedLookDir, onormal);

		vec4 skyColor = skyBlue;

		vec3 rotatedVert = mat3(view) * vec3(0, 1, 0);
		float angleOffVertical = acos(dot(reflectV, rotatedVert));

		if (dot(reflectV, sunDirection) > dotAngle) {
			skyColor = sunColor;
		} else {
			skyColor = mix(skyBlue, vec4(190, 219, 236, 255) / 255.0, pow(angleOffVertical * 2 / M_PI, 8));
		}

		float degrees = deg(asin(length(cross(augmentedLookDir, onormal))));
		finalColor = seaBlue + reflectance(degrees) * (skyColor - seaBlue);
	}
}
