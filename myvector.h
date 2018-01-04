#pragma once

#include <cstring>

template <typename _T>
class MyVector {
public:
  enum {
    _mem_block_size = 2   //items count for size of memory page;
  };
  
protected:
  _T   * m_ptr;
  size_t m_size;
  size_t m_capacity;
  
public:
  MyVector(_T *ptr=NULL) : m_ptr(ptr), m_size(0), m_capacity(0) {}
  ~MyVector();
  
  void destroy();
  void resize(size_t newsize);
  void push_back(const _T& val);
  size_t size() const { return m_size; }
  
  _T& at(size_t i) const;
  _T& operator [](size_t i) const { return at(i); }
};

template <typename _T>
MyVector<_T>::~MyVector() {
  destroy();
}

template <typename _T>
void MyVector<_T>::resize(size_t newsize) {
  if(newsize <= m_capacity)
    return;
  const size_t block_size = _mem_block_size - newsize % _mem_block_size;
  newsize += block_size;
  _T *newptr = new _T[newsize];
  for(size_t i = 0; i < m_size; ++i)
    newptr[i] = m_ptr[i];
  size_t size = m_size;
  destroy();
  m_size = size;
  /*if(m_size != 0) {
    memcpy(newptr, m_ptr, m_size * sizeof(_T));
    memset(m_ptr, 0, m_size * sizeof(_T));
    delete [] m_ptr;
  }*/
  m_ptr = newptr;
  m_capacity = newsize;
}

template <typename _T>
void MyVector<_T>::destroy() {
  if(m_ptr != NULL) {
  	delete [] m_ptr;
  	m_ptr = NULL;
  }
  m_size = 0;
  m_capacity = 0;
}

template <typename _T>
_T&
MyVector<_T>::at(size_t i) const {
  if(m_ptr == NULL || i >= m_capacity) {
  	static _T t;
  	return t;
  }
  return m_ptr[i];
}

template <typename _T>
void
MyVector<_T>::push_back(const _T& val) {
  if(m_capacity <= m_size)
  	resize(m_size+1);

  at(m_size) = val;
  m_size++;
}
