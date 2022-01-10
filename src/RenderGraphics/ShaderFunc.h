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
		bool funcCheckOnGoodCompile() const { return checkOnGoodCompile; } // ��� �� �������� ����������
		void useMainFunc() const;

		ShaderFunc() = delete; // ��������� ����������� ��� ����������
		ShaderFunc(ShaderFunc&) = delete; // ������ �� ����������� ������ �������
		ShaderFunc& operator=(const ShaderFunc&) = delete; // ������ �����. ��������.
		ShaderFunc& operator=(ShaderFunc&&) noexcept;
		ShaderFunc(ShaderFunc&& ShaderFunc) noexcept;

	private:
		// ������� ��������� �������, ������� � ��������� ����������� ���
		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
		bool checkOnGoodCompile = false; // �������� �� ����������
		GLuint IdOfShaderFunc = 0; // �� ����� ��������� ���������


	};
}