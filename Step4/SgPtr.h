#pragma once
#include "SgObject.h"

template <class T> class CSgPtr
{
public:
	CSgPtr() {m_ptr = NULL;}
	CSgPtr(T *p_ptr) {m_ptr = p_ptr; if(m_ptr) m_ptr->IncRef();}
	CSgPtr(CSgPtr &p_ptr) {m_ptr=p_ptr.m_ptr; if(m_ptr) m_ptr->IncRef();}
	~CSgPtr() {Clear();}
	void Clear() {if(m_ptr) {m_ptr->DecRef(); m_ptr = NULL;}}
	T *operator=(T *t) {if (t) t->IncRef(); Clear(); m_ptr = t; return m_ptr;}
	T *operator=(CSgPtr &t) {if (t.m_ptr) t.m_ptr->IncRef();
	Clear(); m_ptr = t.m_ptr; return m_ptr;}
	operator T *() const {return m_ptr;}
	T *operator->() const {return m_ptr;}
private:
	T *m_ptr;
};
