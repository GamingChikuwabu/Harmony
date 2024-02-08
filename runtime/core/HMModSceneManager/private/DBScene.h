#pragma once
#include"StaticScene.h"


namespace HARMONY
{
	namespace CORE
	{
		class DBScene : public StaticScene
		{
		public:
			DBScene();
			~DBScene();
			/// @brief データベースの更新処理
			void Update()override;
			/// @brief データベースなのでオーバーライドしてレンダリングの機能をなくす
			/// @param commandBuffers 
			void Render(const std::vector<ICommandBuffer*>& commandBuffers)override;
		protected:

		};
	}
}