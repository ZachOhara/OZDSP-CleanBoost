#include "OZDSP_CleanCut.h"

#include "IPlug_include_in_plug_src.h"

#include "IControl.h"
#include "resource.h"

const int kNumPrograms = 0;

enum EParams
{
	kVolumePid,
	kNumParams
};

enum ELayout
{
	kWidth = GUI_WIDTH,
	kHeight = GUI_HEIGHT,
	kKnobFrames = 128,

	kVolumeKnobX = 15,
	kVolumeKnobY = 40,

	kVolumeLabelX = 15,
	kVolumeLabelY = 160,
	kVolumeLabelWidth = 120,
	kVolumeLabelHeight = 15
};

OZDSP_CleanCut::OZDSP_CleanCut(IPlugInstanceInfo instanceInfo) :
	IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo)
{
	TRACE;

	//arguments are: name, defaultVal, minVal, maxVal, step, label
	InitVolumeParameter(GetParam(kVolumePid));

	IGraphics* pGraphics = MakeGraphics(this, kWidth, kHeight);
	pGraphics->AttachBackground(BACKGROUND_RID, BACKGROUND_FN);

	IBitmap knob120 = pGraphics->LoadIBitmap(KNOB_120_RID, KNOB_120_FN, kKnobFrames);

	pGraphics->AttachControl(new IKnobMultiControl(this, kVolumeKnobX, kVolumeKnobY, kVolumePid, &knob120));

	IRECT tmpRect(kVolumeLabelX, kVolumeLabelY, kVolumeLabelX + kVolumeLabelWidth, kVolumeLabelY + kVolumeLabelHeight);
	mpVolumeLabel = new ParamValueLabel(this, kVolumePid, tmpRect);
	pGraphics->AttachControl(mpVolumeLabel);

	AttachGraphics(pGraphics);

	CreatePresets();
}

OZDSP_CleanCut::~OZDSP_CleanCut() {}

void OZDSP_CleanCut::CreatePresets()
{
	// No presets
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
	case kVolumePid:
		ZeroVolumeParam(GetParam(kVolumePid));
		if (IsParamMinimized(GetParam(kVolumePid)))
		{
			mVolumeControl.SetZero();
		}
		else
		{
			mVolumeControl.SetDecibels(GetParam(kVolumePid)->Value());
		}
		mpVolumeLabel->UpdateDisplay();
		break;
	default:
		break;
	}
}
