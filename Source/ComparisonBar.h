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
	void drag(int x);
	void startDrag();
	void endDrag();

private:
	float splitPos;
	float widthOrigin = 0;
	bool dragging = false;
};
#endif

