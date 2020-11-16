#include <string>
#include <vector>
#include <fstream>
#include "Statistics.h"
#include "FileExporter.h"

using namespace std;

	//Sets the path where the file will be saved
	void FileExporter::fnSetPath(string p)
	{
		path = p;
	}

	//Returns the path where the file will be saved
	string FileExporter::fnGetPath()
	{
		return path;
	}

	/* Opens a stream and saves all of the stored integers to the
	file at the stored path, appending each to the end of the file
	and returns true if a path is set and the operation is successful
	or returns false if no path is set to save the file */
	bool FileExporter::fnSaveFile(std::vector<int> &v, Statistics &stats)
	{
		if (path.length() > 0)
		{
			ofstream file(path, ios::app);

			for (int i = 0; i < v.size(); i++)
			{
				file << v.at(i) << endl;
			}
			file << "Min: " << stats.min << endl;
			file << "Max: " << stats.max << endl;
			file << "Range: " << stats.range << endl;
			file << "Mean: " << stats.mean << endl;
			file << "Median: " << stats.median << endl;
			file << "Mode: " << stats.mode << endl;
			file.close();

			return true;
		}
		else
		{
			return false;
		}
	}

	/* Overloaded to store the pointer array: Opens a stream and saves
	all of the stored integers to the file at the stored path, appending
	each to the end of the file and returns true if a path is set and the
	operation is successful or returns false if no path is set to save the file */
	bool FileExporter::fnSaveFile(int p[], int len, Statistics &stats)
	{
		if (path.length() > 0)
		{
			ofstream file(path, ios::app);

			for (int i = 0; i < len; i++)
			{
				file << p[i] << endl;
			}
			file << "Min: " << stats.min << endl;
			file << "Max: " << stats.max << endl;
			file << "Range: " << stats.range << endl;
			file << "Mean: " << stats.mean << endl;
			file << "Median: " << stats.median << endl;
			file << "Mode: " << stats.mode << endl;
			file.close();

			return true;
		}
		else
		{
			return false;
		}
	}