#ifndef WND_CALLBACK_H
#define WND_CALLBACK_H

// Do callback functions
class ICall {
public:
	virtual void Call(void *) = 0;
	virtual ~ICall() {}
};

template<class T>
class CCall : public ICall {
private:
	T _callback;

public:
	CCall(T callback) : _callback(callback) {}

	virtual void Call(void *params = nullptr) override {
		_callback(params);
	}
};

class WndCallback {
private:
	ICall *_callback = nullptr;

public:
	WndCallback() = default;
	~WndCallback() {
		if (_callback) delete _callback;
		_callback = nullptr;
	}

	// Delete copy semantic
	WndCallback(const WndCallback &) = delete;
	WndCallback &operator=(const WndCallback &) = delete;

	// Init move semantic
	WndCallback(WndCallback &&obj) noexcept {
		_callback = obj._callback;
		obj._callback = nullptr;
	}
	WndCallback &operator=(WndCallback &&obj) noexcept {
		_callback = obj._callback;
		obj._callback = nullptr;

		return *this;
	}

	// Init callback constructors
	template<class T>
	WndCallback(T callback) {
		if (_callback) delete _callback;
		_callback = new CCall(callback);
	}
	template<class T>
	WndCallback &operator=(T callback) {
		if (_callback) delete _callback;
		_callback = new CCall(callback);

		return *this;
	}

	// Call callback
	void operator()(void *params) {
		_callback->Call(params);
	}

	// Check callback
	bool HasCallback() {
		return (_callback ? true : false);
	}

	template<class T>
	static T &GetCallObject(void *param);
};

class CallbackWindow {
protected:
	WndCallback *_callbacks = nullptr;

	CallbackWindow(const int &count) {
		if (_callbacks) delete _callbacks;
		_callbacks = new WndCallback[count];
	}

public:
	virtual ~CallbackWindow() {
		if (_callbacks) delete[] _callbacks;
		_callbacks = nullptr;
	}

	virtual void RunCallback(const int &index) final {
		if (_callbacks[index].HasCallback())
			_callbacks[index]((void *)this);
	}
};

template<class T>
inline T &WndCallback::GetCallObject(void *param) {
	return (T &)(*(dynamic_cast<T *>((CallbackWindow *)param)));
}

#endif
