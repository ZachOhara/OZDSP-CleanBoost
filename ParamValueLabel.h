#ifndef __PARAMVALUELABEL__
#define __PARAMVALUELABEL__

#include "IPlug_include_in_plug_hdr.h"

#include <string.h>

static IText defaultParamText(18, &COLOR_WHITE, "Roboto", IText::kStyleNormal, IText::kAlignCenter, 0, IText::kQualityDefault);

class ParamValueLabel : public ITextControl
{
public:
	ParamValueLabel(IPlugBase* pPlug, int paramIdx, IRECT pR);
	~ParamValueLabel();

	void UpdateDisplay();
	void SetText(char* text);

private:
	IParam* mpParam;
};

#endif // !__PARAMVALUELABEL__
