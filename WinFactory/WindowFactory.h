#pragma once
#include "stdafx.h"
#include <map>
#include <list>
#include <thread>

#ifdef _USRDLL
#define WINF_API __declspec(dllexport)
#define WINF_EXTERN
#else
#define WINF_API __declspec(dllimport)
#define WINF_EXTERN extern
#endif

#ifdef __cplusplus
extern "C" {
#endif

	WINF_EXTERN template class WINF_API std::map<int, HWND*>;
	WINF_EXTERN template class WINF_API std::list<size_t>;
	namespace Util
	{

		class WINF_API CWindID
		{
		protected:
			static size_t sid;
			static std::list<size_t> unAssignedlist;
			size_t m_id;
			CWindID();
			~CWindID();
		};

		class WINF_API CWindFactory
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
			void Remove(int ID);
			CWnd* const Get(int ID);
		};

	}
	typedef Util::CWindFactory MyAppFactory;

	void WINF_API FunctionNeedToHook();
	void WINF_API *GetWindFactory();

#ifdef __cplusplus
}
#endif