#ifndef __OZDSP_CLEANCUT__
#define __OZDSP_CLEANCUT__

#include "IPlug_include_in_plug_hdr.h"

#include "../OZDSP_Common/CommonPlugBase.h"
#include "../OZDSP_Common/parameter/ParameterInfo.h"
#include "../OZDSP_Common/processing/VolumeProcessor.h"

class OZDSP_CleanCut : public CommonPlugBase
{
public:
	OZDSP_CleanCut(IPlugInstanceInfo instanceInfo);
	~OZDSP_CleanCut();

	void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames) override;

private:
	VolumeProcessor mVolumeProcessor;
};

#endif
