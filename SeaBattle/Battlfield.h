#pragma once
#include <array>
#include <ctime>
#include "Ship.h"
#include "battleship.h"
#include "Cruisers.h"
#include "Destroyers.h"
#include "Submarines.h"



//+-----------------------------+
//|all descriptions will be here|
//+-----------------------------+
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
	public ref class Battlfield : public System::Windows::Forms::Form{

	enum class GameStage {
			Setup,
			Placement,
			Battle,
			GameOver
		};
	public:
		Battlfield(void){

			init_SizeOfShips();
			init_countOfShips();
			init_colors();
			InitializeComponent();
			
			//
			//TODO: Add the constructor code here
			//
			CreateGrid(rows, cols, MainFieldUser1);
		}

	public:

	public:

	public:
	private:
		GameStage currentStage = GameStage::Setup;

		List < Ship ^ > ^ ships_array = gcnew List < Ship ^ > ();
		List < Ship^ >^ user_field_ships_array = gcnew List < Ship^ >();
		List<List<int>^>^ view_coordinates = gcnew List<List<int>^>;
		/*
		   1 ship - a row of 4 cells(“battleship” or “four - deck”)
		   2 ships - a row of 3 squares(“cruisers” or “three - deckers”)
		   3 ships - a row of 2 cells(“destroyers” or “two - deck”)
		   4 ships - 1 cell(“submarines” or “single deck”)*/
		Dictionary < String^, int> ^ sizeOfShips = gcnew Dictionary<String^, int> ();

		Dictionary < String^, int> ^ countOfShips = gcnew Dictionary<String^, int> ();

		Dictionary < String^, System::Drawing::Color>^ colors = gcnew Dictionary<String^, System::Drawing::Color>();


		/*BS = BattleShip*/
		String^ BS = "battleship";
		/*CR = CRuisers*/
		String^ CR = "cruisers";
		/*DS = DeStroyer*/
		String^ DS = "destroyers";
		/*SB = submarines*/
		String^ SB = "submarines";

		//+---size of field----+
		   const int rows = 10;
		   const int cols = 10;
		//+---size of field----+


		//+-----move cursor------+
		   bool dragging = false;
		   Point offset;
		//+----------------------+
		
		int simp_margin = 1;

		PictureBox^ buffer_Cell = nullptr;
		Ship^ choosen_ship = nullptr;


		void init_SizeOfShips() {
			sizeOfShips->Add(BS, 4);
			sizeOfShips->Add(CR, 3);
			sizeOfShips->Add(DS, 2);
			sizeOfShips->Add(SB, 1);
		}
		void init_countOfShips() {
			countOfShips->Add(BS, 1);
			countOfShips->Add(CR, 2);
			countOfShips->Add(DS, 3);
			countOfShips->Add(SB, 4);
		}
		void init_colors() {
			colors->Add(BS, System::Drawing::Color::DarkGray);
			colors->Add(CR, System::Drawing::Color::Crimson);
			colors->Add(DS, System::Drawing::Color::Bisque);
			colors->Add(SB, System::Drawing::Color::DarkViolet);
		}

	private: System::Windows::Forms::Panel^ panel1;
		   

	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
		InitializeGameStage();
	}
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

        System::Windows::Forms::Panel^ MainFieldUser1;
		System::Windows::Forms::Panel^ ShipsField;
		System::Windows::Forms::Panel^ panelGrid2;
		System::Windows::Forms::Panel^ unknown_ship_panel;

		//+-----------------------------------------+
		   System::Windows::Forms::Panel^ BS_P;
		   System::Windows::Forms::Panel^ CR_P;
		   System::Windows::Forms::Panel^ DS_P;
		   System::Windows::Forms::Panel^ SB_P;
		//+-----------------------------------------+
	private: System::Windows::Forms::Button^ button1;

		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
        void InitializeComponent(void)
        {
			this->MainFieldUser1 = (gcnew System::Windows::Forms::Panel());
			this->panelGrid2 = (gcnew System::Windows::Forms::Panel());
			this->ShipsField = (gcnew System::Windows::Forms::Panel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			int sizeFieldY = 300 + (simp_margin * 10), sizeFieldX = 300 + (simp_margin * 10);
			int corrections = simp_margin * 10;
			// 
			// MainFieldUser1
			// 
			this->MainFieldUser1->Location = System::Drawing::Point(12, 21);
			this->MainFieldUser1->Name = L"MainFieldUser1";
			this->MainFieldUser1->Size = System::Drawing::Size(sizeFieldX, sizeFieldY);
			this->MainFieldUser1->TabIndex = 0;
			// 
			// panelGrid2
			// 
			this->panelGrid2->Location = System::Drawing::Point(0, 0);
			this->panelGrid2->Name = L"panelGrid2";
			this->panelGrid2->Size = System::Drawing::Size(sizeFieldX, sizeFieldY);
			this->panelGrid2->TabIndex = 0;
			// 
			// ShipsField
			// 
			this->ShipsField->Location = System::Drawing::Point(0, 0);
			this->ShipsField->Name = L"ShipsField";
			this->ShipsField->Size = System::Drawing::Size(sizeFieldX, sizeFieldY);
			this->ShipsField->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(358 + corrections, 363 + corrections);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Ready";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Battlfield::button1_Click);
			// 
			// Battlfield
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->ClientSize = System::Drawing::Size(792 + corrections, 398 + corrections);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->MainFieldUser1);
			this->Name = L"Battlfield";
			this->Text = L"Battleship Game";
			this->ResumeLayout(false);

		}

