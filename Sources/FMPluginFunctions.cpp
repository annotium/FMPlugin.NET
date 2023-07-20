#include "FMPlugin.h"
#include "PluginUtilities.h"
#include "FMTemplate/FMTemplate.h"

#if FMX_WIN_TARGET
#include <Windows.h>
#endif

#define BUFFER_SIZE 256

fmx::errcode g_last_error;
std::string g_text_encoding;

#pragma mark NK_Version
FMX_PROC(fmx::errcode) FMT_Version(short funcId, const fmx::ExprEnv& environment, const fmx::DataVect& dataVect, fmx::Data& result)
{
    fmx::errcode        err = 0;
    FMX_Unichar         pluginVersion[BUFFER_SIZE];
    fmx::TextAutoPtr    tempText;
    fmx::TextAutoPtr    resultText;
    
    if( dataVect.Size() > 0 )
    {
        //We have at least one parameter. Read it and return correct information.
        
        const fmx::Text& parameter1 = dataVect.AtAsText(0);
        
        if( tempText->Assign(""), *tempText == parameter1 )
        {
            //The parameter is an empty string. Return default, "short", version.

            PluginUtilities::ReadString( pluginVersion, sizeof(pluginVersion)/sizeof(FMX_Unichar), PLUGIN_VERSION_ID );
            resultText->AssignUnicode(pluginVersion);
        }
        else if( tempText->Assign("long"), *tempText == parameter1 )
        {
            //The parameter is "long". Return longer version.
            
            fmx::TextAutoPtr tempText;
            FMX_Unichar      pluginName[BUFFER_SIZE];
            
            PluginUtilities::ReadString(pluginName, sizeof(pluginName)/sizeof(FMX_Unichar), 
                       PLUGIN_NAME_ID);
            
            resultText->AssignUnicode(pluginName);
            tempText->Assign(" ");
            resultText->AppendText(*tempText);
            tempText->Assign(PLUGIN_VERSION);
            resultText->AppendText(*tempText);
        }
        else if( tempText->Assign("platform"), *tempText == parameter1 )
        {
            //The parameter is "platform", return. Return platform information.
            
            #if FMX_MAC_TARGET
                resultText->Assign("Mac OS X");
            #else
                resultText->Assign("Windows");
            #endif
        }
        else if( tempText->Assign("short"), *tempText == parameter1 )
        {
            //The parameter is "short". Return short (default) version.

            PluginUtilities::ReadString( pluginVersion, sizeof(pluginVersion)/sizeof(FMX_Unichar), PLUGIN_VERSION_ID );
            resultText->AssignUnicode(pluginVersion);
        }
        else if( tempText->Assign("autoupdate"), *tempText == parameter1 )
        {
            //The parameter is "autoupdate". Return version in format suitable for autoupdate feature.
            
            char auChars[9];
            sprintf_s(auChars, "%02d%02d%02d%02d", 
                    PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR, 
                    PLUGIN_VERSION_BUILD, PLUGIN_VERSION_DEV);
            resultText->Assign(auChars);
        }
        
        err = result.SetAsText( *resultText, dataVect.At(0).GetLocale() );
    }
    else 
    {
        //The function has no parameter. Return short (default) version in the default locale.
        
        fmx::LocaleAutoPtr locale;

        PluginUtilities::ReadString( pluginVersion, sizeof(pluginVersion)/sizeof(FMX_Unichar), PLUGIN_VERSION_ID );
        resultText->AssignUnicode(pluginVersion);
        
        err = result.SetAsText( *resultText, *locale );
    }

    return err;
}

FMX_PROC(fmx::errcode) FMT_CurrentUser(short funcId, const fmx::ExprEnv& environment, const fmx::DataVect& dataVect, fmx::Data& result)
{
    fmx::errcode err = 0;
	char username[256];
	DWORD usrLength = 256;
	::GetUserName(username, &usrLength);
	PluginUtilities::SetResult(username, result);
	return err;
}