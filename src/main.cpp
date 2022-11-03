#include "CompressionUtils.h"


int main()
{
	std::string input{ "C:\\Users\\ahmed\\Documents\\klinisches_anwendungs_projekt\\Assets_Testing\\dice\\cub.obj" };
	std::string output{ "C:\\Users\\ahmed\\Documents\\klinisches_anwendungs_projekt\\Assets_Testing\\dice\\cub.drc" };
	std::string inputSimple{ "C:\\Users\\ahmed\\Documents\\klinisches_anwendungs_projekt\\resources\\my-obj-models\\cow-nonormals.obj" };
	NarvisCompressionUtils::convertObjToDrc(input, output);

	return 0;
}