#pragma region some initialization

		void InitializeGameStage()
		{
			if (currentStage == GameStage::Battle) {
				this->panelGrid2 = gcnew System::Windows::Forms::Panel();
				this->panelGrid2->Location = System::Drawing::Point(470, 21);
				this->panelGrid2->Name = L"panelGrid2";
				this->panelGrid2->Size = System::Drawing::Size(300, 300);
				this->panelGrid2->TabIndex = 1;

				// Add the panel to the form
				this->Controls->Add(this->panelGrid2);

				CreateGrid(10, 10, panelGrid2);
			}
		}
		void InitializeShips() 
		{
			if (currentStage == GameStage::Placement) {
				this->ShipsField = gcnew System::Windows::Forms::Panel();
				this->ShipsField->Location = System::Drawing::Point(470, 21);
				this->ShipsField->Name = L"Ship";
				this->ShipsField->Size = System::Drawing::Size(300, 300);
				this->ShipsField->TabIndex = 1;

				// Add the panel to the form
				this->Controls->Add(this->ShipsField);

				CreateGrid(10, 10, ShipsField);
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
                    cell->BorderStyle = System::Windows::Forms::BorderStyle::None;
					int x = j * (simp_margin + 30), y = i * (simp_margin + 30);
                    cell->Location = System::Drawing::Point(x, y);
                    cell->BackColor = System::Drawing::Color::LightBlue;
                    cell->Tag = gcnew System::Drawing::Point(i, j);
					cell->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Battlfield::OnCellMouseClick);
					if (panel == MainFieldUser1) {
						cell->MouseEnter += gcnew System::EventHandler(this, &Battlfield::MouseEnter_Cell);

					}

                    panel->Controls->Add(cell); // add the cell on the panel
                }
            }
        }
#pragma endregion

