using System;
using System.Collections.Generic;
using FMTechnologies;
using System.Reflection;
using System.IO;

namespace TestFMPlugin
{
    [PluginClass]
    public class FMTPluginTesting
    {
		[PluginMethod(Prototype = "Add(a, b)", MinArguments = 2, MaxArguments = 2, 
            Flags = PluginFlags.kDisplayInAllDialogs, Description="Adding 2 numbers")]
        public static short Add(List<ManagedData> dataVect, out ManagedData result)
        {
            int a = (int)dataVect[0].AsNumber;
            int b = (int)dataVect[1].AsNumber;
            result = new ManagedData();
            result.SetNumber(a + b);
            return 0;
        }

        [PluginMethod(Prototype = "SaveImage()", MinArguments = 1, MaxArguments = 1,
            Flags = PluginFlags.kDisplayInAllDialogs, Description = "Read image from container field and write to file")]
        public static short SaveImage(List<ManagedData> dataVect, out ManagedData result) {
            ManagedBinaryData imageData = dataVect[0].AsBinary;
            //FileInfo imgFile = new FileInfo("C:/Download/newimage.jpg");
            string path = "C:/Downloads/newimage.jpg";
            //File.WriteAllBytes(path, imageData.DataItems[2].buffer.ToArray());

            foreach (DataItem item in imageData.DataItems) {
                System.Diagnostics.Debug.WriteLine("{0} : {1}", item.quadChar.ToString(), item.buffer.Count);
            }
            /*try {

                // Open file for reading
                System.IO.FileStream _FileStream =
                   new System.IO.FileStream(path, System.IO.FileMode.Create, System.IO.FileAccess.Write);
                // Writes a block of bytes to this stream using data from
                // a byte array.
                byte[] buffer = imageData.DataItems[2].buffer.ToArray();
                _FileStream.Write(buffer, 0, buffer.Length);

                // close file stream
                _FileStream.Close();
            }
            catch (Exception _Exception) {
                // Error
                Console.WriteLine("Exception caught in process: {0}",
                                  _Exception.ToString());
            }*/

            result = new ManagedData();
            return 0;
        }
    }
}
