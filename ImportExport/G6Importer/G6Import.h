#pragma once
#include "MeshHeader.h"
#include <fstream>
class G6Import
{
public:
	static bool ImportStaticMesh(const char * filename, sMesh* outMesh);
	static bool ImportAnimatedMesh(const char * filename, sMesh* outMesh);

	G6Import();
	~G6Import();
};

