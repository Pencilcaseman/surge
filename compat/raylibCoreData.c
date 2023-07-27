#include "raylib.h" // Declares module functions

#include <imguiCompat.h>

// Check if config flags have been externally provided on compilation line
#if !defined(EXTERNAL_CONFIG_FLAGS)
#	include "config.h" // Defines module configuration flags
#endif

#include "utils.h" // Required for: TRACELOG() macros

#define RLGL_IMPLEMENTATION
// #include "rlgl.h" // OpenGL abstraction layer to OpenGL 1.1, 3.3+ or ES2

#define RAYMATH_IMPLEMENTATION // Define external out-of-line implementation
// #include "raymath.h"		   // RlVector3, RlQuaternion and RlMatrix functionality

#if defined(SUPPORT_GESTURES_SYSTEM)
#	define RGESTURES_IMPLEMENTATION
// #	include "rgestures.h" // Gestures detection functionality
#endif

#if defined(SUPPORT_CAMERA_SYSTEM)
#	define RCAMERA_IMPLEMENTATION
//  "rcamera.h" // RlCamera system functionality
#endif

#if defined(SUPPORT_GIF_RECORDING)
#	define MSF_GIF_MALLOC(contextPointer, newSize) RL_MALLOC(newSize)
#	define MSF_GIF_REALLOC(contextPointer, oldMemory, oldSize, newSize)                           \
		RL_REALLOC(oldMemory, newSize)
#	define MSF_GIF_FREE(contextPointer, oldMemory, oldSize) RL_FREE(oldMemory)

#	define MSF_GIF_IMPL
// #	include "external/msf_gif.h" // GIF recording functionality
#endif

#if defined(SUPPORT_COMPRESSION_API)
#	define SINFL_IMPLEMENTATION
#	define SINFL_NO_SIMD
// #	include "external/sinfl.h" // Deflate (RFC 1951) decompressor

#	define SDEFL_IMPLEMENTATION
// #	include "external/sdefl.h" // Deflate (RFC 1951) compressor
#endif

#if (defined(__linux__) || defined(PLATFORM_WEB)) && (_POSIX_C_SOURCE < 199309L)
#	undef _POSIX_C_SOURCE
#	define _POSIX_C_SOURCE                                                                        \
		199309L // Required for: CLOCK_MONOTONIC if compiled with c99 without gnu ext.
#endif
#if defined(__linux__) && !defined(_GNU_SOURCE)
#	define _GNU_SOURCE
#endif

//// Platform specific defines to handle RL_GetApplicationDirectory()
//#if defined(PLATFORM_DESKTOP)
//#	if defined(_WIN32)
//#		ifndef MAX_PATH
//#			define MAX_PATH 1025
//#		endif
//__declspec(dllimport) unsigned long __stdcall GetModuleFileNameA(void *hModule, void *lpFilename,
//																 unsigned long nSize);
//__declspec(dllimport) unsigned long __stdcall GetModuleFileNameW(void *hModule, void *lpFilename,
//																 unsigned long nSize);
//__declspec(dllimport) int __stdcall WideCharToMultiByte(unsigned int cp, unsigned long flags,
//														void *widestr, int cchwide, void *str,
//														int cbmb, void *defchar, int *used_default);
//#	elif defined(__linux__)
//#		include <unistd.h>
//#	elif defined(__APPLE__)
//#		include <sys/syslimits.h>
//#		include <mach-o/dyld.h>
//#	endif // OSs
//#endif	   // PLATFORM_DESKTOP

#include <stdlib.h> // Required for: srand(), rand(), atexit()
#include <stdio.h>	// Required for: sprintf() [Used in RL_OpenURL()]
#include <string.h> // Required for: strrchr(), strcmp(), strlen(), memset()
#include <time.h>	// Required for: time() [Used in InitTimer()]
#include <math.h> // Required for: tan() [Used in RL_BeginMode3D()], atan2f() [Used in RL_LoadVrStereoConfig()]

#define _CRT_INTERNAL_NONSTDC_NAMES 1
#include <sys/stat.h> // Required for: stat(), S_ISREG [Used in RL_GetFileModTime(), IsFilePath()]

#if !defined(S_ISREG) && defined(S_IFMT) && defined(S_IFREG)
#	define S_ISREG(m) (((m)&S_IFMT) == S_IFREG)
#endif

#if defined(PLATFORM_DESKTOP) && defined(_WIN32) && (defined(_MSC_VER) || defined(__TINYC__))
#	define DIRENT_MALLOC RL_MALLOC
#	define DIRENT_FREE	  RL_FREE

