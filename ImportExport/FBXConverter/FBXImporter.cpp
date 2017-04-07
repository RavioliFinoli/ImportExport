#include "FBXImporter.h"



FBXImporter::FBXImporter()
{
	manager = FbxManager::Create();
	ios = FbxIOSettings::Create(manager, IOSROOT);
	manager->SetIOSettings(ios);

	importer = FbxImporter::Create(manager, "");
	
}


FBXImporter::~FBXImporter()
{
}

void FBXImporter::Import(const char * filename)
{
	importer->Initialize(filename, -1, manager->GetIOSettings());
	scene = FbxScene::Create(manager, "Scene");

	importer->Import(scene);
	
		//done with importer
		importer->Destroy();
}
