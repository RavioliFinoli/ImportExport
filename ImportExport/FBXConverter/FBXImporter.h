#pragma once
#include <fbxsdk.h>
#include <fbxsdk\fileio\fbxiosettings.h>
#include <vector>
#include "MeshHeader.h"
#include "MatHeader.h"
using std::vector;
using std::string;

class FBXImporter
{
public:
	FBXImporter();
	~FBXImporter();
	void Import(const char * filename, sMesh* mesh, vector<sMaterial*>& outMaterials);
	void ExportBinary(const char * outputFile, sMesh* mesh, vector<sMaterial*>& outMaterials);
	void ImportBinary(const char * inputFile, sMesh* mesh);
private:
	FbxManager* manager;
	FbxIOSettings* ios;
	FbxImporter* importer;
	FbxScene* scene;
};