// #	include "external/dirent.h" // Required for: DIR, opendir(), closedir() [Used in RL_LoadDirectoryFiles()]
#else
#	include <dirent.h> // Required for: DIR, opendir(), closedir() [Used in RL_LoadDirectoryFiles()]
#endif

#if defined(_WIN32)
#	include <direct.h>	   // Required for: _getch(), _chdir()
#	define GETCWD _getcwd // NOTE: MSDN recommends not to use getcwd(), chdir()
#	define CHDIR  _chdir
#	include <io.h> // Required for: _access() [Used in RL_FileExists()]
#else
#	include <unistd.h> // Required for: getch(), chdir() (POSIX), access()
#	define GETCWD getcwd
#	define CHDIR  chdir
#endif

#if defined(PLATFORM_DESKTOP)
#	define GLFW_INCLUDE_NONE // Disable the standard OpenGL header inclusion on GLFW3
							  // NOTE: Already provided by rlgl implementation (on glad.h)
#	include "GLFW/glfw3.h"	  // GLFW3 library: Windows, OpenGL context and Input management
							  // NOTE: GLFW3 already includes gl.h (OpenGL) headers

// Support retrieving native window handlers
#	if defined(_WIN32)
typedef void *PVOID;
typedef PVOID HANDLE;
typedef HANDLE HWND;
#		define GLFW_EXPOSE_NATIVE_WIN32
#		define GLFW_NATIVE_INCLUDE_NONE // To avoid some symbols re-definition in windows.h
#		include "GLFW/glfw3native.h"

#		if defined(SUPPORT_WINMM_HIGHRES_TIMER) && !defined(SUPPORT_BUSY_WAIT_LOOP)
// NOTE: Those functions require linking with winmm library
unsigned int __stdcall timeBeginPeriod(unsigned int uPeriod);
unsigned int __stdcall timeEndPeriod(unsigned int uPeriod);
#		endif
#	endif
#	if defined(__linux__) || defined(__FreeBSD__) || defined(__OpenBSD__)
#		include <sys/time.h> // Required for: timespec, nanosleep(), select() - POSIX

// #define GLFW_EXPOSE_NATIVE_X11      // WARNING: Exposing Xlib.h > X.h results in dup symbols for
// RlFont type #define GLFW_EXPOSE_NATIVE_WAYLAND #define GLFW_EXPOSE_NATIVE_MIR
#		include "GLFW/glfw3native.h" // Required for: glfwGetX11Window()
#	endif
#	if defined(__APPLE__)
#		include <unistd.h> // Required for: usleep()

// #define GLFW_EXPOSE_NATIVE_COCOA    // WARNING: Fails due to type redefinition
void *glfwGetCocoaWindow(GLFWwindow *handle);
#		include "GLFW/glfw3native.h" // Required for: glfwGetCocoaWindow()
#	endif

// TODO: HACK: Added flag if not provided by GLFW when using external library
// Latest GLFW release (GLFW 3.3.8) does not implement this flag, it was added for 3.4.0-dev
#	if !defined(GLFW_MOUSE_PASSTHROUGH)
#		define GLFW_MOUSE_PASSTHROUGH 0x0002000D
#	endif
#endif

#if defined(PLATFORM_ANDROID)
// #include <android/sensor.h>           // Required for: Android sensors functions (accelerometer,
// gyroscope, light...)
#	include <android/window.h> // Required for: AWINDOW_FLAG_FULLSCREEN definition and others
#	include <android_native_app_glue.h> // Required for: android_app struct and activity management
#	include <jni.h>					 // Required for: JNIEnv and JavaVM [Used in RL_OpenURL()]

#	include <EGL/egl.h> // Native platform windowing system interface
// #include <GLES2/gl2.h>                // OpenGL ES 2.0 library (not required in this module, only
// in rlgl)
#endif

#if defined(PLATFORM_RPI) || defined(PLATFORM_DRM)
#	include <fcntl.h>	 // POSIX file control definitions - open(), creat(), fcntl()
#	include <unistd.h>	 // POSIX standard function definitions - read(), close(), STDIN_FILENO
#	include <termios.h> // POSIX terminal control definitions - tcgetattr(), tcsetattr()
#	include <pthread.h> // POSIX threads management (inputs reading)
#	include <dirent.h>	 // POSIX directory browsing

#	include <sys/ioctl.h> // Required for: ioctl() - UNIX System call for device-specific input/output operations
#	include <linux/kd.h>		// Linux: KDSKBMODE, K_MEDIUMRAM constants definition
#	include <linux/input.h>	// Linux: Keycodes constants definition (RL_RL_KEY_A, ...)
#	include <linux/joystick.h> // Linux: Joystick support library

