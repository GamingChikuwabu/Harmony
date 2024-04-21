#include"HMModLevelEditor.h"
#include"HMModIPCManager.h"
#include"Utility.hpp"

namespace HARMONY
{
	namespace EDITOR
	{
		struct LevelEditorHWNDData {
            HM_MANUAL_REGISTER_BASE_CLASS_BODY(LevelEditorHWNDData)
			HWND parentWindow = 0;
		};

        HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES(LevelEditorHWNDData)
            HM_ADD_PROPERTY_INT64(LevelEditorHWNDData, parentWindow)
        HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES_END(LevelEditorHWNDData)

        RegisterModuleClass(HMModLevelEditor)

		HMModLevelEditor::HMModLevelEditor()
		{

		}

		HMModLevelEditor::~HMModLevelEditor()
		{

		}

		bool HMModLevelEditor::AwakeInitialize()
		{

			return true;
		}

		bool HMModLevelEditor::Initialize()
		{
			_window = ModuleManager::GetModule<IWindow>();
			HM_ASSERT(_window != nullptr, "windowの取得に失敗","");
            //IPCモジュールを取得してコールバック関数を登録
            auto IPC = ModuleManager::GetModule<HMModIPCManager>();
            int32_t command = IPC->GetCommandInfo(TSTR("LevelEditorMakeChild"))._id;
            IPC->RegisterCallBack(IPC->GetCommandInfo(TSTR("LevelEditorMakeChild"))._id, std::bind(&HMModLevelEditor::handleGetLevelEditorWindowHandle, this, std::placeholders::_1));
			return true;
		}

		void HMModLevelEditor::Terminate()
		{

		}

		void HMModLevelEditor::handleGetLevelEditorWindowHandle(const TCHAR* data)
		{
            LevelEditorHWNDData windowdata;
            SERIALIZER::IJsonArchiver ij(data);
            ij& windowdata;
            RECT rec;
            HWND myWindow = (HWND)_window->GetWindowHandle(L"Harmony");
            
            if (!GetWindowRect(windowdata.parentWindow, &rec)) {
                // GetWindowRectのエラーハンドリング
                HM_DEBUG_LOG("red", TSTR("GetWindowRectに失敗しました"));
                return;
            }

            // hwndChildのウィンドウスタイルを取得
            LONG style = GetWindowLong(myWindow, GWL_STYLE);
            if (style == 0) {
                // GetWindowLongのエラーハンドリング
                HM_DEBUG_LOG("red", TSTR("GetWindowLongに失敗しました"));
                return;
            }

            // 子ウィンドウとして設定する必要があるかチェック
            if (style != WS_CHILD) {
                style = (style & ~WS_OVERLAPPEDWINDOW) | WS_CHILD; 

                // ウィンドウスタイルを更新
                if (SetWindowLong(myWindow, GWL_STYLE, style) == 0) {
                    // SetWindowLongのエラーハンドリング
                    HM_DEBUG_LOG("red", TSTR("SetWindowLongに失敗しました"));
                    return;
                }

                // hwndChildをhwndParentの子ウィンドウに設定
                if (SetParent(myWindow, windowdata.parentWindow) == NULL) {
                    // SetParentのエラーハンドリング
                    HM_DEBUG_LOG("red", TSTR("SetParentに失敗しました"));
                    return;
                }
            }

            HM_DEBUG_LOG("white", TSTR("ウィンドウのリサイズ:幅:%d,高さ:%d"), static_cast<int>(rec.right - rec.left), static_cast<int>(rec.bottom - rec.top))

            // ウィンドウの移動とサイズ変更
            if (!MoveWindow(myWindow, 0, 0, rec.right - rec.left, rec.bottom - rec.top, TRUE)) {
                // MoveWindowのエラーハンドリング
                HM_DEBUG_LOG("red", TSTR("MoveWindowに失敗しました"));
                return;
            }
		}
	}
}