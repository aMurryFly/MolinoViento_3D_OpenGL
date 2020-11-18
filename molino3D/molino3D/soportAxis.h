#pragma once
#ifndef SUP_H_
#define SUP_H_
#include <glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shader_m.h>
#include <iostream>


class soportAxis{

public:
	soportAxis(GLfloat inf);
	void init();
	void render();
	virtual ~soportAxis();

private:
	float inf;
	GLuint sup_VAO[4], sup_VBO[4];

};

#endif // !SUP_H_


// CLASS METHODS 

//constructor
soportAxis::soportAxis(GLfloat inf) :
	inf(inf) {
	sup_VAO[4] = (-1, -1, -1, -1);
	sup_VBO[4] = (-1, -1, -1, -1);
}

//destructor
soportAxis::~soportAxis(){
	glDeleteVertexArrays(4, sup_VAO);
	glDeleteBuffers(4, sup_VBO);
}

//Render method
void soportAxis::render() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glBindVertexArray(sup_VAO[0]);
	glDrawArrays(GL_QUADS, 0, 28);
	glDrawArrays(GL_TRIANGLES, 28, 6);
	glBindVertexArray(0);
}

//Primitive constructor 
void soportAxis::init(){

	GLfloat vertices[] = {
		//Position				//Color
		
		//Frontal
		-0.5f, -0.25f, 0.5f,	1.0f, 0.0f, 0.0f,	
		0.5f, -0.25f, 0.5f,		1.0f, 0.0f, 0.0f,	
		0.5f, 0.25f, 0.5f,		1.0f, 0.0f, 0.0f,	
		-0.5f, 0.25f, 0.5f,		1.0f, 0.0f, 0.0f,	

		//Posterior
		0.5f, -0.25f, -0.5f,	1.0f, 1.0f, 0.0f,	 
		-0.5f, -0.25f, -0.5f,	1.0f, 1.0f, 0.0f,	
		-0.5f, 0.25f, -0.5f,	1.0f, 1.0f, 0.0f,	
		0.5f, 0.25f, -0.5f,		1.0f, 1.0f, 0.0f,	

		// Izq
		-0.5f, 0.25f, 0.5f,		0.0f, 0.0f, 1.0f,	 
		-0.5f, 0.25f, -0.5f,	0.0f, 0.0f, 1.0f,	
		-0.5f, -0.25f, -0.5f,	0.0f, 0.0f, 1.0f,	
		-0.5f, -0.25f, 0.5f,	0.0f, 0.0f, 1.0f,	

		//Derecha
		0.5f, 0.25f, 0.5f,		0.0f, 0.0f, 1.0f,
		0.5f, -0.25f, 0.5f,		0.0f, 0.0f, 1.0f,
		0.5f, -0.25f, -0.5f,	0.0f, 0.0f, 1.0f,
		0.5f, 0.25f, -0.5f,		0.0f, 0.0f, 1.0f,

		//Inferior
		-0.5f, -0.25f, 0.5f,	0.0f, 0.0f, 1.0f,
		-0.5f, -0.25f, -0.5f,	0.0f, 0.0f, 1.0f,
		0.5f, -0.25f, -0.5f,	0.0f, 0.0f, 1.0f,
		0.5f, -0.25f, 0.5f,		0.0f, 0.0f, 1.0f,

//NOTA: Todo lo anterior es de un cubo aquí sólo agregamos el "techo", son 4 caras más

		//Techo derecho
		0.5f, 0.25f, 0.5f,		0.0f, 0.0f, 1.0f,
		0.5f, 0.25f, -0.5f,		0.0f, 0.0f, 1.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f,
		0.0f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,

		//Techo izquierdo
		-0.5f, 0.25f, 0.5f,		0.0f, 0.0f, 1.0f,
		-0.5f, 0.25f, -0.5f,	0.0f, 0.0f, 1.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f,
		0.0f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,

		//Techo frontal
		-0.5f, 0.25f, 0.5f,		0.0f, 0.0f, 1.0f,
		0.5f, 0.25f, 0.5f,		0.0f, 0.0f, 1.0f,
		0.0f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,
			
		//Techo posterior
		-0.5f, 0.25f, -0.5f,	0.0f, 0.0f, 1.0f,
		0.5f, 0.25f, -0.5f,		0.0f, 0.0f, 1.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f,

	};



	glGenVertexArrays(1, &sup_VAO[0]);
	glBindVertexArray(sup_VAO[0]);

	glGenBuffers(1, &sup_VBO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, sup_VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

