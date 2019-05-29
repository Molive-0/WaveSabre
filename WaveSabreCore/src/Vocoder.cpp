#include <WaveSabreCore/Vocoder.h>
#include <WaveSabreCore/Helpers.h>
//#include <WaveSabreCore/kissfft.hh>

#include <math.h>

// "Just to let you know, I don't know how to use a c++!"

namespace WaveSabreCore
{
	Vocoder::Vocoder()
		: Device((int)ParamIndices::NumParams)
	{
		master = 1.0f;
		affect = 1.0f;
		q1 = 0.3f;
		q2 = 0.2f;
		exponent = 1.7f;
		power = 2.0f;
		gain1 = 60.0f;
		gain2 = 10.0f;
		freq2 = 1000.0f;
		divide = 100.0f;

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				vocoderfilters[i][j].SetType(BiquadFilterType::Peak);
				vocoderfilters[i][j].SetQ(q1);
				vocoderfilters[i][j].SetFreq((float)(pow(exponent,j+power)));
				//vocoderfilters[i][j].SetFreq(j*1000.0f);
				vocoderfilters[i][j].SetGain(gain1);
			}
		}
		for (int j = 0; j < 16; j++)
		{
			vocoderfilters[2][j].SetType(BiquadFilterType::Lowpass);
			vocoderfilters[2][j].SetQ(q2);
			vocoderfilters[2][j].SetFreq(freq2);
			vocoderfilters[2][j].SetGain(gain2);
		}

		master = 1.0f;
		affect = 1.0f;

	}

	void Vocoder::Run(double songPosition, float **inputs, float **outputs, int numSamples)
	{	
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				vocoderfilters[i][j].SetQ(q1);
				vocoderfilters[i][j].SetFreq((float)(pow(exponent, j + power)));
				vocoderfilters[i][j].SetGain(gain1);
			}
		}
		for (int j = 0; j < 16; j++)
		{
			vocoderfilters[2][j].SetQ(q2);
			vocoderfilters[2][j].SetFreq(freq2);
			vocoderfilters[2][j].SetGain(gain2);
		}
			for (int j = 0; j < numSamples; j++)
			{			
				float modulationsample = inputs[1][j];
				float bandpasses[16];

				//Get bandpasses on the carrier sample
				for (int i = 0; i < 16; i++)
				{
					bandpasses[i] = vocoderfilters[0][i].Next(modulationsample)/60.0f;
				}

				float carriersample = inputs[0][j];
				float outputpasses[16];

				//Get bandpasses on the modular sample
				for (int i = 0; i< 16; i++) 
				{
					outputpasses[i] = vocoderfilters[1][i].Next(carriersample)/60.0f;
				}

				//Use the bandpasses to affect the gain of the modular sample
				for (int i = 0; i< 16; i++) 
				{
					float gain = Helpers::Clamp(vocoderfilters[2][i].Next(fabsf(bandpasses[i]))/divide, -1.0f, 1.0f);
					outputpasses[i] *= Helpers::Clamp(gain*affect, -1.0f, 1.0f);
				}

				//mix all passes down
				float outsample = 0;
				for (int i = 0; i < 16; i++)
				{
					outsample += outputpasses[i] / 16.0f;
				}

				outputs[0][j] = Helpers::Clamp(outsample * master,-1.0f,1.0f);
				outputs[1][j] = outputs[0][j];
			}
	}

	void Vocoder::SetParam(int index, float value)
	{
		switch ((ParamIndices)index)
		{
		case ParamIndices::Master: master = value; break;
		case ParamIndices::Affect: affect = value; break;
		case ParamIndices::Exponent: exponent = value*3.0f; break;
		case ParamIndices::Power: power = value*10.0f; break;
		case ParamIndices::Divide: divide = value*3000.0f; break;
		case ParamIndices::Q1: q1 = Helpers::ParamToQ(value); break;
		case ParamIndices::Q2: q2 = Helpers::ParamToQ(value); break;
		case ParamIndices::Freq2: freq2 = Helpers::ParamToFrequency(value); break;
		case ParamIndices::Gain1: gain1 = Helpers::ParamToDb(value*10.0f); break;
		case ParamIndices::Gain2: gain2 = Helpers::ParamToDb(value); break;
		}
	}

	float Vocoder::GetParam(int index) const
	{
		switch ((ParamIndices)index)
		{
		case ParamIndices::Master:
		default:
			return master;

		case ParamIndices::Affect: return affect;
		case ParamIndices::Exponent: return exponent/3.0f;
		case ParamIndices::Power: return power/10.0f;
		case ParamIndices::Divide: return divide/3000.0f;
		case ParamIndices::Q1: return Helpers::QToParam(q1);
		case ParamIndices::Q2: return Helpers::QToParam(q2);
		case ParamIndices::Freq2: return Helpers::FrequencyToParam(freq2);
		case ParamIndices::Gain1: return Helpers::DbToParam(gain1)/10.0f;
		case ParamIndices::Gain2: return Helpers::DbToParam(gain2);
		}
	}
}
