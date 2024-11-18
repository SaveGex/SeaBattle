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