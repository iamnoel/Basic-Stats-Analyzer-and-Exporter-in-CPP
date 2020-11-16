#pragma once

#include <string>
#include <vector>
#include "Statistics.h"

#ifndef FileExporter_H
#define FileExporter_H

/* Handles all of the file storage functionality to take all 
of the integers in memory, opens streams to write them to a
file at the path provided, appending to the end of the file.
Writes all of the statistical data to the files after the terms. */
class FileExporter {
private:
	std::string path;

public:
	//Sets the path where the file will be saved
	void fnSetPath(std::string p);

	//Returns the path where the file will be saved
	std::string fnGetPath();

	/* Opens a stream and saves all of the stored integers to the
	file at the stored path, appending each to the end of the file
	and returns true if a path is set and the operation is successful
	or returns false if no path is set to save the file */
	bool fnSaveFile(std::vector<int> &v, Statistics &stats);

	/* Overloaded to store the pointer array: Opens a stream and saves
	all of the stored integers to the file at the stored path, appending
	each to the end of the file and returns true if a path is set and the
	operation is successful or returns false if no path is set to save the file */
	bool fnSaveFile(int p[], int len, Statistics &stats);
};

#endif