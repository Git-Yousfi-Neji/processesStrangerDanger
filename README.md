# processesStrangerDanger

**processesStrangerDanger** is a project designed to monitor and analyze running processes, identifying potential security threats by detecting strange or suspicious activities.
Criterias for a strange process (these are some exaamples that could be updated in the future):

 - [x] Unusual Usernames:
Identify processes running under uncommon or non-system usernames. This can help catch processes initiated by unauthorized or unfamiliar users
> As a critera: process with *UID > 1000* the process could be considered as a threat.
- [ ] Unexpected Privileges:
Monitor processes with elevated privileges that are unusual for typical user activities. Unusual sudo or root-level processes might indicate a security concern.
- [ ] Abnormal Process Behavior:
Processes exhibiting abnormal behavior, such as excessive CPU or memory usage, unusual file access patterns, or unexpected network activity.
- [ ] Uncommon Login Times:
Analyze the times at which users are typically logged in. Processes running at odd hours or outside regular business hours may be considered suspicious.
- [ ] Geographical Anomalies:
Tracking the geographical location of login attempts. If a user is connecting from an unfamiliar location, it could indicate a compromised account.
- [ ] Irregular Process Relationships:
To examine relationships between processes. Unusual parent-child relationships or unexpected dependencies may be indicative of malicious activity.
- [ ] Unusual Network Connections:
Monitor network connections associated with processes. Suspicious connections to unknown or suspicious IP addresses may indicate malicious activity.
- [ ] Multiple Simultaneous Logins:
Users with multiple simultaneous logins, especially if it's uncommon for users to be logged in from multiple locations at the same time.
- [ ] Long Running Sessions:
Processes that have been running for unusually long durations. Long-running processes might be indicative of a problem or compromise.
- [ ] Uncommon Process Names:
Flag processes with uncommon or suspicious names. Malicious actors often use disguised names to hide their activities.

## Table of Contents

- [Features](#features)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Configuration](#configuration)
- [Contributing](#contributing)
- [License](#license)

## Features

- Monitors running processes.
- Identifies processes associated with uncommon or unauthorized users.
- Analyzes process behavior for security anomalies.
- Logs and reports potential security threats.

## Project Structure
```
/processesStrangerDanger
├── bin
├── config
├── data
│ └── log
├── include
│ ├── networkAnalyzer.h
│ ├── processManager.h
│ └── userAnalyzer.h
├── lib
├── Makefile
├── LICENCE
├── README.md
└── src
├── main.cpp
├── networkAnalyzer.cpp
├── processManager.cpp
└── userAnalyzer.cpp
```
## Getting Started

To get started with **processesStrangerDanger**, follow these steps:
0. Install libxml used to parse xml files
> sudo apt install libxml2-dev

1. Clone the [repository](https://github.com/Git-Yousfi-Neji//processesStrangerDanger.git)

> git clone https://github.com/Git-Yousfi-Neji//processesStrangerDanger.git

2. Navigate to the project directory: 
> cd processesStrangerDanger

3. Build the project using the provided Makefile:
> make

## Usage

Run the executable to start monitoring processes and analyzing potential security threats.

> ./bin/processesStrangerDanger

## Configuration
Adjust the project's configuration in the config directory, especially config.ini, to suit your needs.

## Contributing
Feel free to contribute to this project. Fork the repository, make your changes, and submit a pull request.

## License
This project is licensed under the [MIT License](LICENSE)
