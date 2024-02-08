#pragma once
#include"Archive/namevaluepair.h"

namespace HARMONY
{
	class TYPEMANAGER_API IArchive
	{
	public:
		virtual ~IArchive() {};
		template<typename T>
		void LoadValue(const NVP<T>& nvp)
		{
			if constexpr (std::is_class<T>::value) {
				// Tがクラスの場合の処理
				if constexpr (std::is_pointer<T>::value) {
					// Tがポインタの場合の処理

				}
			}
			else {
				// Tがクラスでない場合の処理
				if constexpr (std::is_pointer<T>::value)
				{
					LoadValue(nvp.name, *nvp.value);
				}
				else
				{
					LoadValue(nvp.name, nvp.value);
				}
			}
		}
	protected:
		virtual void LoadValue(const char* name, int& value) = 0;
		virtual void LoadValue(const char* name, float& value) = 0;
		virtual void LoadValue(const char* name, double& value) = 0;
		virtual void LoadValue(const char* name, long& value) = 0;
		virtual void LoadValue(const char* name, std::string& value) = 0;
	};
}