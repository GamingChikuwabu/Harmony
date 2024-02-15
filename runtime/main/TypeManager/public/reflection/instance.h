#pragma once

namespace HARMONY
{
	class variant;
	class instance
	{
	public:
		instance();
		instance(const instance& ins);
		instance(const instance&& ins);
		instance(const variant& var);
		template<typename T>
		instance(T& obj);

	};
}