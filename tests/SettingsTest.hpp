#include <irrlicht.h>
#include <iostream>
#include <assert.h>
#include "../Settings.hpp"

//int lol = irr::KEY_KEY_CODES_COUNT;

enum { JUMP = 57, RUN = 42 };

irr::core::stringw driverName = "OPENGL";
irr::core::stringw fullscreen = "0";
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

	testSettings.setSetting("lol", "bbbb");
	testSettings.setSetting("resolution", 45);
	testSettings.save();
	std::cout << "saving settings\n";

	//testSettings.load();
	testSettings.save();
	assert( 45 == testSettings.getSettingAsInteger("resolution") );
	//assert( driverName.c_str() == testSettings.getSetting("driver").c_str() );
	assert( 0 == testSettings.getSettingAsInteger("fullscreen"));
	assert( fullscreen == testSettings.getSetting("fullscreen") );
	assert( driverName == testSettings.getSetting("driver") );

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
