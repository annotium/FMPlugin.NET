#ifndef __MANAGED_PLUGINS_H__
#define __MANAGED_PLUGINS_H__

#include "ManagedPlugin.h"
#include "PluginMethod.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Reflection;
using namespace System::IO;

namespace FMTechnologies
{
	public ref class ManagedPlugins 
	{
	public:
		static Assembly^ embeddedAssembly = nullptr;

		property List<ManagedPlugin^>^ Assemblies
		{
			List<ManagedPlugin^>^ get()
			{
				return _assemblies;
			}
		}

	public:
		ManagedPlugins();
		~ManagedPlugins();
		void loadExtensions();

	private:
		static String ^ PLUGIN_FILES = "*.dll";
		void loadAssembly(System::IO::FileInfo^ fileInfo);
		List<String^>^ _assemblyPaths;
		List<ManagedPlugin^>^ _assemblies;
	};
}

#endif