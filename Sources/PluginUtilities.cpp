#include "PluginUtilities.h"
#include "FMTConfig.h"
#include "FMTemplate/FMTemplate.h"

#if FMX_WIN_TARGET
	#include <Windows.h>
#endif


#if FMX_MAC_TARGET

	#include <CoreServices/CoreServices.h>
	#include <Carbon/Carbon.h>

#endif 


#include "FMWrapper/FMXBinaryData.h"
#include "FMWrapper/FMXData.h"
#include "FMWrapper/FMXFixPt.h"

using namespace fmx;

extern string g_text_encoding;

#pragma mark -
#pragma mark Plug-In Utilities
#pragma mark -

// convenience functions that handle most of the work needed to return text from a function

namespace PluginUtilities
{
	errcode TextConstantFunction(wstring text, Data& results)
	{
		WStringAutoPtr text_constant(new wstring(text));	
		return TextConstantFunction(text_constant, results);
	} // TextConstantFunction


	errcode TextConstantFunction(WStringAutoPtr text, Data& results)
	{
		errcode error_result = kNoError;
	
		try {
		
			TextAutoPtr result_text;
			result_text->AssignWide(text->c_str());
		
			LocaleAutoPtr default_locale;
			results.SetAsText(*result_text, *default_locale);
		
		} catch(bad_alloc&) {
			error_result = kLowMemoryError;
		} catch(exception&) {
			error_result = kErrorUnknown;
		}
	
		return error_result;	
	} // TextConstantFunction


	// get parameters and set function results


	#pragma mark -
	#pragma mark SetResult
	#pragma mark -

	void SetResult(const long number, Data& results)
	{
		FixPtAutoPtr numeric_result;
		numeric_result->AssignInt(number);
		results.SetAsNumber(*numeric_result);
	}


	void SetResult(const Text& text, Data& results)
	{
		LocaleAutoPtr default_locale;
		results.SetAsText(text, *default_locale);
	}


	void SetResult(const StringAutoPtr text, Data& results)
	{
		TextAutoPtr result_text;
		result_text->Assign(text->c_str(), Text::kEncoding_UTF8);			
		SetResult(*result_text, results);
	}


	void SetResult(const WStringAutoPtr text, Data& results)
	{
		TextAutoPtr result_text;
		result_text->AssignWide(text->c_str());			
		SetResult(*result_text, results);
	}

	void SetResult(const std::string& text, Data& results)
	{
		TextAutoPtr result_text;
		result_text->Assign(text.c_str(), Text::kEncoding_UTF8);			
		SetResult(*result_text, results);
	}

	void SetResult(const std::wstring& text, Data& results)
	{
		TextAutoPtr result_text;
		result_text->AssignWide(text.c_str());			
		SetResult(*result_text, results);
	} 

	void SetResult(const string filename, const vector<char> data, Data& results)
	{
		bool as_binary = !filename.empty();
	
		if(as_binary) {	// if a file name is supplied send back a file
		
			BinaryDataAutoPtr resultBinary;
			TextAutoPtr file;
			file->Assign(filename.c_str(), Text::kEncoding_UTF8);
			resultBinary->AddFNAMData(*file); 
			QuadCharAutoPtr data_type('F', 'I', 'L', 'E'); 
			resultBinary->Add(*data_type, data.size(),(void *)&data[0]); 
			results.SetBinaryData(*resultBinary, true); 
		
		} else { // otherwise try sending back text

			// filemaker will go into an infinite loop if non-utf8 data is set as utf8
			// so try to convert it first
		
			const string data_string(data.begin(), data.end());
			StringAutoPtr utf8 = ConvertTextToUTF8((char *)data_string.c_str(), data_string.size());
			SetResult(utf8, results);
		
		}
	
	} // SetBinaryDataResult


	#pragma mark -
	#pragma mark ParameterAs
	#pragma mark -

	bool ParameterAsBoolean(const DataVect& parameters, const unsigned long which, const bool default_value)
	{
		try {
			return parameters.AtAsBoolean(which);
		}
		catch(exception&) {
			return default_value;
		}
	}
	
	
	long ParameterAsLong(const DataVect& parameters, const unsigned long which, const unsigned long default_value)
	{
		try {
			return parameters.AtAsNumber(which).AsLong();
		}
		catch(exception&) {
			return default_value;
		}
	}


