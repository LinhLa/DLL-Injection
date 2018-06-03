#pragma once
#include "stdafx.h"
#include <algorithm>
#include <vector>
#include <map>
namespace Util
{

	template<class T> class Pool
	{
	private:
		std::vector<T*> m_Pool;
		Pool() :m_Pool(1024)
		{
			ExpandPool(16);
		}
		~Pool()
		{
			for (auto itr = m_Pool.begin(); itr != m_Pool.end(); itr = m_Pool.erase(itr))
			{
				delete *itr;
				*itr = nullptr;
			}
		}
	public:
		static Pool* GetInstance()
		{
			static Pool pInstance;
			return &pInstance;
		}

		void Push(T &t) { m_Pool.push_back(&t); }

		T* Pop()
		{
			T* ret = nullptr;
			if (m_Pool.empty())
			{
				ExpandPool(8);
			}
			ret = m_Pool.back();
			m_Pool.pop_back();
			return ret;
		}

		void ExpandPool(int size)
		{
			while (--size >= 0)
			{
				m_Pool.push_back(new T);
			}
		}
		size_t size() { return m_Pool.size(); }
		size_t capacity() { return m_Pool.capacity(); }
	};

	template<
		class T,
		template<class T> class Pool
	>
		class ObjectWrapper {
		private:
			T* internalObject;
			ObjectWrapper& operator=(const ObjectWrapper&) = delete;
		public:
			T* operator->() { return internalObject; }
			T& operator*() { return *internalObject; }
			ObjectWrapper() { internalObject = Pool<T>::GetInstance()->Pop(); }
			/*template<class U>
			ObjectWrapper(const U* u) :ObjectWrapper() throw {throw std::exception()};*/
			~ObjectWrapper() { Pool<T>::GetInstance()->Push(*internalObject); }
	};

	/*Specialize constructor CString(const TCHAR*)*/
	//template<>	template<> ObjectWrapper<::CString, Pool>::ObjectWrapper(const TCHAR* lpsz)
	//	: ObjectWrapper()
	//{
	//	internalObject->Format(_T("%s"), lpsz);
	//}
	

	template<class T>
	class CWindFactory
	{
	private:
		std::map<int, HWND*> m_MapCWndHwnd;
	protected:
		CWindFactory() {}
		CWindFactory(const CWindFactory&) = delete;
		CWindFactory(CWindFactory&&) = delete;
		~CWindFactory() {}
		void operator=(const CWindFactory&) = delete;
		void operator=(CWindFactory&&) = delete;
	public:
		CWindFactory* GetInstance()
		{
			static CWindFactory instance;
			return &instance;
		}

		void Add(int ID, CWnd* const pCWnd)
		{
			auto itr = m_MapCWndHwnd.find(ID);
			if (itr != m_MapCWndHwnd.end() && *itr->second != NULL)
			{
				throw std::exception();	//ID exist and HWND!=NULL
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
	};

	/*Insert item Tab control*/
	template<class T> void InitItemTabControl(T *pTabCtrl, CWnd *pDialogItem, int tabID, ::CString &title)
	{
		TCITEM tcItem;
		tcItem.mask = TCIF_TEXT | TCIF_PARAM;
		tcItem.pszText = title.GetBuffer();
		tcItem.lParam = (LPARAM)&(*pDialogItem);
		pTabCtrl->InsertItem(tabID, &tcItem);

		CRect rcItem, rcDisplayArea;
		pTabCtrl->GetItemRect(0, &rcItem);
		pTabCtrl->GetClientRect(&rcDisplayArea);
		pDialogItem->SetWindowPos(pTabCtrl, rcItem.left, rcItem.bottom, rcDisplayArea.Width() - 5, rcDisplayArea.Height() - rcItem.Height() - 5, SWP_NOZORDER);
	}

}
typedef Util::ObjectWrapper<CString, Util::Pool> CStringPtr;
#define POOL_CSTRING() Util::Pool<CString>::GetInstance()
