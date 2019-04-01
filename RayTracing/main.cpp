#include "Color.h"

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

// 保存渲染图片 
void savepic()
{
	if (count == SamplingRate)
	{
		//文件访问
		std::ofstream outf;
		outf.open("C:/Users/miccall/Desktop/abc.ppm");
		outf << "P3\n" << ImageWidth << " " << ImageHeight << "\n255\n";

		for (int h = ImageHeight - 1; h >= 0; h--)
		{
			for (int i = 0; i < rgbwidth; i += 3)
			{
				outf << PixelData[h *(rgbwidth)+(i + 0)] << " " <<
					PixelData[h *(rgbwidth)+(i + 1)] << " " <<
					PixelData[h *(rgbwidth)+(i + 2)] << " \n";
			}
		}

		outf.close();
		std::cout << "finished" << std::endl;
	}
}

// 显示进度
void showProgress(int num, int sum)
{
	system("cls");
	std::cout << (sum - num) * 100 / sum << "%" << std::endl;
}

// 预处理
void renderdata()
{
	for (int j = ImageHeight - 1; j >= 0; j--)
	{
		for (int i = 0, k = 0; i < rgbwidth; i += 3, k++)
		{
			int index = j * ImageWidth + k;
			col[index] = Vec3(0, 0, 0);

			PixelData[j *(rgbwidth)+(i + 0)] = (GLbyte) int(0);  // R
			PixelData[j *(rgbwidth)+(i + 1)] = (GLbyte) int(0);  // G
			PixelData[j *(rgbwidth)+(i + 2)] = (GLbyte) int(0);  // B	
		}
	}
}

// 数据计算加载 
void data()
{
	// 计算像素数据长度
	PixelLength = ImageWidth * 3;
	while (PixelLength % 3 != 0)
		++PixelLength;
	PixelLength *= ImageHeight;
	PixelData = new GLbyte[PixelLength];
	col = new Vec3[ImageHeight*ImageWidth];
}

// opengl着色 s
void pixel()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawPixels(ImageWidth, ImageHeight,
		GL_RGB, GL_UNSIGNED_BYTE, PixelData);

	glutSwapBuffers();
	glFlush();
}

// 采样 
void setpixdata(int cc, int index_culm)
{
	int start = ImageHeight - 1 - (index_culm * ImageHeight) / 3;
	int loop = ImageHeight - (index_culm + 1) * ImageHeight / 3;
	//std::cout <<"index-"<< index_culm << ":" << "start " << start << "loop until " << loop << std::endl;
	for (int j = start; j >= loop; j--)
	{
		for (int i = 0, k = 0; i < rgbwidth; i += 3, k++)
		{
			float u = float(k + drand48()) / float(ImageWidth);
			float v = float(j + drand48()) / float(ImageHeight);

			Ray r = cam.getRay(u, v);
			int index = j * ImageWidth + k;
			col[index] += color(r, world, 0);

			colorvec = col[index] / float(cc);
			colorvec = Gamma_Correct(colorvec);

			int R = int(255.99 * colorvec[0]);
			int G = int(255.99 * colorvec[1]);
			int B = int(255.99 * colorvec[2]);

			// 像素数据 
			PixelData[j *(rgbwidth)+(i + 0)] = (GLbyte)R;  // R
			PixelData[j *(rgbwidth)+(i + 1)] = (GLbyte)G;  // G
			PixelData[j *(rgbwidth)+(i + 2)] = (GLbyte)B;  // B

		}
	}
}

void setpixdata(int cc, int culm , int row )
{
	int start = ImageHeight - 1 - (culm * ImageHeight) / 3;
	int loop = ImageHeight - (culm + 1) * ImageHeight / 3;
	int rowstart = (row * ImageWidth) / 4;
	int rowend = (row + 1) * ImageWidth / 4 - 1;
	//std::cout <<"index-"<< index_culm << ":" << "start " << start << "loop until " << loop << std::endl;
	for (int j = start; j >= loop; j--)
	{
		for (int i = rowstart * 3 , k = rowstart ; i <= rowend * 3 ; i += 3, k++)
		{
			float u = float(k + drand48()) / float(ImageWidth);
			float v = float(j + drand48()) / float(ImageHeight);

			Ray r = cam.getRay(u, v);
			int index = j * ImageWidth + k;
			col[index] += color(r, world, 0);

			colorvec = col[index] / float(cc);
			colorvec = Gamma_Correct(colorvec);

			int R = int(255.99 * colorvec[0]);
			int G = int(255.99 * colorvec[1]);
			int B = int(255.99 * colorvec[2]);

			// 像素数据 
			PixelData[j *(rgbwidth)+(i + 0)] = (GLbyte)R;  // R
			PixelData[j *(rgbwidth)+(i + 1)] = (GLbyte)G;  // G
			PixelData[j *(rgbwidth)+(i + 2)] = (GLbyte)B;  // B

		}
	}
}
// 循环采样
void timerProc(int id)
{
	/*
	if (count <= SamplingRate)
	{
		setpixdata();
		count++;
	}
	*/
	glutPostRedisplay();
	glutTimerFunc(1, timerProc, 1);//需要在函数中再调用一次，才能保证循环  
}

