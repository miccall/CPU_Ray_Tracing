// RayTracing.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "MicImage.h"

// data of image 

const GLint  ImageWidth = 192 * 4 ;
const GLint  ImageHeight = 108 * 4;
const GLint SamplingRate = 1000;
static GLbyte* PixelData;


// openGL 初始化 
void init(int argc, char** argv, unsigned int mode, int x_position, int y_position, int width, int heigth, const char * title)
{
	// GL 初始化 
	glutInit(&argc, argv);
	// 开启双缓冲机制 和 颜色缓冲 
	glutInitDisplayMode(mode);
	// 窗口位置 
	glutInitWindowPosition(x_position, y_position);
	// 窗口尺寸
	glutInitWindowSize(width, heigth);
	// 窗口名称 
	glutCreateWindow(title);

	// 清空颜色缓存 
	glClearColor(1.0, 0.0, 1.0, 1.0);
	// 矩阵模式 
	/*
	GL_MODELVIEW： 应用这个参数后，表示接下来的矩阵操作都是针对模型视景矩阵堆栈 。  直到下一次调用这个函数并更改参数为止。
	GL_PROJECTION：应用这个参数后，表示接下来的矩阵操作都是针对投影矩阵堆栈    。  直到下一次调用这个函数并更改参数为止。
	GL_TEXTURE ：  应用这个参数后，表示接下来的矩阵操作都是针对纹理矩阵堆栈    。  直到下一次调用这个函数并更改参数为止。
	*/
	glMatrixMode(GL_PROJECTION);
	//特殊的正射投影函数 left right bottom top 
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawPixels(ImageWidth, ImageHeight,
		GL_RGB, GL_UNSIGNED_BYTE, PixelData);

	glutSwapBuffers();
	glFlush();
}

int main(int argc, char *argv[]) {

	PixelData = MicImage::getInstance(ImageWidth, ImageHeight)->render();
	// GL 初始化 自定义初始化内容
	init(argc, argv, GLUT_DOUBLE | GLUT_RGBA, 100, 100, ImageWidth, ImageHeight, "miccall");
	glutDisplayFunc(&display);
	glutMainLoop();
	return 0;
}


