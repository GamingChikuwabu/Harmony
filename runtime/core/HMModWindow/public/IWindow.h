#pragma once
#include"Utility.hpp"

class IWindow : public HARMONY::IModule
{
public:
    //コンストラクタ
    IWindow()
    :windowWide(0)
    ,windowHeight(0)
    ,windowTitle(TSTR("")) {}
    //デストラクタ
    virtual ~IWindow()override {};
    //ウィンドウを作成する関数
    virtual bool MakeWindow(const TCHAR* _title, uint32_t width, uint32_t height) = 0;
    //ウィンドウのハンドルを返す関数
    virtual void* GetWindowHandle(const TCHAR* title) = 0;
    //メッセージ処理
    virtual bool ProcessMessage() = 0;
    //ウィンドウのサイズを設定する関数
    virtual void SetWindowSize(uint32_t w, uint32_t h) { windowWide = w; windowHeight = h; }
    //ウィンドウの幅を取得
    virtual uint32_t GetWindowWidth(const TCHAR* title) = 0;
    //ウィンドウの高さを取得
    virtual uint32_t GetWindowHeight(const TCHAR* title) = 0;
    //ウィンドウのタイトルを設定する関数
    virtual void SetWindowTitle(const TCHAR* title) { windowTitle = title; }
    //ウィンドウタイトルを取得
    virtual const TCHAR* GetWindowTitle() { return windowTitle;}
private:
    uint32_t windowWide;
    uint32_t windowHeight;
    const TCHAR* windowTitle;
};