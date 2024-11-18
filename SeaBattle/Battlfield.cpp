#include <sstream>
#include "Battlfield.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

int main(array<String^>^ args) {

	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	SeaBattle::Battlfield form;
	Application::Run(%form);

	return 0;
}
//
//void SeaBattle::Battlfield::InitializeShips() {
//	if (currentStage == GameStage::Setup) {
//
//		this->ShipsField = gcnew System::Windows::Forms::Panel();
//		this->ShipsField->Location = System::Drawing::Point(470, 21);
//		this->ShipsField->Name = L"Ship";
//		this->ShipsField->Size = System::Drawing::Size(300, 300);
//		this->ShipsField->TabIndex = 1;
//
//		// Добавление panelGrid2 к форме
//		this->Controls->Add(this->ShipsField);
//
//		// Создание сетки на этой панели
//		CreateGrid(10, 10, ShipsField);
//	}
//}
