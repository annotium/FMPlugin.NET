using System;
using System.Collections.Generic;
using System.Text;

namespace FMTechnologies
{

    public class ManagedText
    {
		enum TextSize : uint
		{
			kSize_Invalid = 0xFFFFFFFF,
			kSize_End = 0xFFFFFFFF
		};

        #region variables
        private string _text;
		private List<CharacterStyle> _styleList;
        //private
        #endregion

        #region properties
		public String Text
		{
			get
			{
				return _text;
			}
			set
			{
				_text = value;
			}
		}

        public List<CharacterStyle> Styles
        {
            get
            {
                return _styleList;
            }
        }
        #endregion

        #region methods
		public ManagedText()
		{
			_styleList = new List<CharacterStyle>();
		}

		public CharacterStyle GetStyle(int position)
		{
			if (position < _styleList.Count) {
				return _styleList[position];
			}

			return null;
		}

		public CharacterStyle GetDefaultStyle()
		{
			return null;
		}

		public void SetStyle(CharacterStyle style, UInt32 position = 0, UInt32 size = UInt32.MaxValue)
		{
            for (uint i = position; i < position + size; i++) {
                _styleList[(int)i] = style;
            }
		}

		public void RemoveStyle(CharacterStyle style)
		{ 
		
		}
        #endregion
    }
}
