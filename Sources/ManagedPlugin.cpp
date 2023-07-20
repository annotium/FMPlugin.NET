#include "ManagedPlugin.h"		

using namespace System::Diagnostics;

namespace FMTechnologies
{
	ManagedPlugin::ManagedPlugin(Assembly^ assembly, String^ desc)
	{
		_assembly = assembly;
		_description = desc;
		_methods = gcnew List<PluginMethod^>();
		loadAssembly(assembly);
	}

	ManagedPlugin::~ManagedPlugin()
	{
	}

	void ManagedPlugin::loadAssembly(Assembly^ assembly)
	{
		List<Type^> ^ types = getPluginClasses(assembly);
		for each (Type^ type in types) {
			ConstructorInfo^ constructor = type->GetConstructor(Type::EmptyTypes);
			Object^ plugin = constructor->Invoke(gcnew array<Object^>(0));
			loadAssembly(assembly, plugin);
		}
	}

	List<Type^>^ ManagedPlugin::getPluginClasses(Assembly ^ assembly)
	{
		Debug::WriteLine("Getting Plugin Classes from assembly: " + assembly->ToString());
		List<Type^>^ result = gcnew List<Type^>();
		array<Type^>^ types = assembly->GetTypes();
		for each (Type^ type in types) {
			Debug::WriteLine("\tChecking type: " + type->ToString());
			array <Object^> ^ pObjs = type->GetCustomAttributes(PluginClassAttribute::typeid, false);
			if (pObjs != nullptr && pObjs->Length > 0) {
				result->Add(type);
			}
		}

		return result;
	}

	void ManagedPlugin::loadAssembly(Assembly^ assembly, Object^ plugin)
	{
		Debug::WriteLine("Loading plugin class '" + plugin->ToString() + "' from assembly '" + assembly->FullName + "'");
		array<MethodInfo^>^ methodInfos = plugin->GetType()->GetMethods(BindingFlags::Public | BindingFlags::Static);
		for each (MethodInfo^ methodInfo in methodInfos) {
			updatePluginMethod(methodInfo);
		}
	}

	void ManagedPlugin::updatePluginMethod(MethodInfo^ methodInfo)
	{
		array <Object^> ^ pObjs = methodInfo->GetCustomAttributes(PluginMethodAttribute::typeid, false);
		if (pObjs == nullptr || pObjs->Length == 0) {
			return;
		}
		
		// get method name
		String^ methodName = methodInfo->Name;
		Debug::WriteLine( "\nMethodInfo = {0}", methodInfo );

		// check return type
		Type^ returnType = methodInfo->ReturnType;
		if (returnType != Int16::typeid) {
			return;
		}

		// check parameters
		array<ParameterInfo^>^ pars = methodInfo->GetParameters();
		if (pars->Length != 2) {
			return;
		}

		// check parameter type is generic list
		ParameterInfo^ paramInfo = pars[0];
		Type^ paramInfoType = paramInfo->ParameterType;
		if (!paramInfoType->IsGenericType || paramInfoType->GetGenericTypeDefinition() != List::typeid) {
			return;
		}

		ParameterInfo^ paramInfo1 = pars[1];
		Type^ paramInfoType1 = paramInfo1->ParameterType;
		if (!paramInfoType1->IsByRef && paramInfoType1->GetElementType() != ManagedData::typeid) {
			return;
		}

		// check argument type is ManagedData
		array<Type^>^ typeParameters = paramInfoType->GetGenericArguments();
		Type^ argumentType = typeParameters[0];

		if (argumentType != ManagedData::typeid) {
			return;
		}

		PluginMethodAttribute^ attr = (PluginMethodAttribute^)pObjs[0];
		PluginMethod^ pluginMethod = gcnew PluginMethod(methodName, attr->Prototype, attr->MinArguments, 
			attr->MaxArguments, (unsigned int)attr->Flags);
		pluginMethod->Description = attr->Description;
		if (!pluginMethod->validate()) {
			return;
		}

		pluginMethod->MethodInfoProp = methodInfo;
		_methods->Add(pluginMethod);
	}
}