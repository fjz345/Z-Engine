#pragma once

#include <direct.h>
#include "Model.h"
#include "Material.h"

class AssetManager
{
public:
	static AssetManager* Get(ID3D12Device5* device = nullptr);

	~AssetManager();

	void TempCreateManualCubeModel()
	{
		float vertexCoords[24] = {  // Coordinates for the vertices of a cube.
		   1,1,1,   1,1,-1,   1,-1,-1,   1,-1,1,
		  -1,1,1,  -1,1,-1,  -1,-1,-1,  -1,-1,1 };

		std::vector<float>* vertsVec = new std::vector<float>(vertexCoords, vertexCoords + 24);

		Mesh* cubeMesh = new Mesh(vertsVec);
		AddMeshToLoaded("tempCubeMesh", cubeMesh);

		std::vector<Mesh*>* meshesVec = new std::vector<Mesh*>();
		meshesVec->push_back(cubeMesh);
		Model* cubeModel = new Model(meshesVec);

		AddModelToLoaded("tempCubeModel", cubeModel);

	};

private:
	AssetManager(ID3D12Device5* device = nullptr) {};
	AssetManager(AssetManager const&) = delete;
	void operator=(AssetManager const&) = delete;

	ID3D12Device5* device = nullptr;

	// Core loaded things
	std::map<std::string, Mesh*> _loadedMeshes;
	std::map<std::string, Texture*> _loadedTextures;

	// Model has meshes, mesh has material, material has textures.
	std::map<std::string, Model*> _loadedModels;
	std::map<std::string, Material*> _loadedMaterials;

	// Returns false if already exists
	bool AddModelToLoaded(std::string name, Model* model);
	bool AddMeshToLoaded(std::string name, Mesh* mesh);
};