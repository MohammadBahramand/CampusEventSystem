# Campus Event Management System

A console-based C++ application for managing campus events. Students can be added and registered for events, organizers can create and manage events, and the system can produce reports about attendance. All data is saved to text files when the program exits and loaded again when it starts.

## Project Overview

Colleges run a lot of events: workshops, guest lectures, club meetings, career fairs, study sessions and social events. This program keeps track of:

- **Students** who can sign up for events
- **Organizers** who run events
- **Events** of four different types (Academic, Career, Club, Social)
- **Registrations** that connect students to the events they signed up for

The program checks the rules for every registration. It refuses a registration if the student or event doesn't exist, if the student is already signed up, or if the event is full.

## Team Members

| Name | GitHub | Primary Responsibilities |
|---|---|---|
| Mohammad Bahramand | MohammadBahramand | Repository setup, `Student` class, `EventSystem` (storage for students, organizers and events, registration integration, reports, event search), reviewing and merging PRs |
| Devon Nghiem | DevonNghiem | `Organizer` class, main menu and console interface (`main.cpp`), UML class diagram |
| Jeremy Huang | Synsepalum | `FileManager` and data persistence (loading and saving all four data files), sample data, documentation |
| Vikunwat Lav | viav0 | `Event` base class, `AcademicEvent`, `ClubEvent` |
| Mahir Altuntas | mahiraltuntas | `CareerEvent`, `SocialEvent` |
| Abdullah Shafi | abdullah-shafi2007 | `Registration` and `RegistrationManager` (duplicate and capacity checks, cancellation) |

## Features

- Add students and organizers (duplicate IDs are rejected)
- View all students
- Create events of four types, each with its own extra details
- View all events, with each event type showing its own details
- Search events by name (matches part of the name)
- Register a student for an event, with checks for:
  - student exists
  - event exists
  - student is not already registered
  - event is not full
- Cancel a registration
- View a student's registered events and an event's registered students
- View the events run by a specific organizer
- Four reports:
  1. Events with available capacity
  2. Full events
  3. Number of students registered for each event
  4. Students registered for multiple events
- Automatic saving on exit and loading on startup
- Input validation, so typing letters where a number is expected does not crash the program

## Class Design

| Class | Responsibility |
|---|---|
| `Student` | Holds one student's ID, name, email and major |
| `Organizer` | Holds one organizer's ID, name, email and department |
| `Event` | Base class for all events. Holds the shared fields (ID, name, description, date, time, location, organizer ID, capacity) and a virtual `displayDetails()` |
| `AcademicEvent` | Event with a department and speaker |
| `CareerEvent` | Event with a company name and recruiter name |
| `ClubEvent` | Event with a club name |
| `SocialEvent` | Event with a theme and whether food is provided |
| `Registration` | Links one student ID to one event ID, with a registration date and an active/canceled status |
| `RegistrationManager` | Owns all registrations and enforces the registration rules (duplicates, capacity, cancellation) |
| `EventSystem` | Owns all students, organizers and events, and coordinates the rest of the program (lookups, displays, reports, search) |
| `FileManager` | Reads and writes the data files and rebuilds the objects when the program starts |

`main.cpp` shows the menu, reads the user's input and calls into these classes.

See [docs/DESIGN.md](docs/DESIGN.md) for the full design explanation and [docs/](docs/) for the UML class diagram.

## Building

The project needs a C++17 compiler.

**g++ (Linux, macOS, or Windows with MinGW):**

From the top folder of the repository, run:

```
g++ -std=c++17 -Iinclude src/*.cpp -o CampusEventSystem
```

**Visual Studio:**

1. Create an empty C++ console project.
2. Add every file in `src/` as a source file and every file in `include/` as a header file.
3. In Project Properties, add the `include` folder under C/C++ → General → Additional Include Directories.
4. Set the C++ Language Standard to C++17.
5. Set the working directory (Debugging → Working Directory) to the repository's top folder so the program can find `data/`.

## Running

Run the program **from the top folder of the repository**, because it looks for its data in `data/`:

```
./CampusEventSystem        (Linux / macOS)
CampusEventSystem.exe      (Windows)
```

A menu appears:

```
1. Add Student
2. View Students
3. Create Event
4. View Events
5. Search Events
6. Register Student for Event
7. Cancel Registration
8. View Student Registrations
9. View Event Attendees
10. Add Organizer
11. View Organizers
12. View Events by Organizer
13. System Reports
0. Exit
```

Type a number and press Enter. An event's organizer must already exist before the event can be created, so add organizers first when starting with no data. Choose **0** to save and exit. Data is only saved when the program exits through option 0.

The repository includes sample data, so the program starts with 6 students, 3 organizers, 7 events (all four types) and 13 registrations. One event (E106, Calculus Study Session) is already full, which is useful for showing that a full event rejects new registrations.

## Data Storage

Data is stored in four plain text files in the `data/` folder. Each line is one record, and fields are separated by `|`.

| File | Format |
|---|---|
| `students.txt` | `studentID\|name\|email\|major` |
| `organizers.txt` | `organizerID\|name\|email\|department` |
| `events.txt` | `TYPE\|eventID\|name\|description\|date\|time\|location\|organizerID\|capacity\|extra fields...` |
| `registrations.txt` | `studentID\|eventID\|registrationDate\|active` (`1` = active, `0` = canceled) |

The extra fields at the end of an event line depend on its type:

- `ACADEMIC` → department, speaker
- `CAREER` → company name, recruiter name
- `CLUB` → club name
- `SOCIAL` → theme, food provided (`1` or `0`)

On startup the files are loaded in this order: organizers, students, events, registrations. Events need their organizer to exist, and registrations need their student and event. If a file is missing, the program starts with no data of that kind. If a line is broken, it is skipped with a message and the rest of the file still loads.

## Known Limitations

- Text fields cannot contain the `|` character because it is used to separate fields in the data files. A name with `|` in it gets saved incorrectly and is skipped the next time the program starts.
- The program must be run from the repository's top folder, or it won't find `data/` and will not be able to save.
- Event search is case-sensitive. Searching "robotics" will not find "Introduction to Robotics".
- Dates and times are stored as text and are not checked for a valid format.
- Students, organizers and events cannot be edited or deleted after they are added.
- Data is only saved when exiting through the menu. Closing the window or crashing loses changes from that session.
- Registrations loaded from the file are not checked against existing students and events. If a student or event is removed from the files by hand, its registrations show the raw ID instead of a name.