#pragma region create random ships

		#pragma region auxiliary functions


		void to_tidy_panel_void_ships_mark(Panel^ tidy_panel, List<Ship^>^ arrays_for_check) {
			if (arrays_for_check->Count == 0) {
				for each (Control ^ control in tidy_panel->Controls) {
					PictureBox^ pictureBox = dynamic_cast<PictureBox^>(control);
					pictureBox->BackColor = System::Drawing::Color::LightBlue;
				}
				return;
			}
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					Ship^ some_ship = initialize_ship_by_the_help_of_coords_by_cell(i, j, arrays_for_check);
					if ((some_ship != nullptr) ? some_ship->is_that_coord(i, j) == false : true) {

						for each(Control ^ control in tidy_panel->Controls) {
							PictureBox^ pictureBox = dynamic_cast<PictureBox^>(control);

							if (pictureBox != nullptr) {
								Point^ tagPoint = dynamic_cast<Point^>(pictureBox->Tag);
								if (tagPoint != nullptr && tagPoint->X == i && tagPoint->Y == j) {
									pictureBox->BackColor = System::Drawing::Color::LightBlue;
								}
							}
						}
					}
				}
			}
		}

		//+--------------------------------------------------------------------------+
		//|in this code that function using for initialize coordinates random ships. |
		//|and somehow ships randomize always in the same direction... idk why.		 |
		//|Maybe direction related with something									 |
		//+--------------------------------------------------------------------------+
		bool clear_coordinates(List<List<int>^>^ new_coords) {

			//first of all i'll check whether goes beyond the ship. By using the coordinates
			for (int i = 0; i < new_coords->Count; i++) {
				//X still always first.
				if (new_coords[i]->default[0] >= 10 || new_coords[i]->default[1] >= 10 || new_coords[i]->default[0] < 0 || new_coords[i]->default[1] < 0) {
					return false;
				}
			}
			// and the second it's general if
			if (ships_array->Count > 0) {

				for(int i=0; i<ships_array->Count; i++) { //need to run throgh by the ships array for getting the coords and... make condition
					List<List<int>^>^ where_are_ship = ships_array[i]->your_coords();

					for (int j = 0; j < where_are_ship->Count; j++) {// run through by resulting coordinates

						for (int k = 0; k < new_coords->Count; k++) { // that cycle are exists for don't leave of the limits of list

							if (new_coords[k]->default[0] == where_are_ship[j]->default[0] && new_coords[k]->default[1] == where_are_ship[j]->default[1]) {
								return false;
							}
						}
					}
				}

			}

			return true;
		}

		List<List<int>^>^ randomize_coordinates(int length) {
			srand(static_cast<unsigned int>(time(0)));
			List<List<int>^>^ rand_coords = nullptr;

			bool XY = (rand() % (2) == 1) ? true : false;/*"true" define ONLY value X, false means ONLY the Y define what will be changed. Means on the axis X or Y*/
			bool Y_Direction = (rand() % (2) == 1) ? true : false;/*"true" define direction will be changed only by the "top", false opposite that is to the "down"*/
			bool X_Direction = (rand() % (2) == 1) ? true : false;/*"true" define direction will be changed only by the "rigth", false opposite that is to the "left"*/
			bool okPosition = false; /*while rand_coords don't to follow the ruls! kurwa*/
			int X = rand() % (10);/*randomly determines coordinates on the begin the function*/
			int Y = rand() % (10);/*randomly determines coordinates on the begin the function*/

			while (okPosition == false) {
				
				List<List<int>^>^ buffer = gcnew List<List<int>^>();
				for (int i = 0; i < length; i++) {
					List<int>^ innerList = gcnew List<int>(); 
					buffer->Add(innerList);
					if (XY) {
						X += (X_Direction == true) ? 1 : -1;
					}
					else {
						Y += (Y_Direction == true) ? 1 : -1;
					}
					//for clarity
					/*buffer[i]->default[0] = X;
					buffer[i]->default[1] = Y;*/
					buffer[i]->Add(X);
					buffer[i]->Add(Y);

				}
				if (clear_coordinates(buffer)) {
					okPosition = true;
					rand_coords = buffer;
				}
				else {
					Y = rand() % (10);
					X = rand() % (10);
				}
				/*try {
					throw gcnew System::Exception("Some error occurred!");
				}
				catch (System::Exception^ e) {
					MessageBox::Show(e->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}*/
			}
			return rand_coords;

		} 

		void SetTag(PictureBox^ cell, int x, int y) { 
			Tuple<int, int>^ coordinates = Tuple::Create(x, y); 
			cell->Tag = coordinates; 
		}

		//+--------------------------------------------------------------+
		//|the name coincides with what the function does.				 |
		//|It recieve the Ship^ and operating him parameters.		     |
		//|And that function do important role.							 |
		//|It create events for need cels and connects them to each other|
		//+--------------------------------------------------------------+
		void Mark_the_ship(Ship^ some_ship, System::Windows::Forms::Panel^ some_panel) {
			//general moment where i use attribute from header of function for getting the coords.
			List<List<int>^>^ coords = some_ship->your_coords();
			List<PictureBox^>^ list_with_links_to_Cells = gcnew List<PictureBox^>();

			for (int i = 0; i < coords->Count; i++) {
				int x = coords[i]->default[0];
				int y = coords[i]->default[1];


				//cycle for find need cell by tag of declared the element. I have this element "ShipsField"
				for each (Control ^ control in some_panel->Controls) {
					PictureBox^ cell = dynamic_cast<PictureBox^>(control); 
					Point^ cellTag = safe_cast<Point^>(cell->Tag);

					if (cell != nullptr && cellTag->X == x && cellTag->Y == y) {
						list_with_links_to_Cells->Add(cell);
					}

				}
			}


			//to what color i want to draw the cell
			for each (PictureBox ^ cell in list_with_links_to_Cells) {
				if(some_ship->get_Name() == BS){
					cell->BackColor = colors[BS];
					cell->Name = some_ship->get_Name() + some_ship->get_number_of_ships().ToString();
					//cell->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Battlfield::panel_MouseDown);

					//////////cell->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Battlfield::panel_MouseUp);
					//////////cell->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Battlfield::panel_MouseMove);

					//cell->MouseHover += gcnew System
				}
				else if (some_ship->get_Name() == CR) {
					cell->BackColor = colors[CR];
					cell->Name = some_ship->get_Name() + some_ship->get_number_of_ships().ToString();
				}
				else if (some_ship->get_Name() == DS) {
					cell->BackColor = colors[DS];
					cell->Name = some_ship->get_Name() + some_ship->get_number_of_ships().ToString();
				}
				else if (some_ship->get_Name() == SB) {
					cell->BackColor = colors[SB];
					cell->Name = some_ship->get_Name() + some_ship->get_number_of_ships().ToString();
				}
			}
		}

		//+----------------------------------------------------+
		//| its like search the ship by transmitted coordinates|
		//+----------------------------------------------------+
		Ship^ initialize_ship_by_the_help_of_coords_by_cell(int x, int y, List<Ship^>^ some_array_ships){

			for (int i = 0; i < ships_array->Count; i++) {
				List<List<int>^>^ coords_ship = ships_array[i]->your_coords();
				//check coords
				for (int j = 0; j < coords_ship->Count; j++) {
					if (coords_ship[j]->default[0] == x && coords_ship[j]->default[1] == y) {
						return ships_array[i];
					}
				}
			}
			return nullptr;
		}
