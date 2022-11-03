#pragma once

#include <draco/io/mesh_io.h>
#include <draco/io/file_utils.h>
#include <draco/io/obj_encoder.h>
#include "draco/compression/encode.h"
#include "draco/compression/decode.h"
#include "Unity/IUnityInterface.h"
#include <memory>
#include <thread>

struct Vector3 { float x, y, z; };
struct Vector2 { float u, v; };

class DracoFileLoader
{
public:
	int loadFile(char* fileName);
	int getVerticesCount();
	int getFacesCount();
	bool copyData(Vector3* vertices, int* indices, Vector2* texCoordinates);

private:
	std::unique_ptr<draco::Mesh> mesh_;
};