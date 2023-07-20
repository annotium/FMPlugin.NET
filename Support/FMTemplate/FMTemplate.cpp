//  FMTConfig.h is required somewhere as it configures the FM Template
#include "FMTConfig.h"

#include "FMTemplate/FMTemplate.h"

#include "PluginUtilities.h"

#include "FMPlugin.h"

#include "ManagedWrapper.h"

#if FMX_WIN_TARGET
    #include <Windows.h>
#endif

// ====== Forward Declaration ==============================================================================

#define FMT_FUNCTION_ID 15
static FMX_Int32     Do_PluginInit(FMX_Int16 version);
static void         Do_PluginShutdown(void);

#if WANT_IDLE
static void         Do_PluginIdle(FMX_IdleLevel idleLevel);
#endif //WANT_IDLE

#if WANT_PREFERENCES
static void         Do_PluginPrefs();
#endif //WANT_PREFERENCES

static void         Do_PluginGetString();
static void			ProvideConfigString(FMX_UniChar* ioBuffer, FMX_UInt32 iBufferSize );
static void         ProvideNameString(FMX_UniChar* ioBuffer, FMX_UInt32 iBufferSize);
static void         ProvidePreferencesString(FMX_UniChar* ioBuffer, FMX_UInt32 iBufferSize);

       FMX_Boolean  RegisterExternalFunctions();
       void         UnRegisterExternalFunctions();


// ====== Global Variables =================================================================================

    FMX_ExternCallPtr   gFMX_ExternCallPtr=NULL;
    FMX_Boolean         gPlugInInitialized=0;
    FMX_Boolean         gPrefsOpen=0;
	ManagedWrapper*		g_managedWrapper;
	std::vector<unsigned short> gRegisteredFunctions; 

void FMX_ENTRYPT FMExternCallProc(FMX_ExternCallPtr pb)
{
    // Setup global defined in FMxExtern.h
    gFMX_ExternCallPtr = pb;

    // Message dispatcher
    switch (gFMX_ExternCallPtr->whichCall) 
    {
        case kFMXT_Init:
            gFMX_ExternCallPtr->result = Do_PluginInit(gFMX_ExternCallPtr->extnVersion);
            break;
            
        case kFMXT_Shutdown:
            Do_PluginShutdown();
            break;

        case kFMXT_GetString:
            Do_PluginGetString();
            break;

        #if WANT_IDLE
            case kFMXT_Idle:
                Do_PluginIdle(gFMX_ExternCallPtr->parm1);
                break;
        #endif //WANT_IDLE
        
        #if WANT_PREFERENCES
            case kFMXT_DoAppPreferences:
                Do_PluginPrefs();
                break;
        #endif //WANT_PREFERENCES
        
    };// switch whichCall

} // FMExternCallProc


// ====== Handlers =========================================================================================

static FMX_Int32 Do_PluginInit(FMX_Int16 version) 
{
    // Check the app API version
    if ((version < k70ExtnVersion) || (version > kMaxExtnVersion)) {
        // This version of FileMaker is not supported; let FileMaker disable this 
        // plug-in and report the problem to the user.
        return (kBadExtnVersion);
    }

    if (Startup()) {
        if(RegisterExternalFunctions()) {
            gPlugInInitialized = 1;
            return kCurrentExtnVersion;
        }
        else {
            Shutdown();
		}
    }
    
    return kDoNotEnable;
    
} // Do_PluginInit


static void Do_PluginShutdown(void) 
{
    gPlugInInitialized = 0;

    UnRegisterExternalFunctions();
    Shutdown();
} // Do_PluginShutdown


#if WANT_IDLE
    void Do_PluginIdle(FMX_IdleLevel idleLevel) 
    {
        //  eliminate the race condition we would be called when Startup is not yet done!
        if(gPlugInInitialized) {
            if(idleLevel == kFMXT_UserIdle)
                SafeIdle();
            else if (idleLevel == kFMXT_Unsafe)
                UnsafeIdle();
            else 
                SemiSafeIdle(idleLevel);
        }
    } // Do_PluginIdle
#endif //WANT_IDLE


#if WANT_PREFERENCES    
    static void Do_PluginPrefs()
    {
        //  Avoid opening multiple instances of the preferences dialog
        if (!gPrefsOpen) {
			g_managedWrapper->showPreferencesDialog();
        }
    }
#endif //WANT_PREFERENCES


static void Do_PluginGetString()
{
    FMX_Strings   stringType          = gFMX_ExternCallPtr->parm1;
   // FMX_UInt32     windowsLanguageID   = gFMX_ExternCallPtr->parm2;
    FMX_UInt32   outStringBufferSize = (FMX_UInt32)gFMX_ExternCallPtr->parm3;
    FMX_Unichar*  outStringBuffer     = (FMX_Unichar*)(gFMX_ExternCallPtr->result);
         
    switch(stringType)
    {
        case    kFMXT_OptionsStr:
            ProvideConfigString(outStringBuffer, outStringBufferSize);
            break;
        
        case    kFMXT_NameStr:
            ProvideNameString(outStringBuffer, outStringBufferSize);
            break;
            
        case    kFMXT_AppConfigStr:
            ProvidePreferencesString(outStringBuffer, outStringBufferSize);
            break;
    }
}


