#if !defined(__PLUGINUTILITIES_H__)
	#define __PLUGINUTILITIES_H__

#include "FMWrapper/FMXTypes.h"
#include "FMWrapper/FMXText.h"
#include "FMWrapper/FMXCalcEngine.h"

#include "FMPlugin.h"


#include <vector>

using namespace std;
using namespace fmx;

typedef auto_ptr<string> StringAutoPtr;
typedef auto_ptr<wstring> WStringAutoPtr;

namespace PluginUtilities
{
	errcode TextConstantFunction(wstring text, fmx::Data& results);
	errcode TextConstantFunction(WStringAutoPtr text, fmx::Data& results);

	void SetResult(const long number, fmx::Data& results);
	void SetResult(const fmx::Text& text, fmx::Data& results);
	void SetResult(const StringAutoPtr text, fmx::Data& results);
	void SetResult(const WStringAutoPtr text, fmx::Data& results);
	void SetResult(const string filename, const vector<char> data, fmx::Data& results);
	void SetResult(const std::string& text, fmx::Data& results);
	void SetResult(const std::wstring& text, fmx::Data& results); 

	bool ParameterAsBoolean(const fmx::DataVect& parameters, const unsigned long which, const bool default_value = true);
	long ParameterAsLong(const fmx::DataVect& parameters, const unsigned long which, const unsigned long default_value);
	std::string ParameterAsUTF8String(const fmx::DataVect& parameters, unsigned long which);
	std::wstring ParameterAsWideString(const fmx::DataVect& parameters, unsigned long which);
	std::string ConvertToUTF8String(const fmx::Text& text);
	std::wstring ConvertToWideString(const fmx::Text& text);

	StringAutoPtr ReadFileAsUTF8(WStringAutoPtr path);
	vector<char> ConvertTextTo(char * in, const size_t length, const string& encoding);
	StringAutoPtr ConvertTextTo(StringAutoPtr in, const string& encoding);
	StringAutoPtr ConvertTextToUTF8(char * in, const size_t length);

	void SetTextEncoding(const string& encoding);

	errcode NoError(void);
	errcode MapError(const errcode error = kNoError, const bool map = false);


	// extract localised strings from the plug-in resources

	void Do_GetString(unsigned long whichString, FMX_ULong winLangID, FMX_Long resultsize, FMX_Unichar* string);
	void Do_GetString(unsigned long whichString,  TextAutoPtr& intoHere, bool stripFunctionParams = false);

	// used by Do_GetString
	#if defined(FMX_MAC_TARGET)
		unsigned long  Sub_OSXLoadString(unsigned long stringID, FMX_Unichar* intoHere, long intoHereMax);
	#endif

	void ReadString(FMX_Unichar* ioBuffer, FMX_UInt32 iBufferSize, FMX_UInt32 iStringID);
	fmx::errcode RegisterExternalFunction(FMX_UInt16 funcID, FMX_Int16 minArgs, FMX_Int16 maxArgs, FMX_UInt32 flags, fmx::ExtPluginType funcPtr );
    fmx::errcode RegisterExternalFunctionEx(FMX_UInt16 funcID, fmx::TextAutoPtr name, fmx::TextAutoPtr prototype,
                                       FMX_Int16 minArgs, FMX_Int16 maxArgs, FMX_UInt32 flags, fmx::ExtPluginType funcPtr );
    fmx::errcode UnRegisterExternalFunction(FMX_UInt16 funcID );
}

#endif // BEPLUGINUTILITIES_H
