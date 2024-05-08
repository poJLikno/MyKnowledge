#ifndef WINDOWLIB_WND_LIST_H
#define WINDOWLIB_WND_LIST_H

#include <iostream>
#include <stdlib.h>

template<class T>
class WndList {
private:
	int _wnd_count = 0;
	T **_wnd_list = nullptr;

public:
    WndList() = default;
    ~WndList();

    T *operator[](int i);

    int GetCount();
	void Append(T *wnd);
};

template<class T>
inline WndList<T>::~WndList() {
    if (_wnd_list) {
        for (int i = 0; i < _wnd_count; ++i) {
            _wnd_list[i] = nullptr;
        }

        free(_wnd_list);
        _wnd_list = nullptr;
    }
}

template<class T>
inline T *WndList<T>::operator[](int i) {
    return _wnd_list[i];
}

template<class T>
inline int WndList<T>::GetCount() {
    return _wnd_count;
}

template<class T>
inline void WndList<T>::Append(T *wnd) {
    if (!_wnd_count) {
        _wnd_list = (T **)malloc(++_wnd_count * sizeof(T *));
    }
    else if (_wnd_count && _wnd_list) {
        _wnd_list = (T **)realloc(_wnd_list, ++_wnd_count * sizeof(T **));
    }

    _wnd_list[_wnd_count - 1] = wnd;
}

#endif
