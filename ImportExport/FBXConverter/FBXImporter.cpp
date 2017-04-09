#include "FBXImporter.h"
#include <assert.h>
#include "MeshHeader.h"
#include <fstream>
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

void FBXImporter::Import(const char * filename, sMesh* mesh)
{
	importer->Initialize(filename, -1, manager->GetIOSettings());
	scene = FbxScene::Create(manager, "Scene");

	importer->Import(scene);
	
	//done with importer
	importer->Destroy();

	FbxNode* pFbxRootNode = scene->GetRootNode();

	if (pFbxRootNode)
	{
		for (int i = 0; i < pFbxRootNode->GetChildCount(); i++)
		{
			FbxNode* pCurrentNode = pFbxRootNode->GetChild(i);
			if (pCurrentNode->GetNodeAttribute() == NULL) continue;

			FbxNodeAttribute::EType AttributeType = pCurrentNode->GetNodeAttribute()->GetAttributeType();
			if (AttributeType != FbxNodeAttribute::eMesh) continue;

			

			FbxMesh* currentMesh = (FbxMesh*)pCurrentNode->GetNodeAttribute();
			FbxVector4* pVertices = currentMesh->GetControlPoints();

			for (int j = 0; j < currentMesh->GetPolygonCount(); j++)
			{
				int vertCount = currentMesh->GetPolygonSize(j);
				assert(vertCount == 3);

				for (int k = 0; k < vertCount; k++)
				{
					int iControlPointIndex = currentMesh->GetPolygonVertex(j, k);

					Vertex vertex;
					vertex.posX = (float)pVertices[iControlPointIndex].mData[0];
					vertex.posY = (float)pVertices[iControlPointIndex].mData[1];
					vertex.posZ = (float)pVertices[iControlPointIndex].mData[2];
					
					// TODO //
					vertex.norX = vertex.norY = vertex.norZ = 0;
					vertex.U = vertex.V = 0;
					//////////

					mesh->verts.push_back(vertex);
				}
			}
			
			mesh->name = currentMesh->GetNameOnly();
			mesh->header.meshNameLength = mesh->name.length();
			
			// TODO //
			mesh->header.numberOfIndex = 0;
			mesh->header.textureNameLength = 0;
			mesh->header.numberOfVerts = mesh->verts.size();
			//////////
		}
	}
}

void FBXImporter::ExportBinary(const char * outputFile, sMesh* mesh )
{
	std::ofstream file(outputFile, std::ios::binary);
	assert(file.is_open());

	file.write(reinterpret_cast<char*>(&mesh->header), sizeof(mesh->header));
	file.write((char*)(mesh->name.data()), mesh->header.meshNameLength);
	file.write(reinterpret_cast<char*>(mesh->verts.data()), sizeof(Vertex) * mesh->header.numberOfVerts);

	file.close();
}

void FBXImporter::ImportBinary(const char * inputFile, sMesh* mesh)
{
	std::ifstream file(inputFile, std::ios::binary);

	assert(file.is_open());
	file.read(reinterpret_cast<char*>(&mesh->header), sizeof(mesh->header));
	file.read((char*)(mesh->name.data()), mesh->header.meshNameLength);
	mesh->verts.clear();
	mesh->verts.resize(mesh->header.numberOfVerts);

	file.read(reinterpret_cast<char*>(mesh->verts.data()), sizeof(Vertex) * mesh->header.numberOfVerts);

	file.close();
}
