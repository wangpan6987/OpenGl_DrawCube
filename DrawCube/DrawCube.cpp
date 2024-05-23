//// DrawCube.cpp: 定义应用程序的入口点。
////
//
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Shader.h"
#include <memory>
#include <GLFW/glfw3.h>

using namespace std;

std::unique_ptr<Shader> shader;
GLuint VAO, VBO, EBO;

/* 编写各顶点位置 */
GLfloat vertices_1[] =
{
	//position					
	0.5f, 0.5f, 0.0f,			// top right		0
	0.5f, -0.5f, 0.0f,			// bottom right		1
	-0.5f, -0.5f, 0.0f,			// bottom left		2
	-0.5f, 0.5f, 0.0f,			// top left			3
};

/* 四个顶点的连接信息给出来 */
GLuint indices_1[] =
{
	0, 1, 3,		// 序号为 0、1、3 的顶点组合成一个三角形
	1, 2, 3			// 序号为 1、2、3 的顶点组合成一个三角形
};


void Init()
{
	glfwInit();
	glewInit();
	shader = std::make_unique<Shader>("shader_v.txt", "shader_f.txt");
	//GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);

	/* 设置链接顶点属性 */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);	// 通道 0 打开

	/* 设置索引缓冲对象	*/
	//GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_1), indices_1, GL_STATIC_DRAW);
}

void Timer(int value) {
	glutPostRedisplay(); // 标记当前窗口需要被重绘
	glutTimerFunc(1000 / 60, Timer, 0); // 重新设置定时器
}

void RenderScene(void)
{
	glClearColor(0.1f, 0.8f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 800, 600);

	/*  绘制图形 */
	shader->Use();
	float time = glfwGetTime();						// 获取时间
	float redValue = sin(time) / 2.0f + 0.5f;		// 红色数值计算，范围[0,1]
	float greenValue = 1 - redValue;				// 绿色数值计算，范围[0.1]。且满足 “redValue + greenValue = 1”
	int vertexColorLocation = glGetUniformLocation(shader->Program, "time");
	glUniform4f(vertexColorLocation, redValue, greenValue, 0.0f, 1.0f);

	glBindVertexArray(VAO);									// 绑定 VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);				// 绑定 EBO
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	// 画两个三角形 从第0个顶点开始 一共画6次
	glBindVertexArray(0);									// 解绑定 VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);				// 解绑定 EBO

	glFlush();
}

void onWindowClose()
{
	if(shader)
		shader.reset(nullptr);

	glDeleteVertexArrays(1, &VAO);			// 释放资源	
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("绘制正方形");
	glutPositionWindow(0, 0);
	glutReshapeWindow(800, 600);
	Init();
	glutTimerFunc(0, Timer, 0); // 设置定时器
	glutDisplayFunc(RenderScene);
	glutCloseFunc(onWindowClose);
	glutMainLoop();
	return 0;
}

///* 引入相应的库 */
//#include <iostream>
//using namespace std;
//#include <GL/glew.h>	
//#include <GLFW/glfw3.h> 
//#include "Shader.h"
//
///* 编写各顶点位置 */
//GLfloat vertices_1[] =
//{
//	//position					
//	0.5f, 0.5f, 0.0f,			// top right		0
//	0.5f, -0.5f, 0.0f,			// bottom right		1
//	-0.5f, -0.5f, 0.0f,			// bottom left		2
//	-0.5f, 0.5f, 0.0f,			// top left			3
//};
//
///* 四个顶点的连接信息给出来 */
//GLuint indices_1[] =
//{
//	0, 1, 3,		// 序号为 0、1、3 的顶点组合成一个三角形
//	1, 2, 3			// 序号为 1、2、3 的顶点组合成一个三角形
//};
//
//const GLint WIDTH = 600, HEIGHT = 600;		// 正方形窗口
//
//int main()
//{
//	glfwInit();
//	GLFWwindow* window_1 = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL Triangle test", nullptr, nullptr);
//	int screenWidth_1, screenHeight_1;
//	glfwGetFramebufferSize(window_1, &screenWidth_1, &screenHeight_1);
//	glfwMakeContextCurrent(window_1);
//	glewInit();
//
//	/* 将我们自己设置的着色器文本传进来 */
//	Shader ourShader = Shader("shader_v.txt", "shader_f.txt");		// 相对路径
//
//	/* 设置顶点缓冲对象(VBO) + 设置顶点数组对象(VAO)  */
//	GLuint VAO, VBO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);
//
//	/* 设置链接顶点属性 */
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);	// 通道 0 打开
//
//	/* 设置索引缓冲对象	*/
//	GLuint EBO;
//	glGenBuffers(1, &EBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_1), indices_1, GL_STATIC_DRAW);
//
//	// draw loop 画图循环
//	while (!glfwWindowShouldClose(window_1))
//	{
//		// 视口 + 时间 
//		glViewport(0, 0, screenWidth_1, screenHeight_1);
//		glfwPollEvents();
//
//		// 渲染 + 清除颜色缓冲
//		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		/*  绘制图形 */
//		ourShader.Use();
//		float time = glfwGetTime();						// 获取时间
//		float redValue = sin(time) / 2.0f + 0.5f;		// 红色数值计算，范围[0,1]
//		float greenValue = 1 - redValue;				// 绿色数值计算，范围[0.1]。且满足 “redValue + greenValue = 1”
//		int vertexColorLocation = glGetUniformLocation(ourShader.Program, "time");
//		glUniform4f(vertexColorLocation, redValue, greenValue, 0.0f, 1.0f);
//
//		glBindVertexArray(VAO);									// 绑定 VAO
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);				// 绑定 EBO
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	// 画两个三角形 从第0个顶点开始 一共画6次
//		glBindVertexArray(0);									// 解绑定 VAO
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);				// 解绑定 EBO
//
//		// 交换缓冲
//		glfwSwapBuffers(window_1);
//	}
//
//	glDeleteVertexArrays(1, &VAO);	// 释放资源
//	glDeleteBuffers(1, &VBO);
//	glDeleteBuffers(1, &EBO);
//	glfwTerminate();				// 结束
//	return 0;
//}
