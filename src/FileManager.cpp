//================FileManager.cpp==================
//Reads and writes the four data files:
//    students.txt       id|name|email|major
//    organizers.txt     id|name|email|department
//    events.txt         TYPE|id|name|description|date|time|location|organizerID|capacity|extra fields
//    registrations.txt  studentId|eventId|date|active (1 or 0)
//==================================================

#include "FileManager.h"
#include "AcademicEvent.h"
#include "CareerEvent.h"
#include "ClubEvent.h"
#include "SocialEvent.h"
#include <iostream>
#include <fstream>
#include <sstream>

//all files are kept in the data/ folder
FileManager::FileManager()
{
    this->dataDirectory = "data/";
}

//reads file one line at a time and splits each line on '|'
//returns false if file cannot be opened
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

//writes each record as one line with '|' between fields
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

//loads students from students.txt and adds them to the EventSystem
bool FileManager::loadStudents(EventSystem& system) const
{
    vector<Record> rows;
    if (!readRecords("students.txt", rows))
    {
        return false;
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

//turns every student into a record and writes them to students.txt
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

//same idea as loadStudents, but for organizers
bool FileManager::loadOrganizers(EventSystem& system) const
{
    vector<Record> rows;
    if (!readRecords("organizers.txt", rows))
    {
        return false;
    }

    for (int i = 0; i < rows.size(); i++)
    {
        if (rows[i].size() != 4)
        {
            cout << "Skipping bad line in organizers.txt" << endl;
            continue;
        }
        system.addOrganizer(rows[i][0], rows[i][1], rows[i][2], rows[i][3]);
    }
    return true;
}

//same idea as saveStudents, but for organizers
bool FileManager::saveOrganizers(const EventSystem& system) const
{
    vector<Record> rows;
    const vector<unique_ptr<Organizer>>& organizers = system.getOrganizers();

    for (int i = 0; i < organizers.size(); i++)
    {
        rows.push_back({ organizers[i]->getOrganizerID(), organizers[i]->getName(),
                         organizers[i]->getEmail(), organizers[i]->getDepartment() });
    }
    return writeRecords("organizers.txt", rows);
}

//registrations live in RegistrationManager, so these take that instead of EventSystem
bool FileManager::loadRegistrations(RegistrationManager& manager) const
{
    vector<Record> rows;
    if (!readRecords("registrations.txt", rows))
    {
        return false;
    }

    for (int i = 0; i < rows.size(); i++)
    {
        if (rows[i].size() != 4)
        {
            cout << "Skipping bad line in registrations.txt" << endl;
            continue;
        }
        bool active = (rows[i][3] == "1");
        manager.addLoadedRegistration(Registration(rows[i][0], rows[i][1], rows[i][2], active));
    }
    return true;
}


//turns every registration into a record and writes them to registrations.txt
bool FileManager::saveRegistrations(const RegistrationManager& manager) const
{
    vector<Record> rows;
    const vector<Registration>& registrations = manager.getAllRegistrations();

    for (int i = 0; i < registrations.size(); i++)
    {
        string active = registrations[i].isActive() ? "1" : "0";
        rows.push_back({ registrations[i].getStudentId(), registrations[i].getEventId(),
                         registrations[i].getRegistrationDate(), active });
    }
    return writeRecords("registrations.txt", rows);
}

//The first field is the event type. It decides which subclass to build and how many fields the line should have:
//Every event is handed to EventSystem as a unique_ptr, so EventSystem becomes its owner.
//==================================================
bool FileManager::loadEvents(EventSystem& system) const
{
    vector<Record> rows;
    if (!readRecords("events.txt", rows))
    {
        return false;
    }

    for (int i = 0; i < rows.size(); i++)
    {
        Record& r = rows[i];

        if (r.size() < 10)
        {
            cout << "Skipping bad line in events.txt" << endl;
            continue;
        }

        int capacity;
        try
        {
            capacity = stoi(r[8]);
        }
        catch (...)
        {
            cout << "Skipping event with bad capacity in events.txt" << endl;
            continue;
        }

        string type = r[0];
        if (type == "ACADEMIC" && r.size() == 11)
        {
            system.addEvent(make_unique<AcademicEvent>(r[1], r[2], r[3], r[4], r[5], r[6], r[7],
                                                       capacity, r[9], r[10]));
        }
        else if (type == "CAREER" && r.size() == 11)
        {
            system.addEvent(make_unique<CareerEvent>(r[1], r[2], r[3], r[4], r[5], r[6], r[7],
                                                     capacity, r[9], r[10]));
        }
        else if (type == "CLUB" && r.size() == 10)
        {
            system.addEvent(make_unique<ClubEvent>(r[1], r[2], r[3], r[4], r[5], r[6], r[7],
                                                   capacity, r[9]));
        }
        else if (type == "SOCIAL" && r.size() == 11)
        {
            system.addEvent(make_unique<SocialEvent>(r[1], r[2], r[3], r[4], r[5], r[6], r[7],
                                                     capacity, r[9], r[10] == "1"));
        }
        else
        {
            cout << "Skipping bad line in events.txt" << endl;
        }
    }
    return true;
}

//turns every event into a record and writes them to events.txt
bool FileManager::saveEvents(const EventSystem& system) const
{
    vector<Record> rows;
    const vector<unique_ptr<Event>>& events = system.getEvents();

    for (int i = 0; i < events.size(); i++)
    {
        Event* e = events[i].get();

        Record row = { "", e->getEventID(), e->getName(), e->getDescription(),
                       e->getDate(), e->getTime(), e->getLocation(),
                       e->getOrganizerID(), to_string(e->getCapacity()) };

        if (AcademicEvent* a = dynamic_cast<AcademicEvent*>(e))
        {
            row[0] = "ACADEMIC";
            row.push_back(a->getDepartment());
            row.push_back(a->getSpeaker());
        }
        else if (CareerEvent* c = dynamic_cast<CareerEvent*>(e))
        {
            row[0] = "CAREER";
            row.push_back(c->getCompanyName());
            row.push_back(c->getRecruiterName());
        }
        else if (ClubEvent* c = dynamic_cast<ClubEvent*>(e))
        {
            row[0] = "CLUB";
            row.push_back(c->getClubName());
        }
        else if (SocialEvent* s = dynamic_cast<SocialEvent*>(e))
        {
            row[0] = "SOCIAL";
            row.push_back(s->getTheme());
            row.push_back(s->isFoodProvided() ? "1" : "0");
        }
        else
        {
            continue;
        }

        rows.push_back(row);
    }
    return writeRecords("events.txt", rows);
}

//Loads every file in the order the data depends on each other (organizers->students->events->registrations).
void FileManager::loadAll(EventSystem& system) const
{
    loadOrganizers(system);
    loadStudents(system);
    loadEvents(system);
    loadRegistrations(system.getRegistrationManager());
}


//Saves every file and returns false if any file could not be written.
bool FileManager::saveAll(const EventSystem& system) const
{
    return saveOrganizers(system)
        && saveStudents(system)
        && saveEvents(system)
        && saveRegistrations(system.getRegistrationManager());
}