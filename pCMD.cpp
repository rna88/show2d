#include "pCMD.h"

#include <irrlicht.h>
#include <iostream>
#include <string>
#include <sstream>

/*FUNC: reads in arguments from commandline and applies them to the createdevice parameter structure.
  PARAM: count and value array of arguments.
  NOTE: commandline args should overwrite previously saved args.*/
irr::SIrrlichtCreationParameters processCMDArgs(int argCount, char* argValue[])
{
	// Creation defaults.
	irr::video::E_DRIVER_TYPE driverType=irr::video::EDT_OPENGL;
	int width=640,height=480;
	bool vsync=0;
	bool fullscreen=0;
	int bits=32;
	int antialias=0; //2,4,8,16,32
	
	for (int i = 1; i < argCount; i++)
	{
                irr::core::stringw inputID = argValue[i];
		if (inputID == "-driver" || inputID == "-d")
		{
			//Shift counter to determine value of parameter variable.
			std::string input = argValue[i+=1];	
                	if (input == "opengl") { driverType=irr::video::EDT_OPENGL; }
			else if (input == "software") { driverType=irr::video::EDT_SOFTWARE; }
			else if (input == "burnings") { driverType=irr::video::EDT_BURNINGSVIDEO; }
			else if (input == "directx") { driverType=irr::video::EDT_DIRECT3D9; }
			else if (input == "null") { driverType=irr::video::EDT_NULL; }
		} else if (inputID == "-width" || inputID == "-w") {
			std::string input = argValue[i+=1];
			std::stringstream wd_tostring(input); wd_tostring >> width;
		} else if (inputID == "-height" || inputID == "-h") {
			std::string input = argValue[i+=1];
			std::stringstream ht_tostring(input); ht_tostring >> height;
		} else if (inputID == "-vysnc" || inputID == "-v") {
			std::string input = argValue[i+=1];
			std::stringstream vsync_tostring(input); vsync_tostring >> vsync;
		} else if (inputID == "-fullscreen" || inputID == "-f") {
			std::string input = argValue[i+=1];
			std::stringstream fs_tostring(input); fs_tostring >> fullscreen;
		} else if (inputID == "-bits" || inputID == "-b") {
			std::string input = argValue[i+=1];
			std::stringstream bits_tostring(input); bits_tostring >> bits;
		} else if (inputID == "-antialias" || inputID == "-aa") {
			std::string input = argValue[i+=1];
			std::stringstream aa_tostring(input); aa_tostring >> antialias;
		}
	}

	irr::SIrrlichtCreationParameters params;
	params.DriverType=driverType;
	params.WindowSize=irr::core::dimension2d<irr::u32>(width,height);
	params.Vsync=vsync;
	params.Fullscreen=fullscreen;
	params.Bits=32;
        //params.Bits=u8(bits); // Make sure that the 32 bits actually work in the renderer.
	params.AntiAlias=antialias;
			std::cout << "driver=" << driverType << std::endl;
			std::cout << "width=" << width << std::endl;
			std::cout << "height=" << height << std::endl;
			std::cout << "vsync=" << vsync << std::endl;
			std::cout << "fullscreen=" << fullscreen << std::endl;
			std::cout << "bits=" << bits  << " what" << params.Bits << "whatt" << std::endl;
			std::cout << "antialias=" << antialias << std::endl;
	return params;
}
