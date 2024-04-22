#pragma once
#include"Utility.hpp"
#include"ICommandBuffer.h"

namespace HARMONY
{
	namespace CORE
	{
		/// @brief シーンObjectの基底クラス
		class SceneBase
		{
			HM_MANUAL_REGISTER_BASE_CLASS_BODY(SceneBase)
		public:
			/// @brief デストラクタ
			virtual ~SceneBase() = default;

			/// @brief シーンの名前を取得する関数
			/// @return シーンの名前
			virtual const TCHAR* GetName() { return TSTR(""); }
			
			/// @brief シーンのGUIDを取得する関数
			/// @return GUID
			virtual const TCHAR* GetGuid() { return TSTR(""); }
			
			/// @brief 更新関数
			virtual void Update() {};

			/// @brief 描画関数
			virtual void Render(const HMArray<ICommandBuffer*>& commandBuffers) {};

			/// @brief このシーンにサブシーンを追加する関数
			/// @param _sceneObject 追加するシーンオブジェクト
			/// @return 成功かどうか
			virtual bool AddSceneObject(SceneBase* shild_scene) { return false; }
		};
	}
}