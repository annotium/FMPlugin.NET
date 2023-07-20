using System;
using System.Collections.Generic;
using System.IO;
using System.Drawing.Imaging;
using System.Drawing;
using System.Diagnostics;
using System.Windows.Forms;

namespace FMTechnologies
{
    /// <summary>
    /// DataItem class to contain binary data
    /// </summary>
	public class DataItem
	{
		public ManagedQuadChar quadChar = new ManagedQuadChar();
		public List<byte> buffer = new List<byte>();
	}

    /// <summary>
    /// Managed BinaryData class
    /// </summary>
	public class ManagedBinaryData
	{
		#region variables
		private List<DataItem> _dataItems;
		#endregion

		#region constants
		// images
		private const string BINARY_JPEG = "JPEG";
		private const string BINARY_GIFF = "GIFf";
		private const string BINARY_PNG = "PNG ";
		private const string BINARY_PDF = "PDF ";
		private const string BINARY_EPS = "EPS ";
        private const string BINARY_TIFF = "TIFF";
		private const string BINARY_PICT = "PICT";
		private const string BINARY_META = "META";
		private const string BINARY_BMP = "BMPf";

		// files
		private const string FILE_NAME = "FNAM";
		private const string BINARY_FILE = "FILE";
		private const string BINARY_FORK = "FORK";

		// sounds
		private const string BINARY_SND = "snd ";
		#endregion

		#region property
		public int Count
		{
			get
			{
				return _dataItems.Count;
			}
		}

		public List<DataItem> DataItems
		{
			get
			{
				return _dataItems;
			}
			set
			{
				_dataItems = value;
			}
		}
		#endregion

		#region methods
        /// <summary>
        /// Constructor
        /// </summary>
		public ManagedBinaryData()
		{
			_dataItems = new List<DataItem>();
		}

        /// <summary>
        /// Add data item to binary data
        /// </summary>
        /// <param name="quadChar_">Defined QuadChar data</param>
        /// <param name="buffer_">binary data in byte format</param>
		public void Add(ManagedQuadChar quadChar_, List<byte> buffer_)
		{
			DataItem item = new DataItem();
			item.quadChar = quadChar_;
			item.buffer = buffer_;
            _dataItems.Add(item);
		}

        /// <summary>
        /// Get index of a binary data item
        /// </summary>
        /// <param name="quadChar">Data item quadchar</param>
        /// <returns>Index of data item if found, otherwise return -1</returns>
		public UInt16 getIndex(ManagedQuadChar quadChar)
		{
			return (UInt16)_dataItems.FindIndex(item => item.quadChar.Equals(quadChar));
		}

        /// <summary>
        /// Read file name and add it into binary data (FNAM)
        /// </summary>
        /// <param name="fileInfo">file information</param>
        public void ReadFileName(FileInfo fileInfo)
        {
            try {
                ManagedQuadChar fNameQuadChar = new ManagedQuadChar(FILE_NAME);
                byte[] fileNameBytes = FMSUtility.getBytes(fileInfo.FullName);
                Add(fNameQuadChar, new List<byte>(fileNameBytes));
            }
            catch (Exception ex) {
                System.Diagnostics.Debug.WriteLine("Error while setting managed binary data from file: '" + fileInfo.FullName +
                    "'. Exception occurred: " + ex.StackTrace.ToString());
            }
        }

        /// <summary>
        /// Read file data and add it into binary data (FILE)
        /// </summary>
        /// <param name="fileInfo">file to read</param>
		public void ReadFileBinary(FileInfo fileInfo)
		{
			try {
				using (FileStream fileStream = new FileStream(fileInfo.FullName, FileMode.Open, FileAccess.Read)) {
					byte[] bytes = new byte[fileStream.Length];
					fileStream.Read(bytes, 0, (int)fileStream.Length);
					ManagedQuadChar quadChar = new ManagedQuadChar(BINARY_FILE);
					Add(quadChar, new List<byte>(bytes));
				}
			}
			catch (Exception ex) {
				System.Diagnostics.Debug.WriteLine("Error while setting managed binary data from file: '" + fileInfo.FullName +
					"'. Exception occurred: " + ex.StackTrace.ToString());
			}
		}

