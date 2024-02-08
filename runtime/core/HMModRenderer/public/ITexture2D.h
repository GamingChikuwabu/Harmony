#pragma once
#include"IRenderingAPI.h"
#include"GraphicsPrimitives.h"

/**
 * @brief 2Dテクスチャのインターフェースクラス
 */
class ITexture2D
{
public:
    ITexture2D() {}
    virtual ~ITexture2D() {}

    // 空のテクスチャの生成
    virtual void CreateEmptyTexture(int width, int height, FORMAT format,TEXTUREUSE useflag) = 0;

    // レンダーターゲットとしての設定
    virtual void SetupAsRenderTarget() = 0;
};