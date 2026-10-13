#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include "EventSystem.h"

using namespace std;

using Record = vector<string>;

class FileManager {
public:
    FileManager();

    bool readRecords(const string& filename, vector<Record>& records) const;
    bool writeRecords(const string& filename, const vector<Record>& records) const;

    bool loadStudents(EventSystem& system) const;
    bool saveStudents(const EventSystem& system)const;

private:
    string dataDirectory;
};

#endif