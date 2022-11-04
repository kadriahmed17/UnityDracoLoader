
#include "dracofileloader.h"

//spd log

int DracoFileLoader::loadFile(char* fileName)
{
	std::vector<char> data;

	bool status = draco::ReadFileToBuffer(fileName, &data);
	if (!status)
	{
		return 10;
	}
	draco::DecoderBuffer buffer;
	buffer.Init(data.data(), data.size());

	draco::Decoder decoder;

	auto geom_type = draco::Decoder::GetEncodedGeometryType(&buffer);
	if (geom_type.ok() && geom_type.value() == draco::TRIANGULAR_MESH) {
		auto mesh = decoder.DecodeMeshFromBuffer(&buffer);
		if (!mesh.ok())
			return 20;
		else
		{
			mesh_ = std::move(mesh).value();
			return 0;
		}
	}
	else {
		return 30;
	}
}


int DracoFileLoader::getVerticesCount()
{
	return mesh_->num_points();
}

int DracoFileLoader::getFacesCount()
{
	return mesh_->num_faces();
}



bool DracoFileLoader::copyData(Vector3* vertices, int* indices, Vector2* texCoordinates)
{
	float vector[3];

	auto attr = mesh_->GetNamedAttribute(draco::GeometryAttribute::POSITION);
	if (attr == NULL) return false;
	switch (attr->data_type())
	{
	case draco::DataType::DT_FLOAT32:
		if (attr->num_components() != 3)
		{
			//Print("Error: Invalid number of components in compressed mesh position attribute");
			return false;
		}
		if (attr->byte_stride() > 16)
		{
			//Print("Error: Attribute byte stride is too long");
			return false;
		}
		for (int v = 0; v < mesh_->num_points(); v++)
		{
			attr->GetValue(draco::AttributeValueIndex(v), &vector);
			vertices[v].x = vector[0];
			vertices[v].y = vector[1];
			vertices[v].z = vector[2];
		}
		break;
	default:
		//Print("Error: Invalid data type in compressed mesh position attribute");
		return false;
		break;
	}

	// Load triangle indices
	for (int t = 0; t < mesh_->num_faces(); ++t)
	{
		indices[t * 3] = mesh_->face(draco::FaceIndex(t))[0].value();		// BL
		indices[t * 3 + 2] = mesh_->face(draco::FaceIndex(t))[1].value();	// TL
		indices[t * 3 + 1] = mesh_->face(draco::FaceIndex(t))[2].value();	// BR
	}

	// Load uv coordinates
	attr = mesh_->GetNamedAttribute(draco::GeometryAttribute::TEX_COORD);
	if (attr == NULL) return false;
	switch (attr->data_type())
	{
	case draco::DataType::DT_FLOAT32:
		if (attr->num_components() != 2)
		{
			//Print("Error: Invalid number of components in compressed mesh position attribute");
			return false;
		}
		if (attr->byte_stride() > 16)
		{
			//Print("Error: Attribute byte stride is too long");
			return false;
		}
		for (int v = 0; v < attr->size(); v++)
		{
			attr->GetValue(draco::AttributeValueIndex(v), &vector);
			texCoordinates[v].u = vector[0];
			texCoordinates[v].v = vector[1];
		}
		break;
	default:
		//Print("Error: Invalid data type in compressed mesh position attribute");
		return false;
		break;
	}
	return false;
}
