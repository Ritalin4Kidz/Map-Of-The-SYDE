#pragma once
#include <windows.h>
enum SYDEKeyState {
	NONE,
	KEYDOWN,
	KEYUP,
	KEY
};

class SYDEKey {
public:
	SYDEKey(char a_keyCode) { keyCode = a_keyCode; }
	virtual ~SYDEKey() {}

	//Usage of getKey()
	/*
		GetKey() - get if key is down
		GetKeyDown(bool using_GetKeyUp) - check if key is down on frame, set param to true if keyUp is used in same frame
		GetKeyUp(bool using_GetKeyDown) - check if key is up on frame, set param to true if keyDown is used in same frame
	*/
	bool GetKey();
	///<summary>
	/// Makes sure that the window is in the foreground before keypresses occur
	///</summary>
	bool GetKey_Safe();
	void GetKeyDown();
	///<summary>
	/// Makes sure that the window is in the foreground before keypresses occur
	///</summary>
	void GetKeyDown_Safe(HWND hWnd);
	void GetKeyUp();
	///<summary>
	/// Makes sure that the window is in the foreground before keypresses occur
	///</summary>
	void GetKeyUp_Safe(HWND hWnd);

	char getKeyCode() { return keyCode; }

	SYDEKeyState _GETSTATE() { return _STATE; }
	bool _CompareState(SYDEKeyState m_State);

	void Reset();

	SYDEKey& operator=(char KeyCode);

private:
	bool isPressed = false;
	char keyCode;
	SYDEKeyState _STATE = NONE;
};