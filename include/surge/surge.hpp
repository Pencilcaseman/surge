#pragma once

#include <filesystem>
#include <librapid/librapid.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <implot.h>
#include <implot_internal.h>
#include <raylib.h>

#if !defined(RAYLIB_VERSION_MAJOR) || !defined(RAYLIB_VERSION_MINOR) ||                            \
  RAYLIB_VERSION_MAJOR < 4 || RAYLIB_VERSION_MINOR < 5
#	error "raylib-cpp requires at least raylib 4.5.0"
#endif

#define SURGE_WARN_ONCE(condition, message)                                                        \
	do {                                                                                           \
		static bool warned = false;                                                                \
		if (!(condition) && !warned) {                                                             \
			LIBRAPID_WARN(message);                                                                \
			warned = true;                                                                         \
		}                                                                                          \
	} while (0)

namespace surge {
	namespace global {
		inline static int roundedRectSegments = 0;
	}

	enum class WindowFlag {
		vsync		= RL_FLAG_VSYNC_HINT,		  /// Enable V-Sync on GPU
		fullscreen	= RL_FLAG_FULLSCREEN_MODE,	  /// Run program in fullscreen
		resizable	= RL_FLAG_WINDOW_RESIZABLE,	  /// Allow resizable window
		undecorated = RL_FLAG_WINDOW_UNDECORATED, /// Disable window decoration (frame and buttons)
		hidden		= RL_FLAG_WINDOW_HIDDEN,	  /// Hide window
		minimized	= RL_FLAG_WINDOW_MINIMIZED,	  /// Minimize window (iconify)
		maximized	= RL_FLAG_WINDOW_MAXIMIZED,	  /// Maximize window (expanded to monitor)
		unfocused	= RL_FLAG_WINDOW_UNFOCUSED,	  /// Window non focused
		topmost		= RL_FLAG_WINDOW_TOPMOST,	  /// Window always on top
		alwaysRun	= RL_FLAG_WINDOW_ALWAYS_RUN,  /// Allow windows running while minimized
		transparent = RL_FLAG_WINDOW_TRANSPARENT, /// Allow transparent framebuffer
		highDPI		= RL_FLAG_WINDOW_HIGHDPI,	  /// Support HighDPI
		mousePassthrough =
		  RL_FLAG_WINDOW_MOUSE_PASSTHROUGH,	 /// Support mouse passthrough, only
											 /// supported when FLAG_WINDOW_UNDECORATED
		msaa4x	   = RL_FLAG_MSAA_4X_HINT,	 /// Enable MSAA 4X
		interlaced = RL_FLAG_INTERLACED_HINT /// Enable interlaced video format (for V3D)
	};

	enum class Key {
		nullKey = RL_KEY_NULL, // Null key -- Used for when no key is pressed

		// Alphanumeric keys

