#ifndef __PLUGIN_ASSEMBLY_H__
#define __PLUGIN_ASSEMBLY_H__ 

#include "PluginMethod.h"

using namespace System;
using namespace System::Reflection;
using namespace System::Collections::Generic;

namespace FMTechnologies
{
	public ref class ManagedPlugin
	{
	private:
		Assembly^ _assembly;
		String^ _description;
		List<PluginMethod^>^ _methods;
		unsigned short _methodBase;
	public:
		ManagedPlugin(Assembly^ assembly, String^ desc);
		~ManagedPlugin();
		void loadAssembly(Assembly^ assembly);

		property List<PluginMethod^>^ Methods
		{
			List<PluginMethod^>^ get()
			{
				return _methods;
			}
		}

		property Assembly^ BaseAssembly
		{
			Assembly^ get()
			{
				return _assembly;
			}
		}

		property String^ Description
		{
			String^ get()
			{
				return _description;
			}
		}
	private:
		void loadAssembly(Assembly^ assembly, Object^ plugin);
		List<Type^> ^ getPluginClasses(Assembly ^ assembly);
		void updatePluginMethod(MethodInfo^ methodInfo);
	};
}

#endif