#if FMX_WIN_TARGET
    HINSTANCE   GetPluginInstance()
    {
        return (HINSTANCE)gFMX_ExternCallPtr->instanceID;
    }
#endif


#if FMX_MAC_TARGET
    CFBundleRef GetPluginBundle()
    {
        return (CFBundleRef)gFMX_ExternCallPtr->instanceID;
    }
#endif


void ProvideConfigString(FMX_UniChar* ioBuffer, FMX_UInt32 iBufferSize)
{
    #pragma unused(iBufferSize)
    
    //  Provide plug-in config string here.
    
    ioBuffer[ 0] = ((unsigned char*)PLUGIN_ID_STRING)[0];
    ioBuffer[ 1] = ((unsigned char*)PLUGIN_ID_STRING)[1];
    ioBuffer[ 2] = ((unsigned char*)PLUGIN_ID_STRING)[2];
    ioBuffer[ 3] = ((unsigned char*)PLUGIN_ID_STRING)[3];
    ioBuffer[ 4] = '1'; 

    #if WANT_PREFERENCES
        ioBuffer[ 5] = 'Y';
    #else
        ioBuffer[ 5] = 'n';
    #endif

    ioBuffer[ 6] = 'n';
    ioBuffer[ 7] = 'Y';

    #if WANT_IDLE
        ioBuffer[ 8] = 'Y';
    #else
        ioBuffer[ 8] = 'n';
    #endif

    ioBuffer[ 9] = 'n';
    ioBuffer[10] = 'n';
    ioBuffer[11] = 0;
}


void ProvideNameString(FMX_Unichar* ioBuffer, FMX_UInt32 iBufferSize)
{
    //  Provide plug-in name string here.
    PluginUtilities::ReadString(ioBuffer, iBufferSize, PLUGIN_NAME_ID);
}


void ProvidePreferencesString(FMX_Unichar* ioBuffer, FMX_UInt32 iBufferSize)
{
    //  Provide plug-in name string here.
    PluginUtilities::ReadString(ioBuffer, iBufferSize, PLUGIN_PREFERENCES_ID);
}

#define REGFUNCTION_CONCAT(x) (FUNCTION_ ## x ## _FLAGS)
#define REGFUNCTION_FLAG(x) (0 | REGFUNCTION_CONCAT(x))

fmx::errcode registerFunction(unsigned short funcId, unsigned short minArgs, unsigned short maxArgs, unsigned int flags, fmx::ExtPluginType funcPtr)
{
    fmx::errcode err = PluginUtilities::RegisterExternalFunction(funcId, minArgs, maxArgs, flags, funcPtr);
	if (err) {
		PluginUtilities::UnRegisterExternalFunction(funcId);
	}
	else {
		gRegisteredFunctions.push_back(funcId);
	}

	return err;
}

FMX_Boolean RegisterExternalFunctions()
{   
    //  if enable = FALSE is returned, Shutdown will 
    //  be called and plug-in will not be activated.
    
    FMX_Boolean enable = FALSE;
	g_managedWrapper = new ManagedWrapper();

	registerFunction(2, FUNCTION_2_PARAMS, REGFUNCTION_FLAG(2), FMT_Version);
    registerFunction(3, FUNCTION_2_PARAMS, REGFUNCTION_FLAG(3), FMT_CurrentUser); 
    registerFunction(4, FUNCTION_2_PARAMS, REGFUNCTION_FLAG(4), FMT_GetPluginAssemblies); 

	g_managedWrapper->registerMethods(FMT_FUNCTION_ID);

    return TRUE;
}

void UnRegisterExternalFunctions()
{
    // Unregister plug-in functions
    fmx::QuadCharAutoPtr pluginID(PLUGIN_ID_STRING[0], PLUGIN_ID_STRING[1], PLUGIN_ID_STRING[2], PLUGIN_ID_STRING[3]);
	g_managedWrapper->unregisterMethods();
	for (std::size_t i = 0; i < gRegisteredFunctions.size(); ++i) {
		unsigned short funcId = gRegisteredFunctions[i];
		PluginUtilities::UnRegisterExternalFunction(funcId);
	}

	gRegisteredFunctions.clear(); 
	delete g_managedWrapper;
}

FMX_PROC(fmx::errcode) ManagedPlugin_Function(short funcId, const fmx::ExprEnv& env, const fmx::DataVect& dataVect, fmx::Data& result)
{
    return g_managedWrapper->executeMethod(funcId, dataVect, result);
}

FMX_PROC(fmx::errcode) FMT_GetPluginAssemblies(short funcId, const fmx::ExprEnv& env, const fmx::DataVect& dataVect, fmx::Data& result)
{
	std::string paths = g_managedWrapper->getPluginAssemblyPaths();
	PluginUtilities::SetResult(paths, result);
	return 0;
}

FMX_PROC(fmx::errcode) FMT_UpdateManagedPlugins(short funcId, const fmx::ExprEnv& env, const fmx::DataVect& dataVect, fmx::Data& result)
{
	if (g_managedWrapper != nullptr) {
		g_managedWrapper->unregisterMethods();
		g_managedWrapper->registerMethods(FMT_FUNCTION_ID);
	}
	return 0;
}