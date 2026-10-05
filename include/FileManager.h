#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>

using namespace std;

using Record = vector<string>;

class FileManager {
public:
    FileManager(const string& dataDirectory = "data");

    bool readRecords(const string& filename, vector<Record>& records) const;
    bool writeRecords(const string& filename, const vector<Record>& records) const;

private:
    string dataDirectory;
};

#endif