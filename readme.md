Hotel

Note: The original project structure included a clean folder structure.
When moving the project from the course repository, all files ended up in one directory.
This does not affect the program’s behavior.

Description

This program reads hotel room data from an input file,
where each line specifies the room size and the number of rooms in the format:

room_size;count


Room numbering is determined by the order of lines and their respective counts.
Hotel data is stored using STL containers and smart pointers.

The user can manage the hotel through various commands, such as adding and removing guests,
printing room and guest information, and managing the current date.

The program handles error situations gracefully, such as:

missing or malformed input files

unknown commands

invalid parameters

Available Commands
Command	Description
BOOK	Add a guest and create a new visit
LEAVE	Remove a guest and end their visit
ROOMS	Print information about rooms
PRINT_GUEST_INFO	Print information about a specific guest
PRINT_CURRENT_VISITS	Show all ongoing visits
PRINT_ALL_VISITS	Show all visits (past and current)
PRINT_HONOR_GUESTS	Show guests with multiple visits
SET_DATE	Set the current date
ADVANCE_DATE	Move the current date forward
HELP	List all available commands
QUIT	Exit the program
Structure

The program is organized into several classes and modules:

Hotel – Manages rooms and guest data

Visit – Represents a single visit by a guest

Date – Handles date operations

Cli – Command-line interface for user interaction

Utils – Helper functions and utilities

Each visit is linked to a specific room and guest,
and a hotel can manage multiple rooms and visits simultaneously.

Usage

Run the program from the command line with an input file, for example:

./hotel input.txt


Then enter commands as described above.
You can always type HELP to see all available commands.

Build and Run
Using g++ (Windows / Linux / Mac)

Open a terminal in the project folder.

Compile all .cpp files:

g++ *.cpp -o hotel -std=c++17


Run the program:

./hotel       # Linux/Mac
.\hotel.exe   # Windows
