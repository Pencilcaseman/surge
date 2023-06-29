#pragma once

#include <librapid/librapid.hpp>
#include <raylib.h>

#if !defined(RAYLIB_VERSION_MAJOR) || !defined(RAYLIB_VERSION_MINOR) ||                            \
  RAYLIB_VERSION_MAJOR < 4 || RAYLIB_VERSION_MINOR < 5
#	error "raylib-cpp requires at least raylib 4.5.0"
#endif

#define SURGE_WARN_ONCE(condition, message)                                                        \
	{                                                                                              \
		static bool warned = false;                                                                \
		if (!(condition) && !warned) {                                                             \
			LIBRAPID_WARN(message);                                                                \
			warned = true;                                                                         \
		}                                                                                          \
	}

namespace surge {
	namespace global {
		inline static int roundedRectSegments = 0;
	}

	enum class WindowFlag {
		vsync		= FLAG_VSYNC_HINT,		   /// Enable V-Sync on GPU
		fullscreen	= FLAG_FULLSCREEN_MODE,	   /// Run program in fullscreen
		resizable	= FLAG_WINDOW_RESIZABLE,   /// Allow resizable window
		undecorated = FLAG_WINDOW_UNDECORATED, /// Disable window decoration (frame and buttons)
		hidden		= FLAG_WINDOW_HIDDEN,	   /// Hide window
		minimized	= FLAG_WINDOW_MINIMIZED,   /// Minimize window (iconify)
		maximized	= FLAG_WINDOW_MAXIMIZED,   /// Maximize window (expanded to monitor)
		unfocused	= FLAG_WINDOW_UNFOCUSED,   /// Window non focused
		topmost		= FLAG_WINDOW_TOPMOST,	   /// Window always on top
		alwaysRun	= FLAG_WINDOW_ALWAYS_RUN,  /// Allow windows running while minimized
		transparent = FLAG_WINDOW_TRANSPARENT, /// Allow transparent framebuffer
		highDPI		= FLAG_WINDOW_HIGHDPI,	   /// Support HighDPI
		mousePassthrough = FLAG_WINDOW_MOUSE_PASSTHROUGH, /// Support mouse passthrough, only
														  /// supported when FLAG_WINDOW_UNDECORATED
		msaa4x	   = FLAG_MSAA_4X_HINT,					  /// Enable MSAA 4X
		interlaced = FLAG_INTERLACED_HINT /// Enable interlaced video format (for V3D)
	};

	enum class Key {
		nullKey = KEY_NULL, // Null key -- Used for when no key is pressed

		// Alphanumeric keys

		apostrophe = KEY_APOSTROPHE, // Key: '
		comma	   = KEY_COMMA,		 // Key: ,
		minus	   = KEY_MINUS,		 // Key: -
		period	   = KEY_PERIOD,	 // Key: .
		slash	   = KEY_SLASH,		 // Key: /
		zero	   = KEY_ZERO,		 // Key: 0
		one		   = KEY_ONE,		 // Key: 1
		two		   = KEY_TWO,		 // Key: 2
		three	   = KEY_THREE,		 // Key: 3
		four	   = KEY_FOUR,		 // Key: 4
		five	   = KEY_FIVE,		 // Key: 5
		six		   = KEY_SIX,		 // Key: 6
		seven	   = KEY_SEVEN,		 // Key: 7
		eight	   = KEY_EIGHT,		 // Key: 8
		nine	   = KEY_NINE,		 // Key: 9
		semicolon  = KEY_SEMICOLON,	 // Key: ;
		equal	   = KEY_EQUAL,		 // Key: =
		a		   = KEY_A,			 // Key: A | a
		b		   = KEY_B,			 // Key: B | b
		c		   = KEY_C,			 // Key: C | c
		d		   = KEY_D,			 // Key: D | d
		e		   = KEY_E,			 // Key: E | e
		f		   = KEY_F,			 // Key: F | f
		g		   = KEY_G,			 // Key: G | g
		h		   = KEY_H,			 // Key: H | h
		i		   = KEY_I,			 // Key: I | i
		j		   = KEY_J,			 // Key: J | j
		k		   = KEY_K,			 // Key: K | k
		l		   = KEY_L,			 // Key: L | l
		m		   = KEY_M,			 // Key: M | m
		n		   = KEY_N,			 // Key: N | n
		o		   = KEY_O,			 // Key: O | o
		p		   = KEY_P,			 // Key: P | p
		q		   = KEY_Q,			 // Key: Q | q
		r		   = KEY_R,			 // Key: R | r
		s		   = KEY_S,			 // Key: S | s
		t		   = KEY_T,			 // Key: T | t
		u		   = KEY_U,			 // Key: U | u
		v		   = KEY_V,			 // Key: V | v
		w		   = KEY_W,			 // Key: W | w
		x		   = KEY_X,			 // Key: X | x
		y		   = KEY_Y,			 // Key: Y | y
		z		   = KEY_Z,			 // Key: Z | z

