/*
 * preset_filter
 * Filter effect with low pass, band pass and high pass options
 * Copyright (c) 2017 Damien Clarke
 * damienclarke.me | github.com/dxinteractive/bitshift
 *
 * █▄   ▀ ▄█▄    █▄   ▀ ▄▀ ▄█▄
 * █▄▀ ▀█  ▀▄ ▄▀ █ █ ▀█ █▀  ▀▄
 *
 */

#include "preset_filter.h"
#include "paramset.h"
#include "effect_filter.h"
#include "utils.h"

static const int FREQUENCY = 0;
static const int RESONANCE = 1;
static const int TYPE = 2;
static const int VOLUME = 3;

char const* BitshiftPresetFilter::NAME = "Filter";
char const* BitshiftPresetFilter::PARAM_NAMES[] = {
  "Freq",
  "Res",
  "Type",
  "Volume"
};

BitshiftPresetFilter::BitshiftPresetFilter():
  BitshiftPreset()
{
  initBase(
    &filter,
    &params,
    NAME,
    PARAM_NAMES,
    PARAMS_TOTAL
  );

  const int ANALOG_MAP_SIZE = 4;
  int analogMap[ANALOG_MAP_SIZE] = {0,1,2,3};
  setAnalogMap(analogMap, ANALOG_MAP_SIZE);

  const int MENU_ITEM_MAP_SIZE = 1;
  int menuItemMap[MENU_ITEM_MAP_SIZE] = {2};
  char const** menuItemOptions[MENU_ITEM_MAP_SIZE] = {
    BitshiftEffectFilter::OPTIONS_TYPE
  };

  int menuItemOptionsTotals[MENU_ITEM_MAP_SIZE] = {
    BitshiftEffectFilter::OPTIONS_TYPE_TOTAL
  };

  setMenuItemMap(
    menuItemMap,
    MENU_ITEM_MAP_SIZE,
    menuItemOptions,
    menuItemOptionsTotals
  );
}

void BitshiftPresetFilter::initialParams()
{
  setParam(FREQUENCY, 1000.0);
  setParam(RESONANCE, 2.0);
  setParam(TYPE, 0);
  setParam(VOLUME, 1.0);
}

int BitshiftPresetFilter::paramValueInt(int paramId) const
{
  switch(paramId)
  {
    case TYPE:
      return params.type;
  }
  return -1;
}

void BitshiftPresetFilter::paramValueString(char* str, int paramId) const
{
  switch(paramId)
  {
    case FREQUENCY:
      floatToString(params.frequency, 1, "%sHz", str);
      return;

    case RESONANCE:
      floatToString(params.resonance, 1, "%sHz", str);
      return;

    case TYPE:
      sprintf(str, BitshiftEffectFilter::OPTIONS_TYPE[params.type]);
      return;

    case VOLUME:
      floatToString(params.volume * 100.0, 0, "%s%%", str);
      return;
  }
}

void BitshiftPresetFilter::setAnalogParam(int analogId, float value)
{
  int paramId = paramIdByAnalogId(analogId);
  switch(paramId)
  {
    case FREQUENCY:
    {
      // exponential range from 64.0 (2^6) to 16384.0 (2^14)
      value = pow(2, value * 8.0 + 6.0);
      setParam(paramId, value);
      return;
    }

    case RESONANCE:
    {
      // 0.8 - 5.0
      setParam(paramId, floatRange(value, 0.8, 5.0));
      return;
    }

    case TYPE:
    {
      setParam(paramId, intRange(value, 0, 2));
      return;
    }

    case VOLUME:
    {
      // default range from 0.0 to 0.1
      setParam(paramId, value);
      return;
    }
  }
}

void BitshiftPresetFilter::setMenuItemParam(int itemId, int value)
{
  int paramId = paramIdByMenuItemId(itemId);
  switch(paramId)
  {
    case TYPE:
      setParam(paramId, value);
      return;
  }
}

void BitshiftPresetFilter::setParam(int paramId, float value)
{
  switch(paramId)
  {
    case FREQUENCY:
      params.frequency = filter.frequency(value);
      return;

    case RESONANCE:
      params.resonance = filter.resonance(value);
      return;

    case VOLUME:
      params.volume = filter.volume(value);
      return;
  }
}

void BitshiftPresetFilter::setParam(int paramId, int value)
{
  switch(paramId)
  {
    case TYPE:
      params.type = filter.type(value);
      return;
  }
}
