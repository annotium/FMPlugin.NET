#pragma once

#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>
#include "FMWrapper/FMXText.h"
#include "FMWrapper/FMXBinaryData.h"
#include "FMWrapper/FMXData.h"

using namespace System;

namespace FMTechnologies
{
	public ref class FMTUtility
	{
	public:
		static String^ CRYPTO_KEY = "hoaquo_emperor!@";
		static int TRIAL_DAYS = 60;
		static String^ FM_TECHS = "FMTechs";
		static String^ KEY_USERNAME = "Username";
		static String^ KEY_EMAIL = "Email";
		static String^ KEY_SOFTWARE = "Software";
		static String^ KEY_LICENSE = "License";
		static String^ KEY_TRIAL = "Cont";

		// string utilities
		static std::string stringFromManagedString(String^ value);
		static std::wstring fromManagedString(String^ value);
		static fmx::TextAutoPtr stringToText(String^ value);
		static String^ textToString(fmx::TextAutoPtr text);
		static String^ getText(const fmx::Text* textPtr);

		// quadchar utilities
		static ManagedQuadChar^ convertNativeQuadCharToManaged(fmx::QuadCharAutoPtr quadChar_);
		static fmx::QuadCharAutoPtr convertManagedQuadCharToNative(ManagedQuadChar^ mQuadChar_);

		// binary data utilities
		static fmx::BinaryDataAutoPtr convertManagedBinarytoNative(ManagedBinaryData^ mBinaryData_);
		static ManagedBinaryData^ convertNativeBinaryToManaged(fmx::BinaryDataAutoPtr binaryData_);

		// data utilities
		static fmx::DataAutoPtr convertManagedDatatoNative(ManagedData^ mData_);
		static void convertManagedDatatoNative(ManagedData^ mData_, fmx::Data& data_);
		static ManagedData^ convertNativeDataToManaged(fmx::DataAutoPtr data_);
		static ManagedData^ convertNativeDataToManaged(const fmx::Data* data_);

		// text utilities
		static fmx::TextAutoPtr convertManagedTextToNative(ManagedText^ managedText_);
		static void convertManagedTextToNative(ManagedText^ managedText_, fmx::Text& text_);
		static ManagedText^ convertNativeTextToManaged(fmx::TextAutoPtr textPtr_);
		static ManagedText^ convertNativeTextToManaged(const fmx::Text* text_);

		// files, directories
		static String^ getAssemblyDirectory();

		// encrypt/decrypt
		static String^ Encrypt(String^ input, String^ key);
		static String^ Decrypt(String^ input, String^ key);

		// resource
		static String^ getEmbeddedResourceValue(String^ folderName, String^ fileName);		

		// license
		static bool validateLicense();
		static System::Collections::Generic::Dictionary<String^, String^>^ getLicenseInfo(Boolean% registered);		
		static bool validateLicenseInfo(String^ originalMessage, String^ publicKey, String^ licenseData);
		static void writeLicenseInfo(String^ userName, String^ email, String^ licenseInfo);
		static void writeLicenseInfo(String^ licenseFile);
	};
}

