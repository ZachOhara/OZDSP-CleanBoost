#ifndef __OZDSP_CLEANBOOST__
#define __OZDSP_CLEANBOOST__

#include "IPlug_include_in_plug_hdr.h"

#include <iostream>

#include "CommonParameters.h"
#include "ParamValueLabel.h"
#include "VolumeControl.h"

class OZDSP_CleanBoost : public IPlug
{
public:
	OZDSP_CleanBoost(IPlugInstanceInfo instanceInfo);
	~OZDSP_CleanBoost();

	void Reset() override;
	void OnParamChange(int paramIdx) override;
	void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames) override;

private:
	VolumeControl mVolumeControl;

	ParamValueLabel* mpBoostLabel;

	void CreatePresets();
};

#endif
