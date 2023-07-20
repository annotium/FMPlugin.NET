#if !defined(__MANAGED_WRAPPER_H__)
#define __MANAGED_WRAPPER_H__

#include "FMWrapper/FMXTypes.h"
#include "FMWrapper/FMXCalcEngine.h"

#include <vcclr.h>
#include <msclr/auto_gcroot.h>
#include <vector>
#include "ManagedPlugins.h"
#include "PrefDialog.h"

using namespace System::Collections::Generic;
using namespace FMTechnologies;

class ManagedWrapper
{
private:
	msclr::auto_gcroot<FMTechnologies::ManagedPlugins^> _managedPlugins;
	msclr::auto_gcroot<FMTechnologies::PrefDialog^> _prefDialog;
	msclr::auto_gcroot<Dictionary<unsigned short, PluginMethod^>^> _methodsMap;
	bool _validLicense;
public:
	
	ManagedWrapper ();
	~ManagedWrapper();
	
	std::string getPluginAssemblyPaths();

	void registerMethods(int baseMethodId);
	void unregisterMethods();
	short executeMethod(short funcId, const fmx::DataVect& dataVect, fmx::Data& result);
	void showPreferencesDialog();
};

#endif // __MANAGED_WRAPPER_H__
