#pragma once
#include <iostream>
#include <string>
#include <vector>
#include<memory>
#include<list>
#include"GameObject.h"
#include"ICommandBuffer.h"

namespace HARMONY
{
	namespace CORE
	{
		/// @brief シーンObjectの基底クラス
		class SceneBase
		{
		public:
			/// @brief デストラクタ
			virtual ~SceneBase() = default;

			/// @brief シーンの名前を取得する関数
			/// @return シーンの名前
			virtual const char* GetName() = 0;
			
			/// @brief シーンのGUIDを取得する関数
			/// @return GUID
			virtual const char* GetGuid() = 0;
			
			/// @brief 更新関数
			virtual void Update() = 0;

			/// @brief 描画関数
			virtual void Render(const std::vector<ICommandBuffer*>& commandBuffers) = 0;

			/// @brief このシーンにサブシーンを追加する関数
			/// @param _sceneObject 追加するシーンオブジェクト
			/// @return 成功かどうか
			virtual bool AddSceneObject(std::shared_ptr<SceneBase> shild_scene) = 0;

			virtual std::shared_ptr<SceneBase> FindSceneFromGUID(const char* guid) = 0;
		};
	}
}