#include <iostream>
#include <algorithm>
#include "Menu.h"

/* Displays the menu options to the user and receives their input */
void Menu::fnDisplay()
{
    std::cout << "Available Operations" << std::endl;
    std::cout << "1. Store and Compute with Vector" << std::endl;
    std::cout << "2. Store and Compute with Pointer" << std::endl;
    std::cout << "3. Set File Saving Path" << std::endl;
    std::cout << "4. Exit" << std::endl << std::endl;
    std::cout << "Enter your selection: "; std::cin >> input;
    fnValidateMenu();
}

/* Calls the associated functions based on the menu option that the user inputed */
void Menu::fnValidateMenu()
{
    //Store and compute - vector
    if (input == "1")
    {
        fnSortStoreByVector();
        std::cout << std::endl << std::endl;
    }
    //Store and compute - pointer
    else if (input == "2")
    {
        fnSortStoreByPointer();
        std::cout << std::endl << std::endl;
    }
    //Set file path
    else if (input == "3")
    {
        std::cout << "Please enter the file path: "; std::cin >> input; std::cout << std::endl;
        file.fnSetPath(input);
    }
    //Exit
    else if (input == "4" || input == "exit")
    {
        std::cout << "Merci!" << std::endl << std::endl;
        active = false;
    }
    else {
        std::cout << "Sorry your input was not understood. Please try again." << std::endl << std::endl;
    }
}

//Stores a reference to the file exporter
void Menu::fnDefineFile(FileExporter &f)
{
    file = f;
}

/* Prompts the user to indicate how many integers should be stored,
loops through and stores each of the integers into a vector, sorts 
the integers lowest to highest, then computes statistical values */
void Menu::fnSortStoreByVector()
{
    std::vector<int> v;
    int num;
    
    std::cout << "How many terms would you like to enter: "; std::cin >> num; std::cout << std::endl;

    for (int i = 1; i <= num; i++)
    {
        int value;
        std::cout << "Term " << i << ": "; std::cin >> value;
        v.push_back(value);
    }

    std::cout << std::endl;
    std::cout << "Provided data: ";

    for (int i : v)
    {
        std::cout << i << " ";
    }

    std::cout << std::endl << "Sorted data:   ";

    sort(v.begin(), v.end());

    for (int i : v)
    {
        std::cout << i << " ";
    }

    std::cout << std::endl << std::endl;
    fnDisplayVectorStats(v);
}

/* Calculates the min, max, range, mean, median, displays the values to
the user and then stores them to a file if a path has been set */
void Menu::fnDisplayVectorStats(std::vector<int> &v)
{
    Statistics stats;
    stats.min = v.front();
    stats.max = v.back();
    stats.range = (v.back() - v.front());

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
    if ((v.size() % 2) == 0)
    {
        stats.median = (((float) v.at(v.size() / 2 - 1) + (float) v.at(v.size() / 2)) / 2);
    }
    else
    {
        stats.median = v.at(v.size() / 2);
    }
    //Get 1 decimal point
    stats.median = (((float)((int)(stats.median * 10))) / 10);

    //Declare and begin counting the mode
    std::vector<int> modeCounter;
    std::vector<Mode> modes;
    
    //Every number that occurs more than one time will be added to a vector
    for (int i = 1; i < v.size(); i++)
    {
        if (v.at(i) == v.at(i-1))
        {
            modeCounter.push_back(v.at(i));
        }
    }

    //If there is at least one duplicate we have a mode and need to check how many
    if (modeCounter.size() > 0)
    {
        for (int number : modeCounter)
        {
            Mode m;
            m.number = number;
            m.count = std::count(modeCounter.begin(), modeCounter.end(), number);
            modes.push_back(m);
        }

        //For just one mode we can assign it now
        if (modes.size() == 1) {
            stats.mode = modes.at(0).number;
        }
        //When we have more than one mode we'll need to see which occurs at the highest frequency
        else if (modes.size() > 1)
        {
            for (int i = 1; i < modes.size(); i++)
            {
                if (modes.at(i).count > modes.at(i - 1).count)
                {
                    stats.mode = modes.at(i).number;
                }
                //If they occur the same number of times then we'll just take the largest number for the mode
                else if (modes.at(i).count == modes.at(i - 1).count)
                {
                    stats.mode = modes.at(i).number;
                }
            }
        }

    }
    else
    {
        //If there are no duplicate values then we'll take the first number in the series
        stats.mode = v.at(0);
    }
    

    std::cout << "Statistical results" << std::endl;
    std::cout << "Min: " << stats.min << std::endl;
    std::cout << "Max: " << stats.max << std::endl;
    std::cout << "Range: " << stats.range << std::endl << std::endl;

    std::cout << "Mean: " << stats.mean << std::endl;
    std::cout << "Median: " << stats.median << std::endl;
    std::cout << "Mode: " << stats.mode << std::endl << std::endl;

    if (file.fnSaveFile(v, stats))
    {
        std::cout << "The results have been saved to: " << file.fnGetPath();
    }
    else
    {
        std::cout << "This operation could not be saved as no file path has been provided.";
    }
}

