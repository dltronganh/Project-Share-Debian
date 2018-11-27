
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

// path of the folder containing the data files
const string REPOSITORY = "C:\\your\\folder\\path\\here\\";

// name of the file recording the name of the cities
const string CITY_NAME_FILE = "cities.txt";

// number of cities
const int MAX_CITY = 10;

// the name of cities
string CITY_NAME[MAX_CITY];

// number of month
const int MAX_MONTH = 12;

// the name of month
const string MONTH_NAME[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

// number of data type
const int MAX_DATATYPE = 3;

// the name of data type
const string DATATYPE_NAME[] = {  "Temperature", "Rainfall", "Sunshine hours" };

// the name of the data file (these files are in the folder REPOSITORY)
const string DATATYPE_FILE[] = { "temperature.txt", "rainfall.txt", "sunshine.txt" };

// the database (contains all the content of all data file)
// DATABASE[data][city][month] is the value of
// the data number 'data' for month number 'month' for city number 'city'
double DATABASE[MAX_DATATYPE][MAX_CITY][MAX_MONTH];

void initialize(bool[], int); 
void print_out(string, string);
void analyzeInput(string, bool[], int);
void display(bool[], bool[], bool[]);
int print_out2(bool[]);
int openFile(bool[], ifstream&);
bool more();

int main()
{
    ifstream inFile;
    string input;
    bool setCity[MAX_CITY], setDatatype[MAX_DATATYPE], setMonth[MAX_MONTH];
    initialize(setCity,MAX_CITY);
    initialize(setDatatype,MAX_DATATYPE);
    initialize(setMonth,MAX_MONTH);

/*-------------------------------------------------------------------------------*/
    inFile.open(CITY_NAME_FILE.c_str());
    for (int i=0; i<MAX_CITY; i++)
        inFile >> CITY_NAME[i];
    inFile.close();
    cout << "Welcome to CLIMATE++\n" << endl;
    do{
    print_out("cities", "Austin(1) Boston(2) Chicago(3) Fresno(4) Houston(5) Indianapolis(6) Memphis(7) Nashville(8) Phoenix(9) Washington(10)");
    analyzeInput(input, setCity, MAX_CITY);
    print_out("datatype", "temperature(1) rainfall(2) sunshine hours(3)");
    analyzeInput(input, setDatatype, MAX_DATATYPE);
    print_out("month", "January(1) February(2) March(3) April(4) May(5) June(6) July(7) August(8) September(9) October(10) November(11) December(12)");
    analyzeInput(input, setMonth, MAX_MONTH);
    display(setCity, setDatatype, setMonth);
    } while (more());
    cout << "\n\nThank you for using CLIMATE++" << endl;
    return 0;
}

void initialize(bool set[], int max)
{
    for(int i=0; i<max; i++)
	set[i]=false;
}

void print_out(string name, string inf)
{
   cout << "Choose the " << name << endl
        << inf << endl
        << "Your choice: ";
}

void analyzeInput(string input, bool set[], int max)
{
    getline(cin,input);
    istringstream iss(input);
    int n;
    while (iss >> n)
	if (0<n && n<=max && !set[n-1])
	    set[n-1]=true;
}

void display(bool setCity[], bool setDatatype[], bool setMonth[])
{
    ifstream inFile;
    string name;
    int l=0;
    double m;
    int n=print_out2(setCity);
    int k=openFile(setDatatype, inFile);
    while (inFile >> name)
	if (name == CITY_NAME[n])
	    break;
    cout << DATATYPE_NAME[k] << ":" << endl;
    for (int i=0; i<MAX_MONTH; i++)
	if (setMonth[i])
        {
	    for (;l=i;l++)
		inFile >> m; 
	    cout << setw(10) << m;
	} 
}

int print_out2(bool set[])
{
    cout << "---------------------------------------" << endl;
    int i=0;
    while ((i<MAX_CITY) && (!set[i]))
	i++;
    cout << "Data for " << CITY_NAME[i] << ":\n" << endl << endl;
    set[i]=false;
    return i;
}

int openFile(bool set[], ifstream &inFile)
{
    int i=0;
    while ((i<MAX_DATATYPE) && (!set[i]))
	i++;
    inFile.open(DATATYPE_FILE[i].c_str());
    set[i]=false;
    return i;
}

bool more()
{
    string choice;
    do
    {
	cout << "---------------------------------------------------" << endl
             << "Do you want to continue (enter 'yes' or 'no')? ";
        cin >> choice;
        cin.ignore();
        if (choice == "yes")
            return true;
    } while (choice!="no");
    return false;
}
