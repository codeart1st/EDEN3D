#include "WavefrontLoader.hpp"

#include <fstream>
#include <sstream>
#include <regex>

namespace EDEN3D {

	vector<string> WavefrontLoader::split(const string& s, string rgx_str) {

		vector<string> elems;
		regex rgx(rgx_str);

		sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
		sregex_token_iterator end;

		while (iter != end)  {
			elems.push_back(*iter);
			++iter;
		}

		return elems;
	}
	
	Mesh* WavefrontLoader::load(string filepath) {

		//string type, p1, p2, p3;

		unsigned int index1, index2, counter = 0;

		vector<VERTEX> verticesOut;
		vector<XMFLOAT3> vertices;
		vector<XMFLOAT3> normals;
		vector<DWORD> indicesOut;
		vector<DWORD> indices;

		ifstream file(filepath);

		string line, type, p1, p2, p3;
		vector<string> params;

		int index;

		while (file >> type >> p1 >> p2 >> p3) {

			if (type == "v") {
				vertices.push_back(XMFLOAT3(stof(p1), stof(p2), stof(p3)));
			} else if (type == "vn") {
				normals.push_back(XMFLOAT3(stof(p1), stof(p2), stof(p3)));
			} else if (type == "f") {

				index = p1.find_last_of("/") + 1;
				index1 = stoi(p1) - 1;
				index2 = stoi(p1.substr(index)) - 1;
				indicesOut.push_back(counter++);
				verticesOut.push_back({
					vertices[index1],
					normals[index2]
				});

				index = p2.find_last_of("/") + 1;
				index1 = stoi(p2) - 1;
				index2 = stoi(p2.substr(index)) - 1;
				indicesOut.push_back(counter++);
				verticesOut.push_back({
					vertices[index1],
					normals[index2]
				});
				
				index = p3.find_last_of("/") + 1;
				index1 = stoi(p3) - 1;
				index2 = stoi(p3.substr(index)) - 1;
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
