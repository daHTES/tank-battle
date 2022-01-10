#pragma once 
#include <string>
#include <memory>
#include <map>
namespace Renderer
{
	class ShaderFunc;
}
	class ResourceManager
	{
	public:
		ResourceManager(const std::string& executablePath);
		~ResourceManager() = default;

		ResourceManager(const ResourceManager&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;
		ResourceManager& operator=(ResourceManager&&) = delete;
		ResourceManager(ResourceManager&&) = delete;

		std::shared_ptr<Renderer::ShaderFunc> loadShader(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
		std::shared_ptr<Renderer::ShaderFunc> getShader(const std::string& sharedName);


	private:
		std::string getFileString(const std::string& relativePathFile);

		typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderFunc>> ShaderProgramsMap;
		ShaderProgramsMap shaderPrograms;
		std::string pathShader;

	};
