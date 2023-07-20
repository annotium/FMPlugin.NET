#include "FMWrapper/FMXExtern.h"
#include "FMWrapper/FMXFixPt.h"
#include "FMWrapper/FMXDateTime.h"
#include "Utility.h"

using namespace System::IO;
using namespace System::Text;
using namespace Microsoft::Win32;
using namespace System::Reflection;
using namespace System::Globalization;
using namespace System::Collections::Generic;
using namespace System::Security::Cryptography;

namespace FMTechnologies
{
	std::wstring FMTUtility::fromManagedString(String^ value)
	{
		msclr::interop::marshal_context context;
		return context.marshal_as<std::wstring>(value);
	}

	std::string FMTUtility::stringFromManagedString(String^ value)
	{
		msclr::interop::marshal_context context;
		return context.marshal_as<std::string>(value);
	}

	fmx::TextAutoPtr FMTUtility::stringToText(String^ value)
	{
		fmx::TextAutoPtr textPtr;
		std::wstring wstr = FMTUtility::fromManagedString(value);
		textPtr->AssignWide(wstr.c_str());
		return textPtr;
	}

	String^ FMTUtility::textToString(fmx::TextAutoPtr text)
	{
		String^ result = nullptr;

		try {
			long text_size = text->GetSize();
			unsigned short * buffer = new unsigned short[text_size + 1];
			text->GetUnicode(buffer, 0, text_size);
			buffer[text_size] = 0x0000;

			wchar_t* parameter = (wchar_t*)buffer;
			result = gcnew String(parameter);
			delete [] parameter; 				
		} catch(std::exception&) {
			;
		}

		return result;
	}

	ManagedQuadChar^ FMTUtility::convertNativeQuadCharToManaged(fmx::QuadCharAutoPtr quadChar_)
	{
		ManagedQuadChar^ mQuadChar = gcnew ManagedQuadChar();
		mQuadChar[0] = quadChar_->operator[](0);
		mQuadChar[1] = quadChar_->operator[](1);
		mQuadChar[2] = quadChar_->operator[](2);
		mQuadChar[3] = quadChar_->operator[](3);

		return mQuadChar;
	}

	fmx::QuadCharAutoPtr FMTUtility::convertManagedQuadCharToNative(ManagedQuadChar^ mQuadChar_)
	{
		return fmx::QuadCharAutoPtr((char)mQuadChar_[0], (char)mQuadChar_[1], (char)mQuadChar_[2], (char)mQuadChar_[3]);
	}

	fmx::BinaryDataAutoPtr FMTUtility::convertManagedBinarytoNative(ManagedBinaryData^ mBinaryData_)
	{
		fmx::BinaryDataAutoPtr result;
		for (int i = 0; i < mBinaryData_->DataItems->Count; i++) {
			unsigned int dataSize = mBinaryData_->DataItems[i]->buffer->Count;
			fmx::QuadCharAutoPtr quadChar = convertManagedQuadCharToNative(mBinaryData_->DataItems[i]->quadChar);
			array<Byte>^ tempBuffer = mBinaryData_->DataItems[i]->buffer->ToArray();
			pin_ptr<unsigned char> pinnedValues = &tempBuffer[0];
			result->Add(*quadChar, dataSize, pinnedValues);
		}

		return result;
	}

	ManagedBinaryData^ FMTUtility::convertNativeBinaryToManaged(fmx::BinaryDataAutoPtr binaryData_)
	{
		ManagedBinaryData^ mBinaryData = gcnew ManagedBinaryData();
		for (int index = 0; index < binaryData_->GetCount(); index++) {
			int dataSize = binaryData_->GetSize(index);
			fmx::QuadCharAutoPtr quadCharPtr;
			binaryData_->GetType(index, *quadCharPtr);
			ManagedQuadChar^ quadChar = convertNativeQuadCharToManaged(quadCharPtr);

			unsigned char* buffer = new unsigned char[dataSize];
			binaryData_->GetData(index, 0, dataSize, buffer);

			array<Byte>^ mbuffer = gcnew array<Byte>(dataSize);
			pin_ptr<Byte> pinPtrArray = &mbuffer[0];
			memcpy_s(pinPtrArray, dataSize, buffer, dataSize);
			delete[] buffer;

			List<Byte>^ tempBuff = gcnew List<Byte>(mbuffer);
			mBinaryData->Add(quadChar, tempBuff);
		}

		return mBinaryData;
	}

