/**
 * Project: Baa Corporate Bond Rate Analyzer
 * Author: Thanh Vy Vo
 * Description: Reads historical Moody's Baa seasoned corporate bond yield data,
 * parses time periods and yields into structured vectors, and provides interactive 
 * historical querying and comparison against the all-time average yield rate.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

double average(vector<double> v)
{
   if (v.empty())
   {
      return 0.0;
   }
   double sum = 0;
   for (size_t i = 0; i < v.size(); i++)
   {
      sum = sum + v[i];
   }
   double result = sum / v.size();
   return result; 
}

double find_rate(vector<double> rate_vec, vector<string> date_vec, string date)
{
   for (size_t j = 0; j < date_vec.size(); j++)
   {
      if (date_vec[j] == date)
      {
         return rate_vec[j];
      }
   }
   return -1; // return -1 if unable to match date
}

int main(int argc, char* argv[])
{
    vector<double> rate;
    vector<string> date;

    string filepath = "data/H.15_Baa_Data.csv";
    if (argc > 1)
    {
       filepath = argv[1];
    }

    ifstream infile(filepath);
    if (!infile.is_open())
    {
       // Fallback check if executed from build/ directory
       infile.open("../data/H.15_Baa_Data.csv");
    }
    if (!infile.is_open())
    {
       // Fallback check in current working directory
       infile.open("H.15_Baa_Data.csv");
    }

    if (infile.is_open()) 
    { 
       string line;
       int line_count = 0;

       while (getline(infile, line)) 
       {
          line_count++;
          if (line_count <= 6) // skip the first 6 lines of headers 
          {
             continue;
          }
          if (line.empty())
          {
             continue;
          }
          int comma_pos = line.find(',');
          if (comma_pos == (int)string::npos)
          {
             continue;
          }
          string sub1 = line.substr(0, comma_pos); // create a sub-string for date
          string sub2 = line.substr(comma_pos + 1, string::npos); // create a sub-str for rate
          date.push_back(sub1);
          double rate_value = stod(sub2); // convert rate value from string to double
          rate.push_back(rate_value); 
       }
       infile.close();
    } 
    else 
    {
       cerr << "[Error] Unable to open data file: " << filepath << endl;
       cerr << "Usage: " << argv[0] << " [path/to/H.15_Baa_Data.csv]" << endl;
       return 1;
    }

    if (rate.empty())
    {
       cerr << "[Error] No valid rate data found in file." << endl;
       return 1;
    }

    double avg_rate = average(rate);
    while (true)
    {
       string input;
       cout << "Enter date (yyyy-mm) or press Ctrl+D to exit: " << endl;
       cin >> input; 
       if (cin.eof())
       {
          break; // break the loop if user inputs EOF
       }
       double matched_rate = find_rate(rate, date, input);
       if (matched_rate == -1)
       {
          cerr << "[Error] Date not found or format is invalid. Expected format: yyyy-mm (e.g. 1981-09)" << endl;
          continue; // back to the start of the loop 
       }
       cout << "The annual rate for the input date is " << matched_rate << "%" << endl;
       if (matched_rate > avg_rate)
       {
          cout << "The annual rate for the input date is higher than "
               << "the average rate by " << matched_rate - avg_rate << "%" << endl;
       }
       else if (matched_rate == avg_rate)
       {
          cout << "The annual rate for the input date is equal to "
               << "the average rate" << endl;
       }
       else 
       {
          cout << "The annual rate for the input date is lower than "
               << "the average rate by " << avg_rate - matched_rate << "%" << endl;
       }

    }
   
    return 0; // program end
}


