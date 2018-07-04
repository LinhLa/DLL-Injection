#pragma once
#include <vector>

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

			template<class Type> struct TCHARType { enum { result = false }; };
			template<> struct TCHARType<::TCHAR> { enum { result = true }; };

			template<class Type> struct CStringType { enum { result = false }; };
			template<> struct CStringType<::CString> { enum { result = true }; };

			template<class U>
			ObjectWrapper(const U* u) :ObjectWrapper()
			{
				if (TCHARType<U>::result && CStringType<T>::result)
					*internalObject = u;
			};

			~ObjectWrapper() { Pool<T>::GetInstance()->Push(*internalObject); }
	};
}
typedef Util::ObjectWrapper<CString, Util::Pool> CStringPtr;
#define POOL_CSTRING() Util::Pool<CString>::GetInstance()