	void FMTUtility::convertManagedDatatoNative(ManagedData^ mData_, fmx::Data& data)
	{
		if (mData_->FMDataType == DataType::DTText) {
			std::wstring value = fromManagedString(mData_->AsText);
			fmx::TextAutoPtr result;
			result->AssignWide(value.c_str());
			fmx::LocaleAutoPtr locale;
			data.SetAsText(*result, *locale);
		}
		else if (mData_->FMDataType == DataType::DTNumber) {
			fmx::FixPtAutoPtr result;
			result->AssignDouble(mData_->AsNumber);
			data.SetAsNumber(*result);
		}
		else if (mData_->FMDataType == DataType::DTDate) {
			fmx::DateTimeAutoPtr value;
			DateTime^ _dateTime = mData_->AsDateTime;
			value->SetNormalizedDate(_dateTime->Month, _dateTime->Day, _dateTime->Year);
			data.SetAsDate(*value);
		}
		else if (mData_->FMDataType == DataType::DTTime) {
			fmx::DateTimeAutoPtr value;
			DateTime^ _dateTime = mData_->AsDateTime;
			value->SetNormalizedDate(_dateTime->Month, _dateTime->Day, _dateTime->Year);
			value->SetNormalizedTime(_dateTime->Hour, _dateTime->Minute, _dateTime->Second);
			data.SetAsTime(*value);
		}
		else if (mData_->FMDataType == DataType::DTTimeStamp) {
			fmx::DateTimeAutoPtr value;
			DateTime^ _dateTime = mData_->AsDateTime;
			value->SetNormalizedDate(_dateTime->Month, _dateTime->Day, _dateTime->Year);
			value->SetNormalizedTime(_dateTime->Hour, _dateTime->Minute, _dateTime->Second);
			data.SetAsTimeStamp(*value);
		}
		else if (mData_->FMDataType == DataType::DTBinary) {
			fmx::BinaryDataAutoPtr value = convertManagedBinarytoNative(mData_->AsBinary);
			data.SetBinaryData(*value);
		}
		else if (mData_->FMDataType == DataType::DTBoolean) {
			fmx::FixPtAutoPtr value;
			value->AssignInt(mData_->AsBoolean);
			data.SetAsNumber(*value);
		}
	}

	fmx::DataAutoPtr FMTUtility::convertManagedDatatoNative(ManagedData^ mData_)
	{
		fmx::DataAutoPtr dataPtr;
		if (mData_->FMDataType == DataType::DTText) {
			std::wstring value = fromManagedString(mData_->AsText);
			fmx::TextAutoPtr result;
			result->AssignWide(value.c_str());
			fmx::LocaleAutoPtr locale;
			dataPtr->SetAsText(*result, *locale);
		}
		else if (mData_->FMDataType == DataType::DTNumber) {
			fmx::FixPtAutoPtr result;
			result->AssignDouble(mData_->AsNumber);
			dataPtr->SetAsNumber(*result);
		}
		else if (mData_->FMDataType == DataType::DTDate) {
			fmx::DateTimeAutoPtr value;
			DateTime^ _dateTime = mData_->AsDateTime;
			value->SetNormalizedDate(_dateTime->Month, _dateTime->Day, _dateTime->Year);
			dataPtr->SetAsDate(*value);
		}
		else if (mData_->FMDataType == DataType::DTTime) {
			fmx::DateTimeAutoPtr value;
			DateTime^ _dateTime = mData_->AsDateTime;
			value->SetNormalizedDate(_dateTime->Month, _dateTime->Day, _dateTime->Year);
			value->SetNormalizedTime(_dateTime->Hour, _dateTime->Minute, _dateTime->Second);
			dataPtr->SetAsTime(*value);
		}
		else if (mData_->FMDataType == DataType::DTTimeStamp) {
			fmx::DateTimeAutoPtr value;
			DateTime^ _dateTime = mData_->AsDateTime;
			value->SetNormalizedDate(_dateTime->Month, _dateTime->Day, _dateTime->Year);
			value->SetNormalizedTime(_dateTime->Hour, _dateTime->Minute, _dateTime->Second);
			dataPtr->SetAsTimeStamp(*value);
		}
		else if (mData_->FMDataType == DataType::DTBinary) {
			fmx::BinaryDataAutoPtr value = convertManagedBinarytoNative(mData_->AsBinary);
			dataPtr->SetBinaryData(*value);
		}
		else if (mData_->FMDataType == DataType::DTBoolean) {
			fmx::FixPtAutoPtr value;
			value->AssignInt(mData_->AsBoolean);
			dataPtr->SetAsNumber(*value);
		}
		else {
		
		}

		return dataPtr;
	}

