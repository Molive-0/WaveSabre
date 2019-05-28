#include "VocoderVst.h"
#include "VocoderEditor.h"

#include <WaveSabreCore.h>
using namespace WaveSabreCore;

AudioEffect *createEffectInstance(audioMasterCallback audioMaster)
{
	Helpers::Init();
	return new VocoderVst(audioMaster);
}

VocoderVst::VocoderVst(audioMasterCallback audioMaster)
	: VstPlug(audioMaster, (int)Vocoder::ParamIndices::NumParams, 2, 2, 'Vcdr', new Vocoder())
{
	setEditor(new VocoderEditor(this));
}

void VocoderVst::getParameterName(VstInt32 index, char *text)
{
	switch ((Vocoder::ParamIndices)index)
	{
	case Vocoder::ParamIndices::Sidechain: vst_strncpy(text, "Sidechain???", kVstMaxParamStrLen); break;
	case Vocoder::ParamIndices::Master: vst_strncpy(text, "Master", kVstMaxParamStrLen); break;
	}
}

bool VocoderVst::getEffectName(char *name)
{
	vst_strncpy(name, "WaveSabre - Vocoder", kVstMaxEffectNameLen);
	return true;
}

bool VocoderVst::getProductString(char *text)
{
	vst_strncpy(text, "WaveSabre - Vocoder", kVstMaxProductStrLen);
	return true;
}
