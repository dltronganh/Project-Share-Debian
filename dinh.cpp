#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

#define NUM_MONTHS 12
#define NUM_CITIES 10
#define NUM_DATA_TYPES 3

//For choice
#define TEMPERATURE 0
#define RAINFALL 1
#define SUNSHINE 2

using namespace std;

/*Struct*/

//here we define a struct which store city information
//includes temperatures, rainfall, sunshine data in 12 months
struct CITY_INFO
{
    string cityName;
    double temperatures[NUM_MONTHS];
    double rainfalls[NUM_MONTHS];
    double sunshines[NUM_MONTHS];
};


/*Global variables*/
CITY_INFO cities[NUM_CITIES];
string monthNames[] = {"January","February","March","April","May","June","July","August","September","October","November","December"};

/*Heading*/

/*For reading files*/
bool getCitiesFromFile(string);
bool getTempsFromFile(string);
bool getRainfallFromFile(string);
bool getSunshineFromFile(string);
bool getDataFromFiles(string,string,string,string);

/*For printing*/
void printOpening();
void error(string);

void printCitiesMenu();
void printDataTypeMenu();
void printMonthMenu();

/*For user*/
bool getCitiesChoice(bool[]);
bool getDataTypeChoice(bool[]);
bool getMonthChoice(bool[]);

/*For checking*/
int checkCityNameExist(string);
bool checkExit();

/*For result*/
void printResult(bool[],bool[],bool[]);
void printTemperatureResult(int,bool[]);
void printRainfallResult(int,bool[]);
void printSunshineResult(int,bool[]);

/*End Heading*/

int main()
{
    //loading file path
    string city_file = "Data/cities.txt";
    string temp_file = "Data/temperatures";
    string rainfall_file = "Data/rainfall.txt";
    string sunshine_file = "Data/sunshine.txt";

    //get data
    bool isValidFile = getDataFromFiles(city_file,
                                        temp_file,
                                        rainfall_file,
                                        sunshine_file);

    if(isValidFile == false)
        return -1;

    printOpening();

    bool cities_choice[NUM_CITIES] = {false};
    bool datatype_choice[NUM_DATA_TYPES] = {false};
    bool months_choice[NUM_MONTHS] = {false};

    /*For user in loop*/

    while(true)
    {
        /*get user input*/

        if(getCitiesChoice(cities_choice) == false)
            continue;

        if(getDataTypeChoice(datatype_choice) == false)
            continue;

        if(getMonthChoice(months_choice) == false)
            continue;

        printResult(cities_choice,datatype_choice,months_choice);

        if(checkExit() == false)
            break;
    }

    return 0;
}

/*Definition*/

/*For printing*/
void printOpening()
{
    cout << "Welcome to CLIMATE++" << endl << endl;
}

void error(string message)
{
    cout << "[Error] " << message << endl;
}

void printCitiesMenu()
{
    cout << endl << "Choose the cities" << endl;

    for(int i = 0; i < NUM_CITIES; i++)
    {
        cout << cities[i].cityName << "(" << i + 1<< ") ";
    }

    cout << endl << "Your choice: ";
}

void printDataTypeMenu()
{
    cout << endl << "Choose the data" << endl;
    cout << "Temperature(1) Rainfall(2) Sunshine hours(3)" << endl;
    cout << "Your choice: ";
}

void printMonthMenu()
{
    cout << endl << "Choose the months" << endl;
    for(int i = 0; i < NUM_MONTHS; i++)
    {
        cout << monthNames[i] << "(" << i + 1 << ") ";
    }

    cout << endl << "Your choice: ";

}

/*For user*/
bool getCitiesChoice(bool cities_choice[])
{
    printCitiesMenu();

    //get user input
    string input;
    getline(cin,input);

    istringstream ss(input);

    int choice;
    int countValidInput = 0;

    while(ss >> choice)
    {
        //check if the input value is valid (positive and in the array)
        if(choice <= 0 || choice > NUM_CITIES)
        {
            continue;
        }

        cities_choice[choice - 1] = true;
        countValidInput++;
    }

    if(countValidInput == 0)
    {
        error("You have no valid input !");
        return false;
    }

    return true;
}

bool getDataTypeChoice(bool datatype_choice[])
{
    printDataTypeMenu();

    //get user input
    string input;
    getline(cin,input);

    istringstream ss(input);

    int choice;
    int countValidInput = 0;

    while(ss >> choice)
    {
        //check if the input value is valid (positive and in the array)
        if(choice <= 0 || choice > NUM_DATA_TYPES)
        {
            continue;
        }

        datatype_choice[choice - 1] = true;
        countValidInput++;
    }

    if(countValidInput == 0)
    {
        error("You have no valid input !");
        return false;
    }

    return true;
}

bool getMonthChoice(bool month_choice[])
{
    printMonthMenu();

    //get user input
    string input;
    getline(cin,input);

    istringstream ss(input);

    int choice;
    int countValidInput = 0;

    while(ss >> choice)
    {
        //check if the input value is valid (positive and in the array)
        if(choice <= 0 || choice > NUM_MONTHS)
        {
            continue;
        }

        month_choice[choice - 1] = true;
        countValidInput++;
    }

    if(countValidInput == 0)
    {
        error("You have no valid input !");
        return false;
    }

    return true;
}

