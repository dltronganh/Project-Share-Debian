
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
void display(string, string, string);
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
    //display(input1, input2, input3);
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

void display(bool set1[], bool set2[], bool set3[])
{
    int Count[MAX_MONTH];
    ifstream inFile;
    string in;
    int n1, n2, n3, cmin, cmax, count, k, i=0;
    double min, max, average=0, n;
    while (i<MAX_CITY)
    	if (set1[i])
        {
        cout << "-----------------------------------------------------" << endl
             << "Data for " << CITY_NAME[i-1] << ":\n" << endl;
            {
            inFile.open(DATATYPE_FILE[n2-1].c_str());
            do{
            inFile >> in;
            }
            while (in!=CITY_NAME[n1-1]);
            cout << DATATYPE_NAME[n2-1] << ":" << endl;
            istringstream iss3(input3);
            iss3 >> n3;
            for (int i=0; i<n3; i++)
                inFile >> n;
            cout << setw(10) << n;
            min=n; max=n; average=n; cmin=n3; cmax=n3; count=1; Count[0]=n3; k=n3;
            while (iss3 >> n3)
            {
                for (int i=k; i<n3; i++)
                    inFile >> n;
                cout << setw(10) << fixed << showpoint << setprecision(2) << n;
                if (n<min) {min=n; cmin=n3;}
                if (n>max) {max=n; cmax=n3;}
                average+=n;
                Count[count]=n3;
                count++;
                k=n3;
            }
            inFile.close();
            cout << endl;
            for (int i=0; i<count; i++)
                cout << setw(10) << fixed << showpoint << setprecision(2) << MONTH_NAME[Count[i]-1];
            cout << "\nMinimum value occurs in " << MONTH_NAME[cmin-1] << ": " << fixed << showpoint << setprecision(2) << min << endl
                 << "Maximum value occurs in " << MONTH_NAME[cmax-1] << ": " << fixed << showpoint << setprecision(2) << max << endl
                 << "Average value: " << fixed << showpoint << setprecision(2) << average/count << endl << endl;
        }
        cout << "\n-----------------------------------------------------" << endl;
    }
}

bool more()
{
    string choice;
    do
    {
        cout << "Do you want to continue (enter 'yes' or 'no')? ";
        cin >> choice;
        cin.ignore();
        if (choice == "yes")
            return true;
    } while (choice!="no");
    return false;
}
