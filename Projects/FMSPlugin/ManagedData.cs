using System;
using System.IO;
using System.Drawing;
using System.Drawing.Imaging;
using System.Collections.Generic;

namespace FMTechnologies
{
    /// <summary>
    /// 
    /// </summary>
    public class ManagedData
    {
        private DataType _dataType;
        private String _text;
        private double _number;
        private DateTime _dateTime;
        private bool _boolean;
        private ManagedBinaryData _binary;

        /// <summary>
        /// DataType
        /// </summary>
        public DataType FMDataType
        {
            get
            {
                return _dataType;
            }

            set
            {
                _dataType = value;
            }
        }

        /// <summary>
        /// Text property if managed data is a text
        /// </summary>
        public string AsText
        {
            get
            {
                switch (_dataType) {
                    case DataType.DTText:
                        return _text;
                    case DataType.DTNumber:
                        return _number.ToString();
                    case DataType.DTDate:
                        return _dateTime.ToShortDateString();
                    case DataType.DTTime:
                        return _dateTime.ToShortTimeString();
                    case DataType.DTTimeStamp:
                        return _dateTime.ToString();
                    case DataType.DTBinary:
                        if (_binary == null) {
                            return "Binary Data: <null>";
                        }
                        return _binary.ToString();
                    case DataType.DTBoolean:
                        return _boolean.ToString();
                    default:
                        return "";
                }
            }
            set
            {
                _dataType = DataType.DTText;
                _text = value;
            }
        }

        /// <summary>
        /// Number property if managed data is a number
        /// </summary>
        public double AsNumber
        {
            get
            {
                switch (_dataType) {
                    case DataType.DTText: {
                            double result;
                            Double.TryParse(_text, out result);
                            return result;
                        }
                    case DataType.DTNumber:
                        return _number;
                    default:
                        if (_dataType != DataType.DTBoolean) {
                            return 0.0;
                        }
                        return (double)(_boolean ? 1 : 0);
                }
            }

            set
            {
                _dataType = DataType.DTNumber;
                _number = value;
            }
        }

        /// <summary>
        /// Datetime property if managed data is a datetime
        /// </summary>
        public DateTime AsDate
        {
            get
            {
                switch (_dataType) {
                    case DataType.DTText:
                        return DateTime.Parse(_text);
                    case DataType.DTDate:
                    case DataType.DTTime:
                    case DataType.DTTimeStamp:
                        return _dateTime;
                }
                return DateTime.MinValue;
            }
            set
            {
                _dataType = DataType.DTDate;
                _dateTime = value;
            }
        }

        /// <summary>
        /// Time property if managed data is a time
        /// </summary>
        public DateTime AsTime
        {
            get
            {
                switch (_dataType) {
                    case DataType.DTText:
                        return DateTime.Parse(_text);
                    case DataType.DTDate:
                    case DataType.DTTime:
                    case DataType.DTTimeStamp:
                        return _dateTime;
                }
                return DateTime.MinValue;
            }

            set
            {
                _dataType = DataType.DTDate;
                _dateTime = value;
            }
        }

        /// <summary>
        /// Datetime property if managed data is a datetime
        /// </summary>
        public DateTime AsDateTime
        {
            get
            {
                switch (_dataType) {
                    case DataType.DTText:
                        return DateTime.Parse(_text).Date;
                    case DataType.DTDate:
                    case DataType.DTTime:
                    case DataType.DTTimeStamp:
                        return _dateTime.Date;
                }
                return DateTime.MinValue;
            }

            set
            {
                _dataType = DataType.DTTimeStamp;
                _dateTime = value;
            }
        }

        /// <summary>
        /// BinaryData property if managed data is a binary data
        /// </summary>
        public ManagedBinaryData AsBinary
        {
            get
            {
                if (_dataType == DataType.DTBinary) {
                    return _binary;
                }

                return null;
            }
            set
            {
                _dataType = DataType.DTBinary;
                _binary = value;
            }
        }