		apostrophe = RL_KEY_APOSTROPHE, // Key: '
		comma	   = RL_KEY_COMMA,		// Key: ,
		minus	   = RL_KEY_MINUS,		// Key: -
		period	   = RL_KEY_PERIOD,		// Key: .
		slash	   = RL_KEY_SLASH,		// Key: /
		zero	   = RL_KEY_ZERO,		// Key: 0
		one		   = RL_KEY_ONE,		// Key: 1
		two		   = RL_KEY_TWO,		// Key: 2
		three	   = RL_KEY_THREE,		// Key: 3
		four	   = RL_KEY_FOUR,		// Key: 4
		five	   = RL_KEY_FIVE,		// Key: 5
		six		   = RL_KEY_SIX,		// Key: 6
		seven	   = RL_KEY_SEVEN,		// Key: 7
		eight	   = RL_KEY_EIGHT,		// Key: 8
		nine	   = RL_KEY_NINE,		// Key: 9
		semicolon  = RL_KEY_SEMICOLON,	// Key: ;
		equal	   = RL_KEY_EQUAL,		// Key: =
		a		   = RL_KEY_A,			// Key: A | a
		b		   = RL_KEY_B,			// Key: B | b
		c		   = RL_KEY_C,			// Key: C | c
		d		   = RL_KEY_D,			// Key: D | d
		e		   = RL_KEY_E,			// Key: E | e
		f		   = RL_KEY_F,			// Key: F | f
		g		   = RL_KEY_G,			// Key: G | g
		h		   = RL_KEY_H,			// Key: H | h
		i		   = RL_KEY_I,			// Key: I | i
		j		   = RL_KEY_J,			// Key: J | j
		k		   = RL_KEY_K,			// Key: K | k
		l		   = RL_KEY_L,			// Key: L | l
		m		   = RL_KEY_M,			// Key: M | m
		n		   = RL_KEY_N,			// Key: N | n
		o		   = RL_KEY_O,			// Key: O | o
		p		   = RL_KEY_P,			// Key: P | p
		q		   = RL_KEY_Q,			// Key: Q | q
		r		   = RL_KEY_R,			// Key: R | r
		s		   = RL_KEY_S,			// Key: S | s
		t		   = RL_KEY_T,			// Key: T | t
		u		   = RL_KEY_U,			// Key: U | u
		v		   = RL_KEY_V,			// Key: V | v
		w		   = RL_KEY_W,			// Key: W | w
		x		   = RL_KEY_X,			// Key: X | x
		y		   = RL_KEY_Y,			// Key: Y | y
		z		   = RL_KEY_Z,			// Key: Z | z

		// Function keys

		space		 = RL_KEY_SPACE,		 // Key: Space
		escape		 = RL_KEY_ESCAPE,		 // Key: Escape
		enter		 = RL_KEY_ENTER,		 // Key: Enter
		tab			 = RL_KEY_TAB,			 // Key: Tab
		backspace	 = RL_KEY_BACKSPACE,	 // Key: Backspace
		insert		 = RL_KEY_INSERT,		 // Key: Insert
		del			 = RL_KEY_DELETE,		 // Key: Delete
		right		 = RL_KEY_RIGHT,		 // Key: Right
		left		 = RL_KEY_LEFT,			 // Key: Left
		down		 = RL_KEY_DOWN,			 // Key: Down
		up			 = RL_KEY_UP,			 // Key: Up
		pageUp		 = RL_KEY_PAGE_UP,		 // Key: Page up
		pageDown	 = RL_KEY_PAGE_DOWN,	 // Key: Page down
		home		 = RL_KEY_HOME,			 // Key: Home
		end			 = RL_KEY_END,			 // Key: End
		capsLock	 = RL_KEY_CAPS_LOCK,	 // Key: Caps lock
		scrollLock	 = RL_KEY_SCROLL_LOCK,	 // Key: Scroll lock
		numLock		 = RL_KEY_NUM_LOCK,		 // Key: Num lock
		printScreen	 = RL_KEY_PRINT_SCREEN,	 // Key: Print screen
		pause		 = RL_KEY_PAUSE,		 // Key: Pause
		f1			 = RL_KEY_F1,			 // Key: F1
		f2			 = RL_KEY_F2,			 // Key: F2
		f3			 = RL_KEY_F3,			 // Key: F3
		f4			 = RL_KEY_F4,			 // Key: F4
		f5			 = RL_KEY_F5,			 // Key: F5
		f6			 = RL_KEY_F6,			 // Key: F6
		f7			 = RL_KEY_F7,			 // Key: F7
		f8			 = RL_KEY_F8,			 // Key: F8
		f9			 = RL_KEY_F9,			 // Key: F9
		f10			 = RL_KEY_F10,			 // Key: F10
		f11			 = RL_KEY_F11,			 // Key: F11
		f12			 = RL_KEY_F12,			 // Key: F12
		leftShift	 = RL_KEY_LEFT_SHIFT,	 // Key: Left shift
		leftControl	 = RL_KEY_LEFT_CONTROL,	 // Key: Left control
		leftAlt		 = RL_KEY_LEFT_ALT,		 // Key: Left alt
		leftSuper	 = RL_KEY_LEFT_SUPER,	 // Key: Left super
		rightShift	 = RL_KEY_RIGHT_SHIFT,	 // Key: Right shift
		rightControl = RL_KEY_RIGHT_CONTROL, // Key: Right control
		rightAlt	 = RL_KEY_RIGHT_ALT,	 // Key: Right alt
		rightSuper	 = RL_KEY_RIGHT_SUPER,	 // Key: Right super
		menu		 = RL_KEY_MENU,			 // Key: Menu

