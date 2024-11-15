#pragma once
#include <array>
#include <ctime>
#include <memory>
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
			init_black_colors();

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

		List < Ship ^ > ^ template_ships_array = gcnew List < Ship ^ > ();

		List < Ship^ >^ user_field_ships_array = gcnew List < Ship ^ >();

		List < List < int > ^ > ^ view_coordinates = gcnew List < List < int > ^ >();

		List < List < int > ^ > ^ buffer_coords = gcnew List < List < int > ^ >(); // delete it when it doesn't needed

		List < Tuple < int, int > ^ > ^ required_coordinates = gcnew List<Tuple < int, int >^ >();

		//+-------------------------------------------------------------+
		//|1 ship - a row of 4 cells(“battleship” or “four - deck”)     |
		//|2 ships - a row of 3 squares(“cruisers” or “three - deckers”)|
		//|3 ships - a row of 2 cells(“destroyers” or “two - deck”)		|
		//|4 ships - 1 cell(“submarines” or “single deck”)				|
		//+-------------------------------------------------------------+
		Dictionary < String^, int> ^ sizeOfShips = gcnew Dictionary<String^, int> ();

		Dictionary < String^, int> ^ countOfShips = gcnew Dictionary<String^, int> ();

		Dictionary < String^, System::Drawing::Color>^ colors = gcnew Dictionary<String^, System::Drawing::Color>();

		Dictionary < String^, System::Drawing::Color>^ black_colors = gcnew Dictionary<String^, System::Drawing::Color>();


		//+-----------------+
		//|BS = BattleShip	|
		//|CR = CRuisers	|
		//|DS = DeStroyer	|
		//|SB = SuBmarines	|
		//+-----------------+
		String^ BS = "battleship";
		String^ CR = "cruisers";
		String^ DS = "destroyers";
		String^ SB = "submarines";

		//+---size of field----+
		   const int rows = 10;
		   const int cols = 10;
		//+---size of field----+


		//+-----move cursor------+
		   bool dragging = false;
		//+----------------------+
		
		//+-----------------------------------Field datas--------------------------------+
		int simp_margin = 1;
		int sizeFieldY = 300 + (simp_margin * 10), sizeFieldX = 300 + (simp_margin * 10);
		int corrections = simp_margin * 10;
		//+------------------------------------------------------------------------------+

		//+-----------temp data-----------+
		PictureBox^ buffer_Cell = nullptr;
		Ship^ choosen_ship = nullptr;
		//+-------------------------------+

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
		void init_black_colors() {
			black_colors->Add(BS, System::Drawing::Color::DimGray);       
			black_colors->Add(CR, System::Drawing::Color::DarkRed);       
			black_colors->Add(DS, System::Drawing::Color::SaddleBrown);   
			black_colors->Add(SB, System::Drawing::Color::Indigo);        
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
		//+------------------------TemplateShipsField--------------------------------+
		//|that panel "TemplateShipsField" for placement the ships in tempalte field.|
		//|it's layout for placement . There is sample how it looks.				 |
		//+--------------------------------------------------------------------------+
		System::Windows::Forms::Panel^ TemplateShipsField;
		System::Windows::Forms::Panel^ panelGrid2;
		//System::Windows::Forms::Panel^ unknown_ship_panel;

		//+-----------------------------------------+

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
			this->TemplateShipsField = (gcnew System::Windows::Forms::Panel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
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
			// TemplateShipsField
			// 
			this->TemplateShipsField->Location = System::Drawing::Point(0, 0);
			this->TemplateShipsField->Name = L"ShipsField";
			this->TemplateShipsField->Size = System::Drawing::Size(sizeFieldX, sizeFieldY);
			this->TemplateShipsField->TabIndex = 0;
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
				this->TemplateShipsField = gcnew System::Windows::Forms::Panel();
				this->TemplateShipsField->Location = System::Drawing::Point(470, 21);
				this->TemplateShipsField->Name = L"Ship";
				this->TemplateShipsField->Size = System::Drawing::Size(sizeFieldX, sizeFieldY);
				this->TemplateShipsField->TabIndex = 1;

				// Add the panel to the form
				this->Controls->Add(this->TemplateShipsField);

				CreateGrid(10, 10, TemplateShipsField);
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


#pragma region Fucntions for tidy(pieces of functiong "to_tidy_panel_void_ships_mark")

		bool already_exist_required_point_tuple(List<Tuple<int, int>^>^ array_for_check, int x, int y) {
			for each (Tuple<int, int>^ array_OneDim in array_for_check) {
				if (array_OneDim->Item1 == x && array_OneDim->Item2 == y) {
					return true;
				}
			}
			return false;
		}

		void to_clear_required_coords() {
			required_coordinates->Clear();
		}

		bool here_has_ships(int x, int y, Panel^ tidy_panel, List<Ship^>^ array_for_check, List<Tuple<int, int>^>^ required_coords_temp) {
			for each (Control ^ control in tidy_panel->Controls)
			{
				PictureBox^ pictureBox = dynamic_cast<PictureBox^>(control);

				if (pictureBox != nullptr) {
					Point^ tag = dynamic_cast<Point^>(pictureBox->Tag);
					for each (Ship ^ some_ship_from_array_for_check in array_for_check)
					{
						/*simentic error one and the same coordinate triggered that condition*/ // need to create list of exceptions' coordinates
						//something wrong with that condition. Just read and check in debag
						if (some_ship_from_array_for_check->is_that_your_coord(x, y) 
							&& !already_exist_required_point_tuple(required_coords_temp, tag->X, tag->Y) 
							&& ((tag->X != 0 || tag->Y != 0) || required_coords_temp->Count > 0)) {
							return true;// i add occupied coordinates.
							//if in array has at least just one ship with that coords
						}
					}

				}
			}
			return false; //coordinates is free.
			//if coords are ready for use
		}

		void to_tidy_panel_void_ships_mark(Panel^ tidy_panel, List<Ship^>^ array_for_check) {
			if (array_for_check->Count == 0) {
				for each (Control ^ control in tidy_panel->Controls)
				{
					PictureBox^ pictureBox = dynamic_cast<PictureBox^>(control);
					pictureBox->BackColor = System::Drawing::Color::LightBlue;
				}
				return;
			}

			//searching
			List<Tuple<int, int>^>^ required_coordinates_temp = gcnew List<Tuple<int, int>^>();
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					if (here_has_ships(i, j, tidy_panel, array_for_check, required_coordinates_temp)) {
						required_coordinates_temp->Add(Tuple::Create(i, j));
					}
				}
			}

			for (int i = 0; i < required_coordinates_temp->Count; i++) {
				required_coordinates->Add(required_coordinates_temp[i]);
			}
			//painting
			for each (Control ^ control in tidy_panel->Controls) {
				PictureBox^ pictureBox = dynamic_cast<PictureBox^>(control);

				if (pictureBox != nullptr) {
					Point^ tag = dynamic_cast<Point^>(pictureBox->Tag);
					bool ticket = true;
					for each (Tuple<int, int> ^ required_coords_tuple in required_coordinates) {
						if (tag->X == required_coords_tuple->Item1
							&& tag->Y == required_coords_tuple->Item2) {
							ticket = false;
							break;
						}
					}
					if (ticket) {
						pictureBox->BackColor = System::Drawing::Color::LightBlue;
					}
				}
			}
		}