#pragma endregion/*auxiliary functions*/

#pragma region Pin ship to the cursor

		//void init_unknown_ship_panel(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e, Ship^ unknown_ship) {
		//	PictureBox^ clickedCell = safe_cast<PictureBox^>(sender);
		//	unknown_ship = initialize_ship_by_the_help_of_coords_by_cell(clickedCell->Location.X / 30, clickedCell->Location.Y / 30);

		//	if (clickedCell != nullptr &&
		//		currentStage == GameStage::Placement && 
		//		clickedCell->BackColor != System::Drawing::Color::LightBlue &&
		//		e->Button == System::Windows::Forms::MouseButtons::Left) {

		//		unknown_ship_panel = gcnew Panel();
		//		unknown_ship_panel->Size = System::Drawing::Size(80, 80);
		//		unknown_ship_panel->Location = System::Drawing::Point(e->X + 50, e->Y + 50);

		//		if (unknown_ship->get_Direction() == 'X') {
		//			this->unknown_ship_panel->Size = System::Drawing::Size(unknown_ship->get_Length() * 30, 30);
		//		}
		//		else if (unknown_ship->get_Direction() == 'Y') {
		//			this->unknown_ship_panel->Size = System::Drawing::Size(30, unknown_ship->get_Length() * 30);
		//		}
		//		else {
		//			this->unknown_ship_panel->Size = System::Drawing::Size(30, 30);
		//		}
		//		//unknown_ship_panel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Battlfield::panel_MouseMove);

		//		this->Controls->Add(unknown_ship_panel);
		//		unknown_ship_panel->BringToFront();
		//		this->Invalidate(); // Оновлює форму


		//		int rows = (unknown_ship->get_Direction() == 'X') ? unknown_ship->get_Length() : 1;
		//		int cols = (unknown_ship->get_Direction() == 'Y') ? unknown_ship->get_Length() : 1;

		//		Create_unknown_ship_panel(rows, cols, unknown_ship, unknown_ship_panel);
		//	}
		//	else{
		//		return;
		//	}
		//}
		
		//void Create_unknown_ship_panel(int rows, int cols, Ship^ unknown_ship, System::Windows::Forms::Panel^ USP) {
		//	String^ name = unknown_ship->get_Name();
		//	System::Drawing::Color color = (colors->ContainsKey(name)) ? colors[name] : System::Drawing::Color::BlanchedAlmond;
		//	//create
		//	for (int i = 0; i < rows; ++i) {
		//		for (int j = 0; j < cols; ++j) {
		//			PictureBox^ cell = gcnew PictureBox();
		//			cell->Size = System::Drawing::Size(30, 30);
		//			cell->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		//			cell->Location = System::Drawing::Point(j * 30, i * 30);
		//			cell->BackColor = color;
		//			cell->Tag = gcnew System::Drawing::Point(i, j);
		//			cell->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Battlfield::OnCellMouseClick);
		//			
		//			USP->Controls->Add(cell); // add the cell on the panel

		//		}
		//	}
		//	//US->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Battlfield::panel_MouseDown);
		//	//US->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Battlfield::panel_MouseUp);
		//	//US->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Battlfield::panel_MouseMove);

		//}



		//bool pin_choose_ship(int x, int y, Ship^ some_ship, Object^ sender, MouseEventArgs^ e) {

		//	for (int i = 0; i < ships_array->Count; i++) {
		//		if (ships_array[i]->is_that_coord(x, y)) { // by coordinates

		//			if (ships_array[i]->get_Name() == BS) {
		//				init_unknown_ship_panel(sender, e, some_ship);
		//			}
		//			else if (ships_array[i]->get_Name() == CR) {

		//			}
		//			else if (ships_array[i]->get_Name() == DS){

		//			}
		//			else if (ships_array[i]->get_Name() == SB) {

		//			}


		//		}
		//	}
		//	return true;
		//}

