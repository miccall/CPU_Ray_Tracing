#include "thread.h"

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

/*
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
*/

// ������ 
int main(int argc, char** argv)
{
	// ��ʼ�� 
	data();
	// ��һ֡���� 
	renderdata();
	
	// �����߳����
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

	// GL ��ʼ�� �Զ����ʼ������
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

