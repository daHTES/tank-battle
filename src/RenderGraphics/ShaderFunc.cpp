#include "ShaderFunc.h"
//#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
namespace Renderer 
{
	ShaderFunc::ShaderFunc(const std::string& vertexShader, const std::string& fragmentShader)
	{
		GLuint vertexShaderID;
		if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
		{
			std::cerr << "VERTEX SHADER compile time error " << std::endl;
			return;
		}

		GLuint fragmentShaderID;
		if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
		{
			std::cerr << "FRAGMENT SHADER compile time error " << std::endl;
			glDeleteShader(vertexShaderID);
			return;
		}

		IdOfShaderFunc = glCreateProgram();
		glAttachShader(IdOfShaderFunc, vertexShaderID);
		glAttachShader(IdOfShaderFunc, fragmentShaderID);
		glLinkProgram(IdOfShaderFunc);

		GLint success;
		glGetProgramiv(IdOfShaderFunc, GL_LINK_STATUS, &success);
		if (!success) 
		{
			GLchar logging[1024]; // буффер дл€ сообщени€ ошибок
			glGetShaderInfoLog(IdOfShaderFunc, 1024, nullptr, logging);
			std::cerr << "ERROR::SHADER: Link time error:\n" << logging << std::endl;
		}
		else
		{
			IdOfShaderFunc = true;
		}
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);

	}

	bool ShaderFunc::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID) 
	{
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		GLint succes; // дл€ записи статуса компил€ции шейдера
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &succes);
		if (!succes) 
		{
			GLchar logging[1024]; // буффер дл€ сообщени€ ошибок
			glGetShaderInfoLog(shaderID, 1024, nullptr, logging);
			std::cerr << "ERROR::SHADER: Compile time error:\n" << logging << std::endl;
			return false;
		}
		return true;
	}
	ShaderFunc::~ShaderFunc() 
	{
		glDeleteProgram(IdOfShaderFunc);
	}

	void ShaderFunc::useMainFunc() const 
	{
		glUseProgram(IdOfShaderFunc);
	}

	ShaderFunc& ShaderFunc::operator=(ShaderFunc&& shaderfunc) noexcept
	{
		glDeleteProgram(IdOfShaderFunc);
		IdOfShaderFunc = shaderfunc.IdOfShaderFunc;
		checkOnGoodCompile = shaderfunc.checkOnGoodCompile;

		shaderfunc.IdOfShaderFunc = 0;
		shaderfunc.checkOnGoodCompile = false;
		return *this;
	}
	ShaderFunc::ShaderFunc(ShaderFunc&& shaderFunc)  noexcept
	{
		IdOfShaderFunc = shaderFunc.IdOfShaderFunc;
		checkOnGoodCompile = shaderFunc.checkOnGoodCompile;

		shaderFunc.IdOfShaderFunc = 0;
		shaderFunc.checkOnGoodCompile = false;
	}


}