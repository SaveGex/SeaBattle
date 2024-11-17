#pragma once
#include <array>
#include <ctime>
#include <memory>
#include "Ship.h"
#include "battleship.h"
#include "Cruisers.h"
#include "Destroyers.h"
#include "Submarines.h"
#include "CustomMessageBox.h"


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
			srand(static_cast<unsigned int>(time(0)));
			init_SizeOfShips();
			init_countOfShips();
			init_colors();
			init_black_colors();
			init_hit_colors();

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

		List < Ship^ >^ first_ships_array = gcnew List < Ship ^ >();

		//+---------------temp data----------------+
		//+----might be deleted after placement----+
		List < List < int > ^ > ^ buffer_coords = gcnew List < List < int > ^ >(); 
		List < List < int > ^ > ^ view_coordinates = gcnew List < List < int > ^ >();
		List < Tuple < int, int > ^ > ^ required_coordinates = gcnew List<Tuple < int, int >^ >();
		List < Ship ^ > ^ second_ships_array = gcnew List < Ship ^ > ();
		//+----------------------------------------+



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

		Dictionary < String^, System::Drawing::Color>^ hit_colors = gcnew Dictionary<String^, System::Drawing::Color>();



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
		const int sizeFieldY = 300 + (simp_margin * 10), sizeFieldX = 300 + (simp_margin * 10);
		int corrections = simp_margin * 10;
		//+------------------------------------------------------------------------------+

		//+-----------temp data-----------+
		PictureBox^ buffer_Cell = nullptr; // ...
		Ship^ choosen_ship = nullptr; // used for many functions like current choosen_ship.
		Ship^ backUpShip = nullptr; // used for back up ship of drawing if itself coords isn't correct.
		Ship^ backUpShip_Template = nullptr; //used for back up ship if i choose some ship and didn't set it
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
		void init_hit_colors() {
			hit_colors->Add(BS, System::Drawing::Color::Red);         // Для Battleship (Темно-сірий -> Червоний)
			hit_colors->Add(CR, System::Drawing::Color::OrangeRed);   // Для Cruiser (Малиновий -> Червоний з відтінком помаранчевого)
			hit_colors->Add(DS, System::Drawing::Color::DarkOrange);  // Для Destroyer (Бісквітний -> Темно-оранжевий)
			hit_colors->Add(SB, System::Drawing::Color::Magenta);     // Для Submarine (Темно-фіолетовий -> Яскраво-рожевий)
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
		System::Windows::Forms::Panel^ Bot_Panel_Grid;
		//System::Windows::Forms::Panel^ unknown_ship_panel;

		//+-----------------------------------------+

		//+-----------------------------------------+
	private: System::Windows::Forms::Button^ ready_button;
	private: System::Windows::Forms::Button^ randomize_button;


		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
        void InitializeComponent(void)
        {
			this->MainFieldUser1 = (gcnew System::Windows::Forms::Panel());
			this->Bot_Panel_Grid = (gcnew System::Windows::Forms::Panel());
			this->TemplateShipsField = (gcnew System::Windows::Forms::Panel());
			this->ready_button = (gcnew System::Windows::Forms::Button());
			this->randomize_button = (gcnew System::Windows::Forms::Button());

			this->SuspendLayout();
			// 
			// MainFieldUser1
			// 
			this->MainFieldUser1->Location = System::Drawing::Point(12, 21);
			this->MainFieldUser1->Name = L"MainFieldUser1";
			this->MainFieldUser1->Size = System::Drawing::Size(sizeFieldX, sizeFieldY);
			this->MainFieldUser1->TabIndex = 0;
			// 
			// Bot_Panel_Grid
			// 
			this->Bot_Panel_Grid->Location = System::Drawing::Point(0, 0);
			this->Bot_Panel_Grid->Name = L"panelGrid2";
			this->Bot_Panel_Grid->Size = System::Drawing::Size(sizeFieldX, sizeFieldY);
			this->Bot_Panel_Grid->TabIndex = 0;
			// 
			// TemplateShipsField
			// 
			this->TemplateShipsField->Location = System::Drawing::Point(0, 0);
			this->TemplateShipsField->Name = L"ShipsField";
			this->TemplateShipsField->Size = System::Drawing::Size(sizeFieldX, sizeFieldY);
			this->TemplateShipsField->TabIndex = 0;
			// 
			// ready_button
			// 
			this->ready_button->Location = System::Drawing::Point(358 + corrections, 363 + corrections);
			this->ready_button->Name = L"ready_button";
			this->ready_button->Size = System::Drawing::Size(75, 23);
			this->ready_button->TabIndex = 1;
			this->ready_button->Text = L"Ready";
			this->ready_button->UseVisualStyleBackColor = true;
			this->ready_button->Click += gcnew System::EventHandler(this, &Battlfield::button1_Click);
			// 
			// randomize_button
			// 
			this->randomize_button->Location = System::Drawing::Point((sizeFieldX / 2) - corrections * 2, sizeFieldY + corrections * 2);
			this->randomize_button->Name = L"randomize_button";
			this->randomize_button->Size = System::Drawing::Size(75, 23);
			this->randomize_button->TabIndex = 1;
			this->randomize_button->Text = L"Randomize";
			this->randomize_button->UseVisualStyleBackColor = true;
			this->randomize_button->Hide();
			this->randomize_button->Click += gcnew System::EventHandler(this, &Battlfield::Randomize_User_Field_Ships);
			// 
			// Battlfield
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->ClientSize = System::Drawing::Size(792 + corrections, 398 + corrections);
			this->Controls->Add(this->ready_button);
			this->Controls->Add(this->randomize_button);
			this->Controls->Add(this->MainFieldUser1);
			this->Name = L"Battlfield";
			this->Text = L"Battleship Game";
			this->ResumeLayout(false);
			//
			//event
			//
			this->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &Battlfield::MouseWheel_Rotate_Ship);
		}

