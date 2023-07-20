#ifndef __PLUGIN_METHOD_H__
#define __PLUGIN_METHOD_H__

using namespace System;
using namespace System::Reflection;

namespace FMTechnologies
{
	public ref class PluginMethod
	{
	private:
		String^ _name;
		String^ _prototype;
		unsigned short _methodId;
		unsigned short _minArgs;
		unsigned short _maxArgs;
		UInt32 _methodFlags;
		MethodInfo^ _methodInfo;
		String^ _description;
	public:
		property String^ Name
		{
			String ^ get() {
				return _name;
			}

			void set(String ^ value)
			{
				_name = value;
			}
		}

		property String^ Prototype
		{
			String ^ get() {
				return _prototype;
			}

			void set(String ^ value)
			{
				_prototype = value;
			}
		}

		property unsigned short MinArguments
		{
			unsigned short get() {
				return _minArgs;
			}

			void set(unsigned short value)
			{
				_minArgs = value;
			}
		}

		property unsigned short MaxArguments
		{
			unsigned short get() {
				return _maxArgs;
			}

			void set(unsigned short value)
			{
				_maxArgs = value;
			}
		}

		property unsigned short MethodId
		{
			unsigned short get() {
				return _methodId;
			}

			void set(unsigned short value)
			{
				_methodId = value;
			}
		}

		property UInt32 Flags
		{
			UInt32 get() {
				return _methodFlags;
			}

			void set(UInt32 value)
			{
				_methodFlags = value;
			}
		}

		property MethodInfo^ MethodInfoProp
		{
			MethodInfo^ get() {
				return _methodInfo;
			}

			void set(MethodInfo^ value)
			{
				_methodInfo = value;
			}
		}

		property String^ Description
		{
			String^ get()
			{
				return _description;
			}
			void set(String^ value)
			{
				_description = value;
			}
		}
	public:
		PluginMethod();
		PluginMethod(String^ name, String^ prototype, unsigned short minArgs, unsigned short maxArgs, UInt32 flags);
		bool validate();
	};
}

#endif