		// Function keys

		space		 = KEY_SPACE,		  // Key: Space
		escape		 = KEY_ESCAPE,		  // Key: Escape
		enter		 = KEY_ENTER,		  // Key: Enter
		tab			 = KEY_TAB,			  // Key: Tab
		backspace	 = KEY_BACKSPACE,	  // Key: Backspace
		insert		 = KEY_INSERT,		  // Key: Insert
		del			 = KEY_DELETE,		  // Key: Delete
		right		 = KEY_RIGHT,		  // Key: Right
		left		 = KEY_LEFT,		  // Key: Left
		down		 = KEY_DOWN,		  // Key: Down
		up			 = KEY_UP,			  // Key: Up
		pageUp		 = KEY_PAGE_UP,		  // Key: Page up
		pageDown	 = KEY_PAGE_DOWN,	  // Key: Page down
		home		 = KEY_HOME,		  // Key: Home
		end			 = KEY_END,			  // Key: End
		capsLock	 = KEY_CAPS_LOCK,	  // Key: Caps lock
		scrollLock	 = KEY_SCROLL_LOCK,	  // Key: Scroll lock
		numLock		 = KEY_NUM_LOCK,	  // Key: Num lock
		printScreen	 = KEY_PRINT_SCREEN,  // Key: Print screen
		pause		 = KEY_PAUSE,		  // Key: Pause
		f1			 = KEY_F1,			  // Key: F1
		f2			 = KEY_F2,			  // Key: F2
		f3			 = KEY_F3,			  // Key: F3
		f4			 = KEY_F4,			  // Key: F4
		f5			 = KEY_F5,			  // Key: F5
		f6			 = KEY_F6,			  // Key: F6
		f7			 = KEY_F7,			  // Key: F7
		f8			 = KEY_F8,			  // Key: F8
		f9			 = KEY_F9,			  // Key: F9
		f10			 = KEY_F10,			  // Key: F10
		f11			 = KEY_F11,			  // Key: F11
		f12			 = KEY_F12,			  // Key: F12
		leftShift	 = KEY_LEFT_SHIFT,	  // Key: Left shift
		leftControl	 = KEY_LEFT_CONTROL,  // Key: Left control
		leftAlt		 = KEY_LEFT_ALT,	  // Key: Left alt
		leftSuper	 = KEY_LEFT_SUPER,	  // Key: Left super
		rightShift	 = KEY_RIGHT_SHIFT,	  // Key: Right shift
		rightControl = KEY_RIGHT_CONTROL, // Key: Right control
		rightAlt	 = KEY_RIGHT_ALT,	  // Key: Right alt
		rightSuper	 = KEY_RIGHT_SUPER,	  // Key: Right super
		menu		 = KEY_MENU,		  // Key: Menu

		// Numpad keys

		numpad0		   = KEY_KP_0,		  // Key: Numpad 0
		numpad1		   = KEY_KP_1,		  // Key: Numpad 1
		numpad2		   = KEY_KP_2,		  // Key: Numpad 2
		numpad3		   = KEY_KP_3,		  // Key: Numpad 3
		numpad4		   = KEY_KP_4,		  // Key: Numpad 4
		numpad5		   = KEY_KP_5,		  // Key: Numpad 5
		numpad6		   = KEY_KP_6,		  // Key: Numpad 6
		numpad7		   = KEY_KP_7,		  // Key: Numpad 7
		numpad8		   = KEY_KP_8,		  // Key: Numpad 8
		numpad9		   = KEY_KP_9,		  // Key: Numpad 9
		numpadPeriod   = KEY_KP_DECIMAL,  // Key: Numpad .
		numpadDivide   = KEY_KP_DIVIDE,	  // Key: Numpad /
		numpadMultiply = KEY_KP_MULTIPLY, // Key: Numpad *
		numpadSubtract = KEY_KP_SUBTRACT, // Key: Numpad -
		numpadAdd	   = KEY_KP_ADD,	  // Key: Numpad +
		numpadEnter	   = KEY_KP_ENTER,	  // Key: Numpad Enter
		numpadEqual	   = KEY_KP_EQUAL,	  // Key: Numpad =

		// Android key buttons

		androidBack		  = KEY_BACK,		 // Key: Back
		androidMenu		  = KEY_MENU,		 // Key: Menu
		androidVolumeUp	  = KEY_VOLUME_UP,	 // Key: Volume up
		androidVolumeDown = KEY_VOLUME_DOWN, // Key: Volume down
	};

	enum class MouseButton {
		left	= MOUSE_BUTTON_LEFT,	// Mouse button: Left
		right	= MOUSE_BUTTON_RIGHT,	// Mouse button: Right
		middle	= MOUSE_BUTTON_MIDDLE,	// Mouse button: Middle
		side	= MOUSE_BUTTON_SIDE,	// Mouse button: Side
		extra	= MOUSE_BUTTON_EXTRA,	// Mouse button: Extra
		forward = MOUSE_BUTTON_FORWARD, // Mouse button: Forward
		back	= MOUSE_BUTTON_BACK,	// Mouse button: Back
	};

