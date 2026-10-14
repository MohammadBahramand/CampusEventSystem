//================FileManager.h==================
//Handles saving and loading all program data so nothing is lost
//when the program closes.
//
//Every file is plain text with one record per line, and the fields
//in a line are separated by '|'. For example:
//    S1001|Maria Lopez|mlopez@student.ivc.edu|Computer Science
//
//FileManager doesn't own any data. It is handed the EventSystem
//by reference, reads from it when saving, and fills it when loading.
//================================================

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include "EventSystem.h"
#include "RegistrationManager.h"

using namespace std;

using Record = vector<string>;

class FileManager {
public:
    //Sets folder where all data is kept (data/)
    FileManager();

    //helpers that every load/save function uses
    //readRecords splits each line of a file into a Record.
    //writeRecords joins each Record with '|' and writes one per line.
    //both return false if the file cannot be opened.
    bool readRecords(const string& filename, vector<Record>& records) const;
    bool writeRecords(const string& filename, const vector<Record>& records) const;

    //load funcs return false if file does not exist
    bool loadStudents(EventSystem& system) const;
    bool saveStudents(const EventSystem& system)const;

    bool loadOrganizers(EventSystem& system) const;
    bool saveOrganizers(const EventSystem& system) const;

    //registrations live in RegistrationManager, so these take that instead of EventSystem
    bool loadRegistrations(RegistrationManager& manager) const;
    bool saveRegistrations(const RegistrationManager& manager) const;

    //Events saved with a type tag so loading knows which subclass to rebuild.
    bool loadEvents(EventSystem& system) const;
    bool saveEvents(const EventSystem& system) const;

    //Loads every file in the order the data depends on each other (organizers->students->events->registrations).
    void loadAll(EventSystem& system) const;

    //Saves every file and returns false if any file could not be written.
    bool saveAll(const EventSystem& system) const;
private:
    //folder the data files are in
    string dataDirectory;
};

#endif