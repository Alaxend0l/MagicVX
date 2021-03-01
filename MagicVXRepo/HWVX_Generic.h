#pragma once

#include "Proxy.h"
#include "FunctionCaller.h"

class HWVX_Generic
{
protected:
	int baseAddress = 0;
	FunctionCaller* FC;
public:
	virtual void Update() {};
	int GetBaseAddress();
	void SetBaseAddress(int);
	void SetFunctionCaller(FunctionCaller*);

	void UpdateInt(Proxy<int>&);
	void UpdateFloat(Proxy<float>&);

	void InitInt(Proxy<int>&, int);
	void InitFloat(Proxy<float>&, int);
};