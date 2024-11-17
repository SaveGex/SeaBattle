#pragma once

using namespace System;
using namespace System::Windows::Forms;

public ref class CustomMessageBox : public Form {
public:
    CustomMessageBox(String^ message, String^ title) {
        // settings of form
        this->FormBorderStyle = FormBorderStyle;
        this->StartPosition = FormStartPosition::CenterScreen;
        this->Size = System::Drawing::Size(300, 150);
        this->Text = title;

        // add Label
        Label^ label = gcnew Label();
        label->Text = message;
        label->AutoSize = true;
        label->Location = System::Drawing::Point(20, 20);
        this->Controls->Add(label);

        // add button
        Button^ okButton = gcnew Button();
        okButton->Text = "OK";
        okButton->Location = System::Drawing::Point(100, 70);
        okButton->Click += gcnew EventHandler(this, &CustomMessageBox::OnOkButtonClick);
        this->Controls->Add(okButton);

        this->MouseDown += gcnew MouseEventHandler(this, &CustomMessageBox::OnFormMouseDown);
    }

    static void Show(String^ message, String^ title) {
        CustomMessageBox^ box = gcnew CustomMessageBox(message, title);
        box->ShowDialog();
    }

private:
    void OnOkButtonClick(Object^ sender, EventArgs^ e) {
        this->Close();
    }

    void OnFormMouseDown(Object^ sender, MouseEventArgs^ e) {
        this->Close();
    }
};
