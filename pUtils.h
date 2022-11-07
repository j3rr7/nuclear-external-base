#pragma once

#include <string>
#include <fstream>
#include <random>
#include <limits>
#include <thread>
#include <filesystem>
#include <Windows.h>
#include <sstream>  
#include <iomanip>

template <typename T>
void GetKeyExecuteWaitForRelease(int key, T function)
{
	// waits for key to be pressed, executes the function and then waits until you release the key again
	if (HIBYTE(GetAsyncKeyState(key)))
	{
		function();
		while (HIBYTE(GetAsyncKeyState(key)))
			sleep(100);
	}
}

static uint32_t GenerateRandomNumber(uint32_t min, uint32_t max)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> num(min, max);
	return num(rng);
}

static std::string GenerateRandomString(size_t Size)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist('a', 'z');

	std::string result;
	std::generate_n(std::back_inserter(result), Size, [&] {return dist(mt); });

	return result;
}

namespace Key
{
	namespace Down
	{
		static void W() { keybd_event(0x57, 0x11, 0, 0); }
		static void A() { keybd_event(0x41, 0x1E, 0, 0); }
		static void S() { keybd_event(0x53, 0x1F, 0, 0); }
		static void D() { keybd_event(0x44, 0x20, 0, 0); }
		static void Space() { keybd_event(MapVirtualKey(0x20, 0), 0x39, 0, 0); }

		static void LMouse() {
			INPUT    Input = { 0 };
			Input.type = INPUT_MOUSE;
			Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
			::SendInput(1, &Input, sizeof(INPUT));
		}
	}

	namespace Up
	{
		static void W() { keybd_event(0x57, 0x11, KEYEVENTF_KEYUP, 0); }
		static void A() { keybd_event(0x41, 0x1E, KEYEVENTF_KEYUP, 0); }
		static void S() { keybd_event(0x53, 0x1F, KEYEVENTF_KEYUP, 0); }
		static void D() { keybd_event(0x44, 0x20, KEYEVENTF_KEYUP, 0); }
		static void Space() { keybd_event(MapVirtualKey(0x20, 0), 0x39, KEYEVENTF_KEYUP, 0); }

		static void LMouse() {
			INPUT    Input = { 0 };
			Input.type = INPUT_MOUSE;
			Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			::SendInput(1, &Input, sizeof(INPUT));
		}
	}
}