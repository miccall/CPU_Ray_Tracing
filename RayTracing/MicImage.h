#pragma once
#include <GL/glut.h>
#include "Ray.h"

class MicImage
{
public:

	GLint  _ImageWidth;
	GLint  _ImageHeight;
	GLint  rgbwidth;
	GLint   _PixelLength;
	GLbyte *_PixelData;
	static MicImage* instance;

	MicImage(GLint  ImageWidth, GLint  ImageHeight);
	~MicImage();
	static MicImage* getInstance(GLint  ImageWidth, GLint  ImageHeight);
	GLbyte * render();
private:

	// 数据计算加载 
	void predata();
	void renderdata();
	vec3 color(const Ray & r);
};
