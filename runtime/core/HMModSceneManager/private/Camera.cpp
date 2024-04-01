#include"Camera.h"
#include"GameObject.h"

namespace HARMONY
{
	namespace CORE
	{
		Camera::Camera() 
		: _aspectRatio(16.0f / 9.0f),  // アスペクト比
		_fieldOfView(60.0f),  // 視野角 (デフォルト値は60度)
		_nearClip(0.1f),  // 近クリップ面 (デフォルト値は0.1)
		_farClip(1000.0f)  // 遠クリップ面 (デフォルト値は1000)
		{
			if (!_mainCamera)
			{
				_mainCamera = this;
			}
		}
		Camera::~Camera()
		{
			if (_mainCamera == this)  // このカメラがメインカメラであれば
			{
				_mainCamera = nullptr;  // メインカメラの参照を解除
			}
		}
		//Eigen::Matrix4f Camera::getViewMatrix()
		//{
		//	Eigen::Matrix4f rotationMatrix = Eigen::Matrix4f::Identity();  // 4x4単位行列を作成
		//	Eigen::Matrix3f rot3x3 = _gameObject->getTransform()->getRotation().toRotationMatrix();
		//	rotationMatrix.block<3, 3>(0, 0) = rot3x3;  // 4x4行列の左上の3x3部分に3x3回転行列を配置
		//	Eigen::Matrix4f translationMatrix = Eigen::Matrix4f::Identity();
		//	translationMatrix.block<3, 1>(0, 3) = -_gameObject->getTransform()->getPosition(); // 逆向きに平行移動
		//	_viewMatrix = translationMatrix * rotationMatrix; // 平行移動後に回転
		//	return _viewMatrix;
		//}

		//Eigen::Matrix4f Camera::getProjectionMatrix()
		//{
		//	float tanHalfFOV = tanf(_fieldOfView / 2.0f);
		//	_projectionMatrix = Eigen::Matrix4f::Zero();

		//	_projectionMatrix(0, 0) = 1.0f / (tanHalfFOV * _aspectRatio); // X軸のスケーリング 
		//	_projectionMatrix(1, 1) = 1.0f / tanHalfFOV; // Y軸のスケーリング 
		//	_projectionMatrix(2, 2) = _farClip / (_farClip - _nearClip); // Z軸のスケーリング 
		//	_projectionMatrix(2, 3) = -(_farClip * _nearClip) / (_farClip - _nearClip); // Z軸の移動 
		//	_projectionMatrix(3, 2) = 1.0f; // パースペクティブ分割 
		//	return _projectionMatrix;
		//}
	}
}