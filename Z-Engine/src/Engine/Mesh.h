#pragma once

#include "Material.h"

class Mesh
{
public:
	Mesh(std::vector<float>* verticies);
	~Mesh();

private:
	std::vector<float>* _verticies;
	Material* _material;
};