#pragma once
#include<vector>
#include<unordered_map>
#include<string>
#include<typeindex>

class IShaderObject 
{
public:
	IShaderObject() {};
	virtual ~IShaderObject() {};
	virtual void InitShaderObject(const char* path) = 0;
	virtual void Terminate() = 0;
protected:
	//int:レジスタの番号string : 変数名type_index:変数のタイプ
	std::string_view _guid;
	std::unordered_map<int,std::unordered_map<std::string, std::string>> m_ConstantBuffers;
	std::unordered_map<int, std::string> m_Textures;
	std::unordered_map<int, std::string> m_Samplers;
};