// 子线程1
void func1()
{
	for (int i = 0; i < SamplingRate && count <= SamplingRate; i++)
	{
		showProgress(SamplingRate - count, SamplingRate);
		savepic();
		setpixdata(count, 0,0);
		count++;
	}
}

// 线程2 
void func2()
{
	int cc = 2;
	for (int i = 0; i < SamplingRate && count <= SamplingRate; i++)
	{
		setpixdata(cc, 0,1);
		cc++;
	}
}

// 线程3
void func3()
{
	int cc = 2;
	for (int i = 0; i < SamplingRate && count <= SamplingRate; i++)
	{
		setpixdata(cc, 0,2);
		cc++;
	}
}

// 线程3
void func4()
{
	int cc = 2;
	for (int i = 0; i < SamplingRate && count <= SamplingRate; i++)
	{
		setpixdata(cc, 0, 3);
		cc++;
	}
}

// 线程3
void func5()
{
	int cc = 2;
	for (int i = 0; i < SamplingRate && count <= SamplingRate; i++)
	{
		setpixdata(cc, 1, 0);
		cc++;
	}
}
// 线程3
void func6()
{
	int cc = 2;
	for (int i = 0; i < SamplingRate && count <= SamplingRate; i++)
	{
		setpixdata(cc, 1, 1);
		cc++;
	}
}
// 线程3
void func7()
{
	int cc = 2;
	for (int i = 0; i < SamplingRate && count <= SamplingRate; i++)
	{
		setpixdata(cc, 1, 2);
		cc++;
	}
}
// 线程3
void func8()
{
	int cc = 2;
	for (int i = 0; i < SamplingRate && count <= SamplingRate; i++)
	{
		setpixdata(cc, 1, 3);
		cc++;
	}
}
// 线程3
void func9()
{
	int cc = 2;
	for (int i = 0; i < SamplingRate && count <= SamplingRate; i++)
	{
		setpixdata(cc, 2, 0);
		cc++;
	}
}
// 线程3
void func10()
{
	int cc = 2;
	for (int i = 0; i < SamplingRate && count <= SamplingRate; i++)
	{
		setpixdata(cc, 2, 1);
		cc++;
	}
}
// 线程3
void func11()
{
	int cc = 2;
	for (int i = 0; i < SamplingRate && count <= SamplingRate; i++)
	{
		setpixdata(cc, 2, 2);
		cc++;
	}
}
// 线程3
void func12()
{
	int cc = 2;
	for (int i = 0; i < SamplingRate && count <= SamplingRate; i++)
	{
		setpixdata(cc, 2, 3);
		cc++;
	}
}

inline float pdf(const Vec3 & p)
{
	return 1 / (4 * M_PI);
}

void testMC04()
{
	int N = 1000000;
	float sum = 0;
	for (int i = 0; i < N; i++)
	{
		Vec3 d = Random_in_unitt_cube();
		float cosine_squared = d.z() * d.z();
		sum += cosine_squared / pdf(d);
	}
	std::cout << "I = " << sum / N << std::endl;
	getchar();
}


void testTiledata()
{
	int culm = 1, row = 3 ;

	int start = ImageHeight - 1 - (culm * ImageHeight) / 3;
	int loop = ImageHeight - (culm + 1) * ImageHeight / 3;
	int rowstart = (row * ImageWidth) / 4 ;
	int rowend = (row + 1) * ImageWidth / 4 -1 ;

	// 遍历 高 
	for (int j = start ; j >= loop ; j--)
	{
		// 便利宽 
		for (int i = rowstart * 3 , k = 0 ; i < rowend*3 ; i += 3, k++)
		{
			int index = j * ImageWidth + k;
			col[index] = Vec3(0, 0, 0);

			PixelData[j *(rgbwidth)+(i + 0)] = (GLbyte) int(0);  // R
			PixelData[j *(rgbwidth)+(i + 1)] = (GLbyte) int(255);  // G
			PixelData[j *(rgbwidth)+(i + 2)] = (GLbyte) int(0);  // B	
		}
	}

}
// 主方法 
int main(int argc, char** argv)
{
	// 初始化 
	data();
	// 第一帧数据 
	renderdata();
	
	// 开子线程完成
	std::thread t1(func1);
	std::thread t2(func2);
	std::thread t3(func3);
	std::thread t4(func4);

	std::thread t5(func5);
	std::thread t6(func6);
	std::thread t7(func7);
	std::thread t8(func8);

	std::thread t9(func9);
	std::thread t10(func10);
	std::thread t11(func11);
	std::thread t12(func12);

	// GL 初始化 自定义初始化内容
	init(argc, argv, GLUT_DOUBLE | GLUT_RGBA, 100, 100, ImageWidth, ImageHeight, "miccall");
	glutDisplayFunc(pixel);
	glutTimerFunc(1, timerProc, 1);
	glutMainLoop();

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	t5.join();
	t6.join();
	t7.join();
	t8.join();

	t9.join();
	t10.join();
	t11.join();
	t12.join();

	// testMC04();

	return 0;
}

