/*
 * effect_lfo
 * General purpose low frequency oscillator
 * Copyright (c) 201y Damien Clarke
 * damienclarke.me | github.com/dxinteractive/bitshift
 *
 * █▄   ▀ ▄█▄    █▄   ▀ ▄▀ ▄█▄
 * █▄▀ ▀█  ▀▄ ▄▀ █ █ ▀█ █▀  ▀▄
 *
 */

#ifndef BITSHIFT_EFFECT_LFO_H
#define BITSHIFT_EFFECT_LFO_H

#include "effect.h"
#include <Audio.h>
#include "visualizationdata.h"

// damn arduino's "helpful" default macros...
// might have to deal with this differently as this could be potentially annoying
// if people or other libraries need this macro though
#undef min
#undef max

class BitshiftEffectLfo: public BitshiftEffect
{
  public:
    static const int OPTIONS_SHAPE_TOTAL = 5;
    static char const* OPTIONS_SHAPE[OPTIONS_SHAPE_TOTAL];

    BitshiftEffectLfo();
    ~BitshiftEffectLfo() {}

    virtual void setup();

    virtual AudioStream* audioOut() { return &signalMixer; }

    float speed(float hz);
    float phase(float angle);
    int shape(int shape);
    float mod(float mod);
    float shapeAndMod(float value);
    //int division(int division);
    float min(float min);
    float max(float max);

    //BitshiftVisualizationData const* waveformVisualization() { return &waveformVis; }

  private:
    void updateWaveform();
    void updateMinMax();

    AudioSynthWaveform lfo;
    AudioSynthWaveformDc offset;
    AudioMixer4 signalMixer;

    AudioConnection patchLfoToSignalMixer;
    AudioConnection patchOffsetToSignalMixer;

    float _hz = 1.0;
    float _angle = 0.0;
    int _shape = 0;
    float _mod = 0.5;
    float _shapeAndMod = 0.0;
    //int _division;
    float _min = -1.0;
    float _max = 1.0;

    int16_t wavetable[256];
    //int waveformVisData[256];
    //BitshiftVisualizationData waveformVis;
};

#endif
