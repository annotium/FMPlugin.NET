#ifndef __FMTConfig_h__
#define __FMTConfig_h__

#include "FMPlugin.h"


////////////////////////////////////////////////////////////////////////////////
//
//  Shared constants
//
/////////////////////////////////////////////////////////////////////////////
//
//  The following constants configure your plug-in to behave well under
//  FileMaker applications and to be well recognized on both Mac OS and
//  Windows operating systems. It is recommended to always set all these
//  contants up to contain accurate information about your plug-in.
//

#define PLUGIN_ID_STRING        "HDNP"

#define PLUGIN_NAME             "FMPlugin.NET"
#define PLUGIN_VERSION          "1.0"

#define PLUGIN_VERSION_MAJOR    1
#define PLUGIN_VERSION_MINOR    0
#define PLUGIN_VERSION_BUILD    0
#define PLUGIN_VERSION_DEV      0


#define PLUGIN_INFO             "This plug-in extends FileMaker applications by adding .NET plugin."

#define COMPANY_NAME            "FM Technologies"
#define COPY_STATEMENT          "Copyright ©2014 by " COMPANY_NAME

#define WANT_IDLE               0           // set to 1 if you want idle-processing
#define WANT_PREFERENCES        1           // set to 1 if you want to handle preferences


////////////////////////////////////////////////////////////////////////////////
//
//  Mac OS X constants
//
/////////////////////////////////////////////////////////////////////////////
//
//  Define Mac OS X specific information for you plug-in below.
//

#define PLUGIN_BUNDLE_ID    "com.fmtechs.netplugin"


////////////////////////////////////////////////////////////////////////////////
//
//  Windows constants
//
/////////////////////////////////////////////////////////////////////////////
//
//  Define Windows specific information for you plug-in below.
//

#define FILE_NAME_PC        "FMPlugin.NET.fmx"  // A hint for user who accidentally renames your plug-in

#define PLUGIN_INFO_PC      "This file is a FileMaker applications plug-in. To make this file effective, drop it into FileMaker's Extensions folder and launch the FileMaker application."

#define COMPANY_URL         "http://www.fmtechs.com/"


////////////////////////////////////////////////////////////////////////////////
//
//  Function definitions
//
/////////////////////////////////////////////////////////////////////////////
//
//  Do not modify the following enum, use the defined constants to configure
//  minimum and maximum parameters required for each function
//  (the FUNCTION_X_PARAMS macros)
//

#ifndef __PLIST__
enum {
    kAtLeast_0_Parameters = 0,
    kAtLeast_1_Parameter  = 1,
    kAtLeast_2_Parameters = 2,
    kAtLeast_3_Parameters = 3,
    kAtLeast_4_Parameters = 4,
    kAtLeast_5_Parameters = 5,
    kAtLeast_6_Parameters = 6,
    kAtLeast_7_Parameters = 7,
    kAtLeast_8_Parameters = 8,
    kAtLeast_9_Parameters = 9,
    kAtLeast_10_Parameters = 10,

    kAtWorst_0_Parameters = 0,
    kAtWorst_1_Parameter  = 1,
    kAtWorst_2_Parameters = 2,
    kAtWorst_3_Parameters = 3,
    kAtWorst_4_Parameters = 4,
    kAtWorst_5_Parameters = 5,
    kAtWorst_6_Parameters = 6,
    kAtWorst_7_Parameters = 7,
    kAtWorst_8_Parameters = 8,
    kAtWorst_9_Parameters = 9,
    kAtWorst_10_Parameters = 10,
    kAtWorst_Unlimited_Parameters = -1
};
#endif // __PLIST__

/////////////////////////////////////////////////////////////////////////////
//
//  Define your external functions here. For each of your functions,
//  uncomment the first commented block of defines, and set up the
//  function's name, flags, parameters and prototype.
//

#define FUNCTION_1_C_NAME         ManagedPlugin_Function
#define FUNCTION_1_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
#define FUNCTION_1_PARAMS         kAtLeast_0_Parameters, kAtWorst_1_Parameter
#define FUNCTION_1_PROTOTYPE      "ManagedPlugin_Function( param1 ; ... )"

#define FUNCTION_2_C_NAME         FMT_Version
#define FUNCTION_2_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
#define FUNCTION_2_PARAMS         kAtLeast_0_Parameters, kAtWorst_1_Parameter
#define FUNCTION_2_PROTOTYPE      "FMT_Version({ versionFormat })"

#define FUNCTION_3_C_NAME         FMT_CurrentUser
#define FUNCTION_3_FLAGS          fmx::ExprEnv::kDisplayInAllDialogs
#define FUNCTION_3_PARAMS         kAtLeast_0_Parameters, kAtWorst_1_Parameter
#define FUNCTION_3_PROTOTYPE      "FMT_CurrentUser()"

#define FUNCTION_4_C_NAME         FMT_GetPluginAssemblies
#define FUNCTION_4_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
#define FUNCTION_4_PARAMS         kAtLeast_0_Parameters, kAtWorst_1_Parameter
#define FUNCTION_4_PROTOTYPE      "FMT_GetPluginAssemblies()"

#define FUNCTION_5_C_NAME         FMT_UpdateManagedPlugins
#define FUNCTION_5_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
#define FUNCTION_5_PARAMS         kAtLeast_0_Parameters, kAtWorst_1_Parameter
#define FUNCTION_5_PROTOTYPE      "FMT_UpdateManagedPlugins(param1 ; ... )"

//#define FUNCTION_6_C_NAME         X24FT_Function6
//#define FUNCTION_6_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
//#define FUNCTION_6_PARAMS         kAtLeast_0_Parameters, kAtWorst_Unlimited_Parameters
//#define FUNCTION_6_PROTOTYPE      "X24FT_Function6( param1 ; ... )"

//#define FUNCTION_7_C_NAME         X24FT_Function7
//#define FUNCTION_7_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
//#define FUNCTION_7_PARAMS         kAtLeast_0_Parameters, kAtWorst_Unlimited_Parameters
//#define FUNCTION_7_PROTOTYPE      "X24FT_Function7( param1 ; ... )"

//#define FUNCTION_8_C_NAME         X24FT_Function8
//#define FUNCTION_8_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
//#define FUNCTION_8_PARAMS         kAtLeast_0_Parameters, kAtWorst_Unlimited_Parameters
//#define FUNCTION_8_PROTOTYPE      "X24FT_Function8( param1 ; ... )"

//#define FUNCTION_9_C_NAME         X24FT_Function9
//#define FUNCTION_9_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
//#define FUNCTION_9_PARAMS         kAtLeast_0_Parameters, kAtWorst_Unlimited_Parameters
//#define FUNCTION_9_PROTOTYPE      "X24FT_Function9( param1 ; ... )"

//#define FUNCTION_10_C_NAME         X24FT_Function10
//#define FUNCTION_10_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
//#define FUNCTION_10_PARAMS         kAtLeast_0_Parameters, kAtWorst_Unlimited_Parameters
//#define FUNCTION_10_PROTOTYPE      "X24FT_Function10( param1 ; ... )"

////////////////////////////////////////////////////////////////////////////////

#endif // __FMTConfig_h__
