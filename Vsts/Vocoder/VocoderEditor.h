#ifndef __VocoderEDITOR_H__
#define __VocoderEDITOR_H__

#include <WaveSabreVstLib.h>
using namespace WaveSabreVstLib;

class VocoderEditor : public VstEditor
{
public:
	VocoderEditor(AudioEffect *audioEffect);
	virtual ~VocoderEditor();

	virtual void Open();
};

#endif