#pragma endregion /*Pin ship to the cursor*/


		void CreateTemplateShips() {
			for each (KeyValuePair<String^, int> kvp in countOfShips) {
				
				String^ key = kvp.Key;
				int value = kvp.Value;

				for (int i = 0; i < value; i++) {
					List<List<int>^>^ buf = randomize_coordinates(sizeOfShips[key]);

					if (key == BS) {

						Ship^ ship = gcnew Battleship(buf, sizeOfShips[BS], BS);
						ships_array->Add(ship);
						Mark_the_ship(ship, ShipsField);
					}
					else if (key == CR) {

						Ship^ ship = gcnew Cruisers(buf, sizeOfShips[CR], CR);
						ships_array->Add(ship);
						Mark_the_ship(ship, ShipsField);
					}
					else if (key == DS) {
						Ship^ ship = gcnew Destroyers(buf, sizeOfShips[DS], DS);
						ships_array->Add(ship);
						Mark_the_ship(ship, ShipsField);
					}
					else if (key == SB) {
						Ship^ ship = gcnew Submarines(buf, sizeOfShips[SB], SB);
						ships_array->Add(ship);
						Mark_the_ship(ship, ShipsField);
					}
				}
				// Do something with key and value

			}
		}

#pragma endregion /*create random ships*/

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
			InitializeShips();
			CreateTemplateShips();
			// Код для размещения кораблей игроком
		}

		void StartBattle() {

		}

		void EndGame() {
			// Код завершения игры
		}

