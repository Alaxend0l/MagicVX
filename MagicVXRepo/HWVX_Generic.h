#pragma once

class HWVX_Generic
{
protected:
	int baseAddress = 0;
public:
	virtual void Update(int) {};
	int GetBaseAddress();
	void SetBaseAddress(int);
};

