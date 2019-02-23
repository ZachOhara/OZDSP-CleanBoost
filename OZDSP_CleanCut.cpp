#include "OZDSP_CleanCut.h"
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

OZDSP_CleanCut::OZDSP_CleanCut(IPlugInstanceInfo instanceInfo) :
	IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo)
{
	TRACE;

	//arguments are: name, defaultVal, minVal, maxVal, step, label
	InitGainParameter(GetParam(kBoostPid), "Boost");

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

OZDSP_CleanCut::~OZDSP_CleanCut() {}

void OZDSP_CleanCut::CreatePresets()
{
	// TODO
}

void OZDSP_CleanCut::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
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

void OZDSP_CleanCut::Reset()
{
	TRACE;
	IMutexLock lock(this);
}

void OZDSP_CleanCut::OnParamChange(int paramIdx)
{
	IMutexLock lock(this);

	switch (paramIdx)
	{
	case kBoostPid:
		ZeroGainParam(GetParam(kBoostPid));
		if (IsParamMinimized(GetParam(kBoostPid)))
		{
			mVolumeControl.SetZero();
		}
		else
		{
			mVolumeControl.SetDecibels(GetParam(kBoostPid)->Value());
		}
		mpBoostLabel->UpdateDisplay();
		break;
	default:
		break;
	}
}