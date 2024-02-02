# processesStrangerDanger

**ProcessesStrangerDanger**
is a project meticulously crafted for the vigilant monitoring and analysis of active processes, aiming to discern potential security threats by detecting unusual or suspicious activities.
The criteria defining what constitutes an abnormal process—these examples may evolve over time—include:"
- [x] Uncommon Process Names:
Flag processes with uncommon or suspicious names. Malicious actors often use disguised names to hide their activities.
> As a critera: process name not in the list considered as a threat.
- [x] Unexpected Privileges:
Monitor processes with elevated privileges that are unusual for typical user activities. Unusual sudo or root-level processes might indicate a security concern.
> As a criteria: process with *UID >= 1000* considered as a threat.
- [x] Unusual Parent Process:
Processes spawned by uncommon or unexpected parent processes might be suspicious.
> As a criteria: If ppid does not match the expected parent process IDs, flag the process as a potential threat.
- [ ] Uncommon Login Times:
Analyze the times at which users are typically logged in. Processes running at odd hours or outside regular business hours may be considered suspicious.
- [ ] Geographical Anomalies:
Tracking the geographical location of login attempts. If a user is connecting from an unfamiliar location, it could indicate a compromised account.
- [x] High CPU Usage:
Flag processes exhibiting excessively high CPU usage.
> As a criteria: process with high cpu usage considered as threat.
- [x] Abnormal Number of Threads:
Identify processes with an abnormal number of threads.
> As a criteria: process with high number of threads considered as a threat.
- [ ] Unusual Network Connections:
Monitor network connections associated with processes. Suspicious connections to unknown or suspicious IP addresses may indicate malicious activity.
- [ ] Long Running Sessions:
Processes that have been running for unusually long durations. Long-running processes might be indicative of a problem or compromise.

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
processesStrangerDanger
├── bin
│   └── processesStrangerDanger
├── config
│   └── config.h
├── data
│   ├── log
│   ├── systemUsernames.db
│   └── systemUsernames.xml
├── include
│   ├── networkAnalyzer.h
│   ├── processManager.h
│   ├── userAnalyzer.h
│   └── xml_parser.h
├── lib
├── LICENSE
├── Makefile
├── obj
│   ├── main.d
│   ├── main.o
│   ├── networkAnalyzer.d
│   ├── networkAnalyzer.o
│   ├── processManager.d
│   ├── processManager.o
│   ├── userAnalyzer.d
│   ├── userAnalyzer.o
│   ├── xml_parser.d
│   └── xml_parser.o
├── python_scripts
│   └── add_process_names_to_db.py
├── README.md
├── scripts
│   ├── add_process_name_to_xml.sh
│   ├── get_ppids.sh
│   ├── stress_cpu.sh
│   └── total_cpu_usage.sh
└── src
    ├── main.cpp
    ├── networkAnalyzer.cpp
    ├── processManager.cpp
    ├── userAnalyzer.cpp
    └── xml_parser.c
```
## Getting Started

To get started with **processesStrangerDanger**, follow these steps:
0. Install libxml used to parse xml files
> sudo apt-get install libxml2-dev
> sudo apt-get install inotify-tools
> sudo apt-get install stress
> pip install xmltodict 

1. Clone the repository:

> git clone https://github.com/Git-Yousfi-Neji//processesStrangerDanger.git

2. Navigate to the project directory: 
> cd processesStrangerDanger

3. Build the project using the provided Makefile:
> make

## Usage

Run the executable to start monitoring processes and analyzing potential security threats.

> ./bin/processesStrangerDanger

## Configuration
Adjust the project's configuration in the config/config.h, to suit your needs.

## Contributing
Feel free to contribute to this project. Fork the repository, make your changes, and submit a pull request.

## License
This project is licensed under the [MIT License](LICENSE)
