#include "L_Config.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace L_Atlas {
	L_Config::L_Config()
		: fullscreen(false), forceFullscreen(false), vr(false), initialHeight(720), initialWidth(1280), mouseSensitivity(0.15f), FOV(90.0f), vsync(1), mouseMode(default)
	{

	}
	L_Config::L_Config(std::string name)
	{
		ReadConfig("", name);
	}

	L_Config::L_Config(std::string dir, std::string name)
	{
		ReadConfig(dir, name);
	}

	L_Config::~L_Config()
	{

	}

	void L_Config::ReadConfig(std::string dir, std::string name)
	{
		fullscreen = false;
		forceFullscreen = false;
		vr = false;
		initialWidth = 1280;
		initialHeight = 720;
		mouseSensitivity = 0.15f;
		FOV = 90.0f;
		vsync = 1;
		mouseMode = L_MouseMode::default;

		std::ifstream f(dir + name);

		if (!f.is_open()) {
			std::cout << "Config file: \"" << dir << name << "\" does not exist or could not be loaded.\n";
		}

		while (!f.eof())
		{
			std::string line;
			std::getline(f, line);

			if (line.find("#") != std::string::npos || line.size() == 0) {

			}
			else if (line.find("fullscreen=") != std::string::npos) {
				std::string value = line.substr(11);
				fullscreen = (bool)std::stoi(value);
			}
			else if (line.find("forceFullscreen=") != std::string::npos) {
				std::string value = line.substr(16);
				forceFullscreen = (bool)std::stoi(value);
			}
			else if (line.find("vsync=") != std::string::npos) {
				std::string value = line.substr(6);
				vsync = (bool)std::stoi(value);
			}
			else if (line.find("vr=") != std::string::npos) {
				std::string value = line.substr(3);
				vr = (bool)std::stoi(value);
			}
			else if (line.find("initialWidth=") != std::string::npos) {
				std::string value = line.substr(13);
				initialWidth = std::stoi(value);
			}
			else if (line.find("initialHeight=") != std::string::npos) {
				std::string value = line.substr(14);
				initialHeight = std::stoi(value);
			}
			else if (line.find("mouseSensitivity=") != std::string::npos) {
				std::string value = line.substr(17);
				mouseSensitivity = std::stof(value);
			}
			else if (line.find("FOV=") != std::string::npos) {
				std::string value = line.substr(4);
				FOV = std::stof(value);
			}
			else if (line.find("mouseMode=") != std::string::npos) {
				std::string value = line.substr(10);
				mouseMode = L_MouseMode(std::stoi(value));
			}
		}
	}

	void L_Config::WriteConfig(std::string dir, std::string name)
	{
		printf("Saving to file: %s%s", dir.c_str(), name.c_str());
		std::ofstream outfile(dir + name);
		outfile << "#choose whether the application will launch in fullscreen or not\n";
		outfile << "fullscreen=" << std::to_string(fullscreen) << "\n";
		outfile << "\n";
		outfile << "#choose whether the application will force fullscreen if the window is the\n";
		outfile << "#same size as the screen\n";
		outfile << "forceFullscreen=" << std::to_string(forceFullscreen) << "\n";
		outfile << "\n";
		outfile << "#enable vsync\n";
		outfile << "vsync=" << std::to_string(vsync) << "\n";
		outfile << "\n";
		outfile << "#choose whether the application will attempt to connect to any available vr headset or not\n";
		outfile << "vr=" << std::to_string(vr) << "\n";
		outfile << "\n";
		outfile << "#choose the starting width of the window in pixels\n";
		outfile << "initialWidth=" << std::to_string(initialWidth) << "\n";
		outfile << "\n";
		outfile << "#choose the starting height of the window in pixels\n";
		outfile << "initialHeight=" << std::to_string(initialHeight) << "\n";
		outfile << "\n";
		outfile << "#choose the sensitivity, it is calculated by multiplying mouse position\n";
		outfile << "#and sensitivity to get the answer in degrees so 0.1-0.5 is recommended\n";
		outfile << "mouseSensitivity=" << std::to_string(mouseSensitivity) << "f\n";
		outfile << "\n";
		outfile << "#choose the starting fov\n";
		outfile << "FOV=" << std::to_string(FOV) << "f\n";
		outfile << "\n";
		outfile << "#set the mouse mode (raw = 0, default = 1) RAW NOT SUPPORTED BY EVERY SYSTEM\n";
		outfile << "mouseMode=" << std::to_string(mouseMode) << "\n";
		outfile.close();
	}

	bool L_Config::GetFullscreenPreference()
	{
		return fullscreen;
	}

	void L_Config::SetFullscreenPreference(bool newValue)
	{
		fullscreen = newValue;
	}

	bool L_Config::GetVSyncPreference()
	{
		return vsync;
	}

	void L_Config::SetVSyncPreference(bool newValue)
	{
		vsync = newValue;
	}

	bool L_Config::GetVRPreference()
	{
		return vr;
	}

	void L_Config::SetVRPreference(bool newValue)
	{
		vr = newValue;
	}

	bool L_Config::GetForceFullscreen()
	{
		return forceFullscreen;
	}

	void L_Config::SetForceFullscreen(bool newValue)
	{
		forceFullscreen = newValue;
	}

	int L_Config::GetInitialWidthPreference()
	{
		return initialWidth;
	}

	void L_Config::SetInitialWidthPreference(int newValue)
	{
		initialWidth = newValue;
	}

	int L_Config::GetInitialHeightPreference()
	{
		return initialHeight;
	}

	void L_Config::SetInitialHeightPreference(int newValue)
	{
		initialHeight = newValue;
	}

	float L_Config::GetMouseSensitivityPreference()
	{
		return mouseSensitivity;
	}

	void L_Config::SetMouseSensitivityPreference(float newValue)
	{
		mouseSensitivity = newValue;
	}

	float L_Config::GetFOVPreference()
	{
		return FOV;
	}

	void L_Config::SetFOVPreference(float newValue)
	{
		FOV = newValue;
	}

	L_MouseMode L_Config::GetMouseMode()
	{
		return mouseMode;
	}

	void L_Config::SetMouseMode(L_MouseMode newValue)
	{
		mouseMode = newValue;
	}
}