#pragma once
#include <string>

namespace L_Atlas {

	enum L_MouseMode {
		raw = 0, default = 1
	};

	class L_Config {
	private:
		bool fullscreen;
		bool forceFullscreen;
		bool vr;
		int initialWidth;
		int initialHeight;
		float mouseSensitivity;
		float FOV;
		bool vsync;
		L_MouseMode mouseMode;
	public:
		L_Config();
		L_Config(std::string name);
		L_Config(std::string dir, std::string name);
		~L_Config();
		void ReadConfig(std::string dir, std::string name);
		void WriteConfig(std::string dir, std::string name);

		bool GetFullscreenPreference();
		void SetFullscreenPreference(bool newValue);

		bool GetVSyncPreference();
		void SetVSyncPreference(bool newValue);

		bool GetVRPreference();
		void SetVRPreference(bool newValue);

		bool GetForceFullscreen();
		void SetForceFullscreen(bool newValue);

		int GetInitialWidthPreference();
		void SetInitialWidthPreference(int newValue);

		int GetInitialHeightPreference();
		void SetInitialHeightPreference(int newValue);

		float GetMouseSensitivityPreference();
		void SetMouseSensitivityPreference(float newValue);

		float GetFOVPreference();
		void SetFOVPreference(float newValue);

		L_MouseMode GetMouseMode();
		void SetMouseMode(L_MouseMode newValue);
	};
}