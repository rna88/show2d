#ifndef SETTINGS_H
#define SETTINGS_H

#include <irrlicht.h>

// get rid of these.
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#define TAG_VIDEO "video"
#define TAG_SOUND "sound"
#define TAG_KEYS "keys"

class Settings
{
public:

	// Construct setting managers and set default settings
	Settings(const stringw& settings_file): SettingsFile(settings_file), NullDevice(0)
	{
		// Irrlicht null device, we want to load settings before we actually created our device, therefore, nulldevice
		NullDevice = irr::createDevice(irr::video::EDT_NULL);

		//DriverOptions is an irrlicht map,
		//we can insert values in the map in two ways by calling insert(key,value) or by using the [key] operator
		//the [] operator overrides values if they already exist
		DriverOptions.insert(L"Software", EDT_SOFTWARE);
		DriverOptions.insert(L"OpenGL", EDT_OPENGL);
		DriverOptions.insert(L"Direct3D9", EDT_DIRECT3D9);

		//some resolution options
		ResolutionOptions.insert(L"640x480", dimension2du(640,480));
		ResolutionOptions.insert(L"800x600", dimension2du(800,600));
		ResolutionOptions.insert(L"1024x768", dimension2du(1024,768));

		//our preferred defaults
		SettingMap.insert(L"driver", L"OpenGL");
		SettingMap.insert(L"resolution", L"640x480");
		SettingMap.insert(L"fullscreen", "0"); //0 is false

		//irr::KEY_KEY_W

		// insert all keys here. Use a fucntion to do this?
		keyOptions.insert("w", irr::KEY_KEY_W);
		keyOptions.insert("s", irr::KEY_KEY_S);
		keyOptions.insert("a", irr::KEY_KEY_A);
		keyOptions.insert("d", irr::KEY_KEY_D);

		keyMap.insert(L"forward", L"w");
		keyMap.insert(L"backward", L"s");
		keyMap.insert(L"left", L"a");
		keyMap.insert(L"right", L"d");
		keyMap.insert(L"jump", L"space");
		keyMap.insert(L"shoot", L"left_mouse");
		
//		dataTags.push_back(TAG_VIDEO);
//		dataTags.push_back(TAG_SOUND);
//		dataTags.push_back(TAG_KEYS);
	}

	// Destructor, you could store settings automatically on exit of your
	// application if you wanted to in our case we simply drop the
	// nulldevice
	~Settings()
	{
		if (NullDevice)
		{
			NullDevice->closeDevice();
			NullDevice->drop();
		}
	};

