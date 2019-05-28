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
	addKnob((VstInt32)Vocoder::ParamIndices::Sidechain, "SIDECHAIN");

	addKnob((VstInt32)Vocoder::ParamIndices::Master, "MASTER");

	VstEditor::Open();
}