	ManagedData^ FMTUtility::convertNativeDataToManaged(fmx::DataAutoPtr data_)
	{
		return convertNativeDataToManaged(data_.get());
	}

	ManagedData^ FMTUtility::convertNativeDataToManaged(const fmx::Data* data_)
	{
		ManagedData^ mData = gcnew ManagedData();

		fmx::Data::DataType dataType = data_->GetNativeType();

		switch (dataType) {
		case fmx::Data::kDTText:
		{
			const fmx::Text& text = data_->GetAsText();
			mData->FMDataType = DataType::DTText;
			mData->AsText = getText(&text);
			break;
		}
		case fmx::Data::kDTNumber:
		{
			const fmx::FixPt& fixPt = data_->GetAsNumber();
			mData->FMDataType = DataType::DTNumber;
			mData->AsNumber = fixPt.AsFloat();
			break;
		}
		case fmx::Data::kDTDate:
		{
			mData->FMDataType = DataType::DTDate;	
			const fmx::DateTime& date = data_->GetAsDate();
			mData->AsDateTime = System::DateTime(date.GetYear(), date.GetMonth(), date.GetDay());
			break;
		}
		case fmx::Data::kDTTime:
		{
			mData->FMDataType = DataType::DTTime;	
			const fmx::DateTime& date = data_->GetAsTime();
			mData->AsDateTime = System::DateTime(date.GetYear(), date.GetMonth(), date.GetDay(), 
			date.GetHour(), date.GetMinute(), date.GetSec());
			break;
		}
		case fmx::Data::kDTTimeStamp:
		{
			mData->FMDataType = DataType::DTTimeStamp;	
			const fmx::DateTime& date = data_->GetAsTimeStamp();
			mData->AsDateTime = System::DateTime(date.GetYear(), date.GetMonth(), date.GetDay(), 
			date.GetHour(), date.GetMinute(), date.GetSec());
			break;
		}
		case fmx::Data::kDTBinary:
		{
			const fmx::BinaryData& binary = data_->GetBinaryData();			
			mData->FMDataType = DataType::DTBinary;
			mData->AsBinary = convertNativeBinaryToManaged(fmx::BinaryDataAutoPtr(binary));
			break;
		}
		case fmx::Data::kDTBoolean:
		{
			mData->FMDataType = DataType::DTBoolean;	
			mData->AsBoolean = data_->GetAsBoolean();
			break;
		}
		default:
		{	mData->FMDataType = DataType::DTInvalid;
			break;
		}
		
		}

		return mData;
	}

	fmx::TextAutoPtr FMTUtility::convertManagedTextToNative(ManagedText^ managedText_)
	{
		return fmx::TextAutoPtr();
	}

	void FMTUtility::convertManagedTextToNative(ManagedText^ managedText_, fmx::Text& text_)
	{
	
	}

	ManagedText^ FMTUtility::convertNativeTextToManaged(fmx::TextAutoPtr textPtr_)
	{
		return convertNativeTextToManaged(textPtr_.get());
	}
	
	ManagedText^ FMTUtility::convertNativeTextToManaged(const fmx::Text* text_)
	{
		return nullptr;
	}


	String^ FMTUtility::getText(const fmx::Text* textPtr)
	{
		String^ result = nullptr;
		try {
			long text_size = textPtr->GetSize();
			unsigned short * buffer = new unsigned short [ text_size + 1 ];
			textPtr->GetUnicode(buffer, 0, text_size);
			buffer[text_size] = 0x0000;
			wchar_t * parameter = (wchar_t*)buffer;
			result = gcnew String(parameter);
			delete [] parameter; 
		} catch(std::exception&) {
			;	// return an empty string
		}

		return result;
	}

	String^ FMTUtility::getAssemblyDirectory()
	{
		String^ codeBase = Assembly::GetExecutingAssembly()->CodeBase;
		UriBuilder^ uri = gcnew UriBuilder(codeBase);
		String^ path = Uri::UnescapeDataString(uri->Path);
		return Path::GetDirectoryName(path);
	}

