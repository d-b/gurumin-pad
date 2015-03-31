/*
 * gurumin-pad
 * Copyright (C) 2015 Daniel Bloemendal. All rights reserved.
 *
 * DirectInput device class definition
 */

#include "proxy.hpp"

namespace proxy {
    //////////////////////////////////////////////////////////////////////
    // DirectInput8 Proxy
    //////////////////////////////////////////////////////////////////////

    HRESULT STDMETHODCALLTYPE ProxyDirectInput8A::CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICE8A * slplpDirectInputDevice, LPUNKNOWN pUnkOuter) {
        // Create the input device
        HRESULT res = _target->CreateDevice(rguid, slplpDirectInputDevice, pUnkOuter);
        if (FAILED(res)) return res;

        // Fetch device information
        LPDIRECTINPUTDEVICE8A device = *slplpDirectInputDevice;
        DIDEVICEINSTANCEA device_info;
        device_info.dwSize = sizeof(device_info);
        if (FAILED(device->GetDeviceInfo(&device_info))) return res;

        // If it is a gamepad, set the deadzone
        if ((device_info.dwDevType & 0xFF) == DI8DEVTYPE_GAMEPAD) {
            DIPROPDWORD property;
            property.diph.dwSize = sizeof(property);
            property.diph.dwHeaderSize = sizeof(property.diph);
            property.diph.dwHow = DIPH_DEVICE;
            property.diph.dwObj = 0;
            property.dwData = PROJECT_DEADZONE;
            device->SetProperty(DIPROP_DEADZONE, &property.diph);
        }

        // Return the result
        return res;
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

    //////////////////////////////////////////////////////////////////////
    // DirectInputDevice8 Proxy
    //////////////////////////////////////////////////////////////////////

    ProxyDirectInputDevice8A::ProxyDirectInputDevice8A(IDirectInputDevice8A* target)
        : _refs(1), _target(target)
    {}

    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::QueryInterface(REFIID riid, LPVOID * ppvObj) {
        return _target->QueryInterface(riid, ppvObj);
    }
    ULONG STDMETHODCALLTYPE ProxyDirectInputDevice8A::AddRef() {
        return ++_refs;
    }
    ULONG STDMETHODCALLTYPE ProxyDirectInputDevice8A::Release() {
        if (--_refs != 0) return _refs;
        _target->Release();
        ProxyDirectInputDevice8A* self = this;
        delete self; return 0;
    }

    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::GetCapabilities(LPDIDEVCAPS lpDIDevCaps) {
        return _target->GetCapabilities(lpDIDevCaps);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags) {
        return _target->EnumObjects(lpCallback, pvRef, dwFlags);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::GetProperty(REFGUID rguidProp, LPDIPROPHEADER pdiph) {
        return _target->GetProperty(rguidProp, pdiph);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::SetProperty(REFGUID rguidProp, LPCDIPROPHEADER pdiph) {
        return _target->SetProperty(rguidProp, pdiph);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::Acquire() {
        return _target->Acquire();
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::Unacquire() {
        return _target->Unacquire();
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::GetDeviceState(DWORD cbData, LPVOID lpvData) {
        return _target->GetDeviceState(cbData, lpvData);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::GetDeviceData(DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags) {
        return _target->GetDeviceData(cbObjectData, rgdod, pdwInOut, dwFlags);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::SetDataFormat(LPCDIDATAFORMAT lpdf) {
        return _target->SetDataFormat(lpdf);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::SetEventNotification(HANDLE hEvent) {
        return _target->SetEventNotification(hEvent);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::SetCooperativeLevel(HWND hwnd, DWORD dwFlags) {
        return _target->SetCooperativeLevel(hwnd, dwFlags);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::GetObjectInfo(LPDIDEVICEOBJECTINSTANCEA pdidoi, DWORD dwObj, DWORD dwHow) {
        return _target->GetObjectInfo(pdidoi, dwObj, dwHow);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::GetDeviceInfo(LPDIDEVICEINSTANCEA pdidi) {
        return _target->GetDeviceInfo(pdidi);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::RunControlPanel(HWND hwndOwner, DWORD dwFlags) {
        return _target->RunControlPanel(hwndOwner, dwFlags);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::Initialize(HINSTANCE hinst, DWORD dwVersion, REFGUID rguid) {
        return _target->Initialize(hinst, dwVersion, rguid);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::CreateEffect(REFGUID rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT * ppdeff, LPUNKNOWN punkOuter) {
        return _target->CreateEffect(rguid, lpeff, ppdeff, punkOuter);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::EnumEffects(LPDIENUMEFFECTSCALLBACKA lpCallback, LPVOID pvRef, DWORD dwEffType) {
        return _target->EnumEffects(lpCallback, pvRef, dwEffType);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::GetEffectInfo(LPDIEFFECTINFOA pdei, REFGUID rguid) {
        return _target->GetEffectInfo(pdei, rguid);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::GetForceFeedbackState(LPDWORD pdwOut) {
        return _target->GetForceFeedbackState(pdwOut);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::SendForceFeedbackCommand(DWORD dwFlags) {
        return _target->SendForceFeedbackCommand(dwFlags);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD fl) {
        return _target->EnumCreatedEffectObjects(lpCallback, pvRef, fl);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::Escape(LPDIEFFESCAPE pesc) {
        return _target->Escape(pesc);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::Poll() {
        return _target->Poll();
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::SendDeviceData(DWORD cbObjectData, LPCDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD fl) {
        return _target->SendDeviceData(cbObjectData, rgdod, pdwInOut, fl);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::EnumEffectsInFile(LPCSTR lpszFileName, LPDIENUMEFFECTSINFILECALLBACK pec, LPVOID pvRef, DWORD dwFlags) {
        return _target->EnumEffectsInFile(lpszFileName, pec, pvRef, dwFlags);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::WriteEffectToFile(LPCSTR lpszFileName, DWORD dwEntries, LPDIFILEEFFECT rgDiFileEft, DWORD dwFlags) {
        return _target->WriteEffectToFile(lpszFileName, dwEntries, rgDiFileEft, dwFlags);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::BuildActionMap(LPDIACTIONFORMATA lpdiaf, LPCSTR lpszUserName, DWORD dwFlags) {
        return _target->BuildActionMap(lpdiaf, lpszUserName, dwFlags);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::SetActionMap(LPDIACTIONFORMATA lpdiActionFormat, LPCSTR lptszUserName, DWORD dwFlags) {
        return _target->SetActionMap(lpdiActionFormat, lptszUserName, dwFlags);
    }
    HRESULT STDMETHODCALLTYPE ProxyDirectInputDevice8A::GetImageInfo(LPDIDEVICEIMAGEINFOHEADERA lpdiDevImageInfoHeader) {
        return _target->GetImageInfo(lpdiDevImageInfoHeader);
    }
}