/*For reading files*/
bool getCitiesFromFile(string city_file_path)
{
    ifstream file;
    file.open(city_file_path.c_str());

    if(!file)
    {
        error("Opening the city file failed. Make sure you have a correct file path");
        return false;
    }

    for(int i = 0; i < NUM_CITIES; i++)
    {
        file >> cities[i].cityName;
    }

    file.close();

    return true;
}

bool getTempsFromFile(string temp_file_path)
{
    ifstream file;
    file.open(temp_file_path.c_str());

    if(!file)
    {
        error("Opening the temperatures file failed. Make sure you have a correct file path");
        return false;
    }

    for(int i = 0; i < NUM_CITIES; i++)
    {
        string cityName;
        file >> cityName;

        //check if the city name exist in the cities.txt file, if not ==> show error
        int city_index = checkCityNameExist(cityName);
        if (city_index == -1)
        {
            error("The city [" + cityName + "] in the temperature file doesn't match any city in cities.txt file. Make sure you have a correct city name");
            return false;
        }

        for(int t = 0; t < NUM_MONTHS; t++)
        {
            file >> cities[city_index].temperatures[t];
        }
    }

    file.close();

    return true;
}

bool getRainfallFromFile(string rainfall_file_path)
{
    ifstream file;
    file.open(rainfall_file_path.c_str());

    if(!file)
    {
        error("Opening the rainfall file failed. Make sure you have a correct file path");
        return false;
    }

    for(int i = 0; i < NUM_CITIES; i++)
    {
        string cityName;
        file >> cityName;

        //check if the city name exist in the cities.txt file, if not ==> show error
        int city_index = checkCityNameExist(cityName);
        if (city_index == -1)
        {
            error("The city [" + cityName + "] in the rainfall file doesn't match any city in cities.txt file. Make sure you have a correct city name");
            return false;
        }

        for(int t = 0; t < NUM_MONTHS; t++)
        {
            file >> cities[city_index].rainfalls[t];
        }
    }

    file.close();

    return true;
}

bool getSunshineFromFile(string sunshine_file_path)
{
    ifstream file;
    file.open(sunshine_file_path.c_str());

    if(!file)
    {
        error("Opening the sunshine file failed. Make sure you have a correct file path");
        return false;
    }

    for(int i = 0; i < NUM_CITIES; i++)
    {
        string cityName;
        file >> cityName;

        //check if the city name exist in the cities.txt file, if not ==> show error
        int city_index = checkCityNameExist(cityName);
        if (city_index == -1)
        {
            error("The city [" + cityName + "] in the sunshine file doesn't match any city in cities.txt file. Make sure you have a correct city name");
            return false;
        }

        for(int t = 0; t < NUM_MONTHS; t++)
        {
            file >> cities[city_index].sunshines[t];
        }
    }

    file.close();

    return true;
}

bool getDataFromFiles(string city_file_path,
                      string temp_file_path,
                      string rainfall_file_path,
                      string sunshine_file_path)
{
    bool isValidFiles = false;

    /*zero means false, true otherwise. In this case, true will return 1
    If all files is valid, it means 1 + 1 + 1+ 1 = 4 and 4 / 4 == 1, this is true
    If one of them is invalid, it means the sum will be less than 4, so the divisor will return 0, this is false
    */
    isValidFiles = (getCitiesFromFile(city_file_path) +
                    getTempsFromFile(temp_file_path) +
                    getRainfallFromFile(rainfall_file_path) +
                    getSunshineFromFile(sunshine_file_path))/4;

    return isValidFiles;
}

/*For checking*/
int checkCityNameExist(string cityName)
{
    int pos;
    for(pos = NUM_CITIES - 1 ; pos >= 0; pos--)
    {
        if(cities[pos].cityName == cityName)
            break;
    }

    return pos;
}

bool checkExit()
{
    string answer;
    cout << "Do you want to continue (enter 'yes' or 'no')?";
    cin >> answer;

    while(answer != "yes" && answer != "no")
    {
        cout << "Do you want to continue (enter 'yes' or 'no')?";
        cin >> answer;
    }

    if(answer == "yes")
    {
        cin.ignore();
        return true;
    }

    return false;
}

/*For result*/
void printResult(bool cities_choice[],bool datatype_choice[],bool months_choice[])
{
    cout << "---------------------------------------------------------" << endl;

    for(int i = 0; i < NUM_CITIES; i++)
    {
        if(cities_choice[i] == true)
        {
            cout << "Data for " << cities[i].cityName << ":" << endl;

            //get data type
            for(int d = 0; d < NUM_DATA_TYPES; d++)
            {
                if(datatype_choice[d] == true)
                {
                    switch(d)
                    {
                    case TEMPERATURE:
                        printTemperatureResult(i,months_choice);
                        break;

                    case RAINFALL:
                        printRainfallResult(i,months_choice);
                        break;

                    case SUNSHINE:
                        printSunshineResult(i,months_choice);
                        break;
                    }

                    cout << endl;
                }
            }

            cout << "---------------------------------------------------------" << endl;
        }
    }
}

