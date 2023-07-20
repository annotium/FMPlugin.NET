using System;

namespace FMTechnologies
{
    /// <summary>
    /// Specified flags for plugin's method
    /// </summary>
	public enum PluginFlags : uint
	{
		kMayEvaluateOnServer    = 0x00000001,		                                     
		kDisplayCalcFields      = 0x00000100,
		kDisplayAutoEnter       = 0x00000200,
		kDisplayValidation      = 0x00000400,
		kDisplayCustomFunctions = 0x00000800,
		kDisplayPrivileges      = 0x00001000,
		kDisplayInFuture1       = 0x00002000,
		kDisplayInFuture2       = 0x00004000,
		kDisplayGeneric         = 0x00008000,
		kDisplayInAllDialogs    = 0x0000FF00
	}

    /// <summary>
    /// Attribute to specified the assembly is a FileMaker FMT .NET plugin. Only assemblies with this attribute are enable to load 
    /// </summary>
	[AttributeUsage(AttributeTargets.Assembly)]
    public class PluginAssemblyAttribute : Attribute
	{
        /// <summary>
        /// Plugin Assembly QuadChar
        /// </summary>
		public string QuadChar
		{
			get;
			set;
		}

        /// <summary>
        /// Plugin Assembly Description
        /// </summary>
        public string Description
        {
            get;
            set;
        }
	}

    /// <summary>
    /// Attribute to specified the class is a FileMaker FMT .NET plugin class. Only classes with this attribute are enable to load
    /// </summary>
	[AttributeUsage(AttributeTargets.Class)]
	public class PluginClassAttribute : Attribute
	{
	}

    /// <summary>
    /// Attribute to specified the method is a FileMaker FMT .NET plugin method. Only methods with this attribute are enable to load
    /// </summary>
	[AttributeUsage(AttributeTargets.Method)]
	public class PluginMethodAttribute : Attribute
	{
        /// <summary>
        /// Method Prototype. Example "FunctionName(param1, param2, ...)"
        /// </summary>
        public string Prototype
        {
            get;
            set;
        }

        /// <summary>
        /// Minimum method's arguments, at least 0
        /// </summary>
        public ushort MinArguments
        {
            get;
            set;
        }

        /// <summary>
        /// Maximumm method's argument
        /// </summary>
        public ushort MaxArguments
        {
            get;
            set;
        }

        /// <summary>
        /// Plugin method's flags 
        /// </summary>
		public PluginFlags Flags
		{
			get;
			set;
		}

        /// <summary>
        /// Method description
        /// </summary>
        public string Description
        {
            get;
            set;
        }
	}
}
