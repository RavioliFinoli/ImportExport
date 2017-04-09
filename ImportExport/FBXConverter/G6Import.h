#pragma once
#include "MeshHeader.h"

class G6Import
{
public:
	static bool ImportMesh(sMesh* outMesh);
	G6Import();
	~G6Import();
};

