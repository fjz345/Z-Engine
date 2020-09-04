#include "zepch.h"
#include "Mesh.h"

Mesh::Mesh(std::vector<float>* verticies)
{
	_verticies = verticies;
}

Mesh::~Mesh()
{
	delete _verticies;
}
