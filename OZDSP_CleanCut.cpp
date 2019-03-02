#include "OZDSP_CleanCut.h"
#include "IPlug_include_in_plug_src.h"
#include "resource.h"

const int kNumPrograms = 0;

enum EParams
{
	kVolumePid,
	kNumParams
};

std::vector<ParameterInfo> kParameterList =
{
	ParameterInfo()
		.InitParam("Volume", kVolumePid, KNOB_120_ID, 15, 40)
		.InitLabel()
		.MakeVolumeReductionParam(),
};

OZDSP_CleanCut::OZDSP_CleanCut(IPlugInstanceInfo instanceInfo) :
	CommonPlugBase(instanceInfo, kNumParams, kNumPrograms,
		MakeGraphics(this, GUI_WIDTH, GUI_HEIGHT),
		COMMONPLUG_CTOR_PARAMS)
{
	SetBackground(BACKGROUND_ID, BACKGROUND_FN);
	RegisterBitmap(KNOB_120_ID, KNOB_120_FN, KNOB_FRAMES);
	AddParameters(kParameterList);
	AddVolumeParamBridge(kVolumePid, &mVolumeProcessor);
	FinishConstruction();
}

OZDSP_CleanCut::~OZDSP_CleanCut()
{
}

void OZDSP_CleanCut::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
{
	// Mutex is already locked for us.
	const int nChannels = 2;

	for (int i = 0; i < nFrames; i++)
	{
		for (int j = 0; j < nChannels; j++)
		{
			outputs[j][i] = mVolumeProcessor.GetAdjustedSample(inputs[j][i]);
		}
	}
}