/* Prompts the user to indicate how many integers should be stored,
loops through and stores each of the integers into a pointer array,
sorts the integers lowest to highest, then computes statistical values */
void Menu::fnSortStoreByPointer()
{
    int num;

    std::cout << "How many terms would you like to enter: "; std::cin >> num; std::cout << std::endl;

    //Dynamically allocate memory to create a new pointer array based on the user's input
    int* p;
    p = new int[num];

    for (int i = 1; i <= num; i++)
    {
        int value;
        std::cout << "Term " << i << ": "; std::cin >> value;
        p[(i - 1)] = value;
    }

    std::cout << std::endl;
    std::cout << "Provided data: ";

    for (int i = 0; i < num; i++)
    {
        std::cout << p[i] << " ";
    }

    std::cout << std::endl << "Sorted data:   ";
    std::sort(p, p+num);

    for (int i = 0; i < num; i++)
    {
        std::cout << p[i] << " ";
    }

    std::cout << std::endl << std::endl;

    fnDisplayPointerStats(p, num);

    //Frees the memory we dynamically allocated
    delete[] p;
}

/* Calculates the min, max, range, mean, median, displays the values to
the user and then stores them to a file if a path has been set */
void Menu::fnDisplayPointerStats(int p[], int len)
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
    std::vector<int> modeCounter;
    std::vector<Mode> modes;

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
            m.count = std::count(modeCounter.begin(), modeCounter.end(), number);
            modes.push_back(m);
        }

        //For just one mode we can assign it now
        if (modes.size() == 1) {
            stats.mode = modes.at(0).number;
        }
        //When we have more than one mode we'll need to see which occurs at the highest frequency
        else if (modes.size() > 1)
        {
            for (int i = 1; i < modes.size(); i++)
            {
                if (modes.at(i).count > modes.at(i - 1).count)
                {
                    stats.mode = modes.at(i).number;
                }
                //If they occur the same number of times then we'll just take the highest number for the mode
                else if (modes.at(i).count == modes.at(i - 1).count)
                {
                    stats.mode = modes.at(i).number;
                }
            }
        }

    }
    else
    {
        //If there are no duplicate values then we'll take the first number in the series
        stats.mode = p[0];
    }

    std::cout << "Statistical results" << std::endl;
    std::cout << "Min: " << stats.min << std::endl;
    std::cout << "Max: " << stats.max << std::endl;
    std::cout << "Range: " << stats.range << std::endl << std::endl;

    std::cout << "Mean: " << stats.mean << std::endl;
    std::cout << "Median: " << stats.median << std::endl;
    std::cout << "Mode: " << stats.mode << std::endl;

    if (file.fnSaveFile(p, len, stats))
    {
        std::cout << "The results have been saved to: " << file.fnGetPath();
    }
    else
    {
        std::cout << "This operation could not be saved as no file path has been provided.";
    }
}