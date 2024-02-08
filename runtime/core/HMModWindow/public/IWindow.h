#pragma once
#include"IModule.h"
#include<iostream>

class IWindow : public IModule
{
public:
    //コンストラクタ
    IWindow()
    :windowWide(0)
    ,windowHeight(0)
    ,windowTitle(L" "){}
    //デストラクタ
    virtual ~IWindow()override {};
    //ウィンドウを作成する関数
    virtual bool MakeWindow(const wchar_t* _title, uint32_t width, uint32_t height) = 0;
    //ウィンドウのハンドルを返す関数
    virtual void* GetWindowHandle(const wchar_t* title) = 0;
    //メッセージ処理
    virtual bool ProcessMessage() = 0;
    //ウィンドウのサイズを設定する関数
    virtual void SetWindowSize(unsigned int w, unsigned int h) { windowWide = w; windowHeight = h; }
    //ウィンドウの幅を取得
    virtual unsigned int GetWindowWidth(const wchar_t* title) = 0;
    //ウィンドウの高さを取得
    virtual unsigned int GetWindowHeight(const wchar_t* title) = 0;
    //ウィンドウのタイトルを設定する関数
    virtual void SetWindowTitle(const wchar_t* title) { windowTitle = title; }
    //ウィンドウタイトルを取得
    virtual const wchar_t* GetWindowTitle() { return windowTitle;}
private:
    unsigned int windowWide;
    unsigned int windowHeight;
    const wchar_t* windowTitle;
};