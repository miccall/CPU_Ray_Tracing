#include "Color.h"

// openGL ��ʼ�� 
void init(int argc, char** argv, unsigned int mode, int x_position, int y_position, int width, int heigth, const char * title)
{
	// GL ��ʼ�� 
	glutInit(&argc, argv);
	// ����˫������� �� ��ɫ���� 
	glutInitDisplayMode(mode);
	// ����λ�� 
	glutInitWindowPosition(x_position, y_position);
	// ���ڳߴ�
	glutInitWindowSize(width, heigth);
	// �������� 
	glutCreateWindow(title);

	// �����ɫ���� 
	glClearColor(1.0, 0.0, 1.0, 1.0);
	// ����ģʽ 
	/*
	GL_MODELVIEW�� Ӧ����������󣬱�ʾ�������ľ�������������ģ���Ӿ������ջ ��  ֱ����һ�ε���������������Ĳ���Ϊֹ��
	GL_PROJECTION��Ӧ����������󣬱�ʾ�������ľ�������������ͶӰ�����ջ    ��  ֱ����һ�ε���������������Ĳ���Ϊֹ��
	GL_TEXTURE ��  Ӧ����������󣬱�ʾ�������ľ���������������������ջ    ��  ֱ����һ�ε���������������Ĳ���Ϊֹ��
	*/
	glMatrixMode(GL_PROJECTION);
	//���������ͶӰ���� left right bottom top 
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

// ������ȾͼƬ 
void savepic()
{
	if (count == SamplingRate)
	{
		//�ļ�����
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

// ��ʾ����
void showProgress(int num, int sum)
{
	system("cls");
	std::cout << (sum - num) * 100 / sum << "%" << std::endl;
}

// Ԥ����
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

// ���ݼ������ 
void data()
{
	// �����������ݳ���
	PixelLength = ImageWidth * 3;
	while (PixelLength % 3 != 0)
		++PixelLength;
	PixelLength *= ImageHeight;
	PixelData = new GLbyte[PixelLength];
	col = new Vec3[ImageHeight*ImageWidth];
}

// opengl��ɫ s
void pixel()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawPixels(ImageWidth, ImageHeight,
		GL_RGB, GL_UNSIGNED_BYTE, PixelData);

	glutSwapBuffers();
	glFlush();
}

// ���� 
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

			// �������� 
			PixelData[j *(rgbwidth)+(i + 0)] = (GLbyte)R;  // R
			PixelData[j *(rgbwidth)+(i + 1)] = (GLbyte)G;  // G
			PixelData[j *(rgbwidth)+(i + 2)] = (GLbyte)B;  // B

		}
	}
}

// ѭ������
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
	glutTimerFunc(1, timerProc, 1);//��Ҫ�ں������ٵ���һ�Σ����ܱ�֤ѭ��  
}

// ���߳�1
void func1()
{
	for (int i = 0; i < SamplingRate && count <= SamplingRate; i++)
	{
		showProgress(SamplingRate - count, SamplingRate);
		savepic();
		setpixdata(count, 0);
		count++;
	}
}

// �߳�2 
void func2()
{
	int cc = 2;
	for (int i = 0; i < SamplingRate && count <= SamplingRate; i++)
	{
		setpixdata(cc, 1);
		cc++;
	}
}

// �߳�3
void func3()
{
	int cc = 2;
	for (int i = 0; i < SamplingRate && count <= SamplingRate; i++)
	{
		setpixdata(cc, 2);
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

// ������ 
int main(int argc, char** argv)
{
	data();
	renderdata();

	std::thread t1(func1);
	std::thread t2(func2);
	std::thread t3(func3);

	// GL ��ʼ�� �Զ����ʼ������
	init(argc, argv, GLUT_DOUBLE | GLUT_RGBA, 100, 100, ImageWidth, ImageHeight, "miccall");
	glutDisplayFunc(pixel);
	glutTimerFunc(1, timerProc, 1);
	glutMainLoop();

	t1.join();
	t2.join();
	t3.join();

	// testMC04();

	return 0;
}

