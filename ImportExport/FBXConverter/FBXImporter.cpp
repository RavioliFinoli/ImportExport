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

void FBXImporter::Import(const char * filename, vector<Vertex>* VertexArray)
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
					
					//junk
					vertex.norX = vertex.norY = vertex.norZ = 0;
					vertex.U = vertex.V = 0;
					VertexArray->push_back(vertex);
				}
			}
			
		}
	}
}

void FBXImporter::ExportBinary(const char * outputFile, vector<Vertex>* vertices)
{
	MeshHeader header;
	header.meshNameLength = 4;
	header.numberOfIndex = 0;
	header.numberOfVerts = vertices->size();
	header.textureNameLength = 0;

	std::ofstream file(outputFile, std::ios::binary);

	assert(file.is_open());
	file.write(reinterpret_cast<char*>(&header), sizeof(header));
	file.write(reinterpret_cast<char*>(vertices->data()), sizeof(vertices[0]) * vertices->size());

	file.close();
}

void FBXImporter::ImportBinary(const char * inputFile, vector<Vertex>* vertices)
{
	std::ifstream file(inputFile, std::ios::binary);
	MeshHeader header;
	assert(file.is_open());
	file.read(reinterpret_cast<char*>(&header), sizeof(header));

	vertices->clear();
	vertices->resize(header.numberOfVerts);

	file.read(reinterpret_cast<char*>(vertices->data()), sizeof(Vertex) * header.numberOfVerts);
	int x = 0;
	file.close();
}
