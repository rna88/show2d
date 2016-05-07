#ifndef EVENTRECEIVER_H
#define EVENTRECEIVER_H

#include "irrlicht.h"
#include <vector>
#include <iostream>

enum mouseKeysENUM {LMB, MMB, RMB}; 
const int MOUSE_CODES_COUNT=3;


class MyEventReceiver : public irr::IEventReceiver
{
public:

    MyEventReceiver()
    {
        for (irr::u32 i=0; i<irr::KEY_KEY_CODES_COUNT; ++i) 
	{
		KeyIsDown[i] = false;
		KeyWasDown[i] = false;
		KeyIsPressed[i] = false;
		KeyIsReleased[i] = false;
	}

        for (irr::u32 i=0; i<MOUSE_CODES_COUNT; ++i) 
	{
		MouseIsDown[i] = false;
		MouseIsPressed[i] = false;
		MouseIsReleased[i] = false;
	}

        mouseWheel = 0;
        mousePosition = irr::core::position2di(0,0);
    }
 
 
    // This is the one method that we have to implement
    virtual bool OnEvent(const irr::SEvent& event)
    {   
        // Remember the mouse state
        if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
        {

            switch(event.MouseInput.Event)
            {
	    case irr::EMIE_MOUSE_MOVED:
	        mousePosition.X = event.MouseInput.X;
	        mousePosition.Y = event.MouseInput.Y;
                break;
	   
	    case irr::EMIE_MOUSE_WHEEL:
	        mouseWheel = event.MouseInput.Wheel; 
                break;

	    case irr::EMIE_LMOUSE_PRESSED_DOWN:
	        if (!MouseIsDown[LMB]) 
	        {
	            MouseIsPressed[LMB] = 1;
                }
                MouseIsDown[LMB] = 1;
	        MouseWasDown[LMB] = 1;
	        break;
 
	    case irr::EMIE_LMOUSE_LEFT_UP:
		MouseIsDown[LMB]=0;
		MouseIsReleased[LMB]=0;
		break;

	    case irr::EMIE_RMOUSE_PRESSED_DOWN:
                if (!MouseIsDown[RMB]) 
	        {
	            MouseIsPressed[RMB] = 1;
                }
                MouseIsDown[RMB] = 1;
	        MouseWasDown[RMB] = 1;
		break;
 
	    case irr::EMIE_RMOUSE_LEFT_UP:
		MouseIsDown[RMB]=0;
		MouseIsReleased[RMB]=0;
		break;

	    case irr::EMIE_MMOUSE_PRESSED_DOWN:
                if (!MouseIsDown[MMB]) 
	        {
	            MouseIsPressed[MMB] = 1;
                }
                MouseIsDown[MMB] = 1;
	        MouseWasDown[MMB] = 1;
		break;
	     
	    case irr::EMIE_MMOUSE_LEFT_UP:
		MouseIsDown[MMB]=0;
		MouseIsReleased[MMB]=0;
		break;
   
            default:
                break;
            }
        }
 
        // Remember whether each key is down or up
        // trigger pressed only once somehow
        if (event.EventType == irr::EET_KEY_INPUT_EVENT) 
	{
            if (!KeyIsDown[event.KeyInput.Key]) 
	    {
	      KeyIsPressed[event.KeyInput.Key] = 1;
            }
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	    KeyWasDown[event.KeyInput.Key] = 1;
        }
        return false;
    }
 
    // Check whether a key is being held down
    virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }
    // Receive initial key press.
    virtual bool IsKeyPressed(irr::EKEY_CODE keyCode) const
    {
        return KeyIsPressed[keyCode];
    }
 
    virtual bool IsKeyReleased(irr::EKEY_CODE keyCode) const
    {
        return KeyIsReleased[keyCode];
    }

    virtual bool IsMouseDown(int mouseCode) const
    {
        return MouseIsDown[mouseCode];
    }
 
    virtual bool IsMousePressed(int mouseCode) const
    {
        return MouseIsPressed[mouseCode];
    }
 
    virtual bool IsMouseReleased(int mouseCode) const
    {
        return MouseIsReleased[mouseCode];
    }

    virtual void run()
    {
        mouseWheel = 0.0f;
	for (irr::u32 i=0; i < MOUSE_CODES_COUNT; ++i)
	{
	  if (MouseIsDown[i] && MouseIsPressed[i])
	  {
	    MouseIsPressed[i]=0;
	  }

	  // check if key was pressed last frame.
	  if (!MouseIsDown[i] && MouseWasDown[i])
	  {
            MouseIsReleased[i]=1;
	    MouseWasDown[i]=0;
	  }
	  else
	  {
            MouseIsReleased[i]=0;
	  }
	}

	for (irr::u32 i=0; i < irr::KEY_KEY_CODES_COUNT; ++i)
	{
	  if (KeyIsDown[i] && KeyIsPressed[i])
	  {
	    KeyIsPressed[i]=0;
	  }

	  // check if key was pressed last frame.
	  if (!KeyIsDown[i] && KeyWasDown[i])
	  {
            KeyIsReleased[i]=1;
	    KeyWasDown[i]=0;
	  }
	  else
	  {
            KeyIsReleased[i]=0;
	  }
	}
    }
 
    irr::core::position2di getMousePosition() 
    {
      return mousePosition;
    }
    
    irr::f32 getScrollWheel()
    {
      return mouseWheel;
    }
    
private:
    // We use this array to store the current state of each key
    bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
    bool KeyIsPressed[irr::KEY_KEY_CODES_COUNT];
    bool KeyIsReleased[irr::KEY_KEY_CODES_COUNT];
    bool KeyWasDown[irr::KEY_KEY_CODES_COUNT];


    //irr::core::map<int,int> pressedKeysMap;
    //irr::core::map<int,int> releasedKeysMap;
    
    bool MouseIsDown[MOUSE_CODES_COUNT];
    bool MouseIsPressed[MOUSE_CODES_COUNT];
    bool MouseIsReleased[MOUSE_CODES_COUNT];
    bool MouseWasDown[MOUSE_CODES_COUNT];

    irr::core::position2di mousePosition;
    float mouseWheel;
};


#endif /* EVENTRECEIVER_H */
