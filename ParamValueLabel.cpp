#include "ParamValueLabel.h"

ParamValueLabel::ParamValueLabel(IPlugBase* pPlug, int paramIdx, IRECT pR) :
	ITextControl(pPlug, pR, &defaultParamText, "")
{
	mpParam = pPlug->GetParam(paramIdx);
	UpdateDisplay();
}

ParamValueLabel::~ParamValueLabel()
{
}

void ParamValueLabel::UpdateDisplay()
{
	char* display[MAX_PARAM_DISPLAY_LEN];
	mpParam->GetDisplayForHost((char*) display);
	const char* label = mpParam->GetLabelForHost();
	strcat((char*) display, label);
	SetText((char*) display);
}

void ParamValueLabel::SetText(char* text)
{
	SetTextFromPlug(text);
}
