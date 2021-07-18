#include "zepch.h"
#include "Model.h"

Model::Model(std::vector<Mesh*>* meshes)
{
	_meshes = meshes;
}

Model::~Model()
{
}
