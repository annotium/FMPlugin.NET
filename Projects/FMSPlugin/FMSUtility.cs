using System;

namespace FMTechnologies
{
	internal class FMSUtility
	{
		public static byte[] getBytes(string value)
		{
			byte[] bytes = new byte[value.Length * sizeof(char)];
			System.Buffer.BlockCopy(value.ToCharArray(), 0, bytes, 0, bytes.Length);
			return bytes;
		}

		public static string GetString(byte[] bytes)
		{
			char[] chars = new char[bytes.Length / sizeof(char)];
			System.Buffer.BlockCopy(bytes, 0, chars, 0, bytes.Length);
			return new string(chars);
		}
	}
}
