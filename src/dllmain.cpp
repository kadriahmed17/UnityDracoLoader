// dllmain.cpp : Defines the entry point for the DLL application.

#include <iostream>
#include "Unity/IUnityInterface.h"

extern "C" UNITY_INTERFACE_EXPORT void  UNITY_INTERFACE_API  PrintInt(int value) {
	
std::cout << value << "\n";

}

