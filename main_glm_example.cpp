#include <stdio.h> // Include stdio.h, which contains printf-function
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>	// glm transform functions.
#include <glm/gtx/string_cast.hpp> // glm::to_string
#include <glm/gtc/constants.hpp>	// glm::half_pi

glm::vec4 pos3(float x, float y, float z) {
	// Set component w to be 1.0, because of homogeneous coordinates
	return glm::vec4(x, y, z, 1.0f);
}

glm::mat4 translation(const glm::vec3& pos) {
	return glm::translate(glm::mat4(1.0f), pos);
}

glm::mat4 rotationZ(float angle) {
	return glm::rotate(angle, glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::mat4 scaling(const glm::vec3& scale) {
	return glm::scale(glm::mat4(1.0f), scale);
}


// The main function of the application
int main() {
	// Translate point <0,0,0> to position <1,2,0>
	glm::mat4 tr = translation(glm::vec3(1, 2, 0));
	glm::vec4 res = tr * pos3(0.0f, 0.0f, 0.0f);
	printf("%s\n", glm::to_string(res).c_str());

	// Rotate point <1,0,0> arounf z-axis by half pi (90 degrees)
	tr = rotationZ(glm::half_pi<float>());
	res = tr * pos3(1.0f, 0.0f, 0.0f);
	printf("%s\n", glm::to_string(res).c_str());

	// Scale point <0.1, 0.2, 0.3> to be 10 times as big, with uniform scaling (all axes are scaled with same factor).
	// Result should be <1, 2, 3>
	tr = scaling(glm::vec3(10.0f));
	res = tr * pos3(0.1f, 0.2f, 0.3f);
	printf("%s\n", glm::to_string(res).c_str());

	// Scale first point <0.1, 0.0, 0.0> to be 10 times as big, then rotate -90 degrees around z-axis,
	// then translate to point <1, 2, 0>. This should result to <1, 1, 0>. 
	tr = translation(glm::vec3(1, 2, 0)) * rotationZ(glm::radians(-90.0f)) * scaling(glm::vec3(10.0f));
	res = tr * pos3(0.1f, 0.0f, 0.0f);
	printf("%s\n", glm::to_string(res).c_str());

	// Lets do the inverse of your previous transform point from <1.0, 1.0, 0.0> back to the point <0.1, 0.0, 0.0>
	tr = glm::inverse(tr);
	res = tr * res;
	printf("%s\n", glm::to_string(res).c_str());
}