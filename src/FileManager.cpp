#include "FileManager.h"
#include <fstream>
#include <sstream>

FileManager::FileManager()
{
    this->dataDirectory = "data/";
}

bool FileManager::readRecords(const string& fileName, vector<Record>& records) const
{
    ifstream inFile((dataDirectory + fileName));
    if (!inFile)
    {
        return false;
    }

    string line;
    while (getline(inFile, line))
    {
        if (line.empty())
        {
            continue;
        }
        
        Record record;
        stringstream ss(line);
        string field;
        while (getline(ss, field, '|'))
        {
            record.push_back(field);
        }
        records.push_back(record);
    }
    return true;
}

bool FileManager::writeRecords(const string& fileName, const vector<Record>& records) const
{
    ofstream outFile((dataDirectory + fileName));
    if (!outFile)
    {
        return false;
    }

    for (int i = 0; i < records.size(); i++)
    {
        for (int j = 0; j < records[i].size(); j++)
        {
            if (j > 0)
            {
                outFile << '|';
            }
            outFile << records[i][j];
        }
        outFile << endl;
    }
    return true;
}