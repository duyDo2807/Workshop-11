#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// vector of int.
// used to store the records
typedef vector<int> Records;

class RecordsManager {
 private:
  fstream _file;
  string _filename;

 public:
  RecordsManager(string filename) : _filename(filename) {}

  void read(Records &records) {
    try {
      _file.open(_filename, ios::in);
      if (_file.is_open()) {
        string line;
        while (std::getline(_file, line)) {
          try {
            records.push_back(stoi(line));
          } catch (const invalid_argument &e) {
            // Handle invalid argument exception
            _file.close();
            throw runtime_error("Wrong argument when reading the file: " +
                                string(e.what()));
          } catch (const out_of_range &e) {
            // Handle out of range exception
            _file.close();
            throw runtime_error("Out of range when reading the file: " +
                                string(e.what()));
          }
        }
        _file.close();
      } else {
        throw runtime_error("Failed to open the file.");
      }
    } catch (const runtime_error &e) {
      // Propagate the exception to the calling function (main)
      throw;
    }
  }
};

int main() {
  try {
    RecordsManager receordM("test_corrupt1.txt");
    Records myRecords;
    // reads records
    receordM.read(myRecords);
    // calculate and print out the sum
    int sum = 0;
    for (int i = 0; i < myRecords.size(); i++) {
      sum += myRecords[i];
    }
    cout << "Sum: " << sum << endl;
  } catch (const runtime_error &e) {
    // Handle and display the error message at the main function level
    cerr << "Error: " << e.what() << endl;
  }

  return 0;
}