#ifndef APP_H
#define APP_H

#include <irrlicht.h> //FWD declared.
#include <iostream>

#include "eventReceiver.h" //FWD
#include "pCMD.h" 
//#include "chatBox.h" //FWD
#include "../irrKlang-64bit-1.5.0/include/irrKlang.h"


class App
{
public:
  
  App()
  {
    //driver=NULL;
    //smgr=NULL;
    //guienv=NULL;
    //eReceiver=NULL;

  }

  // Initializes and sets main pointers.
  App(int argc, char *argv[]) 
  {
		      //MyEventReceiver eReceiverObj;	
		//eReceiver=&eReceiverObj;
		
  	      eReceiver = new MyEventReceiver(); 
		
		//eReceiver.init();

		//TODO: Place handler code in seperate function (necassary?)
  	      device = irr::createDeviceEx(processCMDArgs(argc,argv));
		soundEngine = irrklang::createIrrKlangDevice();
		soundEngine->play2D("../../irrKlang-64bit-1.5.0/media/getout.ogg",1,0);
		soundEngine->play2D("../../irrKlang-64bit-1.5.0/media/explosion.wav",1,0);

		if (!device)
		{
		//	exit 1;
		}

  	      device->setEventReceiver(eReceiver);
		device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");

		driver = device->getVideoDriver();
		smgr = device->getSceneManager();
		guienv = device->getGUIEnvironment();


		guienv->addStaticText(L" \"T\" to type. ESC to close.",
		irr::core::rect<irr::s32>(10,10,260,22), true);

  }

  ~App()
  {

    delete eReceiver;
    guienv->drop();
    device->drop();
    //smgr->drop();
  }


  void runLoop()
  {
	  std::cout << "kik\n";

		irr::u32 then = device->getTimer()->getTime();

    while(device->run())
		{
			if (device->isWindowActive())
			{
				irr::u32 now = device->getTimer()->getTime();
				deltaTime = now - then;
				then = now;
				lag += deltaTime;
					
				// locks game logic to LOGIC_MS_PER_UPDATE.
				while ( lag >= LOGIC_MS_PER_UPDATE )
				{
				  	std::cout << lag << " ";
      	   	lag -= LOGIC_MS_PER_UPDATE;
				}

				std::cout << "\n";
      	                  

				if (RENDER_MS_PER_UPDATE - deltaTime >=0)
				{
				//device->sleep(RENDER_MS_PER_UPDATE);
				device->sleep(RENDER_MS_PER_UPDATE - deltaTime);
				}

	
//				eReceiver.startEventProcess();

				//driver->beginScene(true, true, irr::video::SColor(255,100,101,140));
				driver->beginScene(irr::video::ECBF_COLOR | irr::video::ECBF_DEPTH, irr::video::SColor(255,120,102,136));

				smgr->drawAll();
				guienv->drawAll();
				driver->endScene();
				
				// Run chatbox.


				if (eReceiver->IsKeyDown(irr::KEY_ESCAPE))
				{
					//device->closeDevice();
					device->drop();
				}
				
	//			bool pressed = 0;

//				std::cout << eReceiver.getMousePosition().X << "," << eReceiver.getMousePosition().Y << " " ;

				//if (eReceiver->getScrollWheel() == 1) std::cout << "S_UP ";
				//if (eReceiver->getScrollWheel() == -1) std::cout << "S_DOWN ";
				//
				//	std::cout << eReceiver.getScrollWheel() << " " ;
	
				//if (eReceiver->IsMousePressed(MMB)) std::cout << "PRESSED ";
				//if (eReceiver->IsMouseReleased(MMB)) std::cout << "RELEASED ";
				//if (eReceiver->IsMouseDown(MMB)) std::cout << "DOWN ";

				//if (eReceiver->IsMousePressed(LMB)) std::cout << "PRESSED ";
				//if (eReceiver->IsMouseReleased(LMB)) std::cout << "RELEASED ";
				//if (eReceiver->IsMouseDown(LMB)) std::cout << "DOWN ";

				//if (eReceiver->IsMousePressed(RMB)) std::cout << "PRESSED ";
				//if (eReceiver->IsMouseReleased(RMB)) std::cout << "RELEASED ";
				//if (eReceiver->IsMouseDown(RMB)) std::cout << "DOWN ";

				//
				//
				//if (eReceiver->IsKeyPressed(irr::KEY_LBUTTON)) std::cout << "PRESSED ";
				//if (eReceiver->IsKeyReleased(irr::KEY_LBUTTON)) std::cout << "RELEASED ";
				//if (eReceiver->IsKeyDown(irr::KEY_LBUTTON)) std::cout << "DOWN ";

				//if (eReceiver->IsKeyPressed(irr::KEY_RBUTTON)) std::cout << "PRESSED ";
				//if (eReceiver->IsKeyReleased(irr::KEY_RBUTTON)) std::cout << "RELEASED ";
				//if (eReceiver->IsKeyDown(irr::KEY_RBUTTON)) std::cout << "DOWN ";

				//if (eReceiver->IsKeyPressed(irr::KEY_MBUTTON)) std::cout << "PRESSED ";
				//if (eReceiver->IsKeyReleased(irr::KEY_MBUTTON)) std::cout << "RELEASED ";
				//if (eReceiver->IsKeyDown(irr::KEY_MBUTTON)) std::cout << "DOWN ";

				//if (eReceiver->IsKeyPressed(irr::KEY_KEY_L)) std::cout << "PRESSED ";
				//if (eReceiver->IsKeyReleased(irr::KEY_KEY_L)) std::cout << "RELEASED ";
				//if (eReceiver->IsKeyDown(irr::KEY_KEY_L)) std::cout << "DOWN ";
				////if (eReceiver->getMousePtr()->MButton == RELEASED) std::cout << "Mmouse released";
				////if (eReceiver->getMousePtr()->MButton == DOWN) {pressed =  1;}
				////if (pressed) std::cout << "Mmouse pressed"; pressed =false;
				////std::cout << eReceiver.getMousePtr()->wheel << " ";
				//
//				//eReceiver->endEventProcess();
				eReceiver->run();
			}
		}
	}
  
private: 
	
	irr::IrrlichtDevice* device = NULL;
	irrklang::ISoundEngine* soundEngine = NULL;
	irr::video::IVideoDriver* driver = NULL;
	irr::scene::ISceneManager* smgr = NULL;
	irr::gui::IGUIEnvironment* guienv = NULL;
	
	MyEventReceiver* eReceiver = NULL;

	double deltaTime = 0.0;
	int LOGIC_MS_PER_UPDATE = 1000/10; // 10FPS WRITE GETTER/SETTER FOR THESE.
	int RENDER_MS_PER_UPDATE = 1000/1; // 1FPS
	double lag = 0.0;
	
};

#endif /* APP_H */
