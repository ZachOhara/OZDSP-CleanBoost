#include "ParamValueLabel.h"

ParamValueLabel::ParamValueLabel(IPlugBase* pPlug, int paramIdx, IRECT pR) :
	ITextControl(pPlug, pR, &defaultParamText, "Hello PVL!")
{
	mpParam = pPlug->GetParam(paramIdx);
}

ParamValueLabel::~ParamValueLabel()
{
}

void ParamValueLabel::UpdateDisplay()
{
	char* display = (char*)malloc(MAX_PARAM_DISPLAY_LEN);
	mpParam->GetDisplayForHost(display);
	const char* label = mpParam->GetLabelForHost();
	strcat(display, label);
	SetText(display);
}

void ParamValueLabel::SetText(char* text)
{
	SetTextFromPlug(text);
}
