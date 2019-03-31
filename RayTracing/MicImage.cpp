#include "MicImage.h"
#include "Functions.h"


MicImage* MicImage::instance = nullptr;

MicImage* MicImage::getInstance(GLint  ImageWidth, GLint  ImageHeight) {
	if (instance != nullptr)
	{
		return instance;
	}
	return new MicImage(ImageWidth, ImageHeight);
}


MicImage::MicImage(GLint  ImageWidth , GLint  ImageHeight )
{
	_ImageHeight = ImageHeight;
	_ImageWidth = ImageWidth;
	rgbwidth = _ImageWidth * 3;
	predata();
	renderdata();
}

MicImage::~MicImage()
{
	delete(_PixelData);
	delete(instance);
}

void MicImage::predata()
{
	// 计算像素数据长度
	_PixelLength = _ImageWidth * 3;
	while (_PixelLength % 3 != 0)
		++_PixelLength;
	_PixelLength *= _ImageHeight;
	_PixelData = new GLbyte[_PixelLength];
}

// 预处理
void MicImage::renderdata()
{
	for (int j = _ImageHeight - 1; j >= 0; j--)
	{
		for (int i = 0, k = 0; i < rgbwidth; i += 3, k++)
		{
			int index = j * _ImageWidth + k;
			_PixelData[j *(rgbwidth)+(i + 0)] = (GLbyte) int(0);  // R
			_PixelData[j *(rgbwidth)+(i + 1)] = (GLbyte) int(0);  // G
			_PixelData[j *(rgbwidth)+(i + 2)] = (GLbyte) int(0);  // B	
		}
	}
}

vec3 MicImage::color(const Ray & r)
{
	vec3 unit_direction = MicFunc::unit_vector(r.Direction());
	float t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}


GLbyte * MicImage::render()
{
	vec3 LLC(-2.0, -1.0, -1.0);
	vec3 H(4.0, 0.0, 0.0);
	vec3 V(0.0,2.0,0.0);
	vec3 O(0.0,0.0,0.0);
	for (int j = _ImageHeight - 1; j >= 0; j--)
	{
		for (int i = 0, k = 0; i < rgbwidth; i += 3, k++)
		{

			float u = float(k) / float(_ImageWidth);
			float v = float(j) / float(_ImageHeight);
			Ray r(O, LLC + u * H + v * V);
			vec3 col = color(r);

			_PixelData[j *(rgbwidth)+(i + 0)] = (GLbyte) int(255.99 * col[0]);  // R
			_PixelData[j *(rgbwidth)+(i + 1)] = (GLbyte) int(255.99 * col[1]);  // G
			_PixelData[j *(rgbwidth)+(i + 2)] = (GLbyte) int(255.99 * col[2]);  // B	
		}
	}
	return _PixelData;
}