	String^ FMTUtility::Encrypt(String^ input, String^ key)
	{
		array<Byte>^ inputArray = UTF8Encoding::UTF8->GetBytes(input);
		TripleDESCryptoServiceProvider^ tripleDES = gcnew TripleDESCryptoServiceProvider();
		tripleDES->Key = UTF8Encoding::UTF8->GetBytes(key);
		tripleDES->Mode = CipherMode::ECB;
		tripleDES->Padding = PaddingMode::PKCS7;
		ICryptoTransform^ cTransform = tripleDES->CreateEncryptor();
		array<Byte>^ resultArray = cTransform->TransformFinalBlock(inputArray, 0, inputArray->Length);
		tripleDES->Clear();
		return Convert::ToBase64String(resultArray, 0, resultArray->Length);
	}

	String^ FMTUtility::Decrypt(String^ input, String^ key)
	{
		array<Byte>^ inputArray = Convert::FromBase64String(input);
		TripleDESCryptoServiceProvider^ tripleDES = gcnew TripleDESCryptoServiceProvider();
		tripleDES->Key = UTF8Encoding::UTF8->GetBytes(key);
		tripleDES->Mode = CipherMode::ECB;
		tripleDES->Padding = PaddingMode::PKCS7;
		ICryptoTransform^ cTransform = tripleDES->CreateDecryptor();
		array<Byte>^ resultArray = cTransform->TransformFinalBlock(inputArray, 0, inputArray->Length);
		tripleDES->Clear();
		return UTF8Encoding::UTF8->GetString(resultArray);
	}

	String^ FMTUtility::getEmbeddedResourceValue(String^ folderName, String^ fileName)
	{
		String^ result = nullptr;
		try {
			String^ additionalFolder = String::Empty;
			if (!String::IsNullOrEmpty(folderName)) {
				additionalFolder = folderName + ".";
			}
			Stream^ stream = Assembly::GetExecutingAssembly()->GetManifestResourceStream(additionalFolder + fileName);
			if (stream != nullptr) {
				StreamReader^ reader = gcnew StreamReader(stream);
				result = reader->ReadToEnd();
			}
		}
		catch (Exception^) {
			
		}

		return result;
	}

	void FMTUtility::writeLicenseInfo(String^ licenseFile)
	{
		String^ userName = "";
		String^ email = "";
		String^ licenseData = "";

		writeLicenseInfo(userName, email, licenseData);
	}

	void FMTUtility::writeLicenseInfo(String^ userName, String^ email, String^ licenseData)
	{
		RegistryKey^ lmKey = Registry::LocalMachine->OpenSubKey(FMTUtility::KEY_SOFTWARE, true);
		RegistryKey^ subKey = lmKey->OpenSubKey(FMTUtility::FM_TECHS, true);
		subKey->SetValue(FMTUtility::KEY_USERNAME, userName);
		subKey->GetValue(FMTUtility::KEY_EMAIL, email);
		subKey->SetValue(FMTUtility::KEY_LICENSE, licenseData);
	}

	bool FMTUtility::validateLicenseInfo(String^ originalMessage, String^ publicKey, String^ licenseData)
	{
		bool result = false;

		try {
			RSACryptoServiceProvider^ rsa = gcnew RSACryptoServiceProvider();
			rsa->FromXmlString(publicKey);
			array<Byte>^ bytesToVerify = Encoding::UTF8->GetBytes(originalMessage);
			array<Byte>^ signedBytes = Convert::FromBase64String(licenseData);
			SHA512Managed^ hash = gcnew SHA512Managed();
			array<Byte>^ hashedData = hash->ComputeHash(signedBytes);
                
			result = rsa->VerifyData(bytesToVerify, CryptoConfig::MapNameToOID("SHA512"), signedBytes);
		}
		catch (Exception^ ex) {
			throw ex;
		}

		return result;
	}

