#pragma once
#include <algorithm>
#include <map>
#include <thread>
namespace Util
{

	template<class T>
	class CWindFactory
	{
	private:
		std::map<int, HWND*> m_MapCWndHwnd;
		WNDCLASS m_WndClass;
		HWND m_Hwnd;
		MSG m_Msg;
		const TCHAR* m_WndClassName = _T("CWindFactory");

	protected:
		CWindFactory()
		{
			m_WndClass.style = 0; // Class style
			m_WndClass.lpfnWndProc = (WNDPROC)WndProc; // Window procedure address
			m_WndClass.cbClsExtra = 0; // Class extra bytes
			m_WndClass.cbWndExtra = 0; // Window extra bytes
			m_WndClass.hInstance = AfxGetInstanceHandle(); // Instance handle
			m_WndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO); // Icon handle
			m_WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // Cursor handle
			m_WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Background color
			m_WndClass.lpszMenuName = NULL; // Menu name
			m_WndClass.lpszClassName = m_WndClassName; // WNDCLASS name

			RegisterClass(&m_WndClass);

			m_Hwnd = CreateWindow(
				m_WndClassName, // WNDCLASS name
				_T(""), // Window title
				WS_OVERLAPPEDWINDOW, // Window style
				CW_USEDEFAULT, // Horizontal position
				CW_USEDEFAULT, // Vertical position
				CW_USEDEFAULT, // Initial width
				CW_USEDEFAULT, // Initial height
				HWND_MESSAGE, // HWND_MESSAGE for Window message only
				NULL, // Menu handle
				AfxGetInstanceHandle(), // Application's instance handle
				NULL // Window-creation data
			);
		}
		CWindFactory(const CWindFactory&) = delete;
		CWindFactory(CWindFactory&&) = delete;

		~CWindFactory() {
			UnregisterClass(m_WndClassName, AfxGetInstanceHandle());
		}

		void operator=(const CWindFactory&) = delete;
		void operator=(CWindFactory&&) = delete;

		static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message) {
			case WM_USER + 1:
				AfxMessageBox(_T("WM_USER + 1 Message"), MB_OK, 0);
				return TRUE;
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
			}
			return DefWindowProc(hwnd, message, wParam, lParam);
		}

		void MessageLooping()
		{
			while (GetMessage(&m_Msg, NULL, 0, 0)) {
				TranslateMessage(&m_Msg);
				DispatchMessage(&m_Msg);
			}
		}
	public:
		static CWindFactory* GetInstance()
		{
			static CWindFactory instance;
			return &instance;
		}
		const HWND& GetHandle() const
		{
			return this->m_Hwnd;
		}

		void Add(int ID, CWnd* const pCWnd)
		{
			auto itr = m_MapCWndHwnd.find(ID);
			if (itr != m_MapCWndHwnd.end() && *itr->second != NULL)
			{
				throw std::exception("ID exist and HWND!=NULL");
			}
			else
			{
				m_MapCWndHwnd[ID] = &pCWnd->m_hWnd;
			}
		}

		CWnd* const Get(int ID)
		{
			CWnd *pResult = NULL;
			auto itr = m_MapCWndHwnd.find(ID);
			if (itr != m_MapCWndHwnd.end() && *itr->second != NULL)
			{
				pCWnd = CWnd::FromHandle(*itr->second);
			}
			return pResult;
		}
		void Run()
		{
			std::thread t(&CWindFactory::MessageLooping, this);
			t.detach();
		}
	};

}
class CMyAppDlg;
typedef Util::CWindFactory<CMyAppDlg> MyAppFactory;