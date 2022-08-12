// dllmain.cpp : Defines the entry point for the DLL application.

#include "Unity/IUnityInterface.h"
#include <string>
#include <drac>

extern "C" UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API  PrintInt(int value) {
	return value * 2;
}

struct Vector3 {
	float x, y, z;
};

struct Vector2 {
	float x, z;
};



extern "C" UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API  LoadFile(const char* meshFile, const char* imageFile) {


	return true;
}


extern "C" UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API  VerticesCount() {

	return 3;
}


extern "C" UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API  FacesCount() {

	return 1;
}


extern "C" UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API GetData(Vector3 * vertices, Vector2 * uv, int* verticesIndex) {
	vertices[0] = { 0,0,0 };
	vertices[1] = { 1,0,0 };
	vertices[2] = { 0,1,0 };

	uv[0] = { 0,0 };
	uv[1] = { 0,0 };
	uv[2] = { 0,0 };

	verticesIndex[0] = 0;
	verticesIndex[1] = 2;
	verticesIndex[2] = 1;

	return true;
}

