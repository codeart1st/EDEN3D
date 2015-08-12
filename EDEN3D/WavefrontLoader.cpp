#include "WavefrontLoader.hpp"

#include <fstream>

using namespace std;
using namespace DirectX;

namespace EDEN3D {
	
	Mesh* WavefrontLoader::load(string filepath) {

		char type;
		float p1, p2, p3;

		vector<XMFLOAT3> vertices;
		vector<WORD> indices;

		ifstream file(filepath);

		while (file >> type >> p1 >> p2 >> p3) {

			switch (type) {
			case 'v':
				vertices.push_back(XMFLOAT3(p1, p2, p3));
				break;
			case 'f':
				indices.push_back(p1 - 1);
				indices.push_back(p2 - 1);
				indices.push_back(p3 - 1);
				break;
			}
		}

		file.close();

		return new Mesh(vertices, indices);
	}
}
