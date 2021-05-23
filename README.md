# SmartWasher
Compile and execute server with:
```
$ g++ -o SmartWasher Program.cc -std=c++17 -lpistache && && ./SmartWasher
```

Make a request:
```
$ curl http://localhost:port_number/route_name
```

Compile and execute client with:
```
$ g++ Client.cpp -o client.o && ./client.o
```

## Installation

### BUILD ESSENTIALS

```
$ sudo apt update
$ sudo apt install build-essential
```

### PISTACHE

```
$ sudo add-apt-repository ppa:pistache+team/unstable
$ sudo apt update
$ sudo apt install libpistache-dev
```

### NLOHMANN
```
$ sudo apt-get update
$ sudo apt-get install nlohmann-json3-dev
```

# Examples input
```
For /setClothe method
{
	"id": int,
	"type": string,
	"material": string,
	"color": string,
	"weight": int
}

Example:
{
	"id": 4,
	"type": "t-shirt",
	"material": "puf",
	"color": "black",
	"weight": 1
}

```

```
For /washing_modes method
{
 	"name": string,
    "temperature": double,
    "rpm": double,
    "duration": int
}

Example:
{
 	"name": "Spalare delicata",
    "temperature": 60,
    "rpm": 6000,
    "duration": 35
}
```
