# SmartWasher
Compile and execute server with:
```
$ g++ -o SmartWasher Program.cc -std=c++17 -lpistache -pthread && ./SmartWasher
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
	"weight": int,
	"dirtiness": double
}

Example:
{
	"id": 4,
	"type": "t-shirt",
	"material": "puf",
	"color": "black",
	"weight": 1,
	"dirtiness": 0.7
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

### Input buffers
```
{
   "input_buffers":{
      "setClothingItem":{
         "token_delimitators":"",
         "protocol":"HTTP",
         "method":"POST",
         "prefix":"localhost:8094/setClothingItem",
         "buffer-tokens":[
            {
               "name":"type",
               "description":"Type that lets the user know what clothing item is.",
               "value":"t-shirt",
               "token_type":"string",
               "byte_size":256,
               "regex-rule":"[a-zA-Z\-]*",
               "optional":false
            },
            {
               "name":"material",
               "description":"Material that gives clothing item material.",
               "value":"cotton",
               "token_type":"string",
               "byte_size":256,
               "regex-rule":"[a-zA-Z]*",
               "optional":false
            },
            {
               "name":"color",
               "description":"Sensor that gives color.",
               "value":"red",
               "token_type":"string",
               "byte_size":256,
               "optional":false
            },
            {
               "name":"weight",
               "description":"Sensor that gives weight",
               "value":"35",
               "token_type":"double",
               "optional":false
            },
            {
               "name":"dirtiness",
               "description":"Sensor that gives dirtiness",
               "value":"10",
               "token_type":"double",
               "optional":false
            }
         ]
      },
       "washing_modes":{
          "token_delimitators":"",
          "protocol":"HTTP",
          "method":"POST",
          "prefix":"localhost:8094/washing_modes",
          "buffer-tokens":[
             {
                "name":"name",
                "description":"The washing mode name.",
                "value":"",
                "token_type":"string",
                "byte_size":256,
                "regex-rule":"[a-zA-Z]+",
                "optional":false
             },
             {
                "name":"temperature",
                "description":"The washing mode temperature.",
                "value":"false",
                "token_type":"double",
                "optional":false
             },
             {
                "name":"rpm",
                "description":"The washing mode rpm.",
                "value":"false",
                "token_type":"double",
                "optional":false
             },
             {
                "name":"duration",
                "description":"The washing mode duration.",
                "value":"false",
                "token_type":"double",
                "optional":false
             },
          ]
       }
    }
 }
```

### Output buffers
```
{
   "output_buffers":{
      "showClothes":{
         "token_delimitators":"",
         "protocol":"HTTP",
         "method":"GET",
         "prefix":"localhost:8094/showClothes",
         "buffer-tokens":[
            {
               "name":"type",
               "description":"Type that lets the user know what clothing item is.",
               "value":"t-shirt",
               "token_type":"string",
               "byte_size":256,
               "regex-rule":"[a-zA-Z\-]*",
               "optional":false
            },
            {
               "name":"material",
               "description":"Material that gives clothing item material.",
               "value":"cotton",
               "token_type":"string",
               "byte_size":256,
               "regex-rule":"[a-zA-Z]*",
               "optional":false
            },
            {
               "name":"color",
               "description":"Sensor that gives color.",
               "value":"red",
               "token_type":"string",
               "byte_size":256,
               "optional":false
            },
            {
               "name":"weight",
               "description":"Sensor that gives weight",
               "value":"35",
               "token_type":"double",
               "optional":false
            },
            {
               "name":"dirtiness",
               "description":"Sensor that gives dirtiness",
               "value":"10",
               "token_type":"double",
               "optional":false
            }
         ]
      },
       "washing_modes":{
          "token_delimitators":"",
          "protocol":"HTTP",
          "method":"GET",
          "prefix":"localhost:8094/washing_modes",
          "buffer-tokens":[
             {
                "name":"name",
                "description":"The washing mode name.",
                "value":"",
                "token_type":"string",
                "byte_size":256,
                "regex-rule":"[a-zA-Z]+",
                "optional":false
             },
             {
                "name":"temperature",
                "description":"The washing mode temperature.",
                "value":"false",
                "token_type":"double",
                "optional":false
             },
             {
                "name":"rpm",
                "description":"The washing mode rpm.",
                "value":"false",
                "token_type":"double",
                "optional":false
             },
             {
                "name":"duration",
                "description":"The washing mode duration.",
                "value":"false",
                "token_type":"double",
                "optional":false
             },
          ]
       }
    }
 }
```
