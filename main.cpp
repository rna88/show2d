#include "App.hpp"

int main(int argc, char *argv[])
{
  App trun(argc,argv);
  trun.runLoop();
  return 0;
}




//#include <irrlicht.h>
//#include <iostream>
//#include <string>
//#include <sstream>
//
//#include "pSource/eventReceiver.h"
////#include "pSource/MEventReceiver.cpp"
//#include "textArea_v1/TextArea.h"
//#include "pSource/pCMD.h"
////#include "pSource/pCMD.cpp"
//#include "pSource/netHandler.h"
//#include "pSource/chatBox.h"
////#include <pSource/chatBox.h>
////#include "TextArea.h"
//#include "pSource/App.h"
//
//using namespace irr;
//using namespace core;
//using namespace scene;
//using namespace video;
//using namespace io;
//using namespace gui;
//
//#ifdef _MSC_VER
//#pragma comment(lib, "Irrlicht.lib")
//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
//#endif
//
//
////argv[0]=program name
//int main(int argc, char *argv[])
//{
//	MyEventReceiver eReceiver;	
//	//eReceiver.init();
//
//	//TODO: Place handler code in seperate function (necassary?)
//	IrrlichtDevice *device = irr::createDeviceEx(processCMDArgs(argc,argv));
//
//	if (!device)
//	{
//		return 1;
//	}
//
//        device->setEventReceiver(&eReceiver);
//	device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");
//
//	irr::video::IVideoDriver* driver = device->getVideoDriver();
//	irr::scene::ISceneManager* smgr = device->getSceneManager();
//	irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
//
//
//	guienv->addStaticText(L" \"T\" to type. ESC to close.",
//		rect<s32>(10,10,260,22), true);
//	
////	IAnimatedMesh* mesh = smgr->getMesh("../../media/sydney.md2");
////	if (!mesh)
////	{
////		device->drop();
////		return 1;
////	}
////	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );
////
////	if (node)
////	{
////		node->setMaterialFlag(EMF_LIGHTING, false);
////		node->setMD2Animation(scene::EMAT_STAND);
////	//	node->setMaterialTexture( 0, driver->getTexture("../../media/sydney.bmp") );
////	}
////
////	smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));
//
//        // Create chatbox.
//	ChatBox testChat(guienv,&eReceiver);
//	testChat.createChatBox();
//
//	while(device->run())
//	{
////		eReceiver.startEventProcess();
//
//		driver->beginScene(true, true, SColor(255,100,101,140));
//
//		smgr->drawAll();
//		guienv->drawAll();
//		driver->endScene();
//		
//		// Run chatbox.
//		testChat.run();
//
//		if (eReceiver.IsKeyDown(irr::KEY_ESCAPE))
//		{
//                  device->closeDevice();
//		}
//	//	bool pressed = 0;
//
////		std::cout << eReceiver.getMousePosition().X << "," << eReceiver.getMousePosition().Y << " " ;
//
//		//if (eReceiver.getScrollWheel() == 1) std::cout << "S_UP ";
//		//if (eReceiver.getScrollWheel() == -1) std::cout << "S_DOWN ";
//		//
//		//	std::cout << eReceiver.getScrollWheel() << " " ;
//	
//		//if (eReceiver.IsMousePressed(MMB)) std::cout << "PRESSED ";
//		//if (eReceiver.IsMouseReleased(MMB)) std::cout << "RELEASED ";
//		//if (eReceiver.IsMouseDown(MMB)) std::cout << "DOWN ";
//
//		//if (eReceiver.IsMousePressed(LMB)) std::cout << "PRESSED ";
//		//if (eReceiver.IsMouseReleased(LMB)) std::cout << "RELEASED ";
//		//if (eReceiver.IsMouseDown(LMB)) std::cout << "DOWN ";
//
//		//if (eReceiver.IsMousePressed(RMB)) std::cout << "PRESSED ";
//		//if (eReceiver.IsMouseReleased(RMB)) std::cout << "RELEASED ";
//		//if (eReceiver.IsMouseDown(RMB)) std::cout << "DOWN ";
//
//		//
//		//
//		//if (eReceiver.IsKeyPressed(irr::KEY_LBUTTON)) std::cout << "PRESSED ";
//		//if (eReceiver.IsKeyReleased(irr::KEY_LBUTTON)) std::cout << "RELEASED ";
//		//if (eReceiver.IsKeyDown(irr::KEY_LBUTTON)) std::cout << "DOWN ";
//
//		//if (eReceiver.IsKeyPressed(irr::KEY_RBUTTON)) std::cout << "PRESSED ";
//		//if (eReceiver.IsKeyReleased(irr::KEY_RBUTTON)) std::cout << "RELEASED ";
//		//if (eReceiver.IsKeyDown(irr::KEY_RBUTTON)) std::cout << "DOWN ";
//
//		//if (eReceiver.IsKeyPressed(irr::KEY_MBUTTON)) std::cout << "PRESSED ";
//		//if (eReceiver.IsKeyReleased(irr::KEY_MBUTTON)) std::cout << "RELEASED ";
//		//if (eReceiver.IsKeyDown(irr::KEY_MBUTTON)) std::cout << "DOWN ";
//
//		if (eReceiver.IsKeyPressed(irr::KEY_KEY_L)) std::cout << "PRESSED ";
//		if (eReceiver.IsKeyReleased(irr::KEY_KEY_L)) std::cout << "RELEASED ";
//		if (eReceiver.IsKeyDown(irr::KEY_KEY_L)) std::cout << "DOWN ";
//		//if (eReceiver.getMousePtr()->MButton == RELEASED) std::cout << "Mmouse released";
//		//if (eReceiver.getMousePtr()->MButton == DOWN) {pressed =  1;}
//		//if (pressed) std::cout << "Mmouse pressed"; pressed =false;
//		//std::cout << eReceiver.getMousePtr()->wheel << " ";
//		
////		eReceiver.endEventProcess();
//		eReceiver.run();
//	}
//
//	device->drop();
//
//	return 0;
//}
