#pragma once
#include <fbxsdk.h>
#include <fbxsdk\fileio\fbxiosettings.h>
#include <vector>
#include "MeshHeader.h"
using std::vector;
using std::string;

class FBXImporter
{
public:
	FBXImporter();
	~FBXImporter();
	void Import(const char * filename, sMesh* mesh);
	void ExportBinary(const char * outputFile, sMesh* mesh);
	void ImportBinary(const char * inputFile, sMesh* mesh);
private:
	FbxManager* manager;
	FbxIOSettings* ios;
	FbxImporter* importer;
	FbxScene* scene;
};

