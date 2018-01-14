const float M_PI = 3.14159265358979;

vec4 rgb(int r, int g, int b) {
	return vec4(vec3(r, g, b) / 255.0, 1);
}

vec2 getWindowXY(vec2 windowSize) {
	return (gl_FragCoord.xy / windowSize) * 2 - vec2(1, 1);
}

vec3 getAugmentedLookDirection(vec2 windowSize, float fovy, float aspectRatio) {

	vec2 windowXY = getWindowXY(windowSize);

	float top = tan(fovy / 2);
	float right = top * aspectRatio;

	return normalize(vec3(windowXY.x * right, windowXY.y * top, -1.0f));
}

float deg(float rad) {
	return rad * 180.0 / M_PI;
}