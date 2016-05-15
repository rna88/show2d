#include <irrlicht.h>
#include <iostream>
#include "../Settings.hpp"

//int lol = irr::KEY_KEY_CODES_COUNT;

enum { JUMP = 57, RUN = 42 };

void SettingsTest()
{
	Settings testSettings("options.xml");
	std::cout << "constructing Settings object\n";
	testSettings.load();
	std::cout << "loading settings\n";
	testSettings.setSetting("lol", "bbbb");
	std::cout << testSettings.getSettingAsInteger);
	testSettings.setSetting("resolution", 453534);
	testSettings.save();
	std::cout << "saving settings\n";

	//// Should return enums of any pressed action.
	//testSettings.getAction(JUMP);

	//testSettings.setKey(RUN, irr::KEY_SPACE);
	//testSettings.save();

	//testSettings.getAction();
}


//<pre>
//	<?xml version="1.0"?>
//	<mygame>
//		<video>
//			<setting name="driver" value="OPENGL" />
//			<setting name="fullscreen" value="0" />
//			<setting name="resolution" value="640x480" />
//		</video>
//	</mygame>
//</pre>
//
