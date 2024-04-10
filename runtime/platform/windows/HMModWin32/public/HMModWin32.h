#pragma once
#include"ModuleManager.h"
#include"IWindow.h"
#include<map>
#include<functional>
#include<memory>
#include<string>
#include<Windows.h>

namespace HARMONY
{
	namespace PLATFORM
	{
		namespace WINDOWS
		{
			class HMModWin32 :public IWindow
			{
			public:
				HMModWin32();
				~HMModWin32();
				bool ProcessMessage() override;
				void Terminate()override;
				bool MakeWindow(const wchar_t* _title, uint32_t width, uint32_t height)override;
				void* GetWindowHandle(const wchar_t* title)override;
				bool AwakeInitialize()override;
				void Update()override;
				//ウィンドウの幅を取得
				unsigned int GetWindowWidth(const wchar_t* title)override;
				//ウィンドウの高さを取得
				unsigned int GetWindowHeight(const wchar_t* title)override;
			private:
				static LRESULT CALLBACK defWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
				static inline std::map<HWND, std::function<LRESULT(UINT, WPARAM, LPARAM)>> m_hWndarray;
				std::map<std::wstring, std::unique_ptr<class SubWindow>> m_windowArray;
			};
		}
	}
}