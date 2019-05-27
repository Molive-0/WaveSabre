#ifndef __VocoderVST_H__
#define __VocoderVST_H__

#include <WaveSabreVstLib.h>
using namespace WaveSabreVstLib;

class VocoderVst : public VstPlug
{
public:
	VocoderVst(audioMasterCallback audioMaster);

	virtual void getParameterName(VstInt32 index, char *text);

	virtual bool getEffectName(char *name);
	virtual bool getProductString(char *text);
};

#endif