#include "WavefrontLoader.hpp"

#include <fstream>

namespace EDEN3D {
	
	Mesh* WavefrontLoader::load(string filepath) {

		string type, p1, p2, p3;

		unsigned int index1, index2, counter = 0;

		vector<VERTEX> verticesOut;
		vector<XMFLOAT3> vertices;
		vector<XMFLOAT3> normals;
		vector<DWORD> indicesOut;
		vector<DWORD> indices;

		ifstream file(filepath);

		while (file >> type >> p1 >> p2 >> p3) {

			if (type == "v") {
				vertices.push_back(XMFLOAT3(stof(p1), stof(p2), stof(p3)));
			} else if (type == "vn") {
				normals.push_back(XMFLOAT3(stof(p1), stof(p2), stof(p3)));
			} else if (type == "f") {

				index1 = index2 = stoi(p1) - 1;
				indicesOut.push_back(counter++);
				verticesOut.push_back({
					vertices[index1],
					normals[index2]
				});

				index1 = index2 = stoi(p2) - 1;
				indicesOut.push_back(counter++);
				verticesOut.push_back({
					vertices[index1],
					normals[index2]
				});
				
				index1 = index2 = stoi(p3) - 1;
				indicesOut.push_back(counter++);
				verticesOut.push_back({
					vertices[index1],
					normals[index2]
				});
			}
		}

		file.close();

		return new Mesh(verticesOut, indicesOut);
	}
}
