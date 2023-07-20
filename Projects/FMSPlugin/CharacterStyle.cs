using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace FMTechnologies
{	
	public class CharacterStyle
	{
		public enum FontScript
		{
			kRoman = 0,
			kGreek = 1,
			kCyrillic = 2,
			kCentralEurope = 3,
			kShiftJIS = 4,
			kTraditionalChinese = 5,
			kSimplifiedChinese = 6,
			kOEM = 7,
			kSymbol = 8,
			kNative = 9,
			kOther = 10,
			kKorean = 11,
			kDingbats = 12,
			kTurkish = 13,

			kInvalidFont = 0xFFFF
		};

		#region variables
		private Color _color;
		private Font _font;
		#endregion

		#region properties
		public Font Font
		{
			get
			{
				return _font;
			}
		}

		public Color Color
		{
			get 
			{
				return _color;
			}
		}
		#endregion

		#region methods
		public CharacterStyle()
		{ 
		}
		#endregion		
	}
}