#pragma region some initialization

		void InitializeGameStage()
		{
			if (currentStage == GameStage::Battle) {
				this->Bot_Panel_Grid = gcnew System::Windows::Forms::Panel();
				this->Bot_Panel_Grid->Location = System::Drawing::Point(470, 21);
				this->Bot_Panel_Grid->Name = L"panelGrid2";
				this->Bot_Panel_Grid->Size = System::Drawing::Size(sizeFieldX, sizeFieldY);
				this->Bot_Panel_Grid->TabIndex = 1;

				// Add the panel to the form
				this->Controls->Add(this->Bot_Panel_Grid);

				CreateGrid(10, 10, Bot_Panel_Grid);
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

				for each(Ship^ some_ship in array_of_ships_for_check_out) { //need to run through by the ships array for getting the coords and... Check the condition

					for (int k = 0; k < new_coords->Count; k++) { // that cycle are exists for don't leave of the limits of list

						if (some_ship->is_that_your_coord(new_coords[k]->default[0], new_coords[k]->default[1])) {
							return false;
						}
					}
				}

			}

			return true;
		}

		List<List<int>^>^ randomize_coordinates(int length, List<Ship^>^ list_of_pinned_ships) {
			List<List<int>^>^ rand_coords = nullptr;
			bool okPosition = false; /*while rand_coords don't to follow the ruls! kurwa*/


			while (okPosition == false) {
				bool XY = (rand() % (2) == 1) ? true : false;/*"true" define ONLY value X, false means ONLY the Y define what will be changed. Means on the axis X or Y*/
				bool Y_Direction = (rand() % (2) == 1) ? true : false;/*"true" define direction will be changed only by the "top", false opposite that is to the "down"*/
				bool X_Direction = (rand() % (2) == 1) ? true : false;/*"true" define direction will be changed only by the "rigth", false opposite that is to the "left"*/
				int root_x = rand() % (10);/*randomly determines coordinates on the begin the function*/
				int root_y = rand() % (10);/*randomly determines coordinates on the begin the function*/

				List<List<int>^>^ buffer = gcnew List<List<int>^>();
				for (int i = 0; i < length; i++) {
					List<int>^ innerList = gcnew List<int>();
					buffer->Add(innerList);
					if (XY) {
						root_x += (X_Direction == true) ? 1 : -1;
					}
					else {
						root_y += (Y_Direction == true) ? 1 : -1;
					}

					buffer[i]->Add(root_x);
					buffer[i]->Add(root_y);
					if (root_x < 0 || root_x > 9 || root_y < 0 || root_y > 9) {
						break; // Або відразу перезапустіть генерацію координат
					}

				}
				if (clear_coordinates(buffer, list_of_pinned_ships)) {
					okPosition = true;
					rand_coords = buffer;
				}
			}
			return rand_coords;
		}

		void SetTag(PictureBox^ cell, int x, int y) {
			Tuple<int, int>^ coordinates = Tuple::Create(x, y);
			cell->Tag = coordinates;
		}

		//+--------------------------------------------------------------+
		//|filling the "array_for_fill_a_ships" of random generats ships |
		//+--------------------------------------------------------------+
		void CreateFieldShips(List<Ship^>^% array_for_fill_a_ships, System::Windows::Forms::Panel^ panel_for_drawing_ships) {
			for each (KeyValuePair<String^, int> kvp in countOfShips) {

				String^ key = kvp.Key;
				int value = kvp.Value;

				for (int i = 0; i < value; i++) {
					List<List<int>^>^ buf = randomize_coordinates(sizeOfShips[key], array_for_fill_a_ships);

					if (key == BS) {

						Ship^ ship = gcnew Battleship(buf, sizeOfShips[BS], BS);
						
						array_for_fill_a_ships->Add(ship);
						Mark_the_ship(ship, panel_for_drawing_ships);
					}
					else if (key == CR) {

						Ship^ ship = gcnew Cruisers(buf, sizeOfShips[CR], CR);
						array_for_fill_a_ships->Add(ship);
						Mark_the_ship(ship, panel_for_drawing_ships);
					}
					else if (key == DS) {

						Ship^ ship = gcnew Destroyers(buf, sizeOfShips[DS], DS);
						array_for_fill_a_ships->Add(ship);
						Mark_the_ship(ship, panel_for_drawing_ships);
					}
					else if (key == SB) {

						Ship^ ship = gcnew Submarines(buf, sizeOfShips[SB], SB);
						array_for_fill_a_ships->Add(ship);
						Mark_the_ship(ship, panel_for_drawing_ships);
					}
				}
				// Do something with key and value

			}
		}

		void Randomize_User_Field_Ships(System::Object^ sender, System::EventArgs^ e) {
			first_ships_array->Clear();
			TemplateShipsField->Hide();

			to_tidy_panel_void_ships_mark(MainFieldUser1, nullptr);

			CreateFieldShips(first_ships_array, MainFieldUser1);

			manage_visible_of_button(ready_button, first_ships_array);
		}
