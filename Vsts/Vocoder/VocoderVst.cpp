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
	: VstPlug(audioMaster, (int)Vocoder::ParamIndices::NumParams, 2, 2, 'Lvlr', new Vocoder())
{
	setEditor(new VocoderEditor(this));
}

void VocoderVst::getParameterName(VstInt32 index, char *text)
{
	switch ((Vocoder::ParamIndices)index)
	{
	case Vocoder::ParamIndices::LowCutFreq: vst_strncpy(text, "LC Freq", kVstMaxParamStrLen); break;
	case Vocoder::ParamIndices::LowCutQ: vst_strncpy(text, "LC Q", kVstMaxParamStrLen); break;

	case Vocoder::ParamIndices::Peak1Freq: vst_strncpy(text, "Pk1 Freq", kVstMaxParamStrLen); break;
	case Vocoder::ParamIndices::Peak1Gain: vst_strncpy(text, "Pk1 Gain", kVstMaxParamStrLen); break;
	case Vocoder::ParamIndices::Peak1Q: vst_strncpy(text, "Pk1 Q", kVstMaxParamStrLen); break;

	case Vocoder::ParamIndices::Peak2Freq: vst_strncpy(text, "Pk2 Freq", kVstMaxParamStrLen); break;
	case Vocoder::ParamIndices::Peak2Gain: vst_strncpy(text, "Pk2 Gain", kVstMaxParamStrLen); break;
	case Vocoder::ParamIndices::Peak2Q: vst_strncpy(text, "Pk2 Q", kVstMaxParamStrLen); break;

	case Vocoder::ParamIndices::Peak3Freq: vst_strncpy(text, "Pk3 Freq", kVstMaxParamStrLen); break;
	case Vocoder::ParamIndices::Peak3Gain: vst_strncpy(text, "Pk3 Gain", kVstMaxParamStrLen); break;
	case Vocoder::ParamIndices::Peak3Q: vst_strncpy(text, "Pk3 Q", kVstMaxParamStrLen); break;

	case Vocoder::ParamIndices::HighCutFreq: vst_strncpy(text, "HC Freq", kVstMaxParamStrLen); break;
	case Vocoder::ParamIndices::HighCutQ: vst_strncpy(text, "HC Q", kVstMaxParamStrLen); break;

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
