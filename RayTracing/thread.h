#pragma once
#include "Color.h"

// 显示进度
void showProgress(int num, int sum)
{
	system("cls");
	std::cout << (sum - num) * 100 / sum << "%" << std::endl;
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

void setpixdata(int cc, int culm, int row)
{
	int start = ImageHeight - 1 - (culm * ImageHeight) / 3;
	int loop = ImageHeight - (culm + 1) * ImageHeight / 3;
	int rowstart = (row * ImageWidth) / 4;
	int rowend = (row + 1) * ImageWidth / 4 - 1;
	//std::cout <<"index-"<< index_culm << ":" << "start " << start << "loop until " << loop << std::endl;
	for (int j = start; j >= loop; j--)
	{
		for (int i = rowstart * 3, k = rowstart; i <= rowend * 3; i += 3, k++)
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
// 线程 
void func1()
{
	for (int i = 0; i < SamplingRate && count <= SamplingRate; i++)
	{
		showProgress(SamplingRate - count, SamplingRate);
		savepic();
		setpixdata(count, 0, 0);
		count++;
	}
}

// 线程2 
void func2()
{
	int cc = 2;
	for (int i = 0; i < SamplingRate && count <= SamplingRate; i++)
	{
		setpixdata(cc, 0, 1);
		cc++;
	}
}

// 线程3
void func3()
{
	int cc = 2;
	for (int i = 0; i < SamplingRate && count <= SamplingRate; i++)
	{
		setpixdata(cc, 0, 2);
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