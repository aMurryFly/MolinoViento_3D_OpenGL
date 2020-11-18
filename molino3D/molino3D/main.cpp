/*--------------------------------------------------------*/
/* ------  MODELADO JERARQUICO y USO DE PRIMITIVAS  ------*/
/*--------------------------------------------------------*/
/* ---------------------  MOLINO 3D  ---------------------*/
/*-------------------    2021-1   ------------------------*/
/*------------- Alumno: Murrieta Villegas Alfonso --------*/

//BIBLIOTECAS
#include "cylinder.h"
#include "cone.h"
#include "aspa.h"
#include "soportAxis.h"


//CALL FUNCTIONS
void resize(GLFWwindow* window, int width, int height);
void keyboardMap(GLFWwindow *window);
void drawElements(Shader);
void getResolution(void);


//GLOBAL OBJECTS
cylinder cylinder_1( 0.5, 1.0);
cone cone_1(0.5, 1.5);
Aspa aspa_1(1.0, 1.0);
soportAxis soportAxis_1(1.0);

GLFWmonitor *monitors;
GLuint VBO, VAO;


//GLOBAL VARIABLES
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

float	rotAspas = 0.0f;
//
float	movX = 0.0f,
		movY = 0.0f,
		movZ = 0.0f,
		rotY = 0.0f,
		rotX = 0.0f;

//IMPORTANT FUNCTIONS FOR PROJECT
void drawElements(Shader shader){

	//GENERAL DECLARATIONS
		shader.use();
		// create transformations and Projection
		glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
		glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
		glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection

		//Use "projection" in order to change how we see the information
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 500.0f);



	//VIEW DECLARATIONS AND INSTANCE
	movY = -5.0f;
	movZ = -20.0f;
	view = glm::translate(view, glm::vec3(movX, movY, movZ));

	//Auxiliares para revisar el modelo 
	//view = glm::rotate(view, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
	//view = glm::rotate(view, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));

	shader.setMat4("model", model);// pass them to the shaders
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
	glBindVertexArray(VAO);




	//Color zone 
	float	bodyR = 0.120f / 0.256f,
			bodyG = 0.124f / 0.256f,
			bodyB = 0.117f / 0.256f ;

	float	aspaR = 0.021f / 0.256f,
			aspaG = 0.023f / 0.256f,
			aspaB = 0.040f / 0.256f;

	float	maderaR = 0.124f / 0.256f,
			maderaG = 0.1003f / 0.256f,
			maderaB = 0.066f / 0.256f;


	//MODELADO JERARQUICO CON BASE EN LA CLASE 


	//CILINDRO - CUERPO PRINCIPAL
	glm::mat4 temporal = glm::mat4(1.0f);
	temporal = model = glm::translate(model, glm::vec3(0.0f, 2.5f, 0.0f));
	model = glm::scale(model, glm::vec3(4.75f, 5.0f, 4.75f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", glm::vec3(bodyR, bodyG, bodyB));
	cylinder_1.render();

	//CONO - TECHO
	model = glm::translate(temporal, glm::vec3(0.0f, 3.3f, 0.0f));
	model = glm::scale(model, glm::vec3(4.75f, 3.0f, 4.75f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", glm::vec3(aspaR, aspaG, aspaB));
	cone_1.render();

	//SOPORT AXIS (Pentagono/cubo) - SOPORTE DE LOS EJES DE LAS ASPAS 
	temporal = model = glm::translate(temporal, glm::vec3(0.0f, 1.3f, 1.8f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", glm::vec3(maderaR, maderaG, maderaB));
	soportAxis_1.render();

	//CILINDRO - EJE DE ROTACIÓN ASPAS

	temporal = model = glm::rotate(model, glm::radians(rotAspas), glm::vec3(0.0f, 0.0f, 1.0f));
	temporal = model = glm::translate(temporal, glm::vec3(0.0f, 0.0f, 1.1f));
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 1.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", glm::vec3(maderaR - .060, maderaG - .060, maderaB - .060));
	cylinder_1.render();



	//ASPAS DEL MOLINO

	temporal = model = glm::translate(temporal, glm::vec3(0.0f, 0.0f, -0.7f));

		model = glm::translate(temporal, glm::vec3(-1.3f, 1.3f, 1.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 4.0f, 1.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", glm::vec3(aspaR, aspaG, aspaB));
		aspa_1.render();

		model = glm::translate(temporal, glm::vec3(1.3f, 1.3f, 1.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 4.0f, 1.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", glm::vec3(aspaR, aspaG, aspaB));
		aspa_1.render();

		model = glm::translate(temporal, glm::vec3(-1.3f, -1.3f, 1.0f));
		model = glm::rotate(model, glm::radians(135.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 4.0f, 1.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", glm::vec3(aspaR, aspaG, aspaB));
		aspa_1.render();

		model = glm::translate(temporal, glm::vec3(1.3f, -1.3f, 1.0f));
		model = glm::rotate(model, glm::radians(225.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 4.0f, 1.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", glm::vec3(aspaR, aspaG, aspaB));
		aspa_1.render();



	glBindVertexArray(0);

}



//GENERAL FUNCTIONS FOR PROJECT

//For resolution window
void getResolution() {
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

//For resolution viewport
void resize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

//Keyboard mapping 
void keyboardMap(GLFWwindow *window){

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  
        glfwSetWindowShouldClose(window, true);

	//Movimiento aspas
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		rotAspas -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		rotAspas += 0.1f;

/*
	//Para ver el objeto
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rotY += 0.1f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rotY -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		rotX -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		rotX += 0.1f;
*/
}


//MAIN function project
int main() {

// GENERAL CODE FOR WINDOW CREATION DON'T TOUCH
	glfwInit();

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Modelado jerarquico - Molino 3D", NULL, NULL);
	if (window == NULL){
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize);
	glewInit();


// GENERAL FOR PROJECT

	//object instants (Using construct methods)
	cylinder_1.init();
	cone_1.init();
	aspa_1.init();
	soportAxis_1.init();

	glEnable(GL_DEPTH_TEST);
	Shader projectionShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");

	// render loop 
	while (!glfwWindowShouldClose(window)) {

		keyboardMap(window);

		// Render & Background
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		drawElements(projectionShader);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//object (Using destroyer methods)

	glfwTerminate();
	return 0;
}




