#pragma once
#include <stdint.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>
#include <string>
using std::string;
using std::vector;

struct MeshHeader
{
	uint8_t meshNameLength;
	//name

	uint32_t numberOfVerts;
	//verts

	uint32_t numberOfIndex;
	//index

	uint8_t textureNameLength;
	//tex name (texture.png)
};

struct Vertex
{
	float posX, posY, posZ;
	float norX, norY, norZ;
	float U, V;
	//other stuff?
};

struct sMesh
{
	MeshHeader header;
	string name;
	vector<Vertex> verts;
};