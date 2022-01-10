#include "ResourceManager.h"
#include "../RenderGraphics/ShaderFunc.h"
#include <sstream>
#include <fstream>
#include <iostream>
ResourceManager::ResourceManager(const std::string& executablePath) 
{
	size_t foundPosition = executablePath.find_last_of("/\\");
	pathShader = executablePath.substr(0, foundPosition);
}

std::string ResourceManager::getFileString(const std::string& relativePathFile)
{
	std::ifstream fileStream;
	fileStream.open(pathShader+"/"+ relativePathFile.c_str(), std::ios::in | std::ios::binary);
	if (!fileStream.is_open()) 
	{
		std::cerr << "Failed to load file resource" << relativePathFile << std::endl;
		return std::string{};
	}
	std::stringstream buffer;
	buffer << fileStream.rdbuf();
	return buffer.str();
}

std::shared_ptr<Renderer::ShaderFunc> ResourceManager::loadShader(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexString = getFileString(vertexPath);
	if (vertexString.empty()) 
	{
		std::cerr << "Vertex file is empty " << std::endl;
		return nullptr;
	}
	std::string fragmentString = getFileString(fragmentPath);
	if (fragmentString.empty()) 
	{
		std::cerr << "Fragment file is empty" << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::ShaderFunc>& newShader = shaderPrograms.emplace(shaderName, std::make_shared<Renderer::ShaderFunc>(vertexString, fragmentString)).first->second;
	
	
	if (newShader->funcCheckOnGoodCompile())
	{
		std::cerr << "Lox";
	}
	//Временная оишбка не понятно компиляции файла
	// Видео номер 4 - Менеджер Ресурсов 
		/*std::cerr << "Cant load shader program:\n"
		<< "Vertex: " << vertexPath << "\n"
		<< "Fragment: " << fragmentPath << std::endl;
		*/
	return newShader;
}


std::shared_ptr<Renderer::ShaderFunc> ResourceManager::getShader(const std::string& sharedName)
{
	ShaderProgramsMap::const_iterator tempIterator = shaderPrograms.find(sharedName);
	if (tempIterator != shaderPrograms.end()) 
	{
		return tempIterator->second;
	}
	std::cerr << "Cant find the shader: " << sharedName << std::endl;

	return nullptr;
}