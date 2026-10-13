#include "FileManager.h"
#include <iostream>
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

bool FileManager::loadStudents(EventSystem& system) const
{
    vector<Record> rows;
    if (!readRecords("students.txt", rows))
    {
        return false;   // no file yet, start with no students
    }

    for (int i = 0; i < rows.size(); i++)
    {
        if (rows[i].size() != 4)
        {
            cout << "Skipping bad line in students.txt" << endl;
            continue;
        }
        system.addStudent(rows[i][0], rows[i][1], rows[i][2], rows[i][3]);
    }
    return true;
}

bool FileManager::saveStudents(const EventSystem& system) const
{
    vector<Record> rows;
    const vector<unique_ptr<Student>>& students = system.getStudents();

    for (int i = 0; i < students.size(); i++)
    {
        rows.push_back({ students[i]->getId(), students[i]->getName(),
                         students[i]->getEmail(), students[i]->getMajor() });
    }
    return writeRecords("students.txt", rows);
}