#ifndef __OZDSP_CLEANCUT__
#define __OZDSP_CLEANCUT__

#include "IPlug_include_in_plug_hdr.h"

#include <iostream>

#include "../OZDSP_Common/CommonParameters.h"
#include "../OZDSP_Common/ParamValueLabel.h"
#include "../OZDSP_Common/VolumeControl.h"

class OZDSP_CleanCut : public IPlug
{
public:
	OZDSP_CleanCut(IPlugInstanceInfo instanceInfo);
	~OZDSP_CleanCut();

	void Reset() override;
	void OnParamChange(int paramIdx) override;
	void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames) override;

private:
	VolumeControl mVolumeControl;

	ParamValueLabel* mpVolumeLabel;

	void CreatePresets();
};

#endif