	bool FMTUtility::validateLicense()
	{
		String^ licenseKey = nullptr;
		RegistryKey^ lmKey = Registry::LocalMachine->OpenSubKey(FMTUtility::KEY_SOFTWARE, true);
		RegistryKey^ crKey = Registry::ClassesRoot->OpenSubKey(FMTUtility::FM_TECHS, true);
		RegistryKey^ subKey = lmKey->OpenSubKey(FMTUtility::FM_TECHS, true);

		if (subKey != nullptr) {
			licenseKey = (String^)subKey->GetValue(FMTUtility::KEY_LICENSE);
		}

		bool decreaseTrial = false;
		bool registered = false;
		if (licenseKey == nullptr) {
			// if first time
			if (subKey == nullptr || crKey == nullptr) {
				// first time, just write trial info 
				if (subKey == nullptr) {
					subKey = lmKey->CreateSubKey(FMTUtility::FM_TECHS);
				}
				if (crKey == nullptr) {
					crKey = Registry::ClassesRoot->CreateSubKey(FMTUtility::FM_TECHS);
				}

				subKey->SetValue(FMTUtility::KEY_USERNAME, "Trial");
				subKey->SetValue(FMTUtility::KEY_EMAIL, "");
				String^ startDate = DateTime::Now.ToString("yyyyMMdd");
				String^ encryptDate = FMTUtility::Encrypt(startDate, CRYPTO_KEY);
				crKey->SetValue("Cont", encryptDate);
				return true;
			}
			else {
				decreaseTrial = true;
			}
		}
		else { 
			// license ok, checking license and continue to run
			String^ username = (String^)subKey->GetValue(FMTUtility::KEY_USERNAME);
			String^ email = (String^)subKey->GetValue(FMTUtility::KEY_EMAIL);
			String^ originalMessage = username + "\n" + email;
			String^ publicKey = FMTUtility::getEmbeddedResourceValue("", "publicKey.xml");
			registered = validateLicenseInfo(originalMessage, publicKey, licenseKey);
			if (registered) {
				return true;				
			}
			else { // cracked
				return false;
			}
		}

		if (decreaseTrial) {
			String^ encryptDate = (String^)crKey->GetValue("Cont");
			String^ startDateStr = FMTUtility::Decrypt(encryptDate, CRYPTO_KEY);
			DateTime startDate = DateTime::ParseExact(startDateStr, "yyyyMMdd", CultureInfo::InvariantCulture);
			if (DateTime::Now.CompareTo(startDate) < 0) {
				return false;
			}

			TimeSpan^ tm = DateTime::Now.Subtract(startDate);
			return (tm->Days > 0 || tm->Days <= FMTUtility::TRIAL_DAYS);
		}
	
		return false;
	}


	System::Collections::Generic::Dictionary<String^, String^>^ FMTUtility::getLicenseInfo(Boolean% registered)
	{
		System::Collections::Generic::Dictionary<String^, String^>^ result = 
			gcnew System::Collections::Generic::Dictionary<String^, String^>();
		RegistryKey^ lmKey = Registry::LocalMachine->OpenSubKey(FMTUtility::KEY_SOFTWARE, false);
		RegistryKey^ crKey = Registry::ClassesRoot->OpenSubKey(FMTUtility::FM_TECHS, false);
		RegistryKey^ subKey = lmKey->OpenSubKey(FMTUtility::FM_TECHS);
		String^ licenseKey = (String^)subKey->GetValue(FMTUtility::KEY_LICENSE);
		
		if (subKey == nullptr || crKey == nullptr || licenseKey == nullptr) {
			result->Add(FMTUtility::KEY_USERNAME, "Unregistered");
			result->Add(FMTUtility::KEY_EMAIL, "");

			String^ encryptDate = (String^)crKey->GetValue("Cont");
			String^ startDateStr = FMTUtility::Decrypt(encryptDate, CRYPTO_KEY);
			DateTime startDate = 
				DateTime::ParseExact(startDateStr, "yyyyMMdd", CultureInfo::InvariantCulture);
			
			Int32 trialDays = 0;
			if (DateTime::Now.CompareTo(startDate) >= 0) {
				TimeSpan^ tm = DateTime::Now.Subtract(startDate);
				trialDays = FMTUtility::TRIAL_DAYS - tm->Days;
			}
			result->Add(FMTUtility::KEY_TRIAL, trialDays.ToString());
			registered = false;
		}
		else {
			// license ok, checking license and continue to run
			String^ username = (String^)subKey->GetValue(FMTUtility::KEY_USERNAME);
			String^ email = (String^)subKey->GetValue(FMTUtility::KEY_EMAIL);
			String^ trialTime = "Registered";
			result->Add(FMTUtility::KEY_USERNAME, username);
			result->Add(FMTUtility::KEY_EMAIL, email);
			result->Add(FMTUtility::KEY_TRIAL, trialTime);
			registered = true;
		}

		return result;
	}
}