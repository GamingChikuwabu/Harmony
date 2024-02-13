#pragma once

/// @brief クラスのメンバ変数へのアクセスレベル
enum class ACCESS_LEVEL
{
	/// @brief public access
	LEVEL_PUBLIC = 0,
	/// @brief protected access
	LEVEL_PROTECTED,
	/// @brief private access 
	LEVEL_PRIVATE,
	/// @brief readonly access
	LEVEL_READONLY,
	/// @brief num access
	MAX
};