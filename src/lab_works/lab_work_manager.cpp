#include "lab_work_manager.hpp"
#include "imgui.h"
#include "lab_work_1/lab_work_1.hpp"
#include"lab_work_2/lab_work_2.hpp"

namespace M3D_ISICG
{
	LabWorkManager::LabWorkManager()
	{
		// By default, the first lab work is created, you can change it ! :-)
		_current = new LabWork1();
		_type	 = TYPE::LAB_WORK_1;
		_current = new LabWork2();
		_type	 = TYPE::LAB_WORK_2;

	}

	void LabWorkManager::drawMenu()
	{
		// Here you can add other lab works to the menu.
		if ( ImGui::MenuItem( "Lab work 1" ) )
		{
			if ( _type != TYPE::LAB_WORK_1 ) // Change only if needed.
			{
				delete _current;			 // Delete old lab work.
				_current = new LabWork1();	 // Create new lab work.
				_type	 = TYPE::LAB_WORK_1; // Update type.
				_current->init();			 // Don't forget to call init().
			}
		}

		/* if ( ImGui ::MenuItem( "Lab work 2" ) )
		{
			if ( _type != TYPE ::LAB_WORK_2 ) // Change only if needed .
			{
				delete _current;			  // Delete old lab work .
				_current = new LabWork2();	  // Create new lab work .
				_type	 = TYPE ::LAB_WORK_2; // Update type .
				_current -> init();		  // Don ’t forget to call init ().
			}
		}*/
	}
} // namespace M3D_ISICG
