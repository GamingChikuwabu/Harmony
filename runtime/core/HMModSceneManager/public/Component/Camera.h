#pragma once
#include"Behavior.h"
//#include"Eigen/Dense"

namespace HARMONY
{
	namespace CORE
	{
		class Camera : public Behavior
		{
		public:
			Camera();
			~Camera();
			//セッタ
			inline void setFieldOfView(float fov) { _fieldOfView = fov; }
			inline void setAspectRatio(float aspectRatio) { _aspectRatio = aspectRatio; }
			inline void setNearClip(float nearClip) { _nearClip = nearClip; }
			inline void setFarClip(float farClip) { _farClip = farClip; }
			//ゲッタ
			inline float getFieldOfView() const { return _fieldOfView; }
			inline float getAspectRatio() const { return _aspectRatio; }
			inline float getNearClip() const { return _nearClip; }
			inline float getFarClip() const { return _farClip; }

			//mainカメラを取得
			static Camera* getMainCamera() { return _mainCamera; };
		private:
			class IRenderTarget* _rendertarget;
			float _fieldOfView;
			float _aspectRatio;
			float _nearClip;
			float _farClip;
			static inline Camera* _mainCamera;
		};
	}
}