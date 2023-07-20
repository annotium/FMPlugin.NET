using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Security.Cryptography;
using Microsoft.Win32;

namespace FMTLicenseManagement
{
    public partial class GenerateLicenseForm : Form
    {
        private const string CAPTION = "Generate License Key Error";
        private const string PRIVATE_KEY = "privateKey.xml";
        private string _privateKey = string.Empty;
        private const string TRIAL_TYPE = "Trial";
        private const string COMPANY = "Company";
        private const string EMAIL = "Email";
        private const string ASSEMBLY_RESOURCE = "FMTLicenseManagement.";
        private string originalMessage;

        public GenerateLicenseForm()
        {
            InitializeComponent();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void btnGenerate_Click(object sender, EventArgs e)
        {
            string name = txtName.Text;
            if (string.IsNullOrEmpty(name)) {
                return;
            }

            string company = txtCompany.Text;
            string email = txtMail.Text;

            string message = name + "\n" + company + "\n" + email;
            originalMessage = message;
            using (var rsa = new RSACryptoServiceProvider()) {
                string privateKey = Properties.Resources.PrivateKey;
                rsa.FromXmlString(privateKey);
                byte[] data = Encoding.UTF8.GetBytes(message);
                byte[] encryptedData = rsa.SignData(data, CryptoConfig.MapNameToOID("SHA512"));//rsa.Encrypt(data, false);
                txtLicense.Text = Convert.ToBase64String(encryptedData);
                btnCheck.Enabled = true;
            }
            // generate the license
            //var license = generator.Generate(name, id, expireDate, attrs, _licenseType);
            
        }

        private string GetResourceTextFile(string filename)
        {
            string result = string.Empty;

            using (Stream stream = this.GetType().Assembly.GetManifestResourceStream(ASSEMBLY_RESOURCE + filename)) {
                using (StreamReader sr = new StreamReader(stream)) {
                    result = sr.ReadToEnd();
                }
            }
            return result;
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.DefaultExt = "lic";
            dlg.Filter = "License files (*.lic)|*.lic";
            dlg.OverwritePrompt = true;
            if (dlg.ShowDialog() == System.Windows.Forms.DialogResult.OK) {
                string fileName = dlg.FileName;
                File.WriteAllText(fileName, txtLicense.Text);            
            }
        }

        private void onValueChanged(object sender, EventArgs e)
        {
            btnGenerate.Enabled = validate();
        }

        private bool validate()
        {
            if (string.IsNullOrEmpty(txtName.Text)) {
                return false;
            }

            return true;
        }

        private void btnCheck_Click(object sender, EventArgs e)
        {
            using (var rsa = new RSACryptoServiceProvider()) {
                string publicKey = Properties.Resources.PublicKey;
                rsa.FromXmlString(publicKey);
                byte[] bytesToVerify = Encoding.UTF8.GetBytes(originalMessage);
                byte[] signedBytes = Convert.FromBase64String(txtLicense.Text);
                SHA512Managed Hash = new SHA512Managed();
                byte[] hashedData = Hash.ComputeHash(signedBytes);
                bool success = rsa.VerifyData(bytesToVerify, CryptoConfig.MapNameToOID("SHA512"), signedBytes);
                txtCheckValue.Text = Convert.ToString(success);
            }           
        }
    }
}
