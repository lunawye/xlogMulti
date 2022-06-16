#pragma once
#include "app/app_logic.h"

class uwpAppCallback : public marsMulti::app::Callback {

public:
	virtual ~uwpAppCallback() {};

	virtual std::string GetAppFilePath();

	virtual marsMulti::app::AccountInfo GetAccountInfo();

	virtual unsigned int GetClientVersion();

	virtual marsMulti::app::DeviceInfo GetDeviceInfo();

};


