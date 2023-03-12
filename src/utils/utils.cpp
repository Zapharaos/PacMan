//
// Created by mfrei on 11/03/2023.
//

#include "../../include/utils/utils.h"

#include <fstream>

using json = nlohmann::json;

vector<CellType> loadCellTypesFromFile(const string &file_path)
{
    vector<CellType> cell_types;
    ifstream file; // indata is like cin
    char value; // variable for input value

    file.open(file_path); // opens the file
    if (!file)
    { // file couldn't be opened
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    file >> value;
    while (!file.eof())
    { // keep reading until end-of-file
        cell_types.emplace_back((CellType) strtol(&value, nullptr, 10));
        file >> value; // sets EOF flag if no value found
    }
    file.close();
    return cell_types;
}