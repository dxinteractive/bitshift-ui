/*
 * uistate_usage
 * UI state for displaying CPU and processor usage for analysis / debugging
 * Copyright (c) 2017 Damien Clarke
 * damienclarke.me | github.com/dxinteractive/bitshift
 *
 * █▄   ▀ ▄█▄    █▄   ▀ ▄▀ ▄█▄
 * █▄▀ ▀█  ▀▄ ▄▀ █ █ ▀█ █▀  ▀▄
 *
 */

#include "uistate_usage.h"
#include "uistate.h"
#include "display.h"
#include "props.h"
#include "input_consts.h"
#include <Audio.h>

void BitshiftUIStateUsage::eventButton(int id, int value)
{
  if((id == BUTTON_UP || id == BUTTON_DOWN || id == BUTTON_BACK) && value == BUTTONEVENT_PRESS) {
    popState();
    return;
  }
}

void BitshiftUIStateUsage::eventAnalog(int id, float value)
{
  passDownEventAnalog(id, value);
}

void BitshiftUIStateUsage::update(unsigned long ms)
{
  this->ms = ms;
  render();
}

void BitshiftUIStateUsage::render()
{
  BitshiftPropsUsage props;
  props.processorUsage = AudioProcessorUsage();
  props.processorUsageMax = AudioProcessorUsageMax();
  props.memoryUsage = AudioMemoryUsage();
  props.memoryUsageMax = AudioMemoryUsageMax();
  props.ms = ms;
  display->render(props);
}
