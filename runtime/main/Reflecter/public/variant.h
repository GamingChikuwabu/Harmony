#pragma once
#include<type_traits>

namespace HARMONY
{
	class REFLECTER_API variant
	{
	public:
		variant();
		~variant();
		variant(const variant&& var);
		template<typename T,typename Tp = std::remove_cv_t<std::remove_reference_t<T>>>
		variant(T&& var);
	private:
		void* _ptr;
	};
}

#include"inl/variant.inl"