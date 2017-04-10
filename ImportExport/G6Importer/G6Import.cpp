#include "G6Import.h"

bool G6Import::ImportStaticMesh(const char * filename, sMesh * outMesh)
{
	std::ifstream file(filename, std::ios::binary);

	assert(file.is_open());
	file.read(reinterpret_cast<char*>(&outMesh->header), sizeof(outMesh->header));
	file.read((char*)(outMesh->name.data()), outMesh->header.meshNameLength);
	outMesh->verts.clear();
	outMesh->verts.resize(outMesh->header.numberOfVerts);

	file.read(reinterpret_cast<char*>(outMesh->verts.data()), sizeof(Vertex) * outMesh->header.numberOfVerts);

	file.close();

	return true;
}

G6Import::G6Import()
{
}


G6Import::~G6Import()
{
}
