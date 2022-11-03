#include "compressionutils.h"

namespace fs = std::filesystem;

namespace NarvisCompressionUtils
{
	enum FileType
	{
		DracoFile,
		ObjFile,
		TextureFile
	};

	bool convertObjToDrc(std::string filepath, std::string output)
	{
		auto isMeshRead(draco::ReadMeshFromFile(filepath));
		if (isMeshRead.ok())
		{
			const auto& mesh = isMeshRead.value();
			draco::ExpertEncoder encoder{ *mesh };
			//encoder.SetAttributeQuantization(draco::GeometryAttribute::POSITION, 16);  // Position quantization.
			//encoder.SetAttributeQuantization(draco::GeometryAttribute::TEX_COORD, 15);  // Tex-coord 0 quantization.
			//encoder.SetAttributeQuantization(draco::GeometryAttribute::NORMAL, 14);  // Tex-coord 1 quantization.
			encoder.SetTrackEncodedProperties(true);

			draco::EncoderBuffer buffer;
			encoder.EncodeToBuffer(&buffer);

			std::cout << stringFormat("Encoded vertices = ", encoder.num_encoded_points(), " , faces = ", encoder.num_encoded_faces()) << std::endl;
			auto attr = mesh->GetNamedAttribute(draco::GeometryAttribute::TEX_COORD);
			std::cout << stringFormat("texture coordinates = ", attr->data_type()) << std::endl;
			float vector[2];

			for (int v = 0; v < attr->size(); v++)
			{
				attr->GetValue(draco::AttributeValueIndex(v), &vector);
				std::cout << stringFormat("(", vector[0], ",", vector[1], ")") << std::endl;
			}
			return draco::WriteBufferToFile(buffer.data(), buffer.size(), output);
		}
		else
		{
			throw new std::runtime_error("Error: failed to read mesh");
		}
		return false;
	}
}