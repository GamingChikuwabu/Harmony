#include"HMModLevelEditor.h"
#include"LogManager.h"
#include"HMModIPCManager.h"

namespace HARMONY
{
	namespace EDITOR
	{
		enum CommandType {
			GET_LEVEL_EDITOR_HWND = 2,
			RESIZE_COMMAND = 3
		};

		struct LevelEditorHWNDData {
			HWND parentWindow;
		};

		struct ResizeData {
			uint32_t width;
			uint32_t height;
		};

		struct ReceivedData {
			union {
				LevelEditorHWNDData levelEditorHWNDData;
				ResizeData resizeData;
			};
		};

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
            IPC->RegisterCallBack(IPC->GetCommandInfo("LevelEditorMakeChild").id, std::bind(&HMModLevelEditor::handleGetLevelEditorWindowHandle, this, std::placeholders::_1));
			return true;
		}

		void HMModLevelEditor::Terminate()
		{

		}

		void HMModLevelEditor::handleGetLevelEditorWindowHandle(const std::vector<char>& data)
		{
            ReceivedData receive_data;
            memcpy(&receive_data, data.data(), sizeof(LevelEditorHWNDData));
            RECT rec;
            HWND myWindow = (HWND)_window->GetWindowHandle(L"Harmony");
            if (data.size() < sizeof(receive_data.levelEditorHWNDData.parentWindow)) {
                HM_DEBUG_LOG("red",TSTR("受信データが不足しています。必要: %zu, 実際: %zu\n"), (long long)receive_data.levelEditorHWNDData.parentWindow, data.size());
                return;
            }

            if (!receive_data.levelEditorHWNDData.parentWindow || !IsWindow(receive_data.levelEditorHWNDData.parentWindow)) {
                HM_DEBUG_LOG("red", TSTR("無効なウィンドウハンドルです"));
                return;
            }

            if (!GetWindowRect(receive_data.levelEditorHWNDData.parentWindow, &rec)) {
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
                style = (style & ~WS_OVERLAPPEDWINDOW) | WS_CHILD; // 例えば、WS_CHILDスタイルを設定

                // ウィンドウスタイルを更新
                if (SetWindowLong(myWindow, GWL_STYLE, style) == 0) {
                    // SetWindowLongのエラーハンドリング
                    HM_DEBUG_LOG("red", TSTR("SetWindowLongに失敗しました"));
                    return;
                }

                // hwndChildをhwndParentの子ウィンドウに設定
                if (SetParent(myWindow, receive_data.levelEditorHWNDData.parentWindow) == NULL) {
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