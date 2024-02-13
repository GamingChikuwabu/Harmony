#pragma once
#include<functional>
#include<string>

namespace HARMONY
{
	namespace DETAIL
	{	
		// 引数の型情報を基にキーを生成するヘルパー関数
		template<typename... Args>
		std::string GenerateConstructorKey() {
			return typeid(std::tuple<Args...>).name();
		}

		template<class ClassType>
		struct TYPEMANAGER_API Constructor_data
		{
			// コンストラクタ用のデリゲートをテンプレート化
			template <typename... Args>
			using ConstructorDelegate = std::function<ClassType* (Args...)>;
			std:
		};
	}
}