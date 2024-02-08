#pragma once
/**
 * @brief テクスチャの使用方法を示す列挙型
 */
enum class TEXTUREUSE
{
    COLOR, ///< カラーテクスチャとして使用
    DEPTH, ///< 深度テクスチャとして使用
};

enum class FORMAT
{
    FORMAT_B8G8R8A8_UNORM = 0,
    FORMAT_B8G8R8A8_SRGB,
    FORMAT_R8G8B8A8_UNORM,
    FORMAT_R8G8B8A8_SRGB,
    FORMAT_D32_FLOAT, // デプスバッファのフォーマット
    FORMAT_BC1_UNORM, // 圧縮フォーマット BC1
    FORMAT_BC3_UNORM, // 圧縮フォーマット BC3
    FORMAT_MAX
};

/**
 * @brief 2Dテクスチャの作成情報を保持する構造体
 */
//struct KsCreateTexture2DInfo
//{
//    unsigned int width;                         ///< テクスチャの横幅
//    unsigned int height;                        ///< テクスチャの立幅
//    KSFORMAT textureFormat;                     ///< テクスチャのフォーマット
//    KSTEXTUREUSE textureUse;                    ///< テクスチャの使用方法
//    unsigned int mipLevel;                      ///< ミップレベル
//    std::weak_ptr<ISwapchain> pSwapchain;       ///< スワップチェインのポインタ（スワップチェインの描画領域のテクスチャを使って初期化する場合のみポインタが必要）
//    std::weak_ptr<IRenderDevice>* pRenderDevice;///< レンダリングデバイスのポインタ
//};
//
//
//struct KsCreateRendertargetInfo
//{
//	unsigned int    width;
//	unsigned int    height;
//    KSFORMAT        format;
//    void*           texture;
//};