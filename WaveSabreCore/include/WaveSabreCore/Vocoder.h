#ifndef __WAVESABRECORE_Vocoder_H__
#define __WAVESABRECORE_Vocoder_H__

#include "Device.h"
#include "BiquadFilter.h"
//#include "kissfft.hh"

// "Dammit, Jim! I code C#, not C++!"

namespace WaveSabreCore
{
	class Vocoder : public Device
	{
	public:
		enum class ParamIndices
		{
			Master,
			Affect,
			Q1,
			Q2,
			Exponent,
			Power,
			Gain1,
			Gain2,
			Freq2,
			Divide,

			NumParams,
		};

		Vocoder();

		virtual void Run(double songPosition, float **inputs, float **outputs, int numSamples);

		virtual void SetParam(int index, float value);
		virtual float GetParam(int index) const;

	private:
		float master;
		float affect;
		float q1;
		float q2;
		float exponent;
		float power;
		float gain1;
		float gain2;
		float freq2;
		float divide;
		BiquadFilter vocoderfilters[3][16];
	};
}

#endif
