using System;

namespace FMTechnologies
{
    public class ManagedQuadChar
    {
        private const Int16 QUADCHAR_NUMBER = 4;
        private char[] _quadChars = new char[QUADCHAR_NUMBER];

        public char this[int index]
        {
            get
            {
                return _quadChars[index];
            }
            set 
            {
                _quadChars[index] = value;
            }
        }

        public ManagedQuadChar()
        { 
        }

        public ManagedQuadChar(String chars)
        {
            _quadChars[0] = ((chars.Length > 0) ? chars[0] : ' ');
            _quadChars[1] = ((chars.Length > 1) ? chars[1] : ' ');
            _quadChars[2] = ((chars.Length > 2) ? chars[2] : ' ');
            _quadChars[3] = ((chars.Length > 3) ? chars[3] : ' ');
        }

        public ManagedQuadChar(char char0, char char1, char char2, char char3)
        {
            _quadChars[0] = char0;
            _quadChars[1] = char1;
            _quadChars[2] = char2;
            _quadChars[3] = char3;
        }

        public ManagedQuadChar(ManagedQuadChar other)
        {
            _quadChars[0] = other[0];
            _quadChars[1] = other[1];
            _quadChars[2] = other[2];
            _quadChars[3] = other[3];
        }

        public bool Equals(ManagedQuadChar quadChar) 
        {
            return (_quadChars[0] == quadChar[0] && 
                    _quadChars[1] == quadChar[1] &&
                    _quadChars[2] == quadChar[2] &&
                    _quadChars[3] == quadChar[3]); 
        }

        public override string ToString()
        {
            return new string(_quadChars);
        }
    }
}
