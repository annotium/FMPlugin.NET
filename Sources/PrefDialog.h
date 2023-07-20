#pragma once

#include "ManagedPlugin.h"
#include "Utility.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Diagnostics;
using namespace System::Security::Cryptography;

namespace FMTechnologies
{
	/// <summary>
	/// Summary for PrefDialog
	/// </summary>
	public ref class PrefDialog : public System::Windows::Forms::Form
	{
	public:
		PrefDialog(List<ManagedPlugin^>^ plugins)
		{
			_plugins = plugins;
			InitializeComponent();
			displayLicenseInfo();
			loadAssembliesData();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PrefDialog()
		{
			if (components) {
				delete components;
			}
		}

	private: 
		System::Windows::Forms::TabControl^  tabControl1;
		System::Windows::Forms::TabPage^  tabPage1;
		System::Windows::Forms::TabPage^  tabPage2;
		System::Windows::Forms::TabPage^  tabPage3;
		System::Windows::Forms::Button^  okBtn;
		System::Windows::Forms::DataGridView^  assembliesGridView;
		System::Windows::Forms::PictureBox^  pictureBox1;
		System::Windows::Forms::Label^  label3;


		System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  lblUserInfo;


		System::Windows::Forms::Button^  btnRegister;
		System::Windows::Forms::Label^  lblEmail;
		List<ManagedPlugin^>^ _plugins;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
		System::Windows::Forms::DataGridViewTextBoxColumn^  AssemblyName;
		System::Windows::Forms::DataGridViewTextBoxColumn^  Description;
		System::Windows::Forms::DataGridView^  methodsGridView;
		System::Windows::Forms::DataGridViewTextBoxColumn^  AssemblyCol;
		System::Windows::Forms::DataGridViewTextBoxColumn^  MethodCol;
	private: System::Windows::Forms::Label^  label1;
			 System::Windows::Forms::DataGridViewTextBoxColumn^  MethodDescriptionCol;

			 

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(PrefDialog::typeid));
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->lblEmail = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->lblUserInfo = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->assembliesGridView = (gcnew System::Windows::Forms::DataGridView());
			this->AssemblyName = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Description = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->methodsGridView = (gcnew System::Windows::Forms::DataGridView());
			this->AssemblyCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->MethodCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->MethodDescriptionCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->btnRegister = (gcnew System::Windows::Forms::Button());
			this->okBtn = (gcnew System::Windows::Forms::Button());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->assembliesGridView))->BeginInit();
			this->tabPage3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->methodsGridView))->BeginInit();
			this->SuspendLayout();
			// 
			// tabControl1
			// 
			this->tabControl1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Location = System::Drawing::Point(12, 12);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(709, 385);
			this->tabControl1->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->Controls->Add(this->lblEmail);
			this->tabPage1->Controls->Add(this->label3);
			this->tabPage1->Controls->Add(this->label2);
			this->tabPage1->Controls->Add(this->lblUserInfo);
			this->tabPage1->Controls->Add(this->pictureBox1);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(701, 359);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Info";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(155, 315);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(391, 20);
			this->label1->TabIndex = 12;
			this->label1->Text = L"Copyright @ FM Technologies Corp. All rights reserves";
			// 
			// lblEmail
			// 
			this->lblEmail->AutoSize = true;
			this->lblEmail->Location = System::Drawing::Point(259, 211);
			this->lblEmail->Name = L"lblEmail";
			this->lblEmail->Size = System::Drawing::Size(32, 13);
			this->lblEmail->TabIndex = 11;
			this->lblEmail->Text = L"Email";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(166, 211);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(32, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Email";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(166, 180);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(62, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Register To";
			// 
			// lblUserInfo
			// 
			this->lblUserInfo->AutoSize = true;
			this->lblUserInfo->Location = System::Drawing::Point(259, 180);
			this->lblUserInfo->Name = L"lblUserInfo";
			this->lblUserInfo->Size = System::Drawing::Size(52, 13);
			this->lblUserInfo->TabIndex = 3;
			this->lblUserInfo->Text = L"Trial User";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(169, 67);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(343, 61);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->assembliesGridView);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(701, 359);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Assemblies";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// assembliesGridView
			// 
			this->assembliesGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->assembliesGridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {this->AssemblyName, 
				this->Description});
			this->assembliesGridView->Dock = System::Windows::Forms::DockStyle::Fill;
			this->assembliesGridView->Location = System::Drawing::Point(3, 3);
			this->assembliesGridView->Name = L"assembliesGridView";
			this->assembliesGridView->Size = System::Drawing::Size(695, 353);
			this->assembliesGridView->TabIndex = 0;
			// 
			// AssemblyName
			// 
			this->AssemblyName->HeaderText = L"Assembly Info";
			this->AssemblyName->Name = L"AssemblyName";
			this->AssemblyName->ReadOnly = true;
			this->AssemblyName->Width = 300;
			// 
			// Description
			// 
			this->Description->FillWeight = 300;
			this->Description->HeaderText = L"Description";
			this->Description->Name = L"Description";
			this->Description->ReadOnly = true;
			this->Description->Width = 400;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->methodsGridView);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(701, 359);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Methods";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// methodsGridView
			// 
			this->methodsGridView->AllowUserToDeleteRows = false;
			this->methodsGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->methodsGridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {this->AssemblyCol, 
				this->MethodCol, this->MethodDescriptionCol});
			this->methodsGridView->Dock = System::Windows::Forms::DockStyle::Fill;
			this->methodsGridView->Location = System::Drawing::Point(3, 3);
			this->methodsGridView->Name = L"methodsGridView";
			this->methodsGridView->ReadOnly = true;
			this->methodsGridView->Size = System::Drawing::Size(695, 353);
			this->methodsGridView->TabIndex = 0;
			// 
			// AssemblyCol
			// 
			this->AssemblyCol->HeaderText = L"Assembly";
			this->AssemblyCol->Name = L"AssemblyCol";
			this->AssemblyCol->ReadOnly = true;
			this->AssemblyCol->Width = 150;
			// 
			// MethodCol
			// 
			this->MethodCol->HeaderText = L"Method";
			this->MethodCol->Name = L"MethodCol";
			this->MethodCol->ReadOnly = true;
			this->MethodCol->Width = 150;
			// 
			// MethodDescriptionCol
			// 
			this->MethodDescriptionCol->HeaderText = L"Description";
			this->MethodDescriptionCol->Name = L"MethodDescriptionCol";
			this->MethodDescriptionCol->ReadOnly = true;
			this->MethodDescriptionCol->Width = 400;
			// 
			// btnRegister
			// 
			this->btnRegister->Location = System::Drawing::Point(383, 403);
			this->btnRegister->Name = L"btnRegister";
			this->btnRegister->Size = System::Drawing::Size(85, 30);
			this->btnRegister->TabIndex = 10;
			this->btnRegister->Text = L"Register";
			this->btnRegister->UseVisualStyleBackColor = true;
			this->btnRegister->Click += gcnew System::EventHandler(this, &PrefDialog::btnRegister_Click);
			// 
			// okBtn
			// 
			this->okBtn->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->okBtn->Location = System::Drawing::Point(264, 403);
			this->okBtn->Name = L"okBtn";
			this->okBtn->Size = System::Drawing::Size(85, 30);
			this->okBtn->TabIndex = 1;
			this->okBtn->Text = L"OK";
			this->okBtn->UseVisualStyleBackColor = true;
			this->okBtn->Click += gcnew System::EventHandler(this, &PrefDialog::okBtn_Click);
			// 
			// PrefDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(733, 445);
			this->Controls->Add(this->okBtn);
			this->Controls->Add(this->btnRegister);
			this->Controls->Add(this->tabControl1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"PrefDialog";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"FMPlugin.NET Preferences";
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->tabPage2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->assembliesGridView))->EndInit();
			this->tabPage3->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->methodsGridView))->EndInit();
			this->ResumeLayout(false);

		}

		void loadAssembliesData()
		{
			for each (ManagedPlugin^ plugin in _plugins) {
				Assembly^ assembly = plugin->BaseAssembly;
				assembliesGridView->Rows->Add(assembly->FullName, plugin->Description);
				
				String^ name = assembly->GetName()->Name;
				int index = 0;
				for each (PluginMethod^ method in plugin->Methods) {
					if (index == 0) {
						methodsGridView->Rows->Add(name, method->Prototype, method->Description);
					}
					else {
						methodsGridView->Rows->Add("", method->Prototype, method->Description);					
					}

					++index;
				}
			}
		}

		Void okBtn_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->Close();
		}
		
		Void btnRegister_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			OpenFileDialog^ dialog = gcnew OpenFileDialog();
			dialog->DefaultExt = "lic";
			dialog->Filter = "FMT License files|*.lic";

			if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				try {
					FMTUtility::writeLicenseInfo(dialog->FileName);
				}
				catch (Exception^ ex) {
					// show error message
				}
			}
		}

		Void displayLicenseInfo()
		{
			Boolean registered = false;
			Dictionary<String^, String^>^ licenseInfo = FMTUtility::getLicenseInfo(registered);
			String^ regStr = licenseInfo[FMTUtility::KEY_USERNAME];
			if (!registered) {
				Int32 trialDays = 0;
				Int32::TryParse(licenseInfo[FMTUtility::KEY_TRIAL], trialDays);
				regStr += "(expired in " + trialDays.ToString() + " days )";
			}

			lblUserInfo->Text = regStr;
			lblEmail->Text = licenseInfo[FMTUtility::KEY_EMAIL];
		}
#pragma endregion
	};
}
