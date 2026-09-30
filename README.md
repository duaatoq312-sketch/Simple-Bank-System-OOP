\# Simple Bank System



\## About the Project



I developed my Bank System using OOP as my first project to practice object-oriented programming. It also includes a currency exchange system.



I spent about a full month developing, testing, and debugging the project while applying what I learned about OOP.


![Main Screen](images/main-screen.png)

\## Features



\* A main screen that provides access to the different parts of the system.

\* Separate screen classes, with each screen responsible for a specific task.

\* Management of clients, users, currencies, and person objects.

\* Inheritance used in the project, with `Person` used as a base class.

\* A login system with user permissions.

\* Login register to keep track of login activity.

\* Transfer log to record transfer operations.

\* Currency exchange functionality.



\## What I Practiced



\* Practiced designing the structure of a system while thinking about how it could be used in the future.

\* Learned more about handling files and data in a real project.

\* Practiced thinking about the flow of the program and how different parts interact.

\* Practiced representing different object states and handling them correctly.

\* Thought about how the system could be extended for more users and features in the future.

\* Applied OOP concepts in a larger project instead of practicing them only through small exercises.



\## Technologies



\* C++

\* Visual Studio

\* Object-Oriented Programming (OOP)

\* File handling and data storage using text files



\## Project Structure



\* \*\*Main Screen\*\* — The main screen that gives access to the different parts of the system.

\* \*\*Transaction Screen\*\* — Handles banking transactions such as deposits, withdrawals, and transfers.

\* \*\*Currency Exchange Screens\*\* — Handles currency management and exchange operations.

\* \*\*User Management Screens\*\* — Handles users, login, and permissions.



\### Core



Contains the main classes used by the system:



\* Client

\* User

\* Currency

\* Person



\### Screens



The screens are organized into:



\* User screens

\* Client screens

\* Currency screens



\### Library



Contains reusable classes and utility functions:



\* `clsUtil`

\* `clsString`

\* `clsInputValidate`

\* `clsDate`



\### Global



A shared class used by different parts of the system to track the currently logged-in user and save login activity to the login register.



\## How to Run



1\. Open the `.slnx` solution in Visual Studio.

2\. Make sure the `MainScreen` project is the startup project.

3\. Build the project.

4\. Run it.



\*\*Note:\*\* `Users.txt`, `Clients.txt`, `TransferLog.txt`, and `Logins Register.txt` are intentionally not included in the repository. They contain runtime/test data, so I kept them separate from the source code instead of publishing them to GitHub.



\## Notes



\* This is my first larger OOP practice project.

\* I developed and debugged the project over about a month.

\* This is a learning and practice project, not a production banking system.

\* Runtime and test data files are intentionally excluded from the GitHub repository.



