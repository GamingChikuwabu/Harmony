#pragma once

namespace HARMONY
{
	namespace DETAIL
	{
		struct return_as_ptr
		{};

		struct set_as_ptr
		{};

		struct set_as_ref_wrapper
		{};

		struct get_as_ref_wrapper
		{};

		struct return_as_copy
		{};

		struct read_only
		{};

		struct set_value
		{};

		struct member_func_ptr
		{
			using type = member_func_ptr;
		};

		struct function_ptr
		{
			using type = function_ptr;
		};

		struct member_object_ptr
		{
			using type = member_object_ptr;
		};

		struct object_ptr
		{
			using type = object_ptr;
		};
	}
	
}