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
	std::ofstream file(outputFile, std::ios::binary);

	file.write(reinterpret_cast<char*>(&vertices[0]), sizeof(Vertex) * vertices->size());

	file.close();
}
