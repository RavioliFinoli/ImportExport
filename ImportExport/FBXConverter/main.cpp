#include <fbxsdk.h>
#include <fstream>
#include "MeshHeader.h"
#include <iostream>
#include <stdlib.h>
#include "FBXImporter.h"

#define out std::cout <<
#define endline << std::endl
#define pause system("pause")

void PrintVertex(Vertex vertex)
{
	out "Position: { " << vertex.posX << ", " << vertex.posY << ", " << vertex.posZ << "}" << std::endl;
	out "Normal: { " << vertex.norX << ", " << vertex.norY << ", " << vertex.norZ << "}" << std::endl;
	out "UV: { " << vertex.U << ", " << vertex.V << "}" << std::endl;

}

int main() 
{
	//////////////////////////////////////////////////////
	//// FBXImporter TEST ////////////////////////////////
	//////////////////////////////////////////////////////

	FBXImporter importer;
	vector<Vertex> verts;
	importer.Import("test.fbx", &verts);

	out verts.size() endline;

	for (int i = 0; i < verts.size(); i++)
		PrintVertex(verts[i]);

	pause;


	//////////////////////////////////////////////////////
	//// BINARY INPUT OUTPUT TEST BELOW //////////////////
	//////////////////////////////////////////////////////


	//std::ofstream outFile("test3.G6", std::ios::binary);

	//Vertex vertices[3]
	//{
	//	{ 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
	//	{ 21.0f, 2.0f, 33.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
	//	{ 1.0f, 2.0f, 3.0f, 20.0f, 0.0f, 1.0f, 31.0f, 0.0f }
	//};
	//outFile.write(reinterpret_cast<char*>(vertices), sizeof(Vertex) * 3);
	//outFile.close();
	//Vertex inVerts[3];

	//std::ifstream in("test3.G6", std::ios::binary);
	//in.read(reinterpret_cast<char*>(inVerts), sizeof(Vertex) * 3);

	//for (int i = 0; i < 3; i++)
	//{
	//	std::cout << "Vertex " << i + 1 << std::endl;
	//	PrintVertex(inVerts[i]);
	//}
	//system("pause");
	//in.close();

}
