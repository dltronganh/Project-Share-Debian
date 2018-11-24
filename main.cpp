#include <iostream>
#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

int check_file_exist() {
  ifstream rainfall("rainfall.txt");
  ifstream temperature("temperature.txt");
  ifstream sunshine_hours("sunshine.txt");

  if (rainfall.fail() || temperature.fail() || sunshine_hours.fail()){return 0;}
  else{return 1;}
}

string get_specific_line(int line, string fileInput){
    string line_get;
    ifstream file_open;
    file_open.open(fileInput.c_str());
    for (int i=1; i <= line; i++){
        getline(temperature, line_get);
    }
    temperature.close();
    return line_get;
}

int main()
{
  cout << "Hello this is my bullshit file to test get a specific file" << endl;
  if(check_file_exist()){
        cout << "ok" << endl;
        cout << get_specific_line(3, "temperature.txt") << endl;
        cout << get_specific_line(4, "temperature.txt") << endl;
    }
  else{
        cout << "fail";
  }


}
