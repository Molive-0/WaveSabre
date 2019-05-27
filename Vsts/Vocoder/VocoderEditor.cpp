#include "VocoderEditor.h"

#include <WaveSabreCore.h>
using namespace WaveSabreCore;

VocoderEditor::VocoderEditor(AudioEffect *audioEffect)
	: VstEditor(audioEffect, 210, 340, "VOCODER")
{
}

VocoderEditor::~VocoderEditor()
{
}

void VocoderEditor::Open()
{
	addKnob((VstInt32)Vocoder::ParamIndices::LowCutFreq, "LC FREQ");
	addKnob((VstInt32)Vocoder::ParamIndices::LowCutQ, "LC Q");

	startNextRow();

	addKnob((VstInt32)Vocoder::ParamIndices::Peak1Freq, "P1 FREQ");
	addKnob((VstInt32)Vocoder::ParamIndices::Peak1Gain, "P1 GAIN");
	addKnob((VstInt32)Vocoder::ParamIndices::Peak1Q, "P1 Q");

	startNextRow();

	addKnob((VstInt32)Vocoder::ParamIndices::Peak2Freq, "P2 FREQ");
	addKnob((VstInt32)Vocoder::ParamIndices::Peak2Gain, "P2 GAIN");
	addKnob((VstInt32)Vocoder::ParamIndices::Peak2Q, "P2 Q");

	startNextRow();

	addKnob((VstInt32)Vocoder::ParamIndices::Peak3Freq, "P3 FREQ");
	addKnob((VstInt32)Vocoder::ParamIndices::Peak3Gain, "P3 GAIN");
	addKnob((VstInt32)Vocoder::ParamIndices::Peak3Q, "P3 Q");

	startNextRow();

	addKnob((VstInt32)Vocoder::ParamIndices::HighCutFreq, "HC FREQ");
	addKnob((VstInt32)Vocoder::ParamIndices::HighCutQ, "HC Q");
	addKnob((VstInt32)Vocoder::ParamIndices::Master, "MASTER");

	VstEditor::Open();
}
