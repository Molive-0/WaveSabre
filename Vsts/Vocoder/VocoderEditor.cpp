#include "VocoderEditor.h"

#include <WaveSabreCore.h>
using namespace WaveSabreCore;

VocoderEditor::VocoderEditor(AudioEffect *audioEffect)
	: VstEditor(audioEffect, 340, 270, "VOCODER")
{
}

VocoderEditor::~VocoderEditor()
{
}

void VocoderEditor::Open()
{
	addKnob((VstInt32)Vocoder::ParamIndices::Q1, "Q1");
	addKnob((VstInt32)Vocoder::ParamIndices::Exponent, "EXPONENT");
	addKnob((VstInt32)Vocoder::ParamIndices::Power, "POWER");
	addKnob((VstInt32)Vocoder::ParamIndices::Gain1, "GAIN1");

	startNextRow();

	addKnob((VstInt32)Vocoder::ParamIndices::Q2, "Q2");
	addKnob((VstInt32)Vocoder::ParamIndices::Freq2, "FREQUENCY");
	addKnob((VstInt32)Vocoder::ParamIndices::Gain2, "GAIN2");

	startNextRow();
	
	addKnob((VstInt32)Vocoder::ParamIndices::Divide, "DIVIDE");
	addKnob((VstInt32)Vocoder::ParamIndices::Affect, "AFFECT");

	startNextRow();
	
	addKnob((VstInt32)Vocoder::ParamIndices::Master, "MASTER");

	VstEditor::Open();
}
