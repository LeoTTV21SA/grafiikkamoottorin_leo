#include <stdio.h>                  // Include stdio.h, which contains printf-function
#include <glm/glm.hpp>              // General glm include
#include <glm/gtx/transform.hpp>    // glm transform functions.
#include <glm/gtc/constants.hpp>	// glm::half_pi
#include <glm/gtx/string_cast.hpp>  // glm::to_string
#include <glm/gtc/type_ptr.hpp>     // glm::make_mat4

//glm::length  
//glm::sqrtf                  estos son funciones que termiten calcular los vectores ingluidas en la libreria glm
//glm::normalize



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
glm::mat4 rotationX(float angle) {
	return glm::rotate(angle, glm::vec3(1.0f, 0.0f, 0.0f));
}

glm::mat4 rotationVecB(float angle) {
	return glm::rotate(angle, glm::vec3(2.2f, 3.4f, 4.1f));
}

// The main function of the application
int main() {

	// Add two vec3-type variables:
	glm::vec3 a(3.0f, 1.7f, 2.0f); // vector a
	glm::vec3 b(2.2f, 3.4f, 4.1f); // vector b

	// Add one scalar:
	float s = 1.35f;
	

	// Add two arrays of floats to be used as values for matrices:
	float val[16] = {
		2.0f,  1.2f, -0.6f,  3.0f,
		1.4f, -2.7f,  3.2f, -0.8f,
	   -4.1f,  0.1f,  2.2f,  1.7f,
		0.3f,  3.1f, -1.5f,  2.0f
	};
	float val2[16] = {
		0.6f,  0.9f, -2.3f,  1.1f,
	   -0.4f,  0.2f,  1.0f, -3.3f,
		1.2f, -4.3f,  2.0f,  2.8f,
		0.1f,  2.6f, -1.7f,  0.4f
	};

	// Create two matrices from these values:
	glm::mat4 m = glm::make_mat4(val);
	glm::mat4 n = glm::make_mat4(val2);

	//tehtävä 1
	glm::vec3 answer = (b - a * s);
	printf("1. %s\n", glm::to_string(answer).c_str());
	printf("\n");

	//Tehtävä 2
	glm::vec3 answer1 = (b * a / s);
	printf("2. %s\n", glm::to_string(answer1).c_str());
	printf("\n");

	//Tehtävä 3
	float answerq = sqrtf((b.y * b.y) + (b.z * b.z) + (b.x * b.x));
	printf("3. %f\n" , answerq);
	printf("\n");

	//Tehtävä 4
	float apitus = sqrtf((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
	float bPitus = sqrtf((b.x * b.x) + (b.y * b.y) + (b.z * b.z));
	float Tulo = ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
	float answeri = acosf(Tulo / (abs(apitus) * abs(bPitus))) * 180 / glm::pi<float>();
	printf("4. %f\n", answeri);
	printf("\n");

	//tehtävä 5
	glm::vec3 ristiTulo = glm::cross(a, b);
	glm::vec3 answer4 = ristiTulo * s;
	printf("5. %s\n", glm::to_string(answer4).c_str());
	printf("\n");

	//tehtävä 6
	glm::mat4 answero = (m * s);
	printf("6. %s\n", glm::to_string(answero).c_str());
	printf("\n");

	//tehtävä 7
	glm::mat4 answerl = (n * m);
	printf("7. %s\n", glm::to_string(answerl).c_str());
	printf("\n");

	//tehtävä 8
	glm::mat4 ex8 = translation(glm::vec3(3.0f, 1.7f, 2.0f));
	glm::vec4 answerg = ex8 * pos3(0.0f, 0.0f, 0.0f);
	ex8 = scaling(glm::vec3(2.5f));
	answerg = ex8 * pos3(3.0f, 1.7f, 2.0f);
	printf("8. %s\n", glm::to_string(answerg).c_str());
	printf("\n");

	//tehtävä 9
	glm::mat4 teh9 = translation(glm::vec3(3.0f, 1.7f, 2.0f));
	glm::vec4 answere = teh9 * pos3(0.0f, 0.0f, 0.0f);
	teh9 = rotationX(glm::radians(30.0f));
	answere = teh9 * pos3(3.0f, 1.7f, 2.0f);
	printf("\n");

	//tehtävä 10
	glm::mat4 teh10 = translation(glm::vec3(1, 2, 0));
	glm::vec4 answer5 = teh10 * pos3(0.0f, 0.0f, 0.0f);
	teh10 = translation(glm::vec3(2.2f, 3.4f, 4.1f)) * rotationVecB(glm::radians(50.0f)) * scaling(glm::vec3(2.5f));
	answer5 = teh10 * pos3(3.0f, 1.7f, 2.0f);
	printf("10. %s\n", glm::to_string(answer5).c_str());
	printf("\n");

	// Translate point <0,0,0> to position <1,2,0>
	glm::mat4 tr = translation(glm::vec3(1, 2, 0));
	glm::vec4 res = tr * pos3(0.0f, 0.0f, 0.0f);
	/*printf("%s\n", glm::to_string(res).c_str());*/

	// Rotate point <1,0,0> arounf z-axis by half pi (90 degrees)
	tr = rotationZ(glm::half_pi<float>());
	res = tr * pos3(1.0f, 0.0f, 0.0f);
	/*printf("%s\n", glm::to_string(res).c_str());*/

	// Scale point <0.1, 0.2, 0.3> to be 10 times as big, with uniform scaling (all axes are scaled with same factor).
	// Result should be <1, 2, 3>
	tr = scaling(glm::vec3(10.0f));
	res = tr * pos3(0.1f, 0.2f, 0.3f);
	/*printf("%s\n", glm::to_string(res).c_str());*/

	// Scale first point <0.1, 0.0, 0.0> to be 10 times as big, then rotate -90 degrees around z-axis,
	// then translate to point <1, 2, 0>. This should result to <1, 1, 0>. 
	tr = translation(glm::vec3(1, 2, 0)) * rotationZ(glm::radians(-90.0f)) * scaling(glm::vec3(10.0f));
	res = tr * pos3(0.1f, 0.0f, 0.0f);
	/*printf("%s\n", glm::to_string(res).c_str());*/

	// Lets do the inverse of your previous transform point from <1.0, 1.0, 0.0> back to the point <0.1, 0.0, 0.0>
	tr = glm::inverse(tr);
	res = tr * res;
	/*printf("%s\n", glm::to_string(res).c_str());*/
}