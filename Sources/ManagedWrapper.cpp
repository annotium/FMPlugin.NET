#include "ManagedWrapper.h"
#include "FMPlugin.h"
#include "PluginUtilities.h"
#include "FMTConfig.h"
#include "Utility.h"
#include "PluginUtilities.h"
#include "FMTemplate/FMTemplate.h"

using namespace System;
using namespace System::Text;
using namespace System::Diagnostics;

#pragma mark -
#pragma mark Constructors
#pragma mark -

static Assembly^ CurrentDomain_AssemblyResolve(Object^ sender, ResolveEventArgs^ args)
{
	Debug::WriteLine("Resolving current domain assembly {0}", sender, args->Name);

	if (ManagedPlugins::embeddedAssembly != nullptr) {
		return ManagedPlugins::embeddedAssembly;
	}

	System::String^ fmtPluginDLL = "FMTPlugin.dll";
	System::String^ rhinoLicensingDLL = "Rhino.Licensing.dll";

	Stream^ aStream = nullptr;
	FileStream^ fileStream = nullptr;
	try {
		aStream = Assembly::GetExecutingAssembly()->GetManifestResourceStream(fmtPluginDLL);
		array<Byte>^ bytes = gcnew array<Byte>(aStream->Length);
		aStream->Read(bytes, 0, bytes->Length);
		ManagedPlugins::embeddedAssembly = Assembly::Load(bytes);
	}
	catch (Exception^ ex) {
		Debug::WriteLine(String::Format(
			"Exception occurred while resolving CurrentDomain_ Assembly. Error: {0}", ex->Message));
		if (fileStream != nullptr) {
			fileStream->Close();
		}
		if (aStream != nullptr) {
			aStream->Close();
		}
	}

	return ManagedPlugins::embeddedAssembly;
}

ManagedWrapper::ManagedWrapper()
{	
	AppDomain::CurrentDomain->AssemblyResolve += gcnew ResolveEventHandler(&CurrentDomain_AssemblyResolve);
	_managedPlugins = gcnew FMTechnologies::ManagedPlugins();
	_methodsMap = gcnew Dictionary<unsigned short, PluginMethod^>();
	_validLicense = FMTUtility::validateLicense();
}

ManagedWrapper::~ManagedWrapper()
{
	Debug::WriteLine("Releasing ManagedWrapper ...");
}

void ManagedWrapper::showPreferencesDialog()
{
	if (!_prefDialog.get()) {
		_prefDialog = gcnew FMTechnologies::PrefDialog(_managedPlugins->Assemblies);
	}
	
	_prefDialog->ShowDialog();
}

#pragma mark -
#pragma mark Methods
#pragma mark -

void ManagedWrapper::registerMethods(int baseMethodId)
{
	System::Diagnostics::Debug::WriteLine("Register .NET plugin methods ... ");
	if (!_validLicense) {
		return;
	}

	_managedPlugins->loadExtensions();
	unsigned short methodId = baseMethodId + 1;
	List<ManagedPlugin^>^ managedPlugins = _managedPlugins->Assemblies;
	for each (ManagedPlugin^ managedPlugin in managedPlugins) {
		for each (PluginMethod^ method in managedPlugin->Methods) {
			fmx::TextAutoPtr name = FMTechnologies::FMTUtility::stringToText(method->Name);
			String^ funcPrototype = method->Prototype;
			fmx::TextAutoPtr prototype = FMTechnologies::FMTUtility::stringToText(method->Prototype);
			unsigned short minArgs = method->MinArguments;
			unsigned short maxArgs = method->MaxArguments;
			unsigned int methodFlags = method->Flags;
			PluginUtilities::RegisterExternalFunctionEx(methodId, name, prototype, minArgs, maxArgs, methodFlags, FUNCTION_1_C_NAME);			
			_methodsMap->Add(methodId + FUNCTION_OFFSET, method);
			methodId++; 
		}
	}
}

void ManagedWrapper::unregisterMethods()
{
	System::Diagnostics::Debug::WriteLine("Unregister .NET plugin methods ... ");
	if (!_validLicense) {
		return;
	}

	for each (KeyValuePair<unsigned short, PluginMethod^>^ pair in _methodsMap.get()) {
		PluginUtilities::UnRegisterExternalFunction(pair->Key);
	}

	_methodsMap->Clear();
}

std::string ManagedWrapper::getPluginAssemblyPaths()
{
	System::Diagnostics::Debug::WriteLine("Get plugin assemblies paths ... ");
	std::string result = "";
	for each (ManagedPlugin^ pa in _managedPlugins->Assemblies) {
		String^ assemblyPath = pa->BaseAssembly->FullName;
		std::string path = FMTUtility::stringFromManagedString(assemblyPath);

		if (result.length() > 0) {
			result += ";";
		}
		result += path;
	}

	return result;
}

short ManagedWrapper::executeMethod(short funcId, const fmx::DataVect& dataVect, fmx::Data& result)
{
	System::Diagnostics::Debug::WriteLine(String::Format("Execute managed function with ID {0}", funcId));
	
	if (!_methodsMap->ContainsKey(funcId)) {
		return -1;
	}

	try {
		Dictionary<unsigned short, PluginMethod^>^ methodsMap = _methodsMap.get();
		List<ManagedData^>^ managedDataVect = gcnew List<ManagedData^>();
		for (int i = 0; i < dataVect.Size(); ++i) {
			const fmx::Data& data = dataVect.At(i);
			ManagedData^ managedData = FMTUtility::convertNativeDataToManaged(&data);
			managedDataVect->Add(managedData);
		}

		ManagedData^ managedResult = nullptr;
		PluginMethod^ pluginMethod = methodsMap[funcId];
		MethodInfo^ methodInfo = pluginMethod->MethodInfoProp;
		array<Object^>^ parameters = gcnew array<Object^>(2){ managedDataVect, nullptr };
		Object^ retVal = methodInfo->Invoke(nullptr, parameters);
		managedResult = safe_cast<ManagedData^>(parameters[1]);
		FMTUtility::convertManagedDatatoNative(managedResult, result);

		return (Int16)retVal;
	}
	catch (Exception^ ex) {
		System::Diagnostics::Debug::WriteLine(String::Format("Exception occurred while executeing function with ID {0}: {1}",
			funcId, ex->Message));
		return -1;
	}

	return 0;
}
