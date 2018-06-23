#pragma once
#include "stdafx.h"
#include <map>
#include <thread>
#ifdef _USRDLL
#define WINFACTORY_API __declspec(dllexport)
#define WINFACTORY_EXTERN
#else
#define WINFACTORY_API __declspec(dllimport)
#define WINFACTORY_EXTERN extern
#endif
WINFACTORY_EXTERN template class WINFACTORY_API std::map<int, HWND*>;
namespace Util
{
	class WINFACTORY_API CWindFactory
	{
	private:
		std::map<int, HWND*> m_MapCWndHwnd;
		WNDCLASS m_WndClass;
		HWND m_Hwnd;
		MSG m_Msg;
		const TCHAR* m_WndClassName = _T("CWindFactory");

	protected:
		CWindFactory();
		CWindFactory(const CWindFactory&) = delete;
		CWindFactory(CWindFactory&&) = delete;
		~CWindFactory();
		void operator=(const CWindFactory&) = delete;
		void operator=(CWindFactory&&) = delete;
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
		void MessageLooping();
		void Run();
	public:
		static CWindFactory* GetInstance();
		const HWND& GetHandle() const;
		void Add(int ID, CWnd* const pCWnd);
		CWnd* const Get(int ID);
	};

}
typedef Util::CWindFactory MyAppFactory;
extern "C"
{
	void WINFACTORY_API FunctionNeedToHook();
}