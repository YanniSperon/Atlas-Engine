#pragma once
#include <string>
#include <vector>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

namespace L_Atlas {
	struct L_Filepath {
		std::string directory;
		std::string filename;

		L_Filepath()
			: directory(""), filename("")
		{

		}

		L_Filepath(std::string dir, std::string name)
			: directory(dir), filename(name)
		{

		}
	};
	class L_System {
	public:
		static std::vector<std::string> GetFilesInDirectory(const std::string& directory);

		static std::string GetEXEDirectory();
		static std::string GetEXEName();
		static void SetWorkingDirectory();
		static std::string GetWorkingDirectory();
		static bool IsFilePathInWorkingDirectory(const std::string& filePath);
		static bool IsFilePathInEXEDirectory(const std::string& filePath);

		static std::string ConvertFilePathToAbsolute(const std::string& localFilePath);
		static std::string ConvertFilePathToLocal(const std::string& absoluteFilePath);
		
		static bool DoesFileExist(const std::string& filePath);
		static bool HasValidFileAttributes(const std::string& filePath);
		static bool CopyFileAtlas(const std::string& originalFilePathAndName, const std::string& finalFilePath);

		static void Log(const std::string& text);
		static void Warn(const std::string& text);
		static void Err(const std::string& text);

		static void SendConsoleInput(const std::string& input);

		static void DrawConsole();

		static std::string FileOpenDialog(const std::string& label, LPCSTR filter, GLFWwindow* window);

		static L_Filepath SeperateFilepath(const std::string& filePath);

		static unsigned long long int GenerateUniqueID();

		static unsigned long long int UpdateLastUID(unsigned long long int uid);

		static void ResetUIDGenerator();
		//static std::size_t GenerateUniqueID();
	};
};