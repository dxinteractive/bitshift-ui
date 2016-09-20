/*
 * ui
 * Controller class for managing a stack of UI states, handling input, and updating audio objects and display in response to input
 * Copyright (c) 2016 Damien Clarke
 * damienclarke.me | github.com/dxinteractive/bitshift
 *
 * .-.    _  .-.      .-.    _  .--. .-. 
 * : :   :_;.' `.     : :   :_;: .-'.' `.
 * : `-. .-.`. .'.--. : `-. .-.: `; `. .'
 * ' .; :: : : :`._-.': .. :: :: :   : : 
 * `.__.':_; :_;`.__.':_;:_;:_;:_;   :_; 
 */

#include "ui.h"

#include <Arduino.h>
#include <stack>
#include "uistates/uistate_preset.h"

namespace std {
  void __throw_bad_alloc()
  {
    Serial.println("Unable to allocate memory");
  }

  void __throw_length_error( char const*e )
  {
    Serial.print("Length Error :");
    Serial.println(e);
  }
}

BitshiftUI::BitshiftUI()
{
	stateStack.push(new BitshiftUIStatePreset());
}

BitshiftUI::~BitshiftUI()
{
	BitshiftUIState* topState;
	while(!stateStack.empty())
	{
		topState = stateStack.top();
        stateStack.pop();
        delete topState;
    }
}

void BitshiftUI::pushState(BitshiftUIState* newState)
{
	if(stateStack.empty())
	{
		//newState->setup(this, pControl);
		stateStack.push(newState);
		return;
	}
	
	BitshiftUIState* topState = stateStack.top();
	if(newState != topState)
	{
		//newState->setup(this, pControl, topState);
		stateStack.push(newState);
	}
}

void BitshiftUI::popState()
{
    if(stateStack.size() == 1) return;
    
    BitshiftUIState* topState = stateStack.top();
    stateStack.pop();
	delete topState;
}

void BitshiftUI::update()
{
	BitshiftUIState* topState = stateStack.top();
	if(topState != NULL)
	{
		topState->update();
	}
}