		// Numpad keys

		numpad0		   = RL_KEY_KP_0,		 // Key: Numpad 0
		numpad1		   = RL_KEY_KP_1,		 // Key: Numpad 1
		numpad2		   = RL_KEY_KP_2,		 // Key: Numpad 2
		numpad3		   = RL_KEY_KP_3,		 // Key: Numpad 3
		numpad4		   = RL_KEY_KP_4,		 // Key: Numpad 4
		numpad5		   = RL_KEY_KP_5,		 // Key: Numpad 5
		numpad6		   = RL_KEY_KP_6,		 // Key: Numpad 6
		numpad7		   = RL_KEY_KP_7,		 // Key: Numpad 7
		numpad8		   = RL_KEY_KP_8,		 // Key: Numpad 8
		numpad9		   = RL_KEY_KP_9,		 // Key: Numpad 9
		numpadPeriod   = RL_KEY_KP_DECIMAL,	 // Key: Numpad .
		numpadDivide   = RL_KEY_KP_DIVIDE,	 // Key: Numpad /
		numpadMultiply = RL_KEY_KP_MULTIPLY, // Key: Numpad *
		numpadSubtract = RL_KEY_KP_SUBTRACT, // Key: Numpad -
		numpadAdd	   = RL_KEY_KP_ADD,		 // Key: Numpad +
		numpadEnter	   = RL_KEY_KP_ENTER,	 // Key: Numpad Enter
		numpadEqual	   = RL_KEY_KP_EQUAL,	 // Key: Numpad =

		// Android key buttons

		androidBack		  = RL_KEY_BACK,		// Key: Back
		androidMenu		  = RL_KEY_MENU,		// Key: Menu
		androidVolumeUp	  = RL_KEY_VOLUME_UP,	// Key: Volume up
		androidVolumeDown = RL_KEY_VOLUME_DOWN, // Key: Volume down
	};

	enum class MouseButton {
		left	= RL_MOUSE_BUTTON_LEFT,	   // Mouse button: Left
		right	= RL_MOUSE_BUTTON_RIGHT,   // Mouse button: Right
		middle	= RL_MOUSE_BUTTON_MIDDLE,  // Mouse button: Middle
		side	= RL_MOUSE_BUTTON_SIDE,	   // Mouse button: Side
		extra	= RL_MOUSE_BUTTON_EXTRA,   // Mouse button: Extra
		forward = RL_MOUSE_BUTTON_FORWARD, // Mouse button: Forward
		back	= RL_MOUSE_BUTTON_BACK,	   // Mouse button: Back
	};

	enum class MouseCursor {
		defaultCursor	 = RL_MOUSE_CURSOR_DEFAULT,		  // Mouse cursor: Default
		arrow			 = RL_MOUSE_CURSOR_ARROW,		  // Mouse cursor: Arrow
		iBeam			 = RL_MOUSE_CURSOR_IBEAM,		  // Mouse cursor: I-beam
		crosshair		 = RL_MOUSE_CURSOR_CROSSHAIR,	  // Mouse cursor: Crosshair
		pointingHand	 = RL_MOUSE_CURSOR_POINTING_HAND, // Mouse cursor: Pointing hand
		resizeHorizontal = RL_MOUSE_CURSOR_RESIZE_EW,	  // Mouse cursor: Resize east-west
		resizeVertical	 = RL_MOUSE_CURSOR_RESIZE_NS,	  // Mouse cursor: Resize north-south
		resizeNWSE = RL_MOUSE_CURSOR_RESIZE_NWSE, // Mouse cursor: Resize north-west south-east
		resizeNESW = RL_MOUSE_CURSOR_RESIZE_NESW, // Mouse cursor: Resize north-east south-west
		resizeAll  = RL_MOUSE_CURSOR_RESIZE_ALL,  // Mouse cursor: Resize all
		notAllowed = RL_MOUSE_CURSOR_NOT_ALLOWED, // Mouse cursor: Not allowed
	};

