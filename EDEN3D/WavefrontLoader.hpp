#pragma once

#include "EDEN3D.hpp"
#include "Mesh.hpp"

namespace EDEN3D {

	class EDEN3D_API WavefrontLoader {

	public:
		typedef function<void(Mesh*)> Callback;

		static void load(wstring, const Callback&);
		static void load(wstring, Mesh**);

	private:
		static void _load(wstring, vector<VERTEX>*, vector<DWORD>*);
	};
}