	std::string ParameterAsUTF8String(const DataVect& parameters, unsigned long which)
	{	
		std::string result("");
	
		try {
		
			TextAutoPtr raw_data;
			raw_data->SetText(parameters.AtAsText(which));
		
			ulong text_size =(2*(raw_data->GetSize())) + 1;
			char * text = new char [ text_size ]();
			raw_data->GetBytes(text, text_size, 0,(ulong)Text::kSize_End, Text::kEncoding_UTF8);
			result = std::string(text);
			delete [] text;
		
		} catch(exception&) {
			;	// return an empty string
		}
	
		return result;
	} // ParameterAsUTF8String



	std::wstring ParameterAsWideString(const DataVect& parameters, unsigned long which)
	{
		std::wstring result(L"");
	
		try {
		
			TextAutoPtr raw_data;
			raw_data->SetText(parameters.AtAsText(which));
		
			long text_size = raw_data->GetSize();
			ushort * text = new ushort [ text_size + 1 ];
			raw_data->GetUnicode(text, 0, text_size);
			text[text_size] = 0x0000;

			// wchar_t is 4 bytes on OS X and 2 on Windows
		
			#if FMX_MAC_TARGET
		
				wchar_t * parameter = new wchar_t [ text_size + 1 ];
				for(long i = 0 ; i <= text_size ; i++) {
					parameter[i] =(wchar_t)text[i];
				}
				delete [] text;
		
			#endif 
		
			#if FMX_WIN_TARGET	
				wchar_t * parameter =(wchar_t*)text;
			#endif
		
			result.append(parameter);
			delete [] parameter; // parameter == text on Windows
				
		} catch(exception&) {
			;	// return an empty string
		}
	
		return result;
	} // ParameterAsUnicodeString

	std::string ConvertToUTF8String(const fmx::Text& text)
	{
		std::string result("");
	
		try {
			ulong text_size =(2*(text.GetSize())) + 1;
			char * buffer = new char [ text_size ]();
			text.GetBytes(buffer, text_size, 0,(ulong)Text::kSize_End, Text::kEncoding_UTF8);
			result = std::string(buffer);
			delete [] buffer;
		
		} catch(exception&) {
			;	// return an empty string
		}
	
		return result;
	}

	std::wstring ConvertToWideString(const fmx::Text& text)
	{
		std::wstring result(L"");
	
		try {
			long text_size = text.GetSize();
			ushort * buffer = new ushort [ text_size + 1 ];
			text.GetUnicode(buffer, 0, text_size);
			buffer[text_size] = 0x0000;

			// wchar_t is 4 bytes on OS X and 2 on Windows
		
			#if FMX_MAC_TARGET
		
				wchar_t * parameter = new wchar_t [ text_size + 1 ];
				for(long i = 0 ; i <= text_size ; i++) {
					parameter[i] =(wchar_t)text[i];
				}
				delete [] text;
		
			#endif 
		
			#if FMX_WIN_TARGET		
				wchar_t * parameter =(wchar_t*)buffer;
			#endif
		
			result.append(parameter);
			delete [] parameter; // parameter == text on Windows
				
		} catch(exception&) {
			;	// return an empty string
		}
	
		return result;
	}



	#pragma mark -
	#pragma mark Files
	#pragma mark -

	StringAutoPtr ReadFileAsUTF8(WStringAutoPtr path)
	{
	
		StringAutoPtr result(new string);	
		return result;
	
	} // ReadFileAsUTF8



	#pragma mark -
	#pragma mark Unicode
	#pragma mark -

	vector<char> ConvertTextTo(char * in, const size_t length, const string& encoding)
	{
		/*size_t available =(length * 4) + 1;	// worst case for utf-32 to utf-8 ?
		char * encoded = new char [available]();	// value-initialization(to zero)… we crash otherwise
	
		vector<string> codesets;
		codesets.push_back(g_text_encoding);
		codesets.push_back("UTF-16"); // backwards compatibility with v1.2
	
	
		int error_result = -1;
		vector<string>::iterator it = codesets.begin();
		size_t remaining = available;
	
		while(error_result == -1 && it != codesets.end()) {
		
			char * start = in;
			size_t start_length = length;
			char * encoded_start = encoded;
		
			iconv_t conversion = iconv_open(encoding.c_str(), it->c_str());
			error_result = iconv(conversion, &start, &start_length, &encoded_start, &remaining);
			iconv_close(conversion);
		
			++it;
		}
	
		vector<char> out(encoded, encoded + available - remaining);
		delete[] encoded;*/
	
		vector<char> out;
		return out;
	
	} // ConvertToUTF8



