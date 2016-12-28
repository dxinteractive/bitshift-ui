/*
 * preset_tremolo
 * Tremolo effect (modulations in volume)
 * Copyright (c) 2016 Damien Clarke
 * damienclarke.me | github.com/dxinteractive/bitshift
 *
 * .-.    _  .-.      .-.    _  .--. .-.
 * : :   :_;.' `.     : :   :_;: .-'.' `.
 * : `-. .-.`. .'.--. : `-. .-.: `; `. .'
 * ' .; :: : : :`._-.': .. :: :: :   : :
 * `.__.':_; :_;`.__.':_;:_;:_;:_;   :_;
 */

#include "preset_tremolo.h"
#include <Arduino.h>
#include "paramset.h"

static const int SPEED = 0;
static const int DEPTH = 1;
static const int SHAPE = 2;
static const int DIVISION = 3;
static const int BIAS = 4;
static const int VOLUME = 5;

char const* BitshiftPresetTremolo::NAME = "Tremolo";
char const* BitshiftPresetTremolo::PARAM_NAMES[] = {
  "Speed",
  "Depth",
  "Shape",
  "Division",
  "Bias",
  "Volume"
};

BitshiftPresetTremolo::BitshiftPresetTremolo():
  BitshiftPreset()
{
  params.speed = 1.0;
  params.depth = 0.5;
  params.shape = 3;
  params.division = 0;
  params.bias = 0.2;
  params.volume = 0.8;

  thisName = NAME;
  thisParamsTotal = PARAMS_TOTAL;
  thisParamNames = PARAM_NAMES;

  const int ANALOG_MAP_SIZE = 6;
  int analogMap[ANALOG_MAP_SIZE] = {0,1,2,3,4,5};
  setAnalogMap(analogMap, ANALOG_MAP_SIZE);

  const int MENU_ITEM_MAP_SIZE = 1;
  int menuItemMap[MENU_ITEM_MAP_SIZE] = {3};
  setMenuItemMap(menuItemMap, MENU_ITEM_MAP_SIZE);
}

void BitshiftPresetTremolo::paramValueString(char* str, int paramId) const
{
  switch(paramId)
  {
    case SPEED:
      sprintf(str, "%0.1fHz", params.speed);
      break;
    case DEPTH:
      sprintf(str, "%0.0f%%", params.depth * 100.0);
      break;
    case SHAPE:
      sprintf(str, "...");
      break;
    case DIVISION:
      sprintf(str, "...");
      break;
    case BIAS:
      sprintf(str, "...");
      break;
    case VOLUME:
      sprintf(str, "%0.0f%%", params.volume * 100.0);
      break;
    default:
      return;
  }
}

void BitshiftPresetTremolo::setAnalogParam(int analogId, float value)
{
  int paramId = paramIdByAnalogId(analogId);
  switch(paramId)
  {
    case SPEED:
      // exponential range from 0.125 (2^-3) - 64.0 (2^6)
      value = pow(2, value * 9.0 - 3.0);
      break;
    case DEPTH:
    case VOLUME:
      break;
    default:
      return;
  }
  setParam(paramId, value);
}

void BitshiftPresetTremolo::setMenuItemParam(int itemId, int value)
{
  int paramId = paramIdByMenuItemId(itemId);
  switch(paramId)
  {
    case SHAPE:
    case DIVISION:
      break;
    default:
      return;
  }
  setParam(paramId, value);
}

void BitshiftPresetTremolo::setParam(int paramId, float value)
{
  switch(paramId)
  {
    case SPEED:
      params.speed = BitshiftPresetTremolo::tremolo.speed(value);
      return;
    case DEPTH:
      params.depth = BitshiftPresetTremolo::tremolo.depth(value);
      return;
    case VOLUME:
      params.volume = BitshiftPresetTremolo::tremolo.volume(value);
      return;
  }
}

void BitshiftPresetTremolo::setParam(int paramId, int value)
{
  switch(paramId)
  {
    case SHAPE:
      params.shape = BitshiftPresetTremolo::tremolo.shape(value);
      return;
    case DIVISION:
      params.division = BitshiftPresetTremolo::tremolo.division(value);
      return;
  }
}