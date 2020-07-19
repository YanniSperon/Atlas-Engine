#pragma once
#include <string>

namespace Atlas {
	class Console {
	private:

	public:
		static void Success(const std::string& text);
		static void Info(const std::string& text);
		static void Warning(const std::string& text);
		static void Error(const std::string& text);
		static void FatalError(const std::string& text);
	};
}