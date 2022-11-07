#pragma once

#include <thread>
#include <chrono>

class pThread
{
public: 
	pThread() = default;

	template <typename T>
	pThread(T func);

	template <typename T>
	pThread(T func, int64_t interval);

	void Enable();
	void Disable();
	void Destroy();
	void SetInterval(int64_t interval);

private:
	std::thread t;
	bool _is_on = false;
	bool _die = false;
	int64_t _interval = 0;
};

template<typename T>
inline pThread::pThread(T func)
{
	_is_on = true;
	t = std::thread([=]() {

		while (!_die)
		{
			if (_is_on) func();
			std::this_thread::sleep_for(std::chrono::milliseconds(_interval));
		}

		});
	t.detach();
}

template <typename T>
inline pThread::pThread(T func, int64_t miliseconds)
{
	_is_on = true;
	_interval = miliseconds;

	t = std::thread([=]() {
			while (!_die)
			{
				if (_is_on) func();
				std::this_thread::sleep_for(std::chrono::milliseconds(_interval));
			}
		});
}