#	if defined(PLATFORM_RPI)
#		include "bcm_host.h" // Raspberry Pi VideoCore IV access functions
#	endif
#	if defined(PLATFORM_DRM)
#		include <gbm.h>		 // Generic Buffer Management (native platform for EGL on DRM)
#		include <xf86drm.h>	 // Direct Rendering Manager user-level library interface
#		include <xf86drmMode.h> // Direct Rendering Manager mode setting (KMS) interface
#	endif

#	include "EGL/egl.h"	// Native platform windowing system interface
#	include "EGL/eglext.h" // EGL extensions
// #include "GLES2/gl2.h"            // OpenGL ES 2.0 library (not required in this module, only in
// rlgl)
#endif

#if defined(PLATFORM_WEB)
#	define GLFW_INCLUDE_ES2 // GLFW3: Enable OpenGL ES 2.0 (translated to WebGL)
// #define GLFW_INCLUDE_ES3            // GLFW3: Enable OpenGL ES 3.0 (transalted to WebGL2?)
#	include "GLFW/glfw3.h" // GLFW3: Windows, OpenGL context and Input management
#	include <sys/time.h>	// Required for: timespec, nanosleep(), select() - POSIX

#	include <emscripten/emscripten.h> // Emscripten functionality for C
#	include <emscripten/html5.h>	   // Emscripten HTML5 library
#endif

typedef struct {
	int x;
	int y;
} Point;
typedef struct {
	unsigned int width;
	unsigned int height;
} Size;

