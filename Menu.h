#pragma once

#include <string>
#include <vector>
#include "FileExporter.h"
#include "Mode.h"

#ifndef Menu_H
#define Menu_H

/* Handles displaying the menu and options to the user, receives their input,
calls all associated functions related to the menu system and inputs and calls 
the various statistical and file storage functions, passing any needed data */
class Menu {
private:
	std::string input;
	FileExporter file; //A reference will be stored to the file

public:
	bool active = true; //This will track whether the menu is "active" and should continue to be looped and displayed to the user

	/* Displays the menu options to the user and receives their input */
	void fnDisplay();

	/* Calls the associated functions based on the menu option that the user inputed */
	void fnValidateMenu();

	//Stores a reference to the file exporter
	void fnDefineFile(FileExporter &f);

	/* Prompts the user to indicate how many integers should be stored,
	loops through and stores each of the integers into a vector, sorts 
	the integers lowest to highest, then computes statistical values */
	void fnSortStoreByVector();

	/* Calculates the min, max, range, mean, median, displays the values to
	the user and then stores them to a file if a path has been set */
	void fnDisplayVectorStats(std::vector<int> &v);

	/* Prompts the user to indicate how many integers should be stored,
	loops through and stores each of the integers into a pointer array,
	sorts the integers lowest to highest, then computes statistical values */
	void fnSortStoreByPointer();

	/* Calculates the min, max, range, mean, median, displays the values to
	the user and then stores them to a file if a path has been set */
	void fnDisplayPointerStats(int p[], int len);
};

#endif