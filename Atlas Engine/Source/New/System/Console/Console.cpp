#include <chrono>
#include "Console.h"
#include "New/System/Global/Global.h"
#ifdef _WIN32
#include <Windows.h>
#endif

/// <summary>
/// Print a success message to the console
/// </summary>
/// <param name="text">The text you would like to print in the success message, do not include a new line</param>
void Atlas::Console::Success(const std::string& text)
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - Global::Variables.systemStartTime);
	auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
	auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration - hours);
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration - hours - minutes);
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration - hours - minutes - seconds);
	auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration - hours - minutes - seconds - milliseconds);
#ifdef _WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
#endif
	std::string outString = std::to_string(hours.count()) + ":" + std::to_string(minutes.count()) + ":" + std::to_string(seconds.count()) + "." + std::to_string(milliseconds.count()) + std::to_string(microseconds.count()) + " -- SUCCESS:  " + text + "\n";
	printf("%s", outString.c_str());
	Global::Variables.consoleLog.push_back(outString);
	if (Global::Variables.consoleLog.size() > 50) {
		Global::Variables.consoleLog.erase(Global::Variables.consoleLog.begin());
	}
}

/// <summary>
/// Print a message to the console
/// </summary>
/// <param name="text">The text you would like to print in the message, do not include a new line</param>
void Atlas::Console::Info(const std::string& text)
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - Global::Variables.systemStartTime);
	auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
	auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration - hours);
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration - hours - minutes);
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration - hours - minutes - seconds);
	auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration - hours - minutes - seconds - milliseconds);
#ifdef _WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
#endif
	std::string outString = std::to_string(hours.count()) + ":" + std::to_string(minutes.count()) + ":" + std::to_string(seconds.count()) + "." + std::to_string(milliseconds.count()) + std::to_string(microseconds.count()) + " -- INFO:  " + text + "\n";
	printf("%s", outString.c_str());
	Global::Variables.consoleLog.push_back(outString);
	if (Global::Variables.consoleLog.size() > 50) {
		Global::Variables.consoleLog.erase(Global::Variables.consoleLog.begin());
	}
}

/// <summary>
/// Print a warning message to the console
/// </summary>
/// <param name="text">The text you would like to print in the warning, do not include a new line</param>
void Atlas::Console::Warning(const std::string& text)
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - Global::Variables.systemStartTime);
	auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
	auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration - hours);
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration - hours - minutes);
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration - hours - minutes - seconds);
	auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration - hours - minutes - seconds - milliseconds);
#ifdef _WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
#endif
	std::string outString = std::to_string(hours.count()) + ":" + std::to_string(minutes.count()) + ":" + std::to_string(seconds.count()) + "." + std::to_string(milliseconds.count()) + std::to_string(microseconds.count()) + " -- WARNING: " + text + "\n";
	printf("%s", outString.c_str());
	Global::Variables.consoleLog.push_back(outString);
	if (Global::Variables.consoleLog.size() > 50) {
		Global::Variables.consoleLog.erase(Global::Variables.consoleLog.begin());
	}
}

/// <summary>
/// Print an error message to the console
/// </summary>
/// <param name="text">The text you would like to print in the warning, do not include a new line</param>
void Atlas::Console::Error(const std::string& text)
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - Global::Variables.systemStartTime);
	auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
	auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration - hours);
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration - hours - minutes);
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration - hours - minutes - seconds);
	auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration - hours - minutes - seconds - milliseconds);
#ifdef _WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
#endif
	std::string outString = std::to_string(hours.count()) + ":" + std::to_string(minutes.count()) + ":" + std::to_string(seconds.count()) + "." + std::to_string(milliseconds.count()) + std::to_string(microseconds.count()) + " -- ERROR:  " + text + "\n";
	printf("%s", outString.c_str());
	Global::Variables.consoleLog.push_back(outString);
	if (Global::Variables.consoleLog.size() > 50) {
		Global::Variables.consoleLog.erase(Global::Variables.consoleLog.begin());
	}
}

/// <summary>
/// Print a fatal error message to the console
/// </summary>
/// <param name="text">The text you would like to print in the error, do not include a new line</param>
void Atlas::Console::FatalError(const std::string& text)
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - Global::Variables.systemStartTime);
	auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
	auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration - hours);
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration - hours - minutes);
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration - hours - minutes - seconds);
	auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration - hours - minutes - seconds - milliseconds);
#ifdef _WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 79);
#endif
	std::string outString = std::to_string(hours.count()) + ":" + std::to_string(minutes.count()) + ":" + std::to_string(seconds.count()) + "." + std::to_string(milliseconds.count()) + std::to_string(microseconds.count()) + " -- FATAL ERROR:  " + text + "\n";
	printf("%s", outString.c_str());
	Global::Variables.consoleLog.push_back(outString);
	if (Global::Variables.consoleLog.size() > 50) {
		Global::Variables.consoleLog.erase(Global::Variables.consoleLog.begin());
	}
}