void printTemperatureResult(int city_pos,bool month_choice[])
{
    int num_month_choice = 0;
    int sum = 0;
    int max = 0, min = 0;

    cout << "Temperature:" << endl;

    //print temperature of month
    for(int i = 0; i < NUM_MONTHS; i++)
    {
        if(month_choice[i] == true)
        {
            cout << "\t" << cities[city_pos].temperatures[i] << "\t";
        }
    }

    cout << endl;

    //print name of month
    for(int i = 0; i < NUM_MONTHS; i++)
    {
        if(month_choice[i] == true)
        {
            cout << "\t" << monthNames[i] << "\t";
        }
    }

    cout << endl;

    //calculation
    for(int i = 0; i < NUM_MONTHS; i++)
    {
        if(month_choice[i] == true)
        {
            //determine max min value
            if(cities[city_pos].temperatures[i] > cities[city_pos].temperatures[max])
            {
                max = i;
            }
            else if (cities[city_pos].temperatures[i] < cities[city_pos].temperatures[min])
            {
                min = i;
            }

            sum += cities[city_pos].temperatures[i];
            num_month_choice++;
        }
    }

    double average = static_cast<double>(sum)/num_month_choice;

    //print calculation
    cout << fixed << showpoint << setprecision(2);
    cout << "Minimum value occurs in " << monthNames[min] << ": " << cities[city_pos].temperatures[min] << endl;
    cout << "Maximum value occurs in " << monthNames[max] << ": " << cities[city_pos].temperatures[max] << endl;
    cout << "Average value: " << average << endl;
}

void printRainfallResult(int city_pos,bool month_choice[])
{
    int num_month_choice = 0;
    int sum = 0;
    int max = 0, min = 0;

    cout << "Rainfall:" << endl;

    //print temperature of month
    for(int i = 0; i < NUM_MONTHS; i++)
    {
        if(month_choice[i] == true)
        {
            cout << "\t" << cities[city_pos].rainfalls[i] << "\t";
        }
    }

    cout << endl;

    //print name of month
    for(int i = 0; i < NUM_MONTHS; i++)
    {
        if(month_choice[i] == true)
        {
            cout << "\t" << monthNames[i] << "\t";
        }
    }

    cout << endl;

    //calculation
    for(int i = 0; i < NUM_MONTHS; i++)
    {
        if(month_choice[i] == true)
        {
            //determine max min value
            if(cities[city_pos].rainfalls[i] > cities[city_pos].rainfalls[max])
            {
                max = i;
            }
            else if (cities[city_pos].rainfalls[i] < cities[city_pos].rainfalls[min])
            {
                min = i;
            }

            sum += cities[city_pos].rainfalls[i];
            num_month_choice++;
        }
    }

    double average = static_cast<double>(sum)/num_month_choice;

    //print calculation
    cout << fixed << showpoint << setprecision(2);
    cout << "Minimum value occurs in " << monthNames[min] << ": " << cities[city_pos].rainfalls[min] << endl;
    cout << "Maximum value occurs in " << monthNames[max] << ": " << cities[city_pos].rainfalls[max] << endl;
    cout << "Average value: " << average << endl;
}

void printSunshineResult(int city_pos,bool month_choice[])
{
    int num_month_choice = 0;
    int sum = 0;
    int max = 0, min = 0;

    cout << "Sunshine hours:" << endl;

    //print temperature of month
    for(int i = 0; i < NUM_MONTHS; i++)
    {
        if(month_choice[i] == true)
        {
            cout << "\t" << cities[city_pos].sunshines[i] << "\t";
        }
    }

    cout << endl;

    //print name of month
    for(int i = 0; i < NUM_MONTHS; i++)
    {
        if(month_choice[i] == true)
        {
            cout << "\t" << monthNames[i] << "\t";
        }
    }

    cout << endl;

    //calculation
    for(int i = 0; i < NUM_MONTHS; i++)
    {
        if(month_choice[i] == true)
        {
            //determine max min value
            if(cities[city_pos].sunshines[i] > cities[city_pos].sunshines[max])
            {
                max = i;
            }
            else if (cities[city_pos].sunshines[i] < cities[city_pos].sunshines[min])
            {
                min = i;
            }

            sum += cities[city_pos].sunshines[i];
            num_month_choice++;
        }
    }

    double average = static_cast<double>(sum)/num_month_choice;

    //print calculation
    cout << fixed << showpoint << setprecision(2);
    cout << "Minimum value occurs in " << monthNames[min] << ": " << cities[city_pos].sunshines[min] << endl;
    cout << "Maximum value occurs in " << monthNames[max] << ": " << cities[city_pos].sunshines[max] << endl;
    cout << "Average value: " << average << endl;
}
