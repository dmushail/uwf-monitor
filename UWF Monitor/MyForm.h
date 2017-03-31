#include "resource.h"
#include <Windows.h>
#pragma once


int loadMgr();
HICON loadIcon();

namespace UWFMonitor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::NotifyIcon^  uwfMon;




	protected:

	protected:
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->uwfMon = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			this->SuspendLayout();
			// 
			// uwfMon
			// 
			this->uwfMon->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"uwfMon.Icon")));
			this->uwfMon->Text = L"Write Filter";
			this->uwfMon->Visible = true;
			this->uwfMon->DoubleClick += gcnew System::EventHandler(this, &MyForm::uwfMon_DoubleClick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoValidate = System::Windows::Forms::AutoValidate::Disable;
			this->ClientSize = System::Drawing::Size(10, 10);
			this->ControlBox = false;
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->Enabled = false;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"MyForm";
			this->Opacity = 0;
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->Text = L"MyForm";
			this->WindowState = System::Windows::Forms::FormWindowState::Minimized;
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void uwfMon_DoubleClick(System::Object^  sender, System::EventArgs^  e) {


				 // Comment/Uncomment loadMgr below depending on if you would like to launch UWF Manager on doubleclick.
				 // Make sure the UWF Monitor executable is copied to and renamed to match the execution path within the loadMgr function.
				  
				 loadMgr();

				 //Refreshes status indicator on doubleclick.
				 System::Drawing::Icon^ newIco = System::Drawing::Icon::FromHandle((IntPtr)loadIcon());
				 this->uwfMon->Icon = newIco;
	}
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {

				 System::Drawing::Icon^ newIco = System::Drawing::Icon::FromHandle((IntPtr)loadIcon());
				 this->uwfMon->Icon = newIco;
	}
	};
}
