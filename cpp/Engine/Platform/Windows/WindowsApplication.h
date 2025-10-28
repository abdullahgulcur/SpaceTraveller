#pragma once

class WindowsApplication {
private:

	static WindowsApplication* instance;

public:

	WindowsApplication() {}
	~WindowsApplication() {}

	void run();
	static WindowsApplication* getInstance();

};