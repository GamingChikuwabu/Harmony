#pragma once
#include<string>
#include<vector>

namespace HARMONY
{
	class Property;
	class Constructor;
	class Class
	{
	public:
		/// @brief Classのプロパティを取得する関数
		/// @param propname プロパティの名前
		/// @return Property
		Property GetProperty(std::string propname);

		/// @brief クラスのすべてのプロパテぃを取得する関数
		/// @return　プロパティ
		std::vector<Property> GetProperties();

		template<typename T,typename ...Args>
		T* CreateClassInstance(Args...);

	private:


	};
}