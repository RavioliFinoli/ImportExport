#pragma once
#include <fbxsdk.h>
#include <fbxsdk\fileio\fbxiosettings.h>
#include <vector>
#include "MeshHeader.h"
using std::vector;

class FBXImporter
{
public:
	FBXImporter();
	~FBXImporter();
	void Import(const char * filename, vector<Vertex>* VertexArray);
	void ExportBinary(const char * outputFile, vector<Vertex>* vertices);
private:
	FbxManager* manager;
	FbxIOSettings* ios;
	FbxImporter* importer;
	FbxScene* scene;
};

