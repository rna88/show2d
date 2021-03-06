#include <irrlicht.h>
#include <iostream>
#include <string>
#include <assert.h>
#include "../Settings.hpp"

//int lol = irr::KEY_KEY_CODES_COUNT;

enum { JUMP = 57, RUN = 42 };

irr::core::stringw driverName = "OpenGL";
irr::core::stringw fullscreen = "0";
irr::core::stringw key = "space";
//irr::core::stringw driverName = L"lol";

// Runs tests for the setting object.
void SettingsTest()
{
// note: settings are modified once load is called, but permanent modifications only occur
// after write is called.
	Settings testSettings("options.xml");
	std::cout << "constructing Settings object\n";

	testSettings.load();
	std::cout << "loading settings\n";

	//assert( driverName == testSettings.getSetting(driverName) );
	//assert( driverName.c_str() == testSettings.getSetting(driverName).c_str() );

	//testSettings.setSetting("lol", "bbbb");
	testSettings.setSetting("resolution", 45);
	//testSettings.setSetting("shoot", 45);
	testSettings.save();
	std::cout << "saving settings\n";

	//testSettings.load();
	//testSettings.save();
	assert( 45 == testSettings.getSettingAsInteger("resolution") && "resolution setting" );
	assert( 0 == testSettings.getSettingAsInteger("fullscreen") && "fullscreen setting" );
	assert( fullscreen == testSettings.getSetting("fullscreen") && "fullscreen setting" );
	assert( driverName == testSettings.getSetting("driver") && "driver setting" );
//assert( key == testSettings.getSetting("jump") );
	//assert( driverName.c_str() == testSettings.getSetting("driver").c_str() );

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