	/*
	Load xml from disk, overwrite default settings
	The xml we are trying to load has the following structure
	settings nested in sections nested in the root node, like so
	<pre>
		<?xml version="1.0"?>
		<mygame>
			<video>
				<setting name="driver" value="Direct3D9" />
				<setting name="fullscreen" value="0" />
				<setting name="resolution" value="1024x768" />
			</video>
		</mygame>
	</pre>
	*/
	bool load()
	{
		//if not able to create device don't attempt to load
		if (!NullDevice)
			return false;

		irr::io::IXMLReader* xml = NullDevice->getFileSystem()->createXMLReader(SettingsFile);	//create xml reader
		if (!xml)
			return false;

		const stringw settingTag(L"setting"); //we'll be looking for this tag in the xml
		stringw currentSection; //keep track of our current section
		const stringw videoTag(L"video"); //constant for videotag
		const stringw keyTag(L"key"); //constant for key

		//while there is more to read
		while (xml->read())
		{
		//check the node type
			switch (xml->getNodeType())
			{
				//we found a new element
				case irr::io::EXN_ELEMENT:
				{
					//we currently are in the empty or mygame section and find the video tag so we set our current section to video
					if (videoTag.equals_ignore_case(xml->getNodeName()))
					{
						currentSection = videoTag;
					}
					else if (currentSection == videoTag)
					{
						stringw key = xml->getAttributeValueSafe(L"name");
						if (!key.empty())
						{
							SettingMap[key] = xml->getAttributeValueSafe(L"value");
						}
					}
					

					//we currently are in the empty or mygame section and find the video tag so we set our current section to video
					if (keyTag.equals_ignore_case(xml->getNodeName()))
					{
						currentSection = keyTag;
					}
					else if (currentSection == keyTag)
					{
						stringw key = xml->getAttributeValueSafe(L"name");
						if (!key.empty())
						{
							keyMap[key] = xml->getAttributeValueSafe(L"value");
						}
					}




			/////////		if (currentSection.empty() && videoTag.equals_ignore_case(xml->getNodeName()))
			/////////		{
			/////////			currentSection = videoTag;
			/////////		}
			/////////		//we are in the video section and we find a setting to parse
			/////////		else if (currentSection.equals_ignore_case(videoTag) && settingTag.equals_ignore_case(xml->getNodeName() ))
			/////////		{
			/////////			//read in the key
			/////////			stringw key = xml->getAttributeValueSafe(L"name");
			/////////			//if there actually is a key to set
			/////////			if (!key.empty())
			/////////			{
			/////////				//set the setting in the map to the value,
			/////////				//the [] operator overrides values if they already exist or inserts a new key value
			/////////				//pair into the settings map if it was not defined yet
			/////////				SettingMap[key] = xml->getAttributeValueSafe(L"value");
			/////////			}
			/////////		}
					//..
					// You can add your own sections and tags to read in here
					//..

//					else if (currentSection.empty() && keyTag.equals_ignore_case(xml->getNodeName()))
//					{
//						currentSection = keyTag;
//					}
//
//					else if (currentSection.equals_ignore_case(keyTag) && settingTag.equals_ignore_case(xml->getNodeName() ))
//					{
//						//read in the key
//						stringw key = xml->getAttributeValueSafe(L"name");
//						//if there actually is a key to set
//						if (!key.empty())
//						{
//							//set the setting in the map to the value,
//							//the [] operator overrides values if they already exist or inserts a new key value
//							//pair into the settings map if it was not defined yet
//							SettingMap[key] = xml->getAttributeValueSafe(L"value");
//						}
//					}
				}
				break;

				//we found the end of an element
				case irr::io::EXN_ELEMENT_END:
					//we were at the end of the video section so we reset our tag
					currentSection=L"";
				break;
			}
		}

		// don't forget to delete the xml reader
		xml->drop();

		return true;
	}

	// Save the xml to disk. We use the nulldevice.
	bool save()
	{

		//if not able to create device don't attempt to save
		if (!NullDevice)
			return false;

		//create xml writer
		irr::io::IXMLWriter* xwriter = NullDevice->getFileSystem()->createXMLWriter( SettingsFile );
		if (!xwriter)
			return false;

		//write out the obligatory xml header. Each xml-file needs to have exactly one of those.
		xwriter->writeXMLHeader();

		//start element	mygame, you replace the label "mygame" with anything you want
		xwriter->writeElement(L"mygame");
		xwriter->writeLineBreak();					//new line

		//start section with video settings
		xwriter->writeElement(L"video");
		xwriter->writeLineBreak();					//new line

		// getIterator gets us a pointer to the first node of the settings map
		// every iteration we increase the iterator which gives us the next map node
		// until we reach the end we write settings one by one by using the nodes key and value functions
		map<stringw, stringw>::Iterator i = SettingMap.getIterator();
		for(; !i.atEnd(); i++)
		{
			//write element as <setting name="key" value="x" />
			//the second parameter indicates this is an empty element with no children, just attributes
			xwriter->writeElement(L"setting",true, L"name", i->getKey().c_str(), L"value",i->getValue().c_str() );
			xwriter->writeLineBreak();
		}

		//xwriter->writeLineBreak();

		//close video section
		xwriter->writeClosingTag(L"video");
		xwriter->writeLineBreak();




		xwriter->writeElement(L"key");
		xwriter->writeLineBreak();					//new line

		// getIterator gets us a pointer to the first node of the settings map
		// every iteration we increase the iterator which gives us the next map node
		// until we reach the end we write settings one by one by using the nodes key and value functions
		map<stringw, stringw>::Iterator j = keyMap.getIterator();
		for(; !j.atEnd(); j++)
		{
			//write element as <setting name="key" value="x" />
			//the second parameter indicates this is an empty element with no children, just attributes
			xwriter->writeElement(L"setting",true, L"name", j->getKey().c_str(), L"value",j->getValue().c_str() );
			xwriter->writeLineBreak();
		}
		//xwriter->writeLineBreak();

		//close video section
		xwriter->writeClosingTag(L"key");
		xwriter->writeLineBreak();


		//xwriter->writeClosingTag(L"mygame");





		//..
		// You can add writing sound settings, savegame information etc
		//..

		////start section with video settings
		//xwriter->writeElement(L"key");
		//xwriter->writeLineBreak();					//new line

		//map<stringw, stringw>::Iterator j = SettingMap.getIterator();
		//for(; !j.atEnd(); j++)
		//{
		//	//write element as <setting name="key" value="x" />
		//	//the second parameter indicates this is an empty element with no children, just attributes
		//	xwriter->writeElement(L"setting",true, L"name", i->getKey().c_str(), L"value",i->getValue().c_str() );
		//	xwriter->writeLineBreak();
		//}
		//xwriter->writeLineBreak();

		////close video section
		//xwriter->writeClosingTag(L"key");
		//xwriter->writeLineBreak();



		//close mygame section
		xwriter->writeClosingTag(L"mygame");

		//delete xml writer
		xwriter->drop();

		return true;
	}

