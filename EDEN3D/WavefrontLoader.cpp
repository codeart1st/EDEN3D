#include "WavefrontLoader.hpp"

#include <fstream>
#include <sstream>
#include <regex>

namespace EDEN3D {

	void WavefrontLoader::_load(wstring filepath, vector<VERTEX>* verticesOut, vector<DWORD>* indicesOut) {

		unsigned int index1, index2, counter = 0;

		vector<XMFLOAT3> vertices;
		vector<XMFLOAT3> normals;
		vector<DWORD> indices;

		ifstream file(filepath);

		string line, type, p1, p2, p3;
		vector<string> params;

		int index;

		while (file >> type >> p1 >> p2 >> p3) {

			if (type == "v") {
				vertices.push_back(XMFLOAT3(stof(p1), stof(p2), stof(p3)));
			}
			else if (type == "vn") {
				normals.push_back(XMFLOAT3(stof(p1), stof(p2), stof(p3)));
			}
			else if (type == "f") {

				index = p1.find_last_of("/") + 1;
				index1 = stoi(p1) - 1;
				index2 = stoi(p1.substr(index)) - 1;
				indicesOut->push_back(counter++);
				verticesOut->push_back({
					vertices[index1],
					normals[index2]
				});

				index = p2.find_last_of("/") + 1;
				index1 = stoi(p2) - 1;
				index2 = stoi(p2.substr(index)) - 1;
				indicesOut->push_back(counter++);
				verticesOut->push_back({
					vertices[index1],
					normals[index2]
				});

				index = p3.find_last_of("/") + 1;
				index1 = stoi(p3) - 1;
				index2 = stoi(p3.substr(index)) - 1;
				indicesOut->push_back(counter++);
				verticesOut->push_back({
					vertices[index1],
					normals[index2]
				});
			}
		}

		file.close();
	}

	void WavefrontLoader::load(wstring filepath, const Callback& func) {

		vector<VERTEX> verticesOut;
		vector<DWORD> indicesOut;

		_load(filepath, &verticesOut, &indicesOut);
		func(new Mesh(verticesOut, indicesOut));
	}

	void WavefrontLoader::load(wstring filepath, Mesh** mesh) {


		vector<VERTEX> verticesOut;
		vector<DWORD> indicesOut;

		_load(filepath, &verticesOut, &indicesOut);
		*mesh = new Mesh(verticesOut, indicesOut);
	}
}
