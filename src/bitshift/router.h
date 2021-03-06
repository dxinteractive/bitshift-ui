/*
 * router
 * Creates a network of virtual patch cables to route audio between inputs, outputs and presets
 * Copyright (c) 2017 Damien Clarke
 * damienclarke.me | github.com/dxinteractive/bitshift
 *
 * █▄   ▀ ▄█▄    █▄   ▀ ▄▀ ▄█▄
 * █▄▀ ▀█  ▀▄ ▄▀ █ █ ▀█ █▀  ▀▄
 *
 */

#ifndef BITSHIFT_ROUTER_H
#define BITSHIFT_ROUTER_H

#include <Audio.h>
#include "preset.h"

class BitshiftRouter
{
  public:
    BitshiftRouter(
      AudioStream& audioIn,
      int audioInChannel,
      BitshiftPreset** presets,
      int presetsTotal,
      AudioStream& audioOut,
      int audioOutChannel
    );
    ~BitshiftRouter();

    void setActivePreset(int presetId);

  private:
    BitshiftPreset** presets;
    int presetsTotal;
    int activePresetId = -1;

    AudioMixer4 mixer;

    AudioConnection patchMixerToOutput;
    AudioConnection** patchInputToPresets;
    AudioConnection** patchPresetsToMixer;
};

#endif
