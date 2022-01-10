#pragma once 
#include <string>
#include <glad/glad.h>
namespace Renderer
{
	class ShaderFunc
	{
	public:
		ShaderFunc(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderFunc();
		bool funcCheckOnGoodCompile() const { return checkOnGoodCompile; } // чек на успешную компил€цию
		void useMainFunc() const;

		ShaderFunc() = delete; // запрещаем конструктро без параметров
		ShaderFunc(ShaderFunc&) = delete; // запрет на копирование одного другому
		ShaderFunc& operator=(const ShaderFunc&) = delete; // запрет опера. присваив.
		ShaderFunc& operator=(ShaderFunc&&) noexcept;
		ShaderFunc(ShaderFunc&& ShaderFunc) noexcept;

	private:
		// функци€ обработки шейдера, вынесли в отдельный фрагментный код
		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
		bool checkOnGoodCompile = false; // проверка на компил€цию
		GLuint IdOfShaderFunc = 0; // »ƒ нашей шейдерной программы


	};
}