# processesStrangerDanger

**processesStrangerDanger** is a project designed to monitor and analyze running processes, identifying potential security threats by detecting strange or suspicious activities.

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
