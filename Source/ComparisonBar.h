#ifndef GPA_ASS2_COMPARISONBAR_H
#define GPA_ASS2_COMPARISONBAR_H
#include "../Source/GLIncludes.h"

class ComparisonBar
{
public:
	ComparisonBar();
	~ComparisonBar();
	void reshape(int width);
	float getSplitPos() const;
	void setSplitPos(int val);

private:
	float splitPos;
	float widthOrigin = 0;
};
#endif