#pragma region events
		void paint_choosen_ship_while(System::Object^ sender, System::EventArgs^ e) {
			List<List<int>^>^ view_coordinates_temp = gcnew List<List<int>^>;
			PictureBox^ enterCell = dynamic_cast<PictureBox^>(sender);
			Point^ CellTag = dynamic_cast<Point^>(enterCell->Tag);

			int x = (choosen_ship->get_Direction() == 'X') ? choosen_ship->get_Length() : 1;
			int y = (choosen_ship->get_Direction() == 'Y') ? choosen_ship->get_Length() : 1;
			List<List<int>^>^ choosen_ship_coords = choosen_ship->your_coords();

			bool addDirX = (choosen_ship_coords[0]->default[0] == choosen_ship_coords[choosen_ship->get_Length() - 1]->default[0]) ? false : true;
			bool addDirY = (choosen_ship_coords[0]->default[1] == choosen_ship_coords[choosen_ship->get_Length() - 1]->default[1]) ? false : true;

			int i = 0, j = 0;
			while(i < x && i >= 0){
				i++;
				while(j < y && j >= 0) {
					j++;
					List<int>^ XY = gcnew List<int>;
					int X_coord = (addDirX) ? CellTag->X + i : CellTag->X;
					int Y_coord = (addDirY) ? CellTag->Y + j : CellTag->Y;
					XY->Add(X_coord);
					XY->Add(Y_coord);

					view_coordinates_temp->Add(XY);
				}
				j = 0;
			}

			for each (List<int> ^ XY in view_coordinates_temp) {
				for each (Control ^ control in MainFieldUser1->Controls) {
					PictureBox^ cell = dynamic_cast<PictureBox^>(control);
					Point^ tempCellTag = dynamic_cast<Point^>(cell->Tag);

					if (tempCellTag != nullptr &&
						tempCellTag->X == XY->default[0] &&
						tempCellTag->Y == XY->default[1]
						) {
						cell->BackColor = System::Drawing::Color(colors[choosen_ship->get_Name()]);
					}
				}
			}
			view_coordinates = view_coordinates_temp;
		}
		void MouseEnter_Cell(System::Object^ sender, System::EventArgs^ e) {
			if (dragging) {
				to_tidy_panel_void_ships_mark(MainFieldUser1, user_field_ships_array);

				paint_choosen_ship_while(sender, e);
			}
		}
		//+------------------------------------------EVENTS----------------------------------------------+
		//System::Void Battlfield::panel_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {

		//}
		//System::Void Battlfield::panel_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {

		//}
		//+------------------------------------------EVENTS----------------------------------------------+

		//void InitiatorPanel_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		//	if (e->Button == System::Windows::Forms::MouseButtons::Left) {
		//		unknown_ship_panel = gcnew Panel();
		//		unknown_ship_panel->Size = System::Drawing::Size(80, 80);
		//		unknown_ship_panel->BackColor = System::Drawing::Color::;
		//		unknown_ship_panel->Location = System::Drawing::Point(e->X + 50, e->Y + 50);
		//init
		/*
		if (unknown_ship->get_Direction() == 'X') {
			this->unknown_ship_panel->Size = System::Drawing::Size(unknown_ship->get_Length() * 30, 30);
		}
		else if (unknown_ship->get_Direction() == 'Y') {
			this->unknown_ship_panel->Size = System::Drawing::Size(30, unknown_ship->get_Length() * 30);
		}
		else {
			this->unknown_ship_panel->Size = System::Drawing::Size(30, 30);
		}
		
		int rows = (unknown_ship->get_Direction() == 'X') ? unknown_ship->get_Length() : 1;
		int cols = (unknown_ship->get_Direction() == 'Y') ? unknown_ship->get_Length() : 1;*/

		

		//		this->Controls->Add(unknown_ship_panel);

		//		unknown_ship_panel->BringToFront();
		//		unknown_ship_panel->Parent = this;
		//		dragging = true;

		//		offset = Point(e->X, e->Y);
		//	}
		//}

		//void panel_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		//	if (dragging && unknown_ship_panel != nullptr) {
		//		// Переміщуємо новостворений елемент разом із мишею
		//		unknown_ship_panel->Left = e->X - offset.X;
		//		unknown_ship_panel->Top = e->Y - offset.Y;
		//	}
		//}
		
		//void panel_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		//	PictureBox^ clickedCell = safe_cast<PictureBox^>(sender);
		//	Ship^ some_ship = initialize_ship_by_the_help_of_coords_by_cell((clickedCell->Location.X / 30), (clickedCell->Location.Y / 30));

		//	pin_choose_ship((clickedCell->Location.X / 30), (clickedCell->Location.Y / 30), some_ship, sender, e);

		//	dragging = true;



		//}

		//void panel_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		//	if (e->Button == System::Windows::Forms::MouseButtons::Left) {
		//		// Завершуємо перетягування
		//		dragging = false;
		//		unknown_ship_panel->Refresh();
		//		delete unknown_ship_panel;
		//	}
		//}
		void Battlfield::OnCellMouseClick(Object^ sender, MouseEventArgs^ e){

			if (currentStage == GameStage::Setup) {

			}
			else if (currentStage == GameStage::Placement) {
				PictureBox^ clickedCell = safe_cast<PictureBox^>(sender);

				if (clickedCell != nullptr) { 
					Panel^ parentPanel = dynamic_cast<Panel^>(clickedCell->Parent); 
					// Checking, to which the button was pressed
					if (parentPanel == MainFieldUser1) { 
						if (dragging) {
							Point^ cellTag = safe_cast<Point^>(buffer_Cell->Tag);
							Ship^ some_ship = initialize_ship_by_the_help_of_coords_by_cell(cellTag->X, cellTag->Y, ships_array);
							some_ship->change_coordinates(view_coordinates);

							Mark_the_ship(some_ship, MainFieldUser1);
							user_field_ships_array->Add(some_ship);
							dragging = false;
						}
					} 
					else if (parentPanel == ShipsField) { 
						Point^ cellTag = safe_cast<Point^>(clickedCell->Tag);
						Ship^ some_ship = initialize_ship_by_the_help_of_coords_by_cell(cellTag->X, cellTag->Y, ships_array);

						if (dragging == false) {
							buffer_Cell = clickedCell;
							dragging = true;
						}
						else {
							dragging = false;
						}
						if (some_ship != nullptr) {
							choosen_ship = some_ship;
							for each (Control ^ control in MainFieldUser1->Controls) {
								PictureBox^ cell = dynamic_cast<PictureBox^>(control);
								//cell->BackColor = System::Drawing::Color::Blue;
								cell->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
							}
						}
					} 
				}
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
        // +----------------------------------------------------+
		// | handler click by the cell.						    |
		// | It has to working only in Battle mode and only when|
		// | ClickedCell->BackColor != Color::DimGray		    |
		// +----------------------------------------------------+
        void OnCellClick(System::Object^ sender, System::EventArgs^ e){
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

		bool All_Ships_Have_Been_Arranged() {
			return true;
		}
#pragma endregion
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	if (Battlfield::All_Ships_Have_Been_Arranged()) {
		Battlfield::NextStage();
	}
}
};


}
