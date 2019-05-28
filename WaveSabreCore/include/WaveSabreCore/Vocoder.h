#ifndef __WAVESABRECORE_Vocoder_H__
#define __WAVESABRECORE_Vocoder_H__

#include "Device.h"
#include "BiquadFilter.h"
#include "kissfft.hh"

// "Dammit, Jim! I code C#, not C++!"

namespace WaveSabreCore
{
	class Vocoder : public Device
	{
	public:
		enum class ParamIndices
		{
			Sidechain,

			Master,

			NumParams,
		};

		Vocoder();

		virtual void Run(double songPosition, float **inputs, float **outputs, int numSamples);

		virtual void SetParam(int index, float value);
		virtual float GetParam(int index) const;

	private:
		bool sidechain;
		float master;
		int nfft;
		typedef std::complex<float> cpx;
		std::vector<float> inbuf;
		std::vector<cpx> outbuf;
		kissfft<float> fft;
		BiquadFilter vocoderfilters[2][12];
	};
}

#endif
