#include "PluginMethod.h"

namespace FMTechnologies
{
	PluginMethod::PluginMethod()
	{
	}

	PluginMethod::PluginMethod(String^ name, String^ prototype, unsigned short minArgs, unsigned short maxArgs, UInt32 flags)
	{
		_name = name;
		_prototype = prototype;
		_minArgs = minArgs;
		_maxArgs = maxArgs;
		_methodFlags = flags;
	}

	bool PluginMethod::validate()
	{
		if (String::IsNullOrEmpty(_prototype)) {
			throw gcnew Exception(String::Format("Method '{0}' has no prototype", _name));
		}
		if ((_maxArgs > -1) && (_minArgs > _maxArgs)) {
			//#error String::Format("MinArgs is greater than MaxArgs for method: {0}", _name);
			throw gcnew Exception(String::Format("MinArgs is greater than MaxArgs for method: {0}", _name));
		}
		if (_minArgs > 9) {
			throw gcnew Exception(String::Format("MinArgs is greater than 9 for method: {0}", _name));	
		}
		if (_maxArgs > 9) {
			throw gcnew Exception(String::Format("MaxArgs is greater than 9 for method: {0}", _name));		
		}
		if (_minArgs < 0) {
			throw gcnew Exception(String::Format("MinArgs is less than zero for method: {0}", _name));		
		}

		return true;
	}
}