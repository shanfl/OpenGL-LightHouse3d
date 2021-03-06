#include <GL/glew.h>
#include <GL/freeglut.h>
#include <ogl/shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Shader uniformShader("glsl test");
GLuint program, vertex_loc, mvp_matrix_loc;
GLuint color_loc;

using namespace  std;

static const GLfloat VertexData[] = 
{
	0.0f,  0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
};

void init_shader()
{
	uniformShader.init();
	uniformShader.attach(GL_VERTEX_SHADER, "Attribute.vert");
	uniformShader.attach(GL_FRAGMENT_SHADER, "Attribute.frag");
	uniformShader.link();
	uniformShader.use();
	program = uniformShader.GetProgram();

	mvp_matrix_loc = glGetUniformLocation(program, "mvp_matrix");
	color_loc = glGetUniformLocation(program, "color");
	vertex_loc = glGetAttribLocation(program, "position");
	glEnableVertexAttribArray(vertex_loc);
	glVertexAttribPointer(vertex_loc, 3, GL_FLOAT, GL_FALSE, 0, VertexData);

}

void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	init_shader();
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	glUseProgram(program);
	glUniform4f(color_loc, sin(time), cos(time), 0.0, 0.0); //注意第四个元素是alpha，开启后0为透明
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutSwapBuffers();
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(720, 640);
	glutCreateWindow("glsl-Attribute");
	GLenum status = glewInit();
	if (status != GLEW_OK)
		std::cerr << glewGetErrorString(status) << std::endl;
	init();
	glutDisplayFunc(render);
	glutMainLoop();
	return 0;
}