	StringAutoPtr ConvertTextTo(StringAutoPtr in, const string& encoding)
	{
		vector<char> text = ConvertTextTo((char *)in->c_str(),(const size_t)in->size() - 1, encoding);
		StringAutoPtr out(new string(text.begin(), text.end()));
		return out;
	}


	// convert text to utf-8
	// currently handles utf-16, ascii and utf-8 text

	StringAutoPtr ConvertTextToUTF8(char * in, const size_t length)
	{
		vector<char> text = ConvertTextTo(in, length, "UTF-8");
		StringAutoPtr out(new string(text.begin(), text.end()));
		return out;
	} // ConvertToUTF8


	void SetTextEncoding(const string& encoding)
	{
		if(encoding.empty()) {
			g_text_encoding = "UTF-8";
		} else {
			g_text_encoding = encoding;
		}	
	}


	#pragma mark -
	#pragma mark Errors
	#pragma mark -

	// Should be called at the start of each plugin function to clear out the global error

	errcode NoError(void)
	{
		g_last_error = kNoError;
		return g_last_error;
	}

	// use as the return value for al plugin functions
	// only return errors to FileMaker that it can make sense of

	errcode MapError(const errcode error, const bool map)
	{
		errcode mapped_error = kNoError;
	
		// map the error to a FileMaker error(so that FMP can display an
		// appropriate dialog etc.
	
		if(map) {
			mapped_error = error;
			g_last_error = error;
		} else {
			// map all other errors to "unknown"
			if(error != kNoError || g_last_error != kNoError) {
				mapped_error = kErrorUnknown;
			}

			// overwrite g_last_error, but only if it's not already set
			if(g_last_error == kNoError) {
				g_last_error = error;
			}
		}

		return mapped_error;
	}


	#pragma mark -
	#pragma mark Other
	#pragma mark -

	/*
	 The following functions are modifications of ones included in the Example plug-in
	 shipped by FileMaker Inc. with the External Plug-In API on the CDs for 
	 FileMaker Developer/Pro Advance versions 7 through 10 and are used by permission.
	 */

	void Do_GetString(unsigned long whichString, FMX_ULong /* winLangID */, FMX_Long resultsize, FMX_Unichar* string)
	{
		switch(whichString)
		{
			case kFMXT_OptionsStr:
			{
	#if FMX_WIN_TARGET
				LoadStringW((HINSTANCE)(gFMX_ExternCallPtr->instanceID), kNK_OptionsStringID,(LPWSTR)string, resultsize);
	#endif
			
	#if FMX_MAC_TARGET
				Sub_OSXLoadString(kBE_OptionsStringID, string, resultsize);
	#endif

	//			processedSpecialStringID = true;
				break;
			}
			default:
	#if FMX_WIN_TARGET
				LoadStringW((HINSTANCE)(gFMX_ExternCallPtr->instanceID),(unsigned int)whichString,(LPWSTR)string, resultsize);
	#endif
				
	#if FMX_MAC_TARGET
				Sub_OSXLoadString(whichString, string, resultsize);
	#endif
	
		} // switch(whichString)
	
	
	} // Do_GetString(FMX_Unichar* version)


	void Do_GetString(unsigned long whichStringID, TextAutoPtr& intoHere, bool stripFunctionParams)
	{
		FMX_Unichar	tempBuffer[kNK_GetStringMaxBufferSize];
	
		Do_GetString(whichStringID, 0, kNK_GetStringMaxBufferSize, tempBuffer);
		intoHere->AssignUnicode(tempBuffer);
	
		if(stripFunctionParams) {
		
			// The string for this whichStringID is a Function Prototype, but all the plug-in needs now is the Function Name by itself.
		
			TextAutoPtr		parenToken;
			parenToken->Assign("(");
		
			unsigned long		originalSize = intoHere->GetSize();
			unsigned long		firstParenLocation; 
			firstParenLocation = intoHere->Find(*parenToken, 0);
		
			intoHere->DeleteText(firstParenLocation, originalSize-firstParenLocation);
		
		} // stripFunctionParams
	
	} // Do_GetString(TextAutoPtr version)



	#if FMX_MAC_TARGET

