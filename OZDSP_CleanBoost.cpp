#include "OZDSP_CleanBoost.h"
#include "IPlug_include_in_plug_src.h"
#include "IControl.h"
#include "resource.h"

const int kNumPrograms = 0;

enum EParams
{
	kBoostPid,
	kNumParams
};

enum ELayout
{
	kWidth = GUI_WIDTH,
	kHeight = GUI_HEIGHT,
	kKnobFrames = 128,

	kBoostKnobX = 15,
	kBoostKnobY = 40,

	kBoostLabelX = 15,
	kBoostLabelY = 160,
	kBoostLabelWidth = 120,
	kBoostLabelHeight = 15
};

OZDSP_CleanBoost::OZDSP_CleanBoost(IPlugInstanceInfo instanceInfo) :
	IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo)
{
	TRACE;

	//arguments are: name, defaultVal, minVal, maxVal, step, label
	GetParam(kBoostPid)->InitDouble("Boost", 0.0, -100.0, 0, 0.1, " dB");
	GetParam(kBoostPid)->SetShape(0.2);
	GetParam(kBoostPid)->SetDisplayText(-100, "-oo dB");

	IGraphics* pGraphics = MakeGraphics(this, kWidth, kHeight);
	pGraphics->AttachBackground(BACKGROUND_RID, BACKGROUND_FN);

	IBitmap knob120 = pGraphics->LoadIBitmap(KNOB_120_RID, KNOB_120_FN, kKnobFrames);

	pGraphics->AttachControl(new IKnobMultiControl(this, kBoostKnobX, kBoostKnobY, kBoostPid, &knob120));

	IRECT tmpRect(kBoostLabelX, kBoostLabelY, kBoostLabelX + kBoostLabelWidth, kBoostLabelY + kBoostLabelHeight);
	mpBoostLabel = new ParamValueLabel(this, kBoostPid, tmpRect);
	pGraphics->AttachControl(mpBoostLabel);

	AttachGraphics(pGraphics);

	CreatePresets();
}

OZDSP_CleanBoost::~OZDSP_CleanBoost() {}

void OZDSP_CleanBoost::CreatePresets()
{
	// TODO
}

void OZDSP_CleanBoost::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
{
	// Mutex is already locked for us.
	const int nChannels = 2;

	for (int i = 0; i < nFrames; i++)
	{
		for (int j = 0; j < nChannels; j++)
		{
			outputs[j][i] = mVolumeControl.GetAdjustedSample(inputs[j][i]);
		}
	}
}

void OZDSP_CleanBoost::Reset()
{
	TRACE;
	IMutexLock lock(this);
}

void OZDSP_CleanBoost::OnParamChange(int paramIdx)
{
	IMutexLock lock(this);

	switch (paramIdx)
	{
	case kBoostPid:
		if (GetParam(kBoostPid)->Value() > GetParam(kBoostPid)->GetMin())
		{
			mVolumeControl.SetDecibels(GetParam(kBoostPid)->Value());
		}
		else
		{
			mVolumeControl.SetZero();
		}
		mpBoostLabel->UpdateDisplay();
		break;
	default:
		break;
	}
}