// Core global state context data
typedef struct CoreData {
	struct {
#if defined(PLATFORM_DESKTOP) || defined(PLATFORM_WEB)
		GLFWwindow *handle; // GLFW window handle (graphic device)
#endif
#if defined(PLATFORM_RPI)
		EGL_DISPMANX_WINDOW_T handle; // Native window handle (graphic device)
#endif
#if defined(PLATFORM_ANDROID) || defined(PLATFORM_RPI) || defined(PLATFORM_DRM)
#	if defined(PLATFORM_DRM)
		int fd;							// File descriptor for /dev/dri/...
		drmModeConnector *connector;	// Direct Rendering Manager (DRM) mode connector
		drmModeCrtc *crtc;				// CRT Controller
		int modeIndex;					// Index of the used mode of connector->modes
		struct gbm_device *gbmDevice;	// GBM device
		struct gbm_surface *gbmSurface; // GBM surface
		struct gbm_bo *prevBO;			// Previous GBM buffer object (during frame swapping)
		uint32_t prevFB;				// Previous GBM framebufer (during frame swapping)
#	endif								// PLATFORM_DRM
		EGLDisplay device;				// Native display device (physical screen connection)
		EGLSurface surface;				// Surface to draw on, framebuffers (connected to context)
		EGLContext context;				// Graphic context, mode in which drawing can be done
		EGLConfig config;				// Graphic config
#endif
		const char *title;	   // Window text title const pointer
		unsigned int flags;	   // Configuration flags (bit based), keeps window state
		bool ready;			   // Check if window has been initialized successfully
		bool fullscreen;	   // Check if fullscreen mode is enabled
		bool shouldClose;	   // Check if window set for closing
		bool resizedLastFrame; // Check if window has been resized last frame
		bool eventWaiting;	   // Wait for events before ending frame

		Point position;	 // Window position on screen (required on fullscreen toggle)
		Size display;	 // Display width and height (monitor, device-screen, LCD, ...)
		Size screen;	 // Screen width and height (used render area)
		Size currentFbo; // Current render width and height (depends on active fbo)
		Size render; // Framebuffer width and height (render area, including black bars if required)
		Point renderOffset;	  // Offset from render area (must be divided by 2)
		RlMatrix screenScale; // RlMatrix to scale screen (framebuffer rendering)

		char **dropFilepaths;		// Store dropped files paths pointers (provided by GLFW)
		unsigned int dropFileCount; // Count dropped files strings

	} Window;
#if defined(PLATFORM_ANDROID)
	struct {
		bool appEnabled;					// Flag to detect if app is active ** = true
		struct android_app *app;			// Android activity
		struct android_poll_source *source; // Android events polling source
		bool contextRebindRequired;			// Used to know context rebind required
	} Android;
#endif
	struct {
		const char *basePath; // Base path for data storage
	} Storage;
	struct {
#if defined(PLATFORM_RPI) || defined(PLATFORM_DRM)
		InputEventWorker
		  eventWorker[10]; // List of worker threads for every monitored "/dev/input/event<N>"
#endif
		struct {
			int exitKey;							  // Default exit key
			char currentKeyState[MAX_KEYBOARD_KEYS];  // Registers current frame key state
			char previousKeyState[MAX_KEYBOARD_KEYS]; // Registers previous frame key state

			int keyPressedQueue[MAX_KEY_PRESSED_QUEUE]; // Input keys queue
			int keyPressedQueueCount;					// Input keys queue count

			int charPressedQueue[MAX_CHAR_PRESSED_QUEUE]; // Input characters queue (unicode)
			int charPressedQueueCount;					  // Input characters queue count

#if defined(PLATFORM_RPI) || defined(PLATFORM_DRM)
			int defaultMode; // Default keyboard mode
#	if defined(SUPPORT_SSH_KEYBOARD_RPI)
			bool evtMode; // Keyboard in event mode
#	endif
			int defaultFileFlags;			// Default IO file flags
			struct termios defaultSettings; // Default keyboard settings
			int fd;							// File descriptor for the evdev keyboard
#endif
		} Keyboard;
		struct {
			RlVector2 offset;			// Mouse offset
			RlVector2 scale;			// Mouse scaling
			RlVector2 currentPosition;	// Mouse position on screen
			RlVector2 previousPosition; // Previous mouse position

			int cursor;			 // Tracks current mouse cursor
			bool cursorHidden;	 // Track if cursor is hidden
			bool cursorOnScreen; // Tracks if cursor is inside client area

			char currentButtonState[MAX_MOUSE_BUTTONS];	 // Registers current mouse button state
			char previousButtonState[MAX_MOUSE_BUTTONS]; // Registers previous mouse button state
			RlVector2 currentWheelMove;					 // Registers current mouse wheel variation
			RlVector2 previousWheelMove;				 // Registers previous mouse wheel variation
#if defined(PLATFORM_RPI) || defined(PLATFORM_DRM)
			RlVector2 eventWheelMove; // Registers the event mouse wheel variation
			// NOTE: currentButtonState[] can't be written directly due to multithreading, app could
			// miss the update
			char currentButtonStateEvdev[MAX_MOUSE_BUTTONS]; // Holds the new mouse state for the
															 // next polling event to grab
#endif
		} Mouse;
		struct {
			int pointCount;							   // Number of touch points active
			int pointId[MAX_TOUCH_POINTS];			   // Point identifiers
			RlVector2 position[MAX_TOUCH_POINTS];	   // Touch position on screen
			char currentTouchState[MAX_TOUCH_POINTS];  // Registers current touch state
			char previousTouchState[MAX_TOUCH_POINTS]; // Registers previous touch state
		} Touch;
		struct {
			int lastButtonPressed;		 // Register last gamepad button pressed
			int axisCount;				 // Register number of available gamepad axis
			bool ready[MAX_GAMEPADS];	 // Flag to know if gamepad is ready
			char name[MAX_GAMEPADS][64]; // Gamepad name holder
			char currentButtonState[MAX_GAMEPADS]
								   [MAX_GAMEPAD_BUTTONS]; // Current gamepad buttons state
			char previousButtonState[MAX_GAMEPADS]
									[MAX_GAMEPAD_BUTTONS];	 // Previous gamepad buttons state
			float axisState[MAX_GAMEPADS][MAX_GAMEPAD_AXIS]; // Gamepad axis state
#if defined(PLATFORM_RPI) || defined(PLATFORM_DRM)
			pthread_t threadId;			// Gamepad reading thread id
			int streamId[MAX_GAMEPADS]; // Gamepad device file descriptor
#endif
		} Gamepad;
	} Input;
	struct {
		double current;	 // Current time measure
		double previous; // Previous time measure
		double update;	 // Time measure for frame update
		double draw;	 // Time measure for frame draw
		double frame;	 // Time measure for one frame
		double target;	 // Desired time for one frame, if 0 not applied
#if defined(PLATFORM_ANDROID) || defined(PLATFORM_RPI) || defined(PLATFORM_DRM)
		unsigned long long base; // Base time measure for hi-res timer
#endif
		unsigned int frameCounter; // Frame counter
	} Time;
} CoreData;

#include "raylibCoreData.h"

CoreData *getRaylibCoreData() {
	void *raylibCoreData = RL_GetCoreData();
	return (CoreData *)raylibCoreData;
}

#ifdef __cplusplus
extern "C" {
#endif

GLFWwindow *surgeGetGLFWwindow() {
	CoreData *coreData = getRaylibCoreData();
	return coreData->Window.handle;
}

#ifdef __cplusplus
};
#endif
