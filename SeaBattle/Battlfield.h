#pragma once
#include <string>
#include <array>
#include "Ship.h"
#include "battleship.h"

namespace SeaBattle {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Summary for Battlfield
	/// </summary>
	public ref class Battlfield : public System::Windows::Forms::Form
	{
	enum class GameStage {
			Setup,
			Placement,
			Battle,
			GameOver
		};
	public:
		Battlfield(void)
		{
			ships_array = gcnew List<Ship^>;
			InitializeComponent();
			
			//
			//TODO: Add the constructor code here
			//
			CreateGrid(10, 10, panelGrid);

		}

	public:

	public:

	public:
	private:
		GameStage currentStage = GameStage::Setup;
	private: System::Windows::Forms::Panel^ panel1;

		   List<Ship^>^ ships_array;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Battlfield()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

        System::Windows::Forms::Panel^ panelGrid;
		System::Windows::Forms::Panel^ panelGrid2;

		//System::Windows::Forms::Panel^ panelGrid2;

	private: System::Windows::Forms::Button^ button1;

		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
        void InitializeComponent(void)
        {
			this->panelGrid = (gcnew System::Windows::Forms::Panel());
			this->panelGrid2 = (gcnew System::Windows::Forms::Panel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// panelGrid
			// 
			this->panelGrid->Location = System::Drawing::Point(12, 21);
			this->panelGrid->Name = L"panelGrid";
			this->panelGrid->Size = System::Drawing::Size(300, 300);
			this->panelGrid->TabIndex = 0;
			// 
			// panelGrid2
			// 
			this->panelGrid2->Location = System::Drawing::Point(0, 0);
			this->panelGrid2->Name = L"panelGrid2";
			this->panelGrid2->Size = System::Drawing::Size(200, 100);
			this->panelGrid2->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(358, 363);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Ready";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// Battlfield
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->ClientSize = System::Drawing::Size(792, 398);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->panelGrid);
			this->Name = L"Battlfield";
			this->Text = L"Battleship Game";
			this->ResumeLayout(false);

		}
		void InitializeGameStage()
		{
			if (currentStage == GameStage::Setup) {
				// Создание и настройка panelGrid2
				this->panelGrid2 = gcnew System::Windows::Forms::Panel();
				this->panelGrid2->Location = System::Drawing::Point(470, 21);
				this->panelGrid2->Name = L"panelGrid2";
				this->panelGrid2->Size = System::Drawing::Size(300, 300);
				this->panelGrid2->TabIndex = 1;

				// Добавление panelGrid2 к форме
				this->Controls->Add(this->panelGrid2);

				// Создание сетки на этой панели
				CreateGrid(10, 10, panelGrid2);
			}
		}
		void InitializeShips() {
			if (currentStage == GameStage::Setup) {
				Ship^ ship = nullptr;
				ships_array->Add(ship);
				this->panelGrid2 = gcnew System::Windows::Forms::Panel();
				this->panelGrid2->Location = System::Drawing::Point(470, 21);
				this->panelGrid2->Name = L"Ship";
				this->panelGrid2->Size = System::Drawing::Size(300, 300);
				this->panelGrid2->TabIndex = 1;

				// Добавление panelGrid2 к форме
				//this->Controls->Add(this->panelGrid2);

				// Создание сетки на этой панели
				CreateGrid(10, 10, panelGrid2);
			}
		}
        // function which create some grid
        void CreateGrid(int rows, int cols, Panel^ panel)
        {
            for (int i = 0; i < rows; ++i)
            {
                for (int j = 0; j < cols; ++j)
                {
                    PictureBox^ cell = gcnew PictureBox();
                    cell->Size = System::Drawing::Size(30, 30);
                    cell->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
                    cell->Location = System::Drawing::Point(j * 30, i * 30);
                    cell->BackColor = System::Drawing::Color::LightBlue;
                    cell->Tag = gcnew System::Drawing::Point(i, j);
					cell->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Battlfield::OnCellMouseClick);


                    panel->Controls->Add(cell); // add the cell on the panel
                }
            }
        }
		void CreateShip(int rows, int cols, Panel^ panel) {

		}

		void NextStage() {
			switch (currentStage) {
			case GameStage::Setup:
				currentStage = GameStage::Placement;
				StartPlacement();
				break;
			case GameStage::Placement:
				currentStage = GameStage::Battle;
				StartBattle();
				break;
			case GameStage::Battle:
				currentStage = GameStage::GameOver;
				EndGame();
				break;
			default:
				break;
			}
		}
		void StartPlacement() {

			// Код для размещения кораблей игроком
		}

		void StartBattle() {

		}

		void EndGame() {
			// Код завершения игры
		}
		//int check_coordinates_X(PictureBox^ obj) {
		//	int coordinates = 0;
		//	std::string what = obj->Tag->ToString();
		//	return coordinates;
		//}

		void Battlfield::OnCellMouseClick(Object^ sender, MouseEventArgs^ e){

			if (currentStage == GameStage::Setup) {
				InitializeGameStage();

			}
			else if (currentStage == GameStage::Placement) {

			}
			else if (currentStage == GameStage::Battle) {
				if (e->Button == System::Windows::Forms::MouseButtons::Left)
				{
					OnCellClick(sender, e); // Обробка лівого кліку
				}
				else if (e->Button == System::Windows::Forms::MouseButtons::Right)
				{
					MarkCell(sender, e); // Обробка правого кліку
				}
			}
			else if (currentStage == GameStage::GameOver) {

			}
		}
        // handler click by the cell
        void OnCellClick(System::Object^ sender, System::EventArgs^ e)
        {
            PictureBox^ clickedCell = safe_cast<PictureBox^>(sender);
			
			if (clickedCell->BackColor != System::Drawing::Color::DimGray) {
				
				clickedCell->Size = System::Drawing::Size(28, 28);
				if (clickedCell->Location.X % 30 == 0 && clickedCell->Location.Y % 30 == 0) {
					clickedCell->Location = System::Drawing::Point(System::Convert::ToInt32(clickedCell->Location.X) + 1, System::Convert::ToInt32(clickedCell->Location.Y) + 1);
				}
				else {
					clickedCell->Location = System::Drawing::Point(System::Convert::ToInt32(clickedCell->Location.X), System::Convert::ToInt32(clickedCell->Location.Y));
				}
				clickedCell->BackColor = System::Drawing::Color::DimGray; // change color of cell
			}
            // you need to create additional logic, a handler that checks whether the ship is hit or not.
        }
		void MarkCell(System::Object^ sender, System::EventArgs^ e) {
			PictureBox^ clickedCell = safe_cast<PictureBox^>(sender);
			clickedCell->Size = System::Drawing::Size(30, 30);
			clickedCell->Location = System::Drawing::Point(System::Convert::ToInt32(clickedCell->Location.X), System::Convert::ToInt32(clickedCell->Location.Y));


			std::array<int, 2> coords_Cell{ clickedCell->Location.X, clickedCell->Location.Y };
			System::Drawing::Point^ coord = safe_cast<System::Drawing::Point^>(clickedCell->Tag);

			if (clickedCell->BackColor == System::Drawing::Color::DimGray) {

			}
			else if (clickedCell->BackColor == System::Drawing::Color::DarkOrange) {
				clickedCell->BackColor = System::Drawing::Color::LightBlue; // change color of cell
				clickedCell->Size = System::Drawing::Size(30, 30);

			}
			else if (clickedCell->BackColor == System::Drawing::Color::LightBlue) {
				clickedCell->BackColor = System::Drawing::Color::DarkOrange; // change color of cell
			}

		}
#pragma endregion
};
}
