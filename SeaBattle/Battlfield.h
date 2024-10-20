#pragma once

namespace SeaBattle {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Battlfield
	/// </summary>
	public ref class Battlfield : public System::Windows::Forms::Form
	{
	public:
		Battlfield(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			CreateGrid(10, 10, panelGrid);
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
        System::Windows::Forms::Panel^ panelGrid;

		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
        void InitializeComponent(void)
        {
			this->panelGrid = (gcnew System::Windows::Forms::Panel());
			this->SuspendLayout();
			// 
			// panelGrid
			// 
			this->panelGrid->Location = System::Drawing::Point(24, 21);
			this->panelGrid->Name = L"panelGrid";
			this->panelGrid->Size = System::Drawing::Size(300, 300);
			this->panelGrid->TabIndex = 0;
			// 
			// Battlfield
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(792, 398);
			this->Controls->Add(this->panelGrid);
			this->Name = L"Battlfield";
			this->Text = L"Battleship Game";
			this->ResumeLayout(false);

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
                    cell->Click += gcnew System::EventHandler(this, &Battlfield::OnCellClick);
                    panel->Controls->Add(cell); // add the cell on the panel
                }
            }
        }

        // handler click by the cell
        void OnCellClick(System::Object^ sender, System::EventArgs^ e)
        {
            PictureBox^ clickedCell = safe_cast<PictureBox^>(sender);
            System::Drawing::Point^ coord = safe_cast<System::Drawing::Point^>(clickedCell->Tag);
            clickedCell->BackColor = System::Drawing::Color::DimGray; // change color of cell
            // you need to create additional logic, a handler that checks whether the ship is hit or not.
        }

#pragma endregion
	};
}
