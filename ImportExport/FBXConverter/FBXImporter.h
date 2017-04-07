#pragma once
#include <fbxsdk.h>
#include <fbxsdk\fileio\fbxiosettings.h>

class FBXImporter
{
public:
	FBXImporter();
	~FBXImporter();
	void Import(const char* filename);
private:
	FbxManager* manager;
	FbxIOSettings* ios;
	FbxImporter* importer;
	FbxScene* scene;
};

