#include "ManagedPlugins.h"
#include "Utility.h"

using namespace System::Diagnostics;

namespace FMTechnologies
{
    /// <summary>
    /// Constructor
    /// </summary>
	ManagedPlugins::ManagedPlugins()
	{
		_assemblies = gcnew List<ManagedPlugin^>();
	}

	ManagedPlugins::~ManagedPlugins()
	{
	}

    /// <summary>
    /// Load plugin assemblies
    /// </summary>
	void ManagedPlugins::loadExtensions()
	{
		Debug::WriteLine("Loading managed plugins ...");
		_assemblies->Clear();

		String^ path = FMTUtility::getAssemblyDirectory();
		try {
			DirectoryInfo^ directoryInfo = gcnew DirectoryInfo(path);
			if (!directoryInfo->Exists) {
				Debug::WriteLine(String::Format("Extensions folder '{0}' does not exist", path));
				return;
			}

			array<FileInfo^>^ fileInfos = directoryInfo->GetFiles(PLUGIN_FILES);
			for each (FileInfo^ fileInfo in fileInfos) {
				loadAssembly(fileInfo);
			}
		}
		catch(Exception^ ex) {
			Debug::WriteLine("Exception occurred while loading managed plugins. Error: " + ex->Message);
		}
	}

	void ManagedPlugins::loadAssembly(FileInfo^ fileInfo)
	{
		Debug::WriteLine("Loading assembly '" + fileInfo->ToString() + "'");
		try {
			Assembly ^ assembly = Assembly::LoadFile(fileInfo->FullName);
			if (assembly != nullptr) {
				array <Object^> ^ attrs = assembly->GetCustomAttributes(PluginAssemblyAttribute::typeid, false);
				if (attrs == nullptr || attrs->Length == 0) {
					return;
				}

				PluginAssemblyAttribute^ attr = (PluginAssemblyAttribute^)attrs[0];
				String^ description = attr->Description;
				ManagedPlugin^ pluginAsm = gcnew ManagedPlugin(assembly, description);
				_assemblies->Add(pluginAsm);
			}
		}
		catch (System::Exception^ ex) {
			Debug::WriteLine("Error while loading assembly '" + fileInfo->ToString() + "'. Error: " + ex->Message);
			throw;
		}
	}
}