#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include <lvtk-1/lvtk/plugin.hpp>

#include "envgen.hpp"
#include "beatrepeater_mono.hpp"

using namespace lvtk;

BeatRepeaterMono::BeatRepeaterMono(double rate)
: Plugin<BeatRepeaterMono>(p_n_ports)
  {
	m_rate = rate;

	// 60 / tempo * rate * beatSize
	m_sampleFullSize = int(60 / 120 * m_rate * 1 + 0.5);

	m_gate = false;
	m_repeating = false;
	m_tempo = 120;
	m_beatSize = -1;

	m_repeatingPosition = 0;
	m_sampleFull = false;

	m_attack = -1;
	m_release = -1;
  }

void BeatRepeaterMono::run(uint32_t nframes)
{
	/*
	 * gate
	 * tempo
	 * beatSize
	 * attack
	 * release
	 * reverse
	 */

	int tempo = int(*p(p_tempo) + 0.5);
	if(tempo < 40)
	{
		tempo = 40;
	}

	float beatSize = *p(p_beatSize);
	if(beatSize < 0.03125)
	{
		beatSize = 0.03125;
	}

	int attack = int(*p(p_attack));
	if(attack < 3)
	{
		attack = 3;
	}

	int release = int(*p(p_release));
	if(release < 3)
	{
		release  = 3;
	}

	attack = m_rate / 1000 * attack;
	release = m_rate / 1000 * release;

	/*
	if(beatSize != m_beatSize || tempo != m_tempo)
	{
		m_sampleFullSize = int(60 * m_rate * beatSize / tempo + 0.5);
	}
	*/

	if(release + attack > m_sampleFullSize)
	{
		release = int(m_sampleFullSize / 2);
		attack = release;
	}

	if(!m_gate && (tempo != m_tempo || beatSize != m_beatSize || attack != m_attack || release != m_release))
	{
		m_tempo = tempo;
		m_beatSize = beatSize;

		m_attack = attack;
		m_release = release;

		m_envelope = gen_full_envelope(m_sampleFullSize, m_attack, m_release);
		m_envelopeRec = gen_long_release(m_sampleFullSize, m_release);
		m_attackEnv = gen_attack(m_attack);

		m_sampleFullSize = int(60 * m_rate * beatSize / tempo + 0.5);
	}

	for (unsigned int n = 0; n < nframes; n++)
	{
		if (!m_gate && (p(p_gate)[n] > 0.5))
		{
			m_gate = true;
			m_repeating = true;
			m_sample = new float[m_sampleFullSize];
			m_repeatingPosition = 0;
			m_sampleFull = false;
		}
		else if(m_gate && (p(p_gate)[n] < 0.5))
		{
			m_fadePosition = 0;
			m_gate = false;
			m_releaseEnv = gen_release(m_envelope[m_repeatingPosition], m_attack);
		}

		if(m_gate)
		{
			if(m_sampleFull)
			{
				if(*p(p_reverse) < 0.5)
				{
					p(p_output)[n] = m_sample[m_repeatingPosition] * m_envelope[m_repeatingPosition];
				}
				else
				{
					p(p_output)[n] = m_sample[m_sampleFullSize - 1 - m_repeatingPosition] * m_envelope[m_repeatingPosition];
				}

				m_repeatingPosition++;
				if(m_repeatingPosition >= m_sampleFullSize)
				{
					m_repeatingPosition = 0;
				}
			}
			else
			{
				m_sample[m_repeatingPosition] = p(p_input)[n];
				p(p_output)[n] = p(p_input)[n] * m_envelopeRec[m_repeatingPosition];
				m_repeatingPosition++;
				if(m_repeatingPosition >= m_sampleFullSize)
				{
					m_sampleFull = true;
					m_repeatingPosition = 0;
				}
			}
		}
		else
		{
			if(!m_repeating)
			{
				p(p_output)[n] = p(p_input)[n];
			}
			else
			{
				p(p_output)[n] = p(p_input)[n] * m_attackEnv[m_fadePosition] + m_sample[m_repeatingPosition] * m_releaseEnv[m_fadePosition];

				m_repeatingPosition++;
				if(m_repeatingPosition >= m_sampleFullSize)
				{
					m_repeatingPosition = 0;
				}

				m_fadePosition++;
				if(m_fadePosition >= m_attack)
				{
					m_repeating = false;
				}
			}
		}
	}
}


static int _ = BeatRepeaterMono::register_class("http://avwlv2.sourceforge.net/plugins/avw/beatrepeater_mono");

