#pragma once
#include "MeshHeader.h"
#include <fstream>
class G6Import
{
public:
	static bool ImportMesh(const char * filename, sMesh* outMesh);
	G6Import();
	~G6Import();
};

