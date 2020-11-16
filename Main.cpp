// Author: Noel Ward

#include "FileExporter.h"
#include "Menu.h"

Menu menu;
FileExporter file;

int main()
{
	menu.fnDefineFile(file);
	do
	{
		menu.fnDisplay();
	} while (menu.active);

	return 0;
}