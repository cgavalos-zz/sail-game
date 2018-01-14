#version 430 core
#include bigBlock.glsl
#include shaderUtils.glsl

out vec4 finalColor;

void main() {

	vec3 augmentedLookDir = getAugmentedLookDirection(windowSize, fovy, aspectRatio);
	vec3 rotatedVert = mat3(view) * vec3(0, 1, 0);
	float angleOffVertical = acos(dot(augmentedLookDir, rotatedVert));

	if (angleOffVertical > M_PI / 2) {
		angleOffVertical = M_PI / 2;
	}

	if (dot(augmentedLookDir, sunDirection) > dotAngle) {
		finalColor = sunColor;
	} else {
		finalColor = mix(skyBlue, vec4(1, 1, 1, 1), pow(angleOffVertical * 2 / M_PI, 6));
	}
}
