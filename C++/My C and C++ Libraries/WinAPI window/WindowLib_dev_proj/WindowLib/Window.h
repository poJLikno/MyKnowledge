#ifndef WINDOWLIB_WINDOW_H
#define WINDOWLIB_WINDOW_H

#define WINDOWLIB_VERSION "v1.1"

#include "WndList.h"
#include "Button.h"
#include "ComboBox.h"
#include "Edit.h"
#include "Label.h"
#include "Menu.h"

#ifdef WINDOWLIB_NO_CONSOLE
#pragma comment(linker, "/subsystem:WINDOWS")
#endif
#pragma comment(linker, "/entry:mainCRTStartup")

#ifndef WINDOWLIB_NO_MANIFEST
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

#ifndef HINST_THISCOMPONENT
extern "C" IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

class Window : public WndBase, public CallbackManager {
private:
    // Window variables
    wchar_t *_w_class_name = nullptr;
    MSG _msg = { 0 };
    HFONT _normal_font = { 0 };
    bool _ctrls_dlg_msg_flag = false;

    // All exist windows
    static WndList<Window> _wnd_list;
    // All windows pos/size variables
    static WndList<WndPairValue> _wnd_pos_list;
    static WndList<WndPairValue> _wnd_size_list;

    // Window controls lists
    WndList<Button> _btns_list;
    WndList<ComboBox> _cmb_bxs_list;
    WndList<Edit> _edits_list;
    WndList<Label> _lbls_list;
    Menu *_menu = nullptr;

    // Main window procedure
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
    Window(
        const char *name,
        WndPairValue pos = { CW_USEDEFAULT, CW_USEDEFAULT },
        WndPairValue size = { CW_USEDEFAULT, CW_USEDEFAULT },
        int icon_id = -1,
        unsigned long wnd_style = WS_OVERLAPPEDWINDOW);
    ~Window();

    void AttachChildControl(WndBase *wnd);
    void AttachMenu(Menu *menu);

    WndList<Button> &GetButtonsList();
    WndList<ComboBox> &GetComboBoxesList();
    WndList<Edit> &GetEditsList();
    WndList<Label> &GetLabelsList();
    Menu &GetMenu();

    void EnableControlsDialogMessages(const bool &flag);

    int Run();
};

class ParentResizeCallbackParams {
public:
    WndBase *wnd;
    WndPairValue old_size;
};

//class WndSizeParams {
//public:
//	Window &_wnd;
//	WndPairValue _old_size;
//	void **_data = nullptr;
//
//	WndSizeParams(Window &wnd, const WndPairValue &old_size)
//		: _wnd(wnd), _old_size(old_size) {}
//
//	~WndSizeParams() = default;
//};

#endif
