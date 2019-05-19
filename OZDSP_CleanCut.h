#ifndef __OZDSP_CLEANCUT__
#define __OZDSP_CLEANCUT__

#include "IPlug_include_in_plug_hdr.h"

#include "../OZDSP_Core/CorePlugBase.h"
#include "../OZDSP_Core/parameter/ParameterInfo.h"
#include "../OZDSP_Core/audio/VolumeProcessor.h"

class OZDSP_CleanCut : public CorePlugBase
{
public:
	OZDSP_CleanCut(IPlugInstanceInfo instanceInfo);
	~OZDSP_CleanCut();

	void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames) override;

private:
	VolumeProcessor mVolumeProcessor;
};

#endif
