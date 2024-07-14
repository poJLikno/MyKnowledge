#ifndef CALLBACK_MANAGER_H
#define CALLBACK_MANAGER_H

#include <string.h>
#include <vector>

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

    virtual void Call(void *params) override {
        _callback(params);
    }
};

class Callback {
private:
    ICall *_callback = nullptr;

public:
    Callback() = default;
    ~Callback() {
        if (_callback) delete _callback;
        _callback = nullptr;
    }

    // Delete copy semantic
    Callback(const Callback &) = delete;
    Callback &operator=(const Callback &) = delete;

    // Init move semantic
    Callback(Callback &&obj) noexcept {
        _callback = obj._callback;
        obj._callback = nullptr;
    }
    Callback &operator=(Callback &&obj) noexcept {
        _callback = obj._callback;
        obj._callback = nullptr;

        return *this;
    }

    // Init callback constructors
    template<class T>
    Callback(T callback) {
        if (_callback) delete _callback;
        _callback = new CCall(callback);
    }
    template<class T>
    Callback &operator=(T callback) {
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
    static T &GetCallbackParams(void *params) {
        return *((T *)params);
    }
};

class CallbackManager {
protected:
    std::vector<char *> _callbacks_names = std::vector<char *>();
    std::vector<Callback> _callbacks = std::vector<Callback>();

    CallbackManager() = default;

public:
    virtual ~CallbackManager() = default;

    template<class T>
    void AddCallback(const char *name, T callback) {
        _callbacks_names.push_back((char *)name);
        _callbacks.push_back(callback);
    }

    virtual void operator()(const char* name, void *params) final {
        for (int i = 0; i < _callbacks_names.size(); ++i) {
            if (memcmp(name, _callbacks_names[i], strlen(name)) == 0) {
                _callbacks[i](params);
                break;
            }
        }
    }

    virtual bool HasCallback(const char *name) final {
        for (int i = 0; i < _callbacks_names.size(); ++i) {
            if (memcmp(name, _callbacks_names[i], strlen(name)) == 0) {
                return _callbacks[i].HasCallback();
            }
        }
        return false;
    }
};

#endif
