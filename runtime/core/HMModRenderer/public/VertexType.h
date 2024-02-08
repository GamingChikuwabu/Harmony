#pragma once
#include<Eigen/Dense>

struct StaticMeshVertex_1
{
	Eigen::Vector3<float> pos;
	Eigen::Vector3<float> normal;
	Eigen::Vector3<float> texcode;
};

struct SkeletalMeshVertex
{
    Eigen::Vector3<float> pos;       // 位置
    Eigen::Vector3<float> normal;    // 法線
    Eigen::Vector2<float> texCoord;  // テクスチャ座標
    Eigen::Vector4<int> boneIndices; // ボーンインデックス
    Eigen::Vector4<float> weights;   // ボーンのウェイト
};