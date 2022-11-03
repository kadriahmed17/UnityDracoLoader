#pragma once

#include <string>
#include <draco/io/mesh_io.h>
#include <draco/io/file_utils.h>
#include <draco/io/obj_encoder.h>
#include <iostream>
#include <filesystem>
#include <sstream>

namespace NarvisCompressionUtils
{

	template<typename... Args>
	std::string stringFormat(Args const&... args)
	{
		std::ostringstream stream;
		using List = int[];
		(void)List {
			0, ((void)(stream << args), 0) ...
		};

		return stream.str();
	}

	bool convertObjToDrc(std::string input, std::string output);

	std::string extractFilename(std::string fullname, char extension);

	void compressData(std::string inputDir, std::string outputDir);

}