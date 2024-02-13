#pragma once
#include<type_traits>
#include<functional>
#include"Types/property.h"
#include"Types/type.h"

namespace HARMONY
{
	class Property;
	class Type;
	namespace DETAIL
	{
		class ItemCreator
		{
		public:
			template<typename TYPE>
			static Type CreateType(std::string name) {
				TYPE_CATEGORY _typeCategory;
				if constexpr (std::is_arithmetic_v<TYPE>)
					_typeCategory = TYPE_CATEGORY::TYPE_ARITHMETIC;
				else if constexpr (std::is_class_v<TYPE>)
					_typeCategory = TYPE_CATEGORY::TYPE_OBJECT;
				else if constexpr (std::is_array_v<TYPE>)
					_typeCategory = TYPE_CATEGORY::TYPE_ARRAY;
				else if constexpr (std::is_enum_v<TYPE>)
					_typeCategory = TYPE_CATEGORY::TYPE_ENUM;
				return CreateType(name,sizeof(TYPE),typeid(TYPE), _typeCategory);
			};

			template<typename Class,typename MemberType>
			static Property CreateProperty(std::string name, MemberType Class::* memberptr, ACCESS_LEVEL acc = ACCESS_LEVEL::LEVEL_PUBLIC)
			{
				std::function<void(void*, std::any)> setter = [memberptr](void* classInstance, std::any value) {
					// std::any から MemberType へのキャストを試みる
					if (value.type() == typeid(MemberType)) {
						Class* class_ = reinterpret_cast<Class*>(classInstance);
						class_->*memberptr = std::any_cast<MemberType>(value);
					}
					else {
						
					}
				};

				std::function<void* (void*)> getter = [memberptr](void* classInstance) {
					Class* class_ = reinterpret_cast<Class*>(classInstance);
					return static_cast<void*>(&(class_->*memberptr));
					};

				return CreateProperty(name,setter,getter, acc);
			}
		private:
			static Type CreateType(std::string name, std::size_t size, std::type_index index, TYPE_CATEGORY cate);
			static Property CreateProperty(
				std::string name,
				std::function<void(void*,std::any)> setter,
				std::function<void*(void*)> getter,
				ACCESS_LEVEL acc = ACCESS_LEVEL::LEVEL_PUBLIC);
		};
	}
}