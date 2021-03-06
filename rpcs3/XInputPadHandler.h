#pragma once

#include "Emu/Io/PadHandler.h"
#include <Xinput.h>

class XInputPadHandler final : public PadHandlerBase
{
public:
	XInputPadHandler();
	~XInputPadHandler();

	void Init(const u32 max_connect) override;
	void SetRumble(const u32 pad, u8 largeMotor, bool smallMotor) override;
	void Close();

private:
	typedef void (WINAPI * PFN_XINPUTENABLE)(BOOL);
	typedef DWORD (WINAPI * PFN_XINPUTGETSTATE)(DWORD, XINPUT_STATE *);
	typedef DWORD (WINAPI * PFN_XINPUTSETSTATE)(DWORD, XINPUT_VIBRATION *);

private:
	DWORD ThreadProcedure();
	static DWORD WINAPI ThreadProcProxy(LPVOID parameter);

private:
	mutable bool active;
	HANDLE thread;
	HMODULE library;
	PFN_XINPUTGETSTATE xinputGetState;
	PFN_XINPUTSETSTATE xinputSetState;
	PFN_XINPUTENABLE xinputEnable;

};