#pragma endregion /*Fucntions for tidy(pieces of functiong "to_tidy_panel_void_ships_mark")*/

#pragma region auxiliary functions


		bool already_exists_in_field(Ship^ some_ship, List<Ship^>^ array_of_ships) {
			if (!some_ship) {
				return false;
			}
			for each (Ship ^ ship_from_array in array_of_ships) {
				if (some_ship == ship_from_array) {
					return true;
				}
			}
			return false;
		}


		//+--------------------------------------------------------------------------+
		//|in this code that function using for initialize coordinates random ships. |
		//|and somehow ships randomize always in the same direction... idk why.		 |
		//|Maybe direction related with something									 |
		//+--------------------------------------------------------------------------+
		bool clear_coordinates(List<List<int>^>^ new_coords, List<Ship^>^ array_of_ships_for_check_out) {

			//first of all i'll check whether goes beyond the ship. By using the coordinates
			for (int i = 0; i < new_coords->Count; i++) {
				//X still always first.
				if ((new_coords[i]->default[0] > 9 || new_coords[i]->default[0] < 0) || (new_coords[i]->default[1] < 0 || new_coords[i]->default[1] > 9)) {
					return false;
				}
			}
			// and the second it's general if
			if (array_of_ships_for_check_out->Count > 0) {

				for(int i=0; i< array_of_ships_for_check_out->Count; i++) { //need to run through by the ships array for getting the coords and... Check the condition
					List<List<int>^>^ where_are_ship = array_of_ships_for_check_out[i]->your_coords();

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

					buffer[i]->Add(X);
					buffer[i]->Add(Y);

				}
				if (clear_coordinates(buffer, template_ships_array)) {
					try {
						for each (List<int> ^ one_dim_arr in buffer) {
							if (one_dim_arr[0] > 9) {
								throw System::Convert::ToString("X in buffer for the ships more than need it");
							}
							else if (one_dim_arr[0] < 0) {
								throw System::Convert::ToString("X in buffer for ships less than need it");
							}

							if (one_dim_arr[1] > 9) {
								throw System::Convert::ToString("Y in buffer for the ships more than need it");
							}
							else if (one_dim_arr[1] < 0) {
								throw System::Convert::ToString("Y in buffer for ships less than need it");
							}
						}
					}
					catch (String^ errmsg) {
						MessageBox::Show(errmsg);
						return nullptr;
					}
					okPosition = true;
					rand_coords = buffer;
				}
				else {
					Y = rand() % (10);
					X = rand() % (10);
				}
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


				//cycle for find need cell by tag of declared the element. I have this element "some_panel"
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
				if (!dragging && !choosen_ship) {
					if (some_ship->get_Name() == BS) {
						cell->BackColor = colors[BS];
						cell->Name = some_ship->get_Name() + some_ship->get_number_of_ships().ToString();
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
				else if (dragging) {
					if (some_ship->get_Name() == BS) {
						cell->BackColor = black_colors[BS];
						cell->Name = some_ship->get_Name() + some_ship->get_number_of_ships().ToString();
					}
					else if (some_ship->get_Name() == CR) {
						cell->BackColor = black_colors[CR];
						cell->Name = some_ship->get_Name() + some_ship->get_number_of_ships().ToString();
					}
					else if (some_ship->get_Name() == DS) {
						cell->BackColor = black_colors[DS];
						cell->Name = some_ship->get_Name() + some_ship->get_number_of_ships().ToString();
					}
					else if (some_ship->get_Name() == SB) {
						cell->BackColor = black_colors[SB];
						cell->Name = some_ship->get_Name() + some_ship->get_number_of_ships().ToString();
					}
				}
				else if (!dragging && choosen_ship) {
					if (some_ship->get_Name() == BS) {
						cell->BackColor = black_colors[BS];
						cell->Name = some_ship->get_Name() + some_ship->get_number_of_ships().ToString();
					}
					else if (some_ship->get_Name() == CR) {
						cell->BackColor = black_colors[CR];
						cell->Name = some_ship->get_Name() + some_ship->get_number_of_ships().ToString();
					}
					else if (some_ship->get_Name() == DS) {
						cell->BackColor = black_colors[DS];
						cell->Name = some_ship->get_Name() + some_ship->get_number_of_ships().ToString();
					}
					else if (some_ship->get_Name() == SB) {
						cell->BackColor = black_colors[SB];
						cell->Name = some_ship->get_Name() + some_ship->get_number_of_ships().ToString();
					}
				}
			}
		}

		//+----------------------------------------------------+
		//| its like search the ship by transmitted coordinates|
		//+----------------------------------------------------+
		Ship^ initialize_ship_by_the_help_of_coords_by_cell(int x, int y, List<Ship^>^ some_array_ships){

			for (int i = 0; i < some_array_ships->Count; i++) {
				List<List<int>^>^ coords_ship = some_array_ships[i]->your_coords();
				//check coords
				for (int j = 0; j < coords_ship->Count; j++) {
					if (coords_ship[j]->default[0] == x && coords_ship[j]->default[1] == y) {
						return some_array_ships[i];
					}
				}
			}
			return nullptr;
		}
#pragma endregion/*auxiliary functions*/

#pragma region Pin ship to the cursor


#pragma endregion /*Pin ship to the cursor*/


		void CreateTemplateShips() {
			for each (KeyValuePair<String^, int> kvp in countOfShips) {
				
				String^ key = kvp.Key;
				int value = kvp.Value;

				for (int i = 0; i < value; i++) {
					List<List<int>^>^ buf = randomize_coordinates(sizeOfShips[key]);

					if (key == BS) {

						Ship^ ship = gcnew Battleship(buf, sizeOfShips[BS], BS);
						template_ships_array->Add(ship);
						Mark_the_ship(ship, TemplateShipsField);
					}
					else if (key == CR) {

						Ship^ ship = gcnew Cruisers(buf, sizeOfShips[CR], CR);
						template_ships_array->Add(ship);
						Mark_the_ship(ship, TemplateShipsField);
					}
					else if (key == DS) {
						Ship^ ship = gcnew Destroyers(buf, sizeOfShips[DS], DS);
						template_ships_array->Add(ship);
						Mark_the_ship(ship, TemplateShipsField);
					}
					else if (key == SB) {
						Ship^ ship = gcnew Submarines(buf, sizeOfShips[SB], SB);
						template_ships_array->Add(ship);
						Mark_the_ship(ship, TemplateShipsField);
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

#pragma region general functions for reflection of something
		//+-----------------------------------------------------------------+
		//|using the "choosen_ship" for return it back on to its first place|
		//+-----------------------------------------------------------------+
		void return_choosen_ship_back(Panel^ in_which_panel_it_will_be_returned, List<Ship^>^ array_that_uses_that_field) {

			choosen_ship->change_coordinates(buffer_coords);

			array_that_uses_that_field->Add(choosen_ship);

			Mark_the_ship(choosen_ship, in_which_panel_it_will_be_returned);
			to_tidy_panel_void_ships_mark(MainFieldUser1, user_field_ships_array);

			choosen_ship = nullptr;
		}


		//+---------------------------------------------------------------+
		//|checking the axis X and Y if coords more ot less than need it  |
		//+---------------------------------------------------------------+
		Dictionary<String^, bool>^ coords_already_ready(List<List<int>^>^ list_of_coordinates) {
			bool X_less_than_correct{};
			bool X_more_than_correct{};

			bool Y_less_than_correct{};
			bool Y_more_than_correct{};

			Dictionary<String^, bool>^ answers = gcnew Dictionary<String^, bool>();

			for (int i = 0; i < list_of_coordinates->Count; i++) {
				
				if (list_of_coordinates[i]->default[0] < 0 || list_of_coordinates[i]->default[0] > 9) {
					//less than need it in axis X
				
					if (list_of_coordinates[i]->default[0] < 0) {
						X_less_than_correct= true;
					}
					else if (list_of_coordinates[i]->default[0] > 9) {
						//more than need it in axis X
						X_more_than_correct = true;
					}
					else {
						X_less_than_correct = false;
						X_more_than_correct = false;
					}
				}

				if (list_of_coordinates[i]->default[1] < 0 || list_of_coordinates[i]->default[1] > 9) {
					//less than need it in axis Y

					if (list_of_coordinates[i]->default[1] < 0) {
						Y_less_than_correct = true;
					}
					else if (list_of_coordinates[i]->default[1] > 9) {
						Y_more_than_correct = true;
					}
					else {
						Y_less_than_correct = false;
						Y_more_than_correct = false;
					}
				}

				if (Y_more_than_correct && Y_less_than_correct && X_less_than_correct && X_more_than_correct) {
					break;
				}

			}
			
			answers["LessX"] = X_less_than_correct;
			answers["MoreX"] = X_more_than_correct;

			answers["LessY"] = Y_less_than_correct;
			answers["MoreY"] = Y_more_than_correct;

			return answers;
		}

		void corrections_of_coordinates_for_showed(List<List<int>^>^& list_of_coordinates) {

			Dictionary<String^, bool>^ info_About_Correctness_Coordinates = coords_already_ready(list_of_coordinates);

			while ((info_About_Correctness_Coordinates["MoreX"] == true || info_About_Correctness_Coordinates["LessX"] == true)
				|| (info_About_Correctness_Coordinates["MoreY"] == true || info_About_Correctness_Coordinates["LessY"] == true)) {
				/*add X or add Y*/
				
				if (info_About_Correctness_Coordinates["MoreX"] == true) {
					for (int i = 0; i < list_of_coordinates->Count; i++) {
						list_of_coordinates[i]->default[0]-=1;
					}
				}
				else if (info_About_Correctness_Coordinates["LessX"] == true) {
					for (int i = 0; i < list_of_coordinates->Count; i++) {
						list_of_coordinates[i]->default[0] += 1;
					}
				}

				if (info_About_Correctness_Coordinates["MoreY"] == true) {
					for (int i = 0; i < list_of_coordinates->Count; i++) {
						list_of_coordinates[i]->default[1] -= 1;
					}
				}
				else if (info_About_Correctness_Coordinates["LessY"] == true) {
					for (int i = 0; i < list_of_coordinates->Count; i++) {
						list_of_coordinates[i]->default[1] += 1;
					}
				}
				info_About_Correctness_Coordinates = coords_already_ready(list_of_coordinates);
			}			
		}

		//+----------------------------------------------------------------------+
		//|painting the changed coords so called "view_coords - global variable".|
		//|Coords changs when cursor to entered in some cell.					 |
		//+----------------------------------------------------------------------+
		void paint_choosen_ship_while(System::Object^ sender, System::EventArgs^ e) {
			try { (!choosen_ship) ? System::Convert::ToString("choosen_ship in function \"paint_choosen_ship_while\" is equal to nullptr") : "nothing"; }
			catch (String^ errmsg) { return; }

			List<List<int>^>^ view_coordinates_temp = gcnew List<List<int>^>;
			PictureBox^ enterCell = dynamic_cast<PictureBox^>(sender);
			Point^ CellTag = dynamic_cast<Point^>(enterCell->Tag);

			int x = (choosen_ship->get_Direction() == 'X') ? choosen_ship->get_Length() : 1;
			int y = (choosen_ship->get_Direction() == 'Y') ? choosen_ship->get_Length() : 1;
			List<List<int>^>^ choosen_ship_coords = choosen_ship->your_coords();

			bool addDirX = (choosen_ship_coords[0]->default[0] == choosen_ship_coords[choosen_ship->get_Length() - 1]->default[0]) ? false : true;
			bool addDirY = (choosen_ship_coords[0]->default[1] == choosen_ship_coords[choosen_ship->get_Length() - 1]->default[1]) ? false : true;

			for (int i = 0; i < x; i++) {
				for(int j = 0; j < y; j++) {
					List<int>^ XY = gcnew List<int>;
					int X_coord = (addDirX) ? CellTag->X + i : CellTag->X;
					int Y_coord = (addDirY) ? CellTag->Y + j : CellTag->Y;
					XY->Add(X_coord);
					XY->Add(Y_coord);

					view_coordinates_temp->Add(XY);
				}
			}

			corrections_of_coordinates_for_showed(view_coordinates_temp);

			for each (List<int> ^ one_dim_arr in view_coordinates_temp) {

				for each (Ship ^ some_ship in user_field_ships_array) {

					if (some_ship->is_that_your_coord(one_dim_arr[0], one_dim_arr[1])) {
						return;
					}
				}
			}

			for each (List<int> ^ XY in view_coordinates_temp) {
				for each (Control ^ control in MainFieldUser1->Controls) {
					PictureBox^ cell = dynamic_cast<PictureBox^>(control);
					Point^ tempCellTag = dynamic_cast<Point^>(cell->Tag);

					if (tempCellTag &&
						tempCellTag->X == XY->default[0] &&
						tempCellTag->Y == XY->default[1]
						) {
						cell->BackColor = System::Drawing::Color(colors[choosen_ship->get_Name()]);
					}
				}
			}
			view_coordinates = view_coordinates_temp;
		}

#pragma endregion general functions for reflection of something

		void MouseEnter_Cell(System::Object^ sender, System::EventArgs^ e) {
			if (dragging) {
				to_tidy_panel_void_ships_mark(MainFieldUser1, user_field_ships_array);

				paint_choosen_ship_while(sender, e);
			}
			else if (!dragging && choosen_ship) {
				to_tidy_panel_void_ships_mark(MainFieldUser1, user_field_ships_array);

				paint_choosen_ship_while(sender, e);
			}
		}
		void Battlfield::OnCellMouseClick(Object^ sender, MouseEventArgs^ e){

			if (currentStage == GameStage::Setup) {

			}
			else if (currentStage == GameStage::Placement) {
				PictureBox^ clickedCell = safe_cast<PictureBox^>(sender);

				if (clickedCell != nullptr) { 

					Panel^ parentPanel = dynamic_cast<Panel^>(clickedCell->Parent); 
					
					// Checking, to which of the buttons were pressed
					if (parentPanel == MainFieldUser1) { 
					
						if (dragging) {
							Point^ clickedCellTag = safe_cast<Point^>(clickedCell->Tag);

							Point^ cellTag = safe_cast<Point^>(buffer_Cell->Tag);
							Ship^ some_ship = initialize_ship_by_the_help_of_coords_by_cell(cellTag->X, cellTag->Y, template_ships_array);

							if (clear_coordinates(view_coordinates, user_field_ships_array) == false) {
								MessageBox::Show("the ship not on the right coordinates.");
								return;
							}

							some_ship->change_coordinates(view_coordinates);
							view_coordinates = nullptr;

							Mark_the_ship(some_ship, MainFieldUser1);
							
							user_field_ships_array->Add(some_ship);
						
							dragging = false;
							choosen_ship = nullptr;
						}
						else if (!dragging) {
							Point^ clickedCellTag = safe_cast<Point^>(clickedCell->Tag);
							Ship^ some_ship = initialize_ship_by_the_help_of_coords_by_cell(clickedCellTag->X, clickedCellTag->Y, user_field_ships_array);
							try {
								if (!some_ship && !choosen_ship) {
									throw System::Convert::ToString("Our ships for some reason: nullptr's");
								}
							}
							catch (String^ errmsg) {
								MessageBox::Show(errmsg);
								to_tidy_panel_void_ships_mark(MainFieldUser1, user_field_ships_array);
								return;
							}
							//comparisons such as "some_ship == nullptr" call the exception. So... !some_ship
							if (some_ship && !choosen_ship) {
								choosen_ship = some_ship;

								to_clear_required_coords();

								buffer_coords = some_ship->your_coords();

								for (int i = 0; i < user_field_ships_array->Count; i++) {
									if (user_field_ships_array[i]->get_identifier() == some_ship->get_identifier()) {
										user_field_ships_array->RemoveAt(i);
									}
								}
							}
							else if (choosen_ship && some_ship) {
								return_choosen_ship_back(MainFieldUser1, user_field_ships_array);
							}
							else if (clear_coordinates(choosen_ship->your_coords(), user_field_ships_array) && !some_ship && choosen_ship )
							{
								choosen_ship->change_coordinates(view_coordinates);
								view_coordinates = nullptr;

								user_field_ships_array->Add(choosen_ship);

								Mark_the_ship(choosen_ship, MainFieldUser1);
								choosen_ship = nullptr;
							}
						}
					} 
					else if (parentPanel == TemplateShipsField) { 
						if (!choosen_ship) {
							Point^ cellTag = safe_cast<Point^>(clickedCell->Tag);
							Ship^ some_ship = initialize_ship_by_the_help_of_coords_by_cell(cellTag->X, cellTag->Y, template_ships_array);

							try {
								if (already_exists_in_field(some_ship, user_field_ships_array) == false
									&& some_ship != nullptr) {

									if (dragging == false) {
										buffer_Cell = clickedCell;
										dragging = true;
									}
									else {
										dragging = false;
									}

									if (some_ship != nullptr) {
										choosen_ship = some_ship;
										Mark_the_ship(some_ship, TemplateShipsField);

										for each (Control ^ control in MainFieldUser1->Controls) {
											PictureBox^ cell = dynamic_cast<PictureBox^>(control);
											cell->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
										}
									}
								}
								else {
									throw System::Convert::ToString("that's ship already exists in user field \nERROR: " + ((!some_ship) ? "nullptr" : some_ship->get_identifier())->ToString());
								}
							}
							catch (String^ errmsg) {
								MessageBox::Show(errmsg);
							}
						}
						else if (choosen_ship && !dragging) { // if i moved that ship
							return_choosen_ship_back(MainFieldUser1, user_field_ships_array);
							to_tidy_panel_void_ships_mark(MainFieldUser1, user_field_ships_array);//and clearing a traces
						}
						else if (choosen_ship && dragging) { // if the a ship wasn't placed in "MainFieldUser1"
							choosen_ship = nullptr;
							to_tidy_panel_void_ships_mark(MainFieldUser1, user_field_ships_array);
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
