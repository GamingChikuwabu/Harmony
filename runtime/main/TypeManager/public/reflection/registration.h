#pragma once
#include<string>
#include<vector>
#include<memory>

namespace HARMONY
{
	namespace DETAIL
	{
		struct type_data;
	}
	class TYPEMANAGER_API registration
	{
	public:
		static DETAIL::type_data* AddItem(std::unique_ptr<DETAIL::type_data> _data);
	private:
		static inline std::vector<std::unique_ptr<DETAIL::type_data>>				 _typeData;

		/*static inline std::vector<std::unique_ptr<DETAIL::property_wrapper_base>>	 _memberProperty;
		static inline std::vector<std::unique_ptr<DETAIL::property_wrapper_base>>	 _globalProperty;
		
		static inline std::vector<std::unique_ptr<DETAIL::function_wrapper_base>>	 _memberFunction;
		static inline std::vector<std::unique_ptr<DETAIL::function_wrapper_base>>	 _globalFunction;
		
		static inline std::vector<std::unique_ptr<DETAIL::enumeration_wrapper_base>> _enumeration;*/

	};
}