	enum class GameButton {
		unknown		   = RL_GAMEPAD_BUTTON_UNKNOWN, // Gamepad button: Unknown -- for error checking
		leftDPadUp	   = RL_GAMEPAD_BUTTON_LEFT_FACE_UP,	 // Gamepad button: D-pad up
		leftDPadRight  = RL_GAMEPAD_BUTTON_LEFT_FACE_RIGHT,	 // Gamepad button: D-pad right
		leftDPadDown   = RL_GAMEPAD_BUTTON_LEFT_FACE_DOWN,	 // Gamepad button: D-pad down
		leftDPadLeft   = RL_GAMEPAD_BUTTON_LEFT_FACE_LEFT,	 // Gamepad button: D-pad left
		rightDPadUp	   = RL_GAMEPAD_BUTTON_RIGHT_FACE_UP,	 // Gamepad button: D-pad up
		rightDPadRight = RL_GAMEPAD_BUTTON_RIGHT_FACE_RIGHT, // Gamepad button: D-pad right
		rightDPadDown  = RL_GAMEPAD_BUTTON_RIGHT_FACE_DOWN,	 // Gamepad button: D-pad down
		rightDPadLeft  = RL_GAMEPAD_BUTTON_RIGHT_FACE_LEFT,	 // Gamepad button: D-pad left
		leftTrigger1   = RL_GAMEPAD_BUTTON_LEFT_TRIGGER_1,	 // Gamepad button: Left trigger 1
		leftTrigger2   = RL_GAMEPAD_BUTTON_LEFT_TRIGGER_2,	 // Gamepad button: Left trigger 2
		rightTrigger1  = RL_GAMEPAD_BUTTON_RIGHT_TRIGGER_1,	 // Gamepad button: Right trigger 1
		rightTrigger2  = RL_GAMEPAD_BUTTON_RIGHT_TRIGGER_2,	 // Gamepad button: Right trigger 2
		middleLeft	   = RL_GAMEPAD_BUTTON_MIDDLE_LEFT, // Gamepad button: Middle left -- PS3 Select
		middle		= RL_GAMEPAD_BUTTON_MIDDLE, // Gamepad button: Middle -- PS Button/Xbox Button
		middleRight = RL_GAMEPAD_BUTTON_MIDDLE_RIGHT, // Gamepad button: Middle right -- PS3 Start
		leftThumb	= RL_GAMEPAD_BUTTON_LEFT_THUMB,	  // Gamepad button: Left thumb
		rightThumb	= RL_GAMEPAD_BUTTON_RIGHT_THUMB,  // Gamepad button: Right thumb
	};

	enum class GamepadAxis {
		leftX		 = RL_GAMEPAD_AXIS_LEFT_X,		  // Gamepad axis: Left X
		leftY		 = RL_GAMEPAD_AXIS_LEFT_Y,		  // Gamepad axis: Left Y
		rightX		 = RL_GAMEPAD_AXIS_RIGHT_X,		  // Gamepad axis: Right X
		rightY		 = RL_GAMEPAD_AXIS_RIGHT_Y,		  // Gamepad axis: Right Y
		leftTrigger	 = RL_GAMEPAD_AXIS_LEFT_TRIGGER,  // Gamepad axis: Left trigger
		rightTrigger = RL_GAMEPAD_AXIS_RIGHT_TRIGGER, // Gamepad axis: Right trigger
	};
} // namespace surge

#include "transformations.hpp"
#include "color.hpp"
#include "mouse.hpp"
#include "window.hpp"
#include "line.hpp"
#include "rectangle.hpp"
#include "font.hpp"
#include "text.hpp"
