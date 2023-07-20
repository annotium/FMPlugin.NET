#ifndef __FMTemplate_h__
#define __FMTemplate_h__
  
  //  Define macros we can later use regardless of what environment is being used
  //  It is strongly recommended that you use the macros defined here for any conditional
  //  compilation, instead of the environment-dependent equivalents
  
  #if defined( __GNUC__ )

    #undef __CONSTANT_CFSTRINGS__
	
	
	
	//  Requires Prefix file that includes Carbon/Carbon.h
    #define FMX_MAC_TARGET  TARGET_OS_MAC
    #define FMX_WIN_TARGET  TARGET_OS_WIN32
    
    //  XCode projects have the FMPLUGIN_DEBUG macro defined in preprocessor
    //  options for the Development build style
    
    // #define FMPLUGIN_DEBUG  1

  #elif defined(__MWERKS__)

    //  Set the proper FMX_PLATFORM_TARGET macros
    #define FMX_MAC_TARGET  __MACOS__
    #define FMX_WIN_TARGET  __INTEL__
    
    //  Assume debug build if there is a marker in the project window debug column
    #if __option(sym)
        #define FMPLUGIN_DEBUG 1
    #else
        #define FMPLUGIN_DEBUG 0
    #endif

  #elif defined( _MSC_VER )
    #define FMX_MAC_TARGET  0
    #define FMX_WIN_TARGET  1
    #ifdef _DEBUG
        #define FMPLUGIN_DEBUG  1
    #else
        #define FMPLUGIN_DEBUG  0
    #endif // _DEBUG

  #endif // Compiler specific directives

  
  //  Include FMAPI headers so that they don't have to be included manually
  #ifndef _h_Extern_
    #include "FMPlugInSDK/Headers/FMWrapper/FMXExtern.h"
  #endif
  #ifndef _h_Types_
    #include "FMPlugInSDK/Headers/FMWrapper/FMXTypes.h"
  #endif
  #ifndef _h_FixPt_
    #include "FMPlugInSDK/Headers/FMWrapper/FMXFixPt.h"
  #endif
  #ifndef _h_Text_
    #include "FMPlugInSDK/Headers/FMWrapper/FMXText.h"
  #endif
  #ifndef _h_Data_
    #include "FMPlugInSDK/Headers/FMWrapper/FMXData.h"
  #endif
  #ifndef _h_DBCalcEngine_
    #include "FMPlugInSDK/Headers/FMWrapper/FMXCalcEngine.h"
  #endif
  #ifndef _h_TextStyle_
    #include "FMPlugInSDK/Headers/FMWrapper/FMXTextStyle.h"
  #endif
  #ifndef _h_BinaryData_
    #include "FMPlugInSDK/Headers/FMWrapper/FMXBinaryData.h"
  #endif
  #ifndef _h_DateTime_
    #include "FMPlugInSDK/Headers/FMWrapper/FMXDateTime.h"
  #endif

#include <vector>
  
  //  Define a more convenient FMX_UniChar type which matches the UniChar type's case
  typedef FMX_Unichar FMX_UniChar;
  

  //  Include additional FM Template headers so that FMTemplate.h is the only one required
  #ifndef __FMUtils_h__
    //#include "FMTemplate/FMUtils.h"
  #endif
  
  #ifndef __FMTConfig_h__
  	#include "FMTConfig.h"
  #endif
  
  
  #if __cplusplus
    extern "C" {
  #endif
  
    #if FMX_WIN_TARGET
        HINSTANCE   GetPluginInstance();
    #endif

    #if FMX_MAC_TARGET
        CFBundleRef GetPluginBundle();
    #endif
    
  #if __cplusplus
    }
  #endif  
  
	extern FMX_Boolean  Startup();
	extern void         Shutdown();
	
	#if WANT_IDLE
	    extern void         SafeIdle();
    	extern void         SemiSafeIdle(FMX_IdleLevel idleLevel);
    	extern void         UnsafeIdle();
    #endif //WANT_IDLE
    
    #if WANT_PREFERENCES
    	extern void         Preferences();
    #endif //WANT_PREFERENCES

	extern std::vector<unsigned short> gRegisteredFunctions; 

	#ifdef FUNCTION_1_C_NAME
	extern FMX_PROC(fmx::errcode) FUNCTION_1_C_NAME(short, const fmx::ExprEnv&, const fmx::DataVect&, fmx::Data&);
	#endif
	#ifdef FUNCTION_2_C_NAME
	extern FMX_PROC(fmx::errcode) FUNCTION_2_C_NAME(short, const fmx::ExprEnv&, const fmx::DataVect&, fmx::Data&);
	#endif
	#ifdef FUNCTION_3_C_NAME
	extern FMX_PROC(fmx::errcode) FUNCTION_3_C_NAME(short, const fmx::ExprEnv&, const fmx::DataVect&, fmx::Data&);
	#endif
	#ifdef FUNCTION_4_C_NAME
	extern FMX_PROC(fmx::errcode) FUNCTION_4_C_NAME(short, const fmx::ExprEnv&, const fmx::DataVect&, fmx::Data&);
	#endif
	#ifdef FUNCTION_5_C_NAME
	extern FMX_PROC(fmx::errcode) FUNCTION_5_C_NAME(short, const fmx::ExprEnv&, const fmx::DataVect&, fmx::Data&);
	#endif
	#ifdef FUNCTION_6_C_NAME
	extern FMX_PROC(fmx::errcode) FUNCTION_6_C_NAME(short, const fmx::ExprEnv&, const fmx::DataVect&, fmx::Data&);
	#endif
	#ifdef FUNCTION_7_C_NAME
	extern FMX_PROC(fmx::errcode) FUNCTION_7_C_NAME(short, const fmx::ExprEnv&, const fmx::DataVect&, fmx::Data&);
	#endif
	#ifdef FUNCTION_8_C_NAME
	extern FMX_PROC(fmx::errcode) FUNCTION_8_C_NAME(short, const fmx::ExprEnv&, const fmx::DataVect&, fmx::Data&);
	#endif
	#ifdef FUNCTION_9_C_NAME
	extern FMX_PROC(fmx::errcode) FUNCTION_9_C_NAME(short, const fmx::ExprEnv&, const fmx::DataVect&, fmx::Data&);
	#endif
	#ifdef FUNCTION_10_C_NAME
	extern FMX_PROC(fmx::errcode) FUNCTION_10_C_NAME(short, const fmx::ExprEnv&, const fmx::DataVect&, fmx::Data&);
	#endif
  

#endif // __FMTemplate_h__


