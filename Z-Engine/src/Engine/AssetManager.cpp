#include "zepch.h"
#include "AssetManager.h"

AssetManager* AssetManager::Get()
{
	static AssetManager instance;

	return &instance;
}

AssetManager::~AssetManager()
{
	// remove all models
	for (auto m : _loadedModels)
	{
		delete _loadedModels[m.first];
	}

	// remove all meshes
	for (auto m : _loadedMeshes)
	{
		delete _loadedMeshes[m.first];
	}

	// remove all materials
	for (auto m : _loadedModels)
	{
		delete _loadedModels[m.first];
	}

	// remove all textures
	for (auto m : _loadedModels)
	{
		delete _loadedModels[m.first];
	}
}

bool AssetManager::AddModelToLoaded(std::string name, Model* model)
{
	// Check if a mesh is not loaded
	if (_loadedModels[name] != nullptr)
	{
		// Model is loaded
		ZE_WARNING("Model already loaded, probably want to check/fix this.");
		return false;
	}

	// Add the mesh to the map
	_loadedModels[name] = model;

	return true;
}

bool AssetManager::AddMeshToLoaded(std::string name, Mesh* mesh)
{
	// Check if a mesh is not loaded
	if (_loadedMeshes[name] != nullptr)
	{
		// Mesh is loaded
		ZE_WARNING("Mesh already loaded, probably want to check/fix this.");
		return false;
	}

	// Add the mesh to the map
	_loadedMeshes[name] = mesh;

	return true;
}
