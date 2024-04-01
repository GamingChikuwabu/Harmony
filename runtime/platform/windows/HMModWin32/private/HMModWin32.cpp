#include"HMModWin32.h"
#include"GameLoopManager.h"
#include"EventManager.h"

namespace HARMONY
{
	namespace PLATFORM
	{
		namespace WINDOWS
		{
			class SubWindow
			{
			public:
				inline LRESULT CALLBACK WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
				{
					switch (uMsg)
					{
					case WM_DESTROY:
					{
						if (numwindow == 1)
						{
							PostQuitMessage(0);
						}
						numwindow--;
					}
					break;
					case WM_KEYDOWN:
						if (LOWORD(wParam) == VK_ESCAPE)
						{
							PostMessage(hWnd, WM_CLOSE, wParam, lParam);
						}
						break;
					case WM_SIZE:
						if (wParam == SIZE_MINIMIZED)
						{
							// ウィンドウが最小化されたときの処理
							// ここでウィンドウの新しい幅と高さを0に設定するか、または意味のある値に設定
							uint32_t newWidth = 0; 
							uint32_t newHeight = 0; 

							// "WindowResize" イベントを発行
							EventManager::GetEvent<void*, uint32_t, uint32_t>(TEXT("WindowResize")).Broadcast(hWnd, newWidth, newHeight); 
						}
						else
						{
							// ウィンドウが最小化されていない場合のリサイズ処理
							// ここでウィンドウの新しい幅と高さを lParam から取得
							uint32_t newWidth = LOWORD(lParam); 
							uint32_t newHeight = HIWORD(lParam); 

							// "WindowResize" イベントを発行
							EventManager::GetEvent<void*, uint32_t, uint32_t>(TEXT("WindowResize")).Broadcast(hWnd, newWidth, newHeight); 
						}
						break;
					default:
					{ /* DO_NOTHING */ }
					break;
					}

					return DefWindowProc(this->hWnd, uMsg, wParam, lParam);
				}
				HWND hWnd;
				static inline int numwindow = 0;

			};

			//モジュールを登録する
			RegisterModuleClass(HMModWin32);

			HMModWin32::HMModWin32()
			{

			}

			HMModWin32::~HMModWin32()
			{
				
			}

			bool HMModWin32::ProcessMessage()
			{
				MSG msg = {};

				while (WM_QUIT != msg.message &&
					PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) == TRUE)
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}


				if (WM_QUIT == msg.message)
				{
					return false;
				}
				return true;
			}

			void HMModWin32::Terminate()
			{

			}

			bool HMModWin32::MakeWindow(const wchar_t* _title, uint32_t width, uint32_t height)
			{
				WNDCLASSEX wcex;
				wcex.cbSize = sizeof(WNDCLASSEX);
				wcex.style = CS_HREDRAW | CS_VREDRAW;
				wcex.lpfnWndProc = defWndProc;
				wcex.cbClsExtra = 0;
				wcex.cbWndExtra = 0;
				wcex.hInstance = GetModuleHandle(NULL);
				wcex.hIcon = NULL;
				wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
				wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
				wcex.lpszMenuName = NULL;
				wcex.lpszClassName = _title;
				wcex.hIconSm = NULL;

				if (!RegisterClassEx(&wcex))
				{
					return false;
				}

				m_windowArray[_title] = std::make_unique<SubWindow>();

				m_windowArray[_title]->hWnd = CreateWindowEx(
					0,                                  // Optional window styles.
					_title,                             // Window class
					_title,                             // Window text
					WS_VISIBLE | WS_OVERLAPPEDWINDOW,   // Window style. Make it a popup window and visible.
					CW_USEDEFAULT, CW_USEDEFAULT, width, height,
					NULL,                               // Parent window HWND
					NULL,                // Menu
					GetModuleHandle(NULL),           // Instance handle
					NULL                 // Additional application data
				);

				if (m_windowArray[_title]->hWnd == NULL) {
					DWORD errorMessageID = ::GetLastError();
					LPSTR messageBuffer = nullptr;
					size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
						NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
					std::string message(messageBuffer, size);
					// Free the buffer.
					LocalFree(messageBuffer);
					return false;
				}
				SubWindow::numwindow++;

				m_hWndarray[m_windowArray[_title]->hWnd] = std::bind(&SubWindow::WndProc, m_windowArray[_title].get(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
				return true;
			}

			void* HMModWin32::GetWindowHandle(const wchar_t* title)
			{
				return (void*)m_windowArray[title]->hWnd;
			}

			bool HMModWin32::AwakeInitialize()
			{
				return true;
			}

			void HMModWin32::Update()
			{
				if (!ProcessMessage())
				{
					GameLoopManager::Stop();
				}
			}

			unsigned int HMModWin32::GetWindowWidth(const wchar_t* title)
			{
				RECT rt;
				GetClientRect(m_windowArray[title]->hWnd, &rt);
				uint32_t w = rt.right - rt.left;
				return w;
			}

			unsigned int HMModWin32::GetWindowHeight(const wchar_t* title)
			{
				RECT rt; 
				GetClientRect(m_windowArray[title]->hWnd, &rt); 
				uint32_t h = rt.bottom - rt.top;
				return h;
			}

			LRESULT HMModWin32::defWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
			{
				auto it = m_hWndarray.find(hWnd);
				if (it != m_hWndarray.end()) {
					return it->second(uMsg, wParam, lParam);
				}
				return DefWindowProc(hWnd, uMsg, wParam, lParam);
			}
		}
	}
}