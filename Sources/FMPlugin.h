#ifndef __FMPlugin_h__
#define __FMPlugin_h__

/////////////////////////////////////////////////////////////////////////////
//
//  Don't modify the following constats, they are not yet fully customizable
//  in this version of 24U Plug-In Template. These constants define IDs of
//  localizable string resources, and are required for the plug-in to
//  work properly.
//

#define PLUGIN_NAME_ID          1
#define PLUGIN_PREFERENCES_ID   2
#define PLUGIN_VERSION_ID       3

#define FUNCTION_OFFSET       100

#include "FMPlugInSDK/Headers/FMWrapper/FMXExtern.h"

/////////////////////////////////////////////////////////////////////////////
//
//  We are including this header in FMTConfig.h which is included by
//  FMTemplate.plc. The following definitions are for use in code only,
//  so we are excluding them from Plist definition from.
//

#if defined( __GNUC__ )

	#define FMX_MAC_TARGET	1

	/*
	 Unloadable modules can not use the new style constant strings that Apple introduced
	 in 10.4. So we have to turn if off in the headers and the project file with
	 */
	#undef __CONSTANT_CFSTRINGS__

	#define USER_PREFERENCES_DOMAIN L"au.com.goya.baseelements.plugin-user"

#elif defined( _MSC_VER )

	#define FMX_WIN_TARGET	1
	#define USER_PREFERENCES_DOMAIN L"Software\\NKSoftware\\PluginTemplate\\PluginUser"

#endif 

class ManagedWrapper;

#ifndef __PLIST__

  #if __cplusplus
    extern "C" {
  #endif
  
	extern fmx::errcode g_last_error;
	extern ManagedWrapper* g_managedWrapper;
	enum {
		kNK_OptionsStringID = 1
	}; 

	enum functions {
		kNK_Version = 102,
		kNK_VersionAutoUpdate = 103,
		kNK_ClipboardFormats = 104,
		kNK_ClipboardData = 105,
		kNK_SetClipboardData = 106,
		kNK_CreateFolder = 107,
		kNK_DeleteFile = 108,
		kNK_FileExists = 109,
		kNK_ReadTextFromFile = 110,
		kNK_WriteTextToFile = 111,
		kNK_SelectFile = 112,
		kNK_SelectFolder = 113,
		kNK_DisplayDialog = 114,
		kNK_ApplyXSLT = 115,
		kNK_ExtractScriptVariables = 116,
		kNK_StripInvalidUTF16CharactersFromXMLFile = 117,
		kNK_MoveFile = 118,
		kNK_CopyFile = 119,
		kNK_ExecuteShellCommand = 120,
		kNK_ListFilesInFolder = 121,
		kNK_FileMaker_Tables = 122,
		kNK_FileMaker_Fields = 123,
		kNK_OpenURL = 124,
		kNK_OpenFile = 125,
		kNK_ExecuteScript = 150,
		kNK_FileMakerSQL = 151,
		kNK_GetURL = 152,
		kNK_GetLastError = 153,
		kNK_MessageDigest = 154,
		kNK_GetLastDDLError = 155,
		kNK_SaveURLToFile = 156,
		kNK_SetPreference = 160,
		kNK_GetPreference = 161,
		kNK_Unzip = 170,
		kNK_Zip = 171,
		kNK_Base64_Decode = 172,
		kNK_Base64_Encode = 173,
		kNK_SetTextEncoding = 174,
		kNK_HTTP_POST = 180,
		kNK_HTTP_Response_Code = 181,
		kNK_HTTP_Response_Headers = 182,
		kNK_HTTP_Set_Custom_Header = 183,
		kNK_ApplyXSLTInMemory = 200,
		kNK_XPath = 201,
		kNK_XPathAll = 202
	};


	enum dialog_buttons {
		kNK_OKButton = 1,
		kNK_CancelButton = 2,
		kNK_AlternateButton = 3
	};


	enum errors {
		kErrorUnknown = -1,
		kNoError = 0,
		kNoSuchFileOrDirectoryError = 2,
		kLowMemoryError = 7,
		kRequestedDataIsMissingError = 10,
		kFileExistsError = 17,
		kErrorParameterMissing = 102,
		kFileSystemError = 10000,
		kDDLCommandQueued = 11000
	};


	enum {
		kNK_NumericConstantOffset = 1000,
		kNK_ButtonOffset = 1000,
		kNK_MessageDigestTypeOffset = 2000,
		kNK_FileTypeOffset = 3000,
		kNK_GetStringMaxBufferSize = 4096
	};


	enum message_digest_type {
		kNK_MessageDigestType_MD5 = 1,
		kNK_MessageDigestType_SHA256 = 2
	};


	enum file_type {
		kNK_FileType_ALL = 0,
		kNK_FileType_File = 1,
		kNK_FileType_Folder = 2
	};
  
  #if __cplusplus
    }
  #endif

#endif //__PLIST__

/////////////////////////////////////////////////////////////////////////////

#endif // __FMPlugin_h__