	enum class MouseCursor {
		defaultCursor	 = MOUSE_CURSOR_DEFAULT,	   // Mouse cursor: Default
		arrow			 = MOUSE_CURSOR_ARROW,		   // Mouse cursor: Arrow
		iBeam			 = MOUSE_CURSOR_IBEAM,		   // Mouse cursor: I-beam
		crosshair		 = MOUSE_CURSOR_CROSSHAIR,	   // Mouse cursor: Crosshair
		pointingHand	 = MOUSE_CURSOR_POINTING_HAND, // Mouse cursor: Pointing hand
		resizeHorizontal = MOUSE_CURSOR_RESIZE_EW,	   // Mouse cursor: Resize east-west
		resizeVertical	 = MOUSE_CURSOR_RESIZE_NS,	   // Mouse cursor: Resize north-south
		resizeNWSE		 = MOUSE_CURSOR_RESIZE_NWSE,   // Mouse cursor: Resize north-west south-east
		resizeNESW		 = MOUSE_CURSOR_RESIZE_NESW,   // Mouse cursor: Resize north-east south-west
		resizeAll		 = MOUSE_CURSOR_RESIZE_ALL,	   // Mouse cursor: Resize all
		notAllowed		 = MOUSE_CURSOR_NOT_ALLOWED,   // Mouse cursor: Not allowed
	};

	enum class GameButton {
		unknown		   = GAMEPAD_BUTTON_UNKNOWN, // Gamepad button: Unknown -- for error checking
		leftDPadUp	   = GAMEPAD_BUTTON_LEFT_FACE_UP,	  // Gamepad button: D-pad up
		leftDPadRight  = GAMEPAD_BUTTON_LEFT_FACE_RIGHT,  // Gamepad button: D-pad right
		leftDPadDown   = GAMEPAD_BUTTON_LEFT_FACE_DOWN,	  // Gamepad button: D-pad down
		leftDPadLeft   = GAMEPAD_BUTTON_LEFT_FACE_LEFT,	  // Gamepad button: D-pad left
		rightDPadUp	   = GAMEPAD_BUTTON_RIGHT_FACE_UP,	  // Gamepad button: D-pad up
		rightDPadRight = GAMEPAD_BUTTON_RIGHT_FACE_RIGHT, // Gamepad button: D-pad right
		rightDPadDown  = GAMEPAD_BUTTON_RIGHT_FACE_DOWN,  // Gamepad button: D-pad down
		rightDPadLeft  = GAMEPAD_BUTTON_RIGHT_FACE_LEFT,  // Gamepad button: D-pad left
		leftTrigger1   = GAMEPAD_BUTTON_LEFT_TRIGGER_1,	  // Gamepad button: Left trigger 1
		leftTrigger2   = GAMEPAD_BUTTON_LEFT_TRIGGER_2,	  // Gamepad button: Left trigger 2
		rightTrigger1  = GAMEPAD_BUTTON_RIGHT_TRIGGER_1,  // Gamepad button: Right trigger 1
		rightTrigger2  = GAMEPAD_BUTTON_RIGHT_TRIGGER_2,  // Gamepad button: Right trigger 2
		middleLeft	   = GAMEPAD_BUTTON_MIDDLE_LEFT, // Gamepad button: Middle left -- PS3 Select
		middle		   = GAMEPAD_BUTTON_MIDDLE, // Gamepad button: Middle -- PS Button/Xbox Button
		middleRight	   = GAMEPAD_BUTTON_MIDDLE_RIGHT, // Gamepad button: Middle right -- PS3 Start
		leftThumb	   = GAMEPAD_BUTTON_LEFT_THUMB,	  // Gamepad button: Left thumb
		rightThumb	   = GAMEPAD_BUTTON_RIGHT_THUMB,  // Gamepad button: Right thumb
	};

	enum class GamepadAxis {
		leftX		 = GAMEPAD_AXIS_LEFT_X,		   // Gamepad axis: Left X
		leftY		 = GAMEPAD_AXIS_LEFT_Y,		   // Gamepad axis: Left Y
		rightX		 = GAMEPAD_AXIS_RIGHT_X,	   // Gamepad axis: Right X
		rightY		 = GAMEPAD_AXIS_RIGHT_Y,	   // Gamepad axis: Right Y
		leftTrigger	 = GAMEPAD_AXIS_LEFT_TRIGGER,  // Gamepad axis: Left trigger
		rightTrigger = GAMEPAD_AXIS_RIGHT_TRIGGER, // Gamepad axis: Right trigger
	};
} // namespace surge

#include "color.hpp"
#include "mouse.hpp"
#include "window.hpp"
#include "line.hpp"
#include "rectangle.hpp"