	// Set setting in our manager
	void setSetting(const stringw& name, const stringw& value)
	{
		SettingMap[name]=value;
	}

	// set setting overload to quickly assign integers to our setting map
	void setSetting(const stringw& name, s32 value)
	{
		SettingMap[name]=stringw(value);
	}

	// Get setting as string
	stringw getSetting(const stringw& key) const
	{
		//the find function or irrmap returns a pointer to a map Node
		//if the key can be found, otherwise it returns null
		//the map node has the function getValue and getKey, as we already know the key, we return node->getValue()
		map<stringw, stringw>::Node* n = SettingMap.find(key);
		if (n)
			return n->getValue();
		else
			return L"";
	}

	//
	bool getSettingAsBoolean(const stringw& key ) const
	{
		stringw s = getSetting(key);
		if (s.empty())
			return false;
		return s.equals_ignore_case(L"1");
	}

	//
	s32 getSettingAsInteger(const stringw& key) const
	{
		//we implicitly cast to string instead of stringw because strtol10 does not accept wide strings
		const stringc s = getSetting(key);
		if (s.empty())
			return 0;

		return strtol10(s.c_str());
	}

public:
	map<stringw, s32> DriverOptions; //available options for driver config
	map<stringw, dimension2du> ResolutionOptions; //available options for resolution config
	map<irr::core::stringw, irr::EKEY_CODE> keyOptions; //available options for key config
private:
	Settings(const Settings& other); // defined but not implemented
	Settings& operator=(const Settings& other); // defined but not implemented

	map<stringw, stringw> SettingMap; //current config
	map<stringw, stringw> keyMap; //key config

	stringw SettingsFile; // location of the xml, usually the
	irr::IrrlichtDevice* NullDevice;

//	// Holds the types of tags to check for eg. video, sound
//	irr::core::array<core::stringw> dataTags;

//	int lookForTags(CURRENT ELEMENT)
//	{
//		return -1;
//	}
//
//	void readElement(EXML_NODE inputNode)
//	{
//			//check the node type
//		switch (inputNode)
//		{
//			//we found a new element
//			case irr::io::EXN_ELEMENT:
//			{
//				//we currently are in the empty or mygame section and find the video tag so we set our current section to video
//				if (currentSection.empty() && videoTag.equals_ignore_case(xml->getNodeName()))
//				{
//					currentSection = videoTag;
//				}
//				//we are in the video section and we find a setting to parse
//				else if (currentSection.equals_ignore_case(videoTag) && settingTag.equals_ignore_case(xml->getNodeName() ))
//				{
//					//read in the key
//					stringw key = xml->getAttributeValueSafe(L"name");
//					//if there actually is a key to set
//					if (!key.empty())
//					{
//						//set the setting in the map to the value,
//						//the [] operator overrides values if they already exist or inserts a new key value
//						//pair into the settings map if it was not defined yet
//						SettingMap[key] = xml->getAttributeValueSafe(L"value");
//					}
//				}
//				//..
//				// You can add your own sections and tags to read in here
//			}
//			break;
//
//			//we found the end of an element
//			case irr::io::EXN_ELEMENT_END:
//				//we were at the end of the video section so we reset our tag
//				currentSection=L"";
//			break;
//		}
//	}

};

#endif /* SETTINGS_H */
