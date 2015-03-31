/*
 * gurumin-pad
 * Copyright (C) 2015 Daniel Bloemendal. All rights reserved.
 *
 * DirectInput device class declaration
 */

namespace proxy {
    class ProxyDirectInput8A : public IUnknown {
    public:
        ProxyDirectInput8A(IDirectInput8A* target);

        // IUnknown interface
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID * ppvObj);
        virtual DECLSPEC_NOTHROW ULONG STDMETHODCALLTYPE AddRef();
        virtual DECLSPEC_NOTHROW ULONG STDMETHODCALLTYPE Release();

        // IDirectInput8A interface
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICE8A * slplpDirectInputDevice, LPUNKNOWN pUnkOuter);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE GetDeviceStatus(REFGUID rguidInstance);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE RunControlPanel(HWND hwndOwner, DWORD dwFlags);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE Initialize(HINSTANCE hinst, DWORD dwVersion);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE FindDevice(REFGUID rguidClass, LPCSTR ptszName, LPGUID pguidInstance);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE EnumDevicesBySemantics(LPCSTR ptszUserName, LPDIACTIONFORMATA lpdiActionFormat, LPDIENUMDEVICESBYSEMANTICSCBA lpCallback, LPVOID pvRef, DWORD dwFlags);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK lpdiCallback, LPDICONFIGUREDEVICESPARAMSA lpdiCDParams, DWORD dwFlags, LPVOID pvRefData);

    protected:
        // Internal data
        ULONG _refs;
        IDirectInput8A* _target;
        
    };

    class ProxyDirectInputDevice8A : public IUnknown {
    public:
        ProxyDirectInputDevice8A(IDirectInputDevice8A* target);

        // IUnknown interface
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID * ppvObj);
        virtual DECLSPEC_NOTHROW ULONG STDMETHODCALLTYPE AddRef();
        virtual DECLSPEC_NOTHROW ULONG STDMETHODCALLTYPE Release();

        // IDirectInputDevice8A interface
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE GetCapabilities(LPDIDEVCAPS lpDIDevCaps);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE GetProperty(REFGUID rguidProp, LPDIPROPHEADER pdiph);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE SetProperty(REFGUID rguidProp, LPCDIPROPHEADER pdiph);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE Acquire();
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE Unacquire();
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE GetDeviceState(DWORD cbData, LPVOID lpvData);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE GetDeviceData(DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE SetDataFormat(LPCDIDATAFORMAT lpdf);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE SetEventNotification(HANDLE hEvent);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE SetCooperativeLevel(HWND hwnd, DWORD dwFlags);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE GetObjectInfo(LPDIDEVICEOBJECTINSTANCEA pdidoi, DWORD dwObj, DWORD dwHow);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE GetDeviceInfo(LPDIDEVICEINSTANCEA pdidi);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE RunControlPanel(HWND hwndOwner, DWORD dwFlags);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE Initialize(HINSTANCE hinst, DWORD dwVersion, REFGUID rguid);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE CreateEffect(REFGUID rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT * ppdeff, LPUNKNOWN punkOuter);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE EnumEffects(LPDIENUMEFFECTSCALLBACKA lpCallback, LPVOID pvRef, DWORD dwEffType);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE GetEffectInfo(LPDIEFFECTINFOA pdei, REFGUID rguid);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE GetForceFeedbackState(LPDWORD pdwOut);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE SendForceFeedbackCommand(DWORD dwFlags);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD fl);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE Escape(LPDIEFFESCAPE pesc);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE Poll();
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE SendDeviceData(DWORD cbObjectData, LPCDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD fl);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE EnumEffectsInFile(LPCSTR lpszFileName, LPDIENUMEFFECTSINFILECALLBACK pec, LPVOID pvRef, DWORD dwFlags);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE WriteEffectToFile(LPCSTR lpszFileName, DWORD dwEntries, LPDIFILEEFFECT rgDiFileEft, DWORD dwFlags);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE BuildActionMap(LPDIACTIONFORMATA lpdiaf, LPCSTR lpszUserName, DWORD dwFlags);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE SetActionMap(LPDIACTIONFORMATA lpdiActionFormat, LPCSTR lptszUserName, DWORD dwFlags);
        virtual DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE GetImageInfo(LPDIDEVICEIMAGEINFOHEADERA lpdiDevImageInfoHeader);

    protected:
        // Internal data
        ULONG _refs;
        IDirectInputDevice8A* _target;
    };
}
