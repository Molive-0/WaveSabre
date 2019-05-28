#include <WaveSabreCore/Vocoder.h>
#include <WaveSabreCore/Helpers.h>
#include <WaveSabreCore/kissfft.hh>

#include <math.h>

// "Just to let you know, I don't know how to use a c++!"

namespace WaveSabreCore
{
	Vocoder::Vocoder()
		: Device((int)ParamIndices::NumParams),
		fft (nfft,false)
	{
		typedef std::complex<float> cpx;

		sidechain = false;

		std::vector<float> inbuf(nfft);
		std::vector<cpx> outbuf(nfft);

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				vocoderfilters[i][j].SetType(BiquadFilterType::Peak);
				vocoderfilters[i][j].SetQ(0.2f);
				vocoderfilters[i][j].SetFreq((float)(pow(2.4,j)));
				inbuf[j] = 0.0f;
			}
		}

		nfft = 12;
		kissfft<float> fft(nfft,false);

		master = 1.0f;
	}

	void Vocoder::Run(double songPosition, float **inputs, float **outputs, int numSamples)
	{	
			for (int j = 0; j < numSamples; j++)
			{			
				for (int shuf = 0; shuf<nfft-1; shuf++)
				{
					inbuf[shuf] = inbuf[shuf+1];
				}
				inbuf[nfft-1] = inputs[0][j];

				fft.transform_real( &inbuf[0] , &outbuf[0] );

				for (int i = 0; i<nfft; i++) {
					vocoderfilters[0][i].SetGain(1.0-outbuf[i].imag());					
				}

				float sample = inputs[1][j];

				for (int i = 0; i<nfft; i++) {
					sample = vocoderfilters[0][i].Next(sample);				
				}

				outputs[0][j] = sample * master;
				outputs[1][j] = sample * master;
			}
	}

	void Vocoder::SetParam(int index, float value)
	{
		switch ((ParamIndices)index)
		{
		case ParamIndices::Sidechain: sidechain = Helpers::ParamToBoolean(value); break;
		case ParamIndices::Master: master = value; break;
		}
	}

	float Vocoder::GetParam(int index) const
	{
		switch ((ParamIndices)index)
		{
		case ParamIndices::Sidechain:
		default:
			return Helpers::BooleanToParam(sidechain);

		case ParamIndices::Master: return master;
		}
	}
}
