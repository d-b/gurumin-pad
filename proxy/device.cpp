/*
 * gurumin-pad
 * Copyright (C) 2015 Daniel Bloemendal. All rights reserved.
 *
 * DirectInput device class definition
 */

#include "proxy.hpp"

namespace proxy {
    HRESULT STDMETHODCALLTYPE ProxyDirectInput8A::CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICE8A * slplpDirectInputDevice, LPUNKNOWN pUnkOuter) {
        return _target->CreateDevice(rguid, slplpDirectInputDevice, pUnkOuter);
    }

    ProxyDirectInput8A::ProxyDirectInput8A(IDirectInput8A* target)
        : _refs(1), _target(target)
    {}

    HRESULT STDMETHODCALLTYPE ProxyDirectInput8A::QueryInterface(REFIID riid, LPVOID * ppvObj) {
        return _target->QueryInterface(riid, ppvObj);
    }
    ULONG STDMETHODCALLTYPE ProxyDirectInput8A::AddRef() {
        return ++_refs;
    }
    ULONG STDMETHODCALLTYPE ProxyDirectInput8A::Release() {
        if (--_refs != 0) return _refs;
        _target->Release();
        ProxyDirectInput8A* self = this;
        delete self; return 0;
    }

    HRESULT STDMETHODCALLTYPE ProxyDirectInput8A::EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags) {
        return _target->EnumDevices(dwDevType, lpCallback, pvRef, dwFlags);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInput8A::GetDeviceStatus(REFGUID rguidInstance) {
        return _target->GetDeviceStatus(rguidInstance);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInput8A::RunControlPanel(HWND hwndOwner, DWORD dwFlags) {
        return _target->RunControlPanel(hwndOwner, dwFlags);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInput8A::Initialize(HINSTANCE hinst, DWORD dwVersion) {
        return _target->Initialize(hinst, dwVersion);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInput8A::FindDevice(REFGUID rguidClass, LPCSTR ptszName, LPGUID pguidInstance) {
        return _target->FindDevice(rguidClass, ptszName, pguidInstance);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInput8A::EnumDevicesBySemantics(LPCSTR ptszUserName, LPDIACTIONFORMATA lpdiActionFormat, LPDIENUMDEVICESBYSEMANTICSCBA lpCallback, LPVOID pvRef, DWORD dwFlags) {
        return _target->EnumDevicesBySemantics(ptszUserName, lpdiActionFormat, lpCallback, pvRef, dwFlags);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInput8A::ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK lpdiCallback, LPDICONFIGUREDEVICESPARAMSA lpdiCDParams, DWORD dwFlags, LPVOID pvRefData) {
        return _target->ConfigureDevices(lpdiCallback, lpdiCDParams, dwFlags, pvRefData);
    }
}