        /// <summary>
        /// Boolean property if managed data is a boolean
        /// </summary>
        public Boolean AsBoolean
        {
            get
            {
                switch (_dataType) {
                    case DataType.DTText:
                        return Boolean.Parse(_text);
                    case DataType.DTNumber:
                        return _number != 0.0;
                    default:
                        return _dataType == DataType.DTBoolean && _boolean;
                }
            }
            set
            {
                _dataType = DataType.DTBoolean;
                _boolean = value;
            }
        }

        /// <summary>
        /// Constructor
        /// </summary>
        public ManagedData()
        {
            _dataType = DataType.DTInvalid;
        }

        /// <summary>
        /// Set text data
        /// </summary>
        /// <param name="value">data to set</param>
        public void SetText(String value)
        {
            _dataType = DataType.DTText;
            _text = value.ToString();
        }

        /// <summary>
        /// Set number data
        /// </summary>
        /// <param name="value">data to set</param>
        public void SetNumber(Int16 value)
        {
            _dataType = DataType.DTNumber;
            _number = Convert.ToDouble(value);
        }

        /// <summary>
        /// Set number data
        /// </summary>
        /// <param name="value">data to set</param>
        public void SetNumber(Int32 value)
        {
            _dataType = DataType.DTNumber;
            _number = Convert.ToDouble(value);
        }

        /// <summary>
        /// Set number data
        /// </summary>
        /// <param name="value">data to set</param>
        public void SetNumber(Int64 value)
        {
            _dataType = DataType.DTNumber;
            _number = Convert.ToDouble(value);
        }

        /// <summary>
        /// Set number data
        /// </summary>
        /// <param name="value">data to set</param>
        public void SetNumber(UInt16 value)
        {
            _dataType = DataType.DTNumber;
            _number = Convert.ToDouble(value);
        }

        /// <summary>
        /// Set number data
        /// </summary>
        /// <param name="value">data to set</param>
        public void SetNumber(UInt32 value)
        {
            _dataType = DataType.DTNumber;
            _number = Convert.ToDouble(value);
        }

        /// <summary>
        /// Set number data
        /// </summary>
        /// <param name="value">data to set</param>
        public void SetNumber(UInt64 value)
        {
            _dataType = DataType.DTNumber;
            _number = Convert.ToDouble(value);
        }

        /// <summary>
        /// Set number data
        /// </summary>
        /// <param name="value">data to set</param>
        public void SetNumber(Single value)
        {
            _dataType = DataType.DTNumber;
            _number = Convert.ToDouble(value);
        }

        /// <summary>
        /// Set number data
        /// </summary>
        /// <param name="value">data to set</param>
        public void SetNumber(Double value)
        {
            _dataType = DataType.DTNumber;
            _number = Convert.ToDouble(value);
        }

        /// <summary>
        /// Set number data
        /// </summary>
        /// <param name="value">data to set</param>
        public void SetNumber(Decimal value)
        {
            _dataType = DataType.DTNumber;
            _number = Convert.ToDouble(value);
        }

        /// <summary>
        /// Set datetime data
        /// </summary>
        /// <param name="value">data to set</param>
        public void SetDateTime(DateTime value)
        {
            _dataType = DataType.DTDate;
            _dateTime = (DateTime)value;
        }

        /// <summary>
        /// Set boolean data
        /// </summary>
        /// <param name="value">data to set</param>
        public void SetBoolean(bool value)
        {
            _dataType = DataType.DTBoolean;
            _boolean = value;
        }

        /// <summary>
        /// Set binary data
        /// </summary>
        /// <param name="value">data to set</param>
        public void SetBinaryData(FileInfo fileInfo)
        {
            _dataType = DataType.DTBinary;
            _binary.ReadFileBinary(fileInfo);
        }

        /// <summary>
        /// Set binary data from file
        /// </summary>
        /// <param name="value">read file data and set</param>
        public void SetBinaryData(string fileName)
        {
            _dataType = DataType.DTBinary;
            _binary.ReadFileName(fileName);
        }

        /// <summary>
        /// Set binary data from image
        /// </summary>
        /// <param name="image">image to read data</param>
        public void SetBinaryData(Image image)
        {
            _dataType = DataType.DTBinary;
            _binary.ReadImage(image);
        }
    }
}
