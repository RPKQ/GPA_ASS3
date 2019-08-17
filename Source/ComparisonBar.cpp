#include "ComparisonBar.h"

ComparisonBar::ComparisonBar(int initPos)
{
	this->splitPos = (float)initPos;
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
	this->splitPos = this->splitPos / widthOrigin * (float)width;
	widthOrigin = (float)width;
}