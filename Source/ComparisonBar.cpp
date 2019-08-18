#include "ComparisonBar.h"

ComparisonBar::ComparisonBar()
{
}

ComparisonBar::~ComparisonBar()
{
}

float ComparisonBar::getSplitPos() const
{
	return this->splitPos;
}

void ComparisonBar::setSplitPos(int val)
{
	this->splitPos = (float)val;
}

void ComparisonBar::reshape(int width)
{
	if (this->widthOrigin == 0)
	{
		this->widthOrigin = (float)width;
		this->splitPos = (float)width / 2;
		return;
	}
	this->splitPos = this->splitPos / widthOrigin * (float)width;
	widthOrigin = (float)width;
}