#pragma once

#include "Mesh.h"

class Model
{
public:
	Model(std::vector<Mesh*>* meshes);
	~Model();
	
private:
	std::vector<Mesh*>* _meshes;
};