	unsigned long Sub_OSXLoadString(unsigned long stringID, FMX_Unichar* intoHere, long intoHereMax)
	{
		unsigned long		returnResult = 0;
	
	
		if((intoHere != NULL) &&(intoHereMax > 1)) {
			// Turn stringID to a textual identifier, then get the string from the .strings file as a null-term unichar array.
			CFStringRef 	strIdStr = CFStringCreateWithFormat(kCFAllocatorDefault, NULL, CFSTR("%d"), stringID);
		
			// Note: The plug-in must be explicit about the bundle and file it wants to pull the string from.
			CFStringRef 	osxStr = CFBundleCopyLocalizedString(reinterpret_cast<CFBundleRef>(gFMX_ExternCallPtr->instanceID), strIdStr, strIdStr, CFSTR(PLUGIN_NAME));
		
			if((osxStr != NULL) &&(osxStr != strIdStr)) {
			
				long	osxStrLen = CFStringGetLength(osxStr);
			
				if(osxStrLen <(intoHereMax-1)) {
				
					CFRange		allChars;
					allChars.location = 0;
					allChars.length = osxStrLen;
				
					CFStringGetCharacters(osxStr, allChars,(UniChar*)(intoHere));
					intoHere[osxStrLen] = 0x0000;
					returnResult =(unsigned long)osxStrLen;
				
				} // osxStrLen
			
				CFRelease(osxStr);
			
			} // osxStr
		
			CFRelease(strIdStr);
		
		} // intoHere
	
		return(returnResult);
	
	} // Sub_OSXLoadString

	#endif

	void ReadString(FMX_Unichar* ioBuffer, FMX_UInt32 iBufferSize, FMX_UInt32 iStringID)
	{
		#if FMX_WIN_TARGET
			LoadStringW(GetPluginInstance(), iStringID,(LPWSTR)ioBuffer, iBufferSize);
		#endif
    
		#if FMX_MAC_TARGET
        
			ioBuffer[0] = 0;

			// Turn stringID to a textual identifier, then get the string from the .strings file as a null-term unichar array.
			CFStringRef     strIdStr = CFStringCreateWithFormat(kCFAllocatorDefault, NULL, CFSTR("String%d"), iStringID);
        
			// Note: The plug-in must be explicit about the bundle and file it wants to pull the string from.
			CFStringRef     osxStr = CFBundleCopyLocalizedString(GetPluginBundle(), strIdStr, strIdStr, CFSTR("Localizable"));

			if((osxStr != NULL) &&(osxStr != strIdStr))
			{
				long    osxStrLen = CFStringGetLength(osxStr);
				if(osxStrLen <(long)(iBufferSize-1))
				{
					CFStringGetCharacters(osxStr, CFRangeMake(0,osxStrLen),(UniChar*)(ioBuffer));
					ioBuffer[osxStrLen] = 0;
                
				};// osxStrLen
            
				CFRelease(osxStr);
            
			};// osxStr
        
			CFRelease(strIdStr);        
    
		#endif
	}

	fmx::errcode RegisterExternalFunction(FMX_UInt16 funcId, FMX_Int16 minArgs, FMX_Int16 maxArgs, FMX_UInt32 flags, fmx::ExtPluginType funcPtr)
	{
		fmx::TextAutoPtr        name;
		fmx::TextAutoPtr        prototype;

		//long funcId = iFunctionID+FUNCTION_OFFSET;
		Do_GetString(funcId+FUNCTION_OFFSET, name, true);
		Do_GetString(funcId+FUNCTION_OFFSET, prototype, false);

		return RegisterExternalFunctionEx(funcId+FUNCTION_OFFSET, name, prototype, minArgs, maxArgs, flags, funcPtr);
	}

	fmx::errcode RegisterExternalFunctionEx(FMX_UInt16 funcId, fmx::TextAutoPtr name, fmx::TextAutoPtr prototype, FMX_Int16 minArgs,
										   FMX_Int16 maxArgs, FMX_UInt32 flags, fmx::ExtPluginType funcPtr)
	{
		fmx::QuadCharAutoPtr pluginID(PLUGIN_ID_STRING[0], PLUGIN_ID_STRING[1], PLUGIN_ID_STRING[2], PLUGIN_ID_STRING[3]);
		unsigned short funcOffsetId = funcId + FUNCTION_OFFSET;
		return fmx::ExprEnv::RegisterExternalFunction(*pluginID, funcOffsetId, *name, *prototype, minArgs, 
			maxArgs, flags, funcPtr);
	}

	fmx::errcode UnRegisterExternalFunction(FMX_UInt16 funcId)
	{
		fmx::QuadCharAutoPtr pluginID(PLUGIN_ID_STRING[0], PLUGIN_ID_STRING[1], PLUGIN_ID_STRING[2], PLUGIN_ID_STRING[3]);
		return fmx::ExprEnv::UnRegisterExternalFunction(*pluginID, funcId+FUNCTION_OFFSET);
	}
}

