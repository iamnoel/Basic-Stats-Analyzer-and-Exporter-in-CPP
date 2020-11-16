// Author: Noel Ward

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

/* Stores an integer number and the frequency of how many times it was counted in a series */
struct Mode {
	int number;
	int count;
};

/* Stores the various statistical data for the terms to be conveniently stored
and passed between classes */
struct Statistics {
	int min;
	int max;
	int range;
	float mean;
	float median;
	int mode;
};

/* Handles all of the file storage functionality to take all 
of the integers in memory, opens streams to write them to a
file at the path provided, appending to the end of the file.
Writes all of the statistical data to the files after the terms. */
class FileExporter {
private:
	string path;

public:
	//Sets the path where the file will be saved
	void fnSetPath(string p)
	{
		path = p;
	}

	//Returns the path where the file will be saved
	string fnGetPath()
	{
		return path;
	}

	/* Opens a stream and saves all of the stored integers to the
	file at the stored path, appending each to the end of the file
	and returns true if a path is set and the operation is successful
	or returns false if no path is set to save the file */
	bool fnSaveFile(vector<int> &v, Statistics &stats)
	{
		if (path.length() > 0)
		{
			ofstream file(path, ios::app);

			for (int i = 0; i < v.size(); i++)
			{
				file << v[i] << endl;
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
	bool fnSaveFile(int p[], int len, Statistics &stats)
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
};

/* Handles displaying the menu and options to the user, receives their input,
calls all associated functions related to the menu system and inputs and calls 
the various statistical and file storage functions, passing any needed data */
class UserMenu {
private:
	string input;
	FileExporter file; //A reference will be stored to the file

public:
	bool active = true; //This will track whether the menu is "active" and should continue to be looped and displayed to the user

	/* Displays the menu options to the user and receives their input */
	void fnDisplay()
	{
		cout << "Available Operations" << endl;
		cout << "1. Store and Compute with Vector" << endl;
		cout << "2. Store and Compute with Pointer" << endl;
		cout << "3. Set File Saving Path" << endl;
		cout << "4. Exit" << endl << endl;
		cout << "Enter your selection: "; cin >> input;
		fnValidateMenu();
	}

	/* Calls the associated functions based on the menu option that the user inputed */
	void fnValidateMenu()
	{
		//Store and compute - vector
		if (input == "1")
		{
			fnSortStoreByVector();
			cout << endl << endl;
		}
		//Store and compute - pointer
		else if (input == "2")
		{
			fnSortStoreByPointer();
			cout << endl << endl;
		}
		//Set file path
		else if (input == "3")
		{
			cout << "Please enter the file path: "; cin >> input; cout << endl;
			file.fnSetPath(input);
		}
		//Exit
		else if (input == "4" || input == "exit")
		{
			cout << "Merci!" << endl << endl;
			active = false;
		}
		else {
			cout << "Sorry your input was not understood. Please try again." << endl << endl;
		}
	}

	//Stores a reference to the file exporter
	void fnDefineFile(FileExporter &f)
	{
		file = f;
	}

	/* Prompts the user to indicate how many integers should be stored,
	loops through and stores each of the integers into a vector, sorts 
	the integers lowest to highest, then computes statistical values */
	void fnSortStoreByVector()
	{
		vector<int> v;
		int num;
		
		cout << "How many terms would you like to enter: "; cin >> num; cout << endl;

		for (int i = 1; i <= num; i++)
		{
			int value;
			cout << "Term " << i << ": "; cin >> value;
			v.push_back(value);
		}

		cout << endl;
		cout << "Provided data: ";

		for (int i : v)
		{
			cout << i << " ";
		}

		cout << endl << "Sorted data:   ";

		sort(v.begin(), v.end());

		for (int i : v)
		{
			cout << i << " ";
		}

		cout << endl << endl;
		fnDisplayVectorStats(v);
	}

	/* Calculates the min, max, range, mean, median, displays the values to
	the user and then stores them to a file if a path has been set */
	void fnDisplayVectorStats(vector<int> &v)
	{
		Statistics stats;
		stats.min = v[0];
		stats.max = v[(v.size() - 1)];
		stats.range = (v[v.size() - 1] - v[0]);

		//Declare and begin calculating the mean
		stats.mean = 0;
		for (int val : v)
		{
			stats.mean += val;
		}
		stats.mean /= v.size();
		//Get 1 decimal point
		stats.mean = (((float)((int)(stats.mean * 10))) / 10);

		//Declare and begin calculating the median
		stats.median;
		if ((v.size() % 2) == 0)
		{
			stats.median = (((float)v[v.size() / 2 - 1] + (float)v[v.size() / 2]) / 2);
		}
		else
		{
			stats.median = v[(v.size() / 2)];
		}
		//Get 1 decimal point
		stats.median = (((float)((int)(stats.median * 10))) / 10);

		//Declare and begin counting the mode
		vector<int> modeCounter;
		vector<Mode> modes;
		
		//Every number that occurs more than one time will be added to a vector
		for (int i = 1; i < v.size(); i++)
		{
			if (v[i] == v[(i - 1)])
			{
				modeCounter.push_back(v[i]);
			}
		}

		//If there is at least one duplicate we have a mode and need to check how many
		if (modeCounter.size() > 0)
		{
			for (int number : modeCounter)
			{
				Mode m;
				m.number = number;
				m.count = 0;

				for (int i = 0; i < v.size(); i++)
				{
					if (m.number == number) {
						m.count++;
					}
				}
				modes.push_back(m);
			}

			//For just one mode we can assign it now
			if (modes.size() == 1) {
				stats.mode = modes[0].number;
			}
			//When we have more than one mode we'll need to see which occurs at the highest frequency
			else if (modes.size() > 1)
			{
				for (int i = 1; i < modes.size(); i++)
				{
					if (modes[i].count > modes[i - 1].count)
					{
						stats.mode = modes[i].number;
					}
					//If they occur the same number of times then we'll just take the highest number for the mode
					else if (modes[i].count == modes[i - 1].count)
					{
						stats.mode = modes[i].number;
					}
				}
			}

		}
		else
		{
			//If there are no duplicate values then we'll take the first number in the series
			stats.mode = v[0];
		}
		

		cout << "Statistical results" << endl;
		cout << "Min: " << stats.min << endl;
		cout << "Max: " << stats.max << endl;
		cout << "Range: " << stats.range << endl << endl;

		cout << "Mean: " << stats.mean << endl;
		cout << "Median: " << stats.median << endl;
		cout << "Mode: " << stats.mode << endl << endl;

		if (file.fnSaveFile(v, stats))
		{
			cout << "The results have been saved to: " << file.fnGetPath();
		}
		else
		{
			cout << "This operation could not be saved as no file path has been provided.";
		}
	}

	/* Prompts the user to indicate how many integers should be stored,
	loops through and stores each of the integers into a pointer array,
	sorts the integers lowest to highest, then computes statistical values */
	void fnSortStoreByPointer()
	{
		int num;

		cout << "How many terms would you like to enter: "; cin >> num; cout << endl;

		//Dynamically allocate memory to create a new pointer array based on the user's input
		int* p;
		p = new int[num];

		for (int i = 1; i <= num; i++)
		{
			int value;
			cout << "Term " << i << ": "; cin >> value;
			p[(i - 1)] = value;
		}

		cout << endl;
		cout << "Provided data: ";

		for (int i = 0; i < num; i++)
		{
			cout << p[i] << " ";
		}

		cout << endl << "Sorted data:   ";
		sort(p, p+num);

		for (int i = 0; i < num; i++)
		{
			cout << p[i] << " ";
		}

		cout << endl << endl;

		fnDisplayPointerStats(p, num);

		//Frees the memory we dynamically allocated
		delete[] p;
	}

	/* Calculates the min, max, range, mean, median, displays the values to
	the user and then stores them to a file if a path has been set */
	void fnDisplayPointerStats(int p[], int len)
	{
		Statistics stats;

		stats.min = p[0];
		stats.max = p[(len - 1)];
		stats.range = (p[len - 1] - p[0]);

		//Declare and begin calculating the mean
		stats.mean = 0;
		for (int i = 0; i < len; i++)
		{
			stats.mean += p[i];
		}
		stats.mean /= len;
		//Get 1 decimal point
		stats.mean = (((float)((int)(stats.mean * 10))) / 10);

		//Declare and begin calculating the median
		stats.median;
		if ((len % 2) == 0)
		{
			stats.median = (((float)p[len / 2 - 1] + (float)p[len / 2]) / 2);
		}
		else
		{
			stats.median = p[(len / 2)];
		}
		//Get 1 decimal point
		stats.median = (((float)((int)(stats.median * 10))) / 10);

		//Declare and begin counting the mode
		vector<int> modeCounter;
		vector<Mode> modes;

		//Every number that occurs more than one time will be added to a vector
		for (int i = 1; i < len; i++)
		{
			if (p[i] == p[(i - 1)])
			{
				modeCounter.push_back(p[i]);
			}
		}

		//If there is at least one duplicate we have a mode and need to check how many
		if (modeCounter.size() > 0)
		{
			for (int number : modeCounter)
			{
				Mode m;
				m.number = number;
				m.count = 0;

				for (int i = 0; i < len; i++)
				{
					if (m.number == number) {
						m.count++;
					}
				}
				modes.push_back(m);
			}

			//For just one mode we can assign it now
			if (modes.size() == 1) {
				stats.mode = modes[0].number;
			}
			//When we have more than one mode we'll need to see which occurs at the highest frequency
			else if (modes.size() > 1)
			{
				for (int i = 1; i < modes.size(); i++)
				{
					if (modes[i].count > modes[i - 1].count)
					{
						stats.mode = modes[i].number;
					}
					//If they occur the same number of times then we'll just take the highest number for the mode
					else if (modes[i].count == modes[i - 1].count)
					{
						stats.mode = modes[i].number;
					}
				}
			}

		}
		else
		{
			//If there are no duplicate values then we'll take the first number in the series
			stats.mode = p[0];
		}

		cout << "Statistical results" << endl;
		cout << "Min: " << stats.min << endl;
		cout << "Max: " << stats.max << endl;
		cout << "Range: " << stats.range << endl << endl;

		cout << "Mean: " << stats.mean << endl;
		cout << "Median: " << stats.median << endl;
		cout << "Mode: " << stats.mode << endl;

		if (file.fnSaveFile(p, len, stats))
		{
			cout << "The results have been saved to: " << file.fnGetPath();
		}
		else
		{
			cout << "This operation could not be saved as no file path has been provided.";
		}
	}
};

UserMenu menu;
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