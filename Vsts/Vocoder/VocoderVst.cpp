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
	case Vocoder::ParamIndices::Master: vst_strncpy(text, "Master", kVstMaxParamStrLen); break;
	case Vocoder::ParamIndices::Affect: vst_strncpy(text, "Affect", kVstMaxParamStrLen); break;
	case Vocoder::ParamIndices::Q1: vst_strncpy(text, "Q1", kVstMaxParamStrLen); break;
	case Vocoder::ParamIndices::Q2: vst_strncpy(text, "Q2", kVstMaxParamStrLen); break;
	case Vocoder::ParamIndices::Exponent: vst_strncpy(text, "Exponent", kVstMaxParamStrLen); break;
	case Vocoder::ParamIndices::Power: vst_strncpy(text, "Power", kVstMaxParamStrLen); break;
	case Vocoder::ParamIndices::Gain1: vst_strncpy(text, "Gain1", kVstMaxParamStrLen); break;
	case Vocoder::ParamIndices::Gain2: vst_strncpy(text, "Gain2", kVstMaxParamStrLen); break;
	case Vocoder::ParamIndices::Freq2: vst_strncpy(text, "Freq2", kVstMaxParamStrLen); break;
	case Vocoder::ParamIndices::Divide: vst_strncpy(text, "Divide", kVstMaxParamStrLen); break;
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
