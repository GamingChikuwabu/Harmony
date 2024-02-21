#pragma once
#include<string>
#include<unordered_map>
#include<memory>

namespace HARMONY
{
	namespace DETAIL
	{
		struct type_data;
	}
	class registration
	{
	public:

	private:
		static inline std::unordered_map<std::string, std::unique_ptr<DETAIL::type_data>> _typeData;
	};
}