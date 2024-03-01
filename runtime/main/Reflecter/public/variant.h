#pragma once

namespace HARMONY
{
	class REFLECTER_API variant
	{
	public:
		variant();
		~variant();
		variant(const variant&& var);
		template<typename T>
		variant(T&& var);
	private:

	};
}

#include"inl/variant.inl"