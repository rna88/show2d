#include <irrlicht.h>
#include "../irrKlang-64bit-1.5.0/include/irrKlang.h"
#include <iostream>
#include "driverChoice.h"
#include "exampleHelper.h"

using namespace irr;

class App
{
public:

	App()
	{

	}

	~App()
	{
		device->drop();
		soundEngine->drop();
	}

	void start()
	{
	video::E_DRIVER_TYPE driverType=driverChoiceConsole();
	if (driverType==video::EDT_COUNT)
		exit(1);

	// create device

	//IrrlichtDevice *device = createDevice(driverType, core::dimension2d<u32>(512, 384));
	IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(512, 384), 32, 0, 0 , 1, 0);
	irrklang::ISoundEngine* soundEngine = irrklang::createIrrKlangDevice();

	if (device == 0 || soundEngine == 0 )
		exit(1);

	device->setWindowCaption(L"show2d");

	video::IVideoDriver* driver = device->getVideoDriver();

	const io::path mediaPath = getExampleMediaPath();

		images = driver->getTexture(mediaPath + "2ddemo.png");
	driver->makeColorKeyTexture(images, core::position2d<s32>(0,0));

	font = device->getGUIEnvironment()->getBuiltInFont();
	font2 = device->getGUIEnvironment()->getFont(mediaPath + "bigfont.png");
		//device->getGUIEnvironment()->getFont(mediaPath + "fonthaettenschweiler.bmp");

	imp1 = core::rect<s32>(349,15,385,78);
	imp2 = core::rect<s32>(387,15,423,78);

	/*
	Prepare a nicely filtering 2d render mode for special cases.
	*/
	driver->getMaterial2D().TextureLayer[0].BilinearFilter=true;
	driver->getMaterial2D().AntiAliasing=video::EAAM_FULL_BASIC;


	}

	void loop()
	{
		while(device->run() && driver)
		{
			if (device->isWindowActive())
			{
				u32 now = device->getTimer()->getTime();
				double deltaTime = now - then;
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
	
	
				u32 time = device->getTimer()->getTime();
	
				driver->beginScene(video::ECBF_COLOR | video::ECBF_DEPTH, video::SColor(255,120,102,136));
	
								// draw fire & dragons background world
				driver->draw2DImage(images, core::position2d<s32>(50,50),
					core::rect<s32>(0,0,342,224), 0,
					video::SColor(255,255,255,255), true);
	
				// draw flying imp
				driver->draw2DImage(images, core::position2d<s32>(164,125),
					(time/500 % 2) ? imp1 : imp2, 0,
					video::SColor(255,255,255,255), true);
	
				// draw second flying imp with colorcylce
				driver->draw2DImage(images, core::position2d<s32>(270,105),
					(time/500 % 2) ? imp1 : imp2, 0,
					video::SColor(255,(time) % 255,255,255), true);
	
	
				core::array< core::position2d<s32> > pos;
				core::array< core::rect<s32> > src;
	
				driver->draw2DImageBatch(
					images, 
					pos,
					src,
					0,
					video::SColor(255,255,255,255),
				       	0);
	
	
				/*
				Drawing text is really simple. The code should be self
				explanatory.
				*/
	
				// draw some text
				if (font2)
					font2->draw((core::stringc)(deltaTime),
					//font->draw(L"This demo shows that Irrlicht is also capable of drawing 2D graphics.",
						core::rect<s32>(130,10,300,50),
						video::SColor(255,255,255,255));
	
				// draw some other text
				if (font2)
					font2->draw(L"Also mixing with 3d graphics is possible.",
						core::rect<s32>(130,50,300,60),
						video::SColor(255,time % 255,time % 255,255));
	
				/*
				Next, we draw the Irrlicht Engine logo (without
				using a color or an alpha channel). Since we slightly scale
				the image we use the prepared filter mode.
				*/
				driver->enableMaterial2D();
				driver->draw2DImage(images, core::rect<s32>(10,10,108,48),
					core::rect<s32>(354,87,442,118));
				driver->enableMaterial2D(false);
	
				/*
				Finally draw a half-transparent rect under the mouse cursor.
				*/
				core::position2d<s32> m = device->getCursorControl()->getPosition();
				driver->draw2DRectangle(video::SColor(100,255,255,255),
					core::rect<s32>(m.X-20, m.Y-20, m.X+20, m.Y+20));
	
				driver->endScene();
	
				int FPS = driver->getFPS();
				core::stringw fps = "";
				fps+=FPS;
				device->setWindowCaption(fps.c_str());
			}
		}

	}

	void end()
	{
		device->drop();
		soundEngine->drop();
	}

private:

	const int LOGIC_MS_PER_UPDATE = 1000/10; // 10FPS
	const int RENDER_MS_PER_UPDATE = 1000/1; // 1FPS
	
	u32 then = device->getTimer()->getTime();
	double lag = 0.0;

	video::ITexture* images = 0;
	gui::IGUIFont* font = 0;
	gui::IGUIFont* font2 = 0;
	core::rect<s32> imp1;
	core::rect<s32> imp2;

	
	irr::IrrlichtDevice* device = 0;
	irrklang::ISoundEngine* soundEngine = 0;
	irr::video::IVideoDriver* driver = 0;


	irr::core::stringw mediaPath = "";
};