        /// <summary>
        /// Read file name and add it into binary data
        /// </summary>
        /// <param name="fileName">fileName to read</param>
        public void ReadFileName(string fileName)
		{
			FileInfo fileInfo = new FileInfo(fileName);
			if (fileInfo.Exists) {
				ReadFileName(fileInfo);
			}
		}

        /// <summary>
        /// Read file data and add it into binary data
        /// </summary>
        /// <param name="fileName">filename to read</param>
        public void ReadFileBinary(string fileName)
        {
            FileInfo fileInfo = new FileInfo(fileName);
            if (fileInfo.Exists) {
                ReadFileBinary(fileInfo);
            }
        }

        /// <summary>
        /// Read image and add it into binary data
        /// </summary>
        /// <param name="image">image to read</param>
		public void ReadImage(Image image)
		{
			try {
				ManagedQuadChar quadChar = new ManagedQuadChar();
				MemoryStream memoryStream = new MemoryStream();

				if (ImageFormat.Jpeg.Equals(image.RawFormat)) {
					quadChar = new ManagedQuadChar(BINARY_JPEG);
					image.Save(memoryStream, ImageFormat.Jpeg);
				}
				else if (ImageFormat.Gif.Equals(image.RawFormat)) {
					quadChar = new ManagedQuadChar(BINARY_GIFF);
					image.Save(memoryStream, ImageFormat.Gif);
				}
				else if (ImageFormat.Png.Equals(image.RawFormat)) {
					quadChar = new ManagedQuadChar(BINARY_PNG);
					image.Save(memoryStream, ImageFormat.Png);
				}
				else if (ImageFormat.Tiff.Equals(image.RawFormat)) {
					quadChar = new ManagedQuadChar(BINARY_TIFF);
				}
				else if (ImageFormat.Bmp.Equals(image.RawFormat)) {
					quadChar = new ManagedQuadChar(BINARY_BMP);
					image.Save(memoryStream, ImageFormat.Bmp);
				}
				else {
					return;
				}

				Add(quadChar, new List<byte>(memoryStream.GetBuffer()));
			}
			catch (Exception ex) {
				System.Diagnostics.Debug.WriteLine("Error while setting managed binary data from image. Exception occurred: " + ex.StackTrace.ToString());
			}
		}

        /// <summary>
        /// Write binary data item to file
        /// </summary>
        /// <param name="dataItem">Working data item </param>
        /// <param name="fileName">file to write data</param>
        public static void WriteFile(DataItem dataItem, string fileName)
        {
            FileInfo fileInfo = new FileInfo(fileName);
            WriteFile(dataItem, fileInfo);
        }

        /// <summary>
        /// Write binary data item to file
        /// </summary>
        /// <param name="dataItem">Working data item</param>
        /// <param name="fileInfo">file to write data</param>
        public static void WriteFile(DataItem dataItem, FileInfo fileInfo)
        {
            if (fileInfo.Exists) {
                string message = string.Format("File '{0}' already existed!", fileInfo.FullName);
                MessageBox.Show(message, "Write file failed", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            try {
                using (FileStream fileStream = new FileStream(fileInfo.FullName, FileMode.Create, FileAccess.Write)) {
                    fileStream.Write(dataItem.buffer.ToArray(), 0, dataItem.buffer.Count); 
                }
            }
            catch (Exception ex) {
                System.Diagnostics.Debug.WriteLine("Error while writing managed binary data to file: '" + fileInfo.FullName +
                    "'. Exception occurred: " + ex.StackTrace.ToString());
            }
        }

        /// <summary>
        /// Read binary data item and write it to image
        /// </summary>
        /// <param name="dataItem">working data item</param>
        /// <param name="image">image to write data</param>
        public static void GetImage(DataItem dataItem, out Image image)
        {
            image = null;
            try {
                using (MemoryStream memStream = new MemoryStream(dataItem.buffer.ToArray())) {
                    image = Image.FromStream(memStream);
                }
            }
            catch (Exception ex) {
                System.Diagnostics.Debug.WriteLine("Error while getting image from binary data. Exception occurred: " + 
                    ex.StackTrace.ToString());
            }
        }
		#endregion
	}
}