#pragma endregion /*create random ships*/

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

						if (some_ship_from_array_for_check->is_that_your_coord(x, y) 
							&& !already_exist_required_point_tuple(required_coords_temp, tag->X, tag->Y) 
							&& ((tag->X != 0 || tag->Y != 0) || required_coords_temp->Count > 0)) {
							return true;// i add occupied coordinates.

						}
					}

				}
			}
			return false; //coordinates is free.
			//if coords are ready for use
		}

		void to_tidy_panel_void_ships_mark(Panel^ tidy_panel, List<Ship^>^ array_for_check) {
			if (!array_for_check) {
				for each (Control ^ control in tidy_panel->Controls)
				{
					PictureBox^ pictureBox = dynamic_cast<PictureBox^>(control);
					pictureBox->BackColor = System::Drawing::Color::LightBlue;
				}
				return;
			}
			else if (array_for_check->Count == 0) {
				for each (Control ^ control in tidy_panel->Controls) {
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
			if (array_of_ships->Count <= 0) {
				return false;
			}
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
				else if (dragging || choosen_ship) {
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

		//+-------------------------------------------+
		//|i'd not want to make function much hardest.|
		//|So I have just copy without condition	  |
		//+-------------------------------------------+
		void Marks_BackUp(Ship^ some_BackUp_Ship, System::Windows::Forms::Panel^ some_panel) {
			//general moment where i use attribute from header of function for getting the coords.
			List<List<int>^>^ coords = some_BackUp_Ship->your_coords();
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
				if (some_BackUp_Ship->get_Name() == BS) {
					cell->BackColor = colors[BS];
					cell->Name = some_BackUp_Ship->get_Name() + some_BackUp_Ship->get_number_of_ships().ToString();
				}
				else if (some_BackUp_Ship->get_Name() == CR) {
					cell->BackColor = colors[CR];
					cell->Name = some_BackUp_Ship->get_Name() + some_BackUp_Ship->get_number_of_ships().ToString();
				}
				else if (some_BackUp_Ship->get_Name() == DS) {
					cell->BackColor = colors[DS];
					cell->Name = some_BackUp_Ship->get_Name() + some_BackUp_Ship->get_number_of_ships().ToString();
				}
				else if (some_BackUp_Ship->get_Name() == SB) {
					cell->BackColor = colors[SB];
					cell->Name = some_BackUp_Ship->get_Name() + some_BackUp_Ship->get_number_of_ships().ToString();
				}
			}
		}

		void Mark_Hits_by_Ships(Ship^ some_hitted_ship, System::Windows::Forms::Panel^ some_panel) {
			//general moment where i use attribute from header of function for getting the coords.
			List<List<int>^>^ coords = some_hitted_ship->your_hitted_coords();
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
				if (some_hitted_ship->get_Name() == BS) {
					cell->BackColor = hit_colors[BS];
					cell->Name = some_hitted_ship->get_Name() + some_hitted_ship->get_number_of_ships().ToString();
				}
				else if (some_hitted_ship->get_Name() == CR) {
					cell->BackColor = hit_colors[CR];
					cell->Name = some_hitted_ship->get_Name() + some_hitted_ship->get_number_of_ships().ToString();
				}
				else if (some_hitted_ship->get_Name() == DS) {
					cell->BackColor = hit_colors[DS];
					cell->Name = some_hitted_ship->get_Name() + some_hitted_ship->get_number_of_ships().ToString();
				}
				else if (some_hitted_ship->get_Name() == SB) {
					cell->BackColor = hit_colors[SB];
					cell->Name = some_hitted_ship->get_Name() + some_hitted_ship->get_number_of_ships().ToString();
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

	#pragma region elements in window

		//+------------------------------------------------------------+
		//|it recieve the "list_of_ships_for_compare" and			   |
		//|it compare of with "template_ships_array" by number of ships|
		//+------------------------------------------------------------+
		void manage_visible_of_button(Button^ some_button, List<Ship^>^ list_of_ships_for_compare) {
			if (!All_Ships_Have_Been_Arranged(list_of_ships_for_compare)) {
				some_button->Hide();
			}
			else if (All_Ships_Have_Been_Arranged(list_of_ships_for_compare)) {
				some_button->Visible = true;
			}
		}


	#pragma endregion/*elements in window*/

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
			randomize_button->Visible = true;

			InitializeShips();
			CreateFieldShips(second_ships_array, TemplateShipsField);

			manage_visible_of_button(ready_button, first_ships_array);

			CustomMessageBox::Show("You are into stage Placement. Here you can press your LMB for choicing ship and move your mouse " +
				"by left of the margin for changing place of a ship. \nWhen you will be ready for placement a ship in field press " +
				"LMB by cell.", "Stage have been changed stage to Placement");
		}

		void StartBattle() {
			{
				TemplateShipsField->Hide();
				randomize_button->Hide();
				ready_button->Hide();

				backUpShip_Template = nullptr;
				choosen_ship = nullptr;
				buffer_Cell = nullptr;
				backUpShip = nullptr;

				required_coordinates ? required_coordinates->Clear() : required_coordinates;
				second_ships_array ? second_ships_array->Clear() : second_ships_array;
				view_coordinates ? view_coordinates->Clear() : view_coordinates;
				buffer_coords ? buffer_coords->Clear() : buffer_coords;
			}
			
			InitializeGameStage();
			CreateFieldShips(second_ships_array, Bot_Panel_Grid);
			to_tidy_panel_void_ships_mark(Bot_Panel_Grid, nullptr);

			CustomMessageBox::Show("You've passed stage Placement and finally! Switched to stage's Battle", "Stage have been changed stage to Battle");
		}

		void EndGame() {
			// Код завершения игры
		}

#pragma region events

#pragma region general functions for reflection of ships

		//+-------------------------------------------------------------------------------------+
		//|using the "choosen_ship" for return it back on to its first place					|
		//| strange what that are working because i often change the coordinates of choosen_ship|
		//+-------------------------------------------------------------------------------------+
		void return_choosen_ship_back(Panel^ in_which_panel_it_will_be_returned, List<Ship^>^ array_that_uses_that_field) {

			choosen_ship->change_coordinates(buffer_coords);

			array_that_uses_that_field->Add(choosen_ship);

			Mark_the_ship(choosen_ship, in_which_panel_it_will_be_returned);
			to_tidy_panel_void_ships_mark(MainFieldUser1, first_ships_array);

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

		//+---------------------------------------------------------------+
		//|it doesn't just checking. Even changed it on correct!		  |
		//+---------------------------------------------------------------+
		void corrections_of_coordinates_for_showed(List<List<int>^>^% list_of_coordinates) {

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
		void paint_choosen_ship(System::Object^ sender, System::EventArgs^ e) {
			try { (!choosen_ship) ? System::Convert::ToString("choosen_ship in function \"paint_choosen_ship_while\" is equal to nullptr") : "nothing"; }
			catch (String^ errmsg) { return; }

			List<List<int>^>^ view_coordinates_temp = gcnew List<List<int>^>;
			PictureBox^ enterCell = dynamic_cast<PictureBox^>(sender);
			Point^ CellTag = dynamic_cast<Point^>(enterCell->Tag);

			int x = (choosen_ship->get_Direction() == 'X') ? choosen_ship->get_Length() : 1;
			int y = (choosen_ship->get_Direction() == 'Y') ? choosen_ship->get_Length() : 1;
			List<List<int>^>^ choosen_ship_coords = choosen_ship->your_coords();

			//default coords for changing from that point
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

			choosen_ship->change_coordinates(view_coordinates_temp);
			corrections_of_coordinates_for_showed(view_coordinates_temp);

			for each (List<int> ^ one_dim_arr in view_coordinates_temp) {

				for each (Ship ^ some_ship in first_ships_array) {

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

		void generate_opposite_coords_wheel(int root_x, int root_y) {
			List<List<int>^>^ view_coordinates_temp = gcnew List<List<int>^>;

			int x = (choosen_ship->get_Direction() == 'X') ? choosen_ship->get_Length() : 1;
			int y = (choosen_ship->get_Direction() == 'Y') ? choosen_ship->get_Length() : 1;
			List<List<int>^>^ choosen_ship_coords = choosen_ship->your_coords();

			//default coords for changing from that point. Defined by last coordinates. If it equal so thats is a direction
			Char addDirXY = choosen_ship->get_Direction();

			for (int i = 0; i < x; i++) {
				for (int j = 0; j < y; j++) {
					List<int>^ XY = gcnew List<int>;
					int X_coord = (addDirXY == 'X') ? root_x + i : root_x;
					int Y_coord = (addDirXY == 'Y') ? root_y + j : root_y;
					XY->Add(X_coord);
					XY->Add(Y_coord);

					view_coordinates_temp->Add(XY);
				}
			}

			if (!clear_coordinates(view_coordinates_temp, first_ships_array) ){
				choosen_ship = backUpShip;
				choosen_ship->change_direction();
				view_coordinates = backUpShip->your_coords();
				backUpShip = nullptr;
				return;
			}

			view_coordinates = view_coordinates_temp;
		}

#pragma endregion general functions for reflection of something

		//+---------------------------------------+
		//|draws x or y axis based on root [x:y]  |
		//+---------------------------------------+
		void Battlfield::MouseWheel_Rotate_Ship(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e){
			if (choosen_ship) {
				backUpShip = choosen_ship;

				choosen_ship->change_direction();

				generate_opposite_coords_wheel(view_coordinates[0]->default[0], view_coordinates[0]->default[1]); // changed view_coords because it's a global variable

				choosen_ship->change_coordinates(view_coordinates); // because in generate_opposite (and maybe others func) using that coords like main coords of ship

				to_tidy_panel_void_ships_mark(MainFieldUser1, first_ships_array);

				Mark_the_ship(choosen_ship, MainFieldUser1);
			}
		}

		//+------------------------------------------------------------------------------------------+
		//|cleaning the "panel" and paint choosen ship based on coords of cell which was hold a mouse|
		//+------------------------------------------------------------------------------------------+
		void MouseEnter_Cell(System::Object^ sender, System::EventArgs^ e) {
			if (choosen_ship) {

				to_tidy_panel_void_ships_mark(MainFieldUser1, first_ships_array);
				/*MessageBox::Show(String::Format("choosen_ship: {0}, backUpShip_Template: {1}",
					choosen_ship->GetHashCode(), backUpShip_Template->GetHashCode()));*/

				paint_choosen_ship(sender, e);

			}
		}
		void Battlfield::OnCellMouseClick(Object^ sender, MouseEventArgs^ e){

			if (currentStage == GameStage::Setup) {
				//nothing? Or have created crucial moment for 1v1?
			}
			else if (currentStage == GameStage::Placement) {
				PictureBox^ clickedCell = safe_cast<PictureBox^>(sender);

				if (clickedCell != nullptr) { 
					Panel^ parentPanel = dynamic_cast<Panel^>(clickedCell->Parent); 
					
					// Checking, to which of the buttons were pressed
					if (parentPanel == MainFieldUser1) { 
					
						if (dragging && choosen_ship) {
							Point^ clickedCellTag = safe_cast<Point^>(clickedCell->Tag);

							Point^ cellTag = safe_cast<Point^>(buffer_Cell->Tag);
							Ship^ some_ship = choosen_ship;

							if (clear_coordinates(view_coordinates, first_ships_array) == false) {
								MessageBox::Show("the ship not on the right coordinates.");
								return;
							}

							some_ship->change_coordinates(view_coordinates);

							Mark_the_ship(some_ship, MainFieldUser1);
							
							first_ships_array->Add(some_ship);
						
							dragging = false;
							choosen_ship = nullptr;
						}
						else if (!dragging) {
							Point^ clickedCellTag = safe_cast<Point^>(clickedCell->Tag);
							Ship^ some_ship = initialize_ship_by_the_help_of_coords_by_cell(clickedCellTag->X, clickedCellTag->Y, first_ships_array);
							try {
								if (!some_ship && !choosen_ship) {
									throw System::Convert::ToString("Our ships for some reason: nullptr's");
								}
							}
							catch (String^ errmsg) {
								MessageBox::Show(errmsg);
								to_tidy_panel_void_ships_mark(MainFieldUser1, first_ships_array);
								return;
							}
							//comparisons such as "some_ship == nullptr" call the exception. So... !some_ship
							if (some_ship && !choosen_ship) {
								choosen_ship = some_ship;

								to_clear_required_coords();

								buffer_coords = some_ship->your_coords();

								for (int i = 0; i < first_ships_array->Count; i++) {
									if (first_ships_array[i]->get_identifier() == some_ship->get_identifier()) {
										first_ships_array->RemoveAt(i);
									}
								}
							}
							else if (choosen_ship && some_ship) {
								return_choosen_ship_back(MainFieldUser1, first_ships_array);
							}
							else if (clear_coordinates(choosen_ship->your_coords(), first_ships_array) && !some_ship && choosen_ship )
							{
								choosen_ship->change_coordinates(view_coordinates);
								view_coordinates = nullptr;

								first_ships_array->Add(choosen_ship);

								Mark_the_ship(choosen_ship, MainFieldUser1);
								choosen_ship = nullptr;
							}
						}
					} 
					else if (parentPanel == TemplateShipsField) { 
						if (!choosen_ship) {
							Point^ cellTag = safe_cast<Point^>(clickedCell->Tag);
							Ship^ some_ship = initialize_ship_by_the_help_of_coords_by_cell(cellTag->X, cellTag->Y, second_ships_array);

							try {
								if (already_exists_in_field(some_ship, first_ships_array) == false
									&& some_ship != nullptr) {

									if (dragging == false) {
										buffer_Cell = clickedCell;
										dragging = true;
									}
									else {
										dragging = false;
									}

									if (some_ship != nullptr) {
										choosen_ship = some_ship->Clone();
										backUpShip_Template = some_ship->Clone(); // Глибоке копіювання
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
							return_choosen_ship_back(MainFieldUser1, first_ships_array);
							to_tidy_panel_void_ships_mark(MainFieldUser1, first_ships_array);//and clearing a traces
						}
						else if (choosen_ship && dragging) { // if the a ship wasn't placed in "MainFieldUser1"
							choosen_ship = nullptr;
							dragging = false;
							Marks_BackUp(backUpShip_Template, TemplateShipsField);
							to_tidy_panel_void_ships_mark(MainFieldUser1, first_ships_array);
						}
					} 
					if (All_Ships_Have_Been_Arranged(first_ships_array)) {
						manage_visible_of_button(ready_button, first_ships_array);
						return;
					}
				}
			}
			else if (currentStage == GameStage::Battle) {
				PictureBox^ clickedCell = safe_cast<PictureBox^>(sender);
				Panel^ parentPanel = dynamic_cast<Panel^>(clickedCell->Parent);
				if (parentPanel != MainFieldUser1) {
					if (e->Button == System::Windows::Forms::MouseButtons::Left) {
						ShootByThatCoordinates(sender, e); // Обробка лівого кліку
					}
					else if (e->Button == System::Windows::Forms::MouseButtons::Right){
						MarkCell(sender, e); // Обробка правого кліку
					}
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
        void ShootByThatCoordinates(System::Object^ sender, System::EventArgs^ e){
            PictureBox^ clickedCell = safe_cast<PictureBox^>(sender);
			
			if (clickedCell->BackColor != System::Drawing::Color::DimGray) {
				Ship^ some_ship;
				//clickedCell->Size = System::Drawing::Size(28, 28);
				System::Drawing::Point^ clickedCellTag = safe_cast<System::Drawing::Point^>(clickedCell->Tag);
				some_ship = initialize_ship_by_the_help_of_coords_by_cell(clickedCellTag->X, clickedCellTag->Y, first_ships_array);
				if (some_ship) {
					clickedCell->BackColor = hit_colors[some_ship->get_Name()]; // change color of cell
				}
				else {
					clickedCell->Location = System::Drawing::Point(System::Convert::ToInt32(clickedCell->Location.X), System::Convert::ToInt32(clickedCell->Location.Y));
					clickedCell->BackColor = System::Drawing::Color::DimGray; // change color of cell
				}
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

		bool All_Ships_Have_Been_Arranged(List<Ship^>^ some_array) {
			if (some_array->Count == second_ships_array->Count) {
				return true;
			}
			return false;
		}
#pragma endregion
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	Battlfield::NextStage();
}
};


}
