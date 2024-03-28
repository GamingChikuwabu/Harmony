#include"ClassBuilder.h"
#pragma once
#include"Construction/Construction.h"
#include"Class/deteil/ClassData.h"

namespace HARMONY
{
	template<typename C>
	template<typename ...Args>
	inline ClassBuilder<C>& ClassBuilder<C>::Constructer()
	{
		
		return *this;
	}
}