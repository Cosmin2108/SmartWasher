#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include "HTTPRequest.hpp"




int main()
{
	while(1)
	{
		try
		{
			std::cout << "Select from this options:\n \
1 - Print what clothes do you have in your washer\n \
2 - Set the temperature in washer\n \
3 - Get the temperature from washer\n \
4 - Insert a new clothe in your washer\n \
5 - Save all your clothes in a file\n \
6 - Print all washing modes\n \
7 - Add a washing mode\n \
8 - Print current washing mode\n \
9 - Select/Change washing mode\n \
10 - Remove any clothe from washer\n \
11 - Save all your washing modes in a file";

			std::cout << "\n\n";
			int option;
			std::cin >> option;
			switch (option){
				case 1: 
				{
					http::Request request{"http://127.0.0.1:8094/showClothes"};
					const auto response = request.send("GET");
					std::cout << std::string{response.body.begin(), response.body.end()} << '\n';
					break;
				}
				case 2:
				{
					http::Request request{"http://127.0.0.1:8094/setTemperature"};
					
					std::cout << "Select new temperature:\n";
					float new_temperature;
					std::cin >> new_temperature;
					nlohmann::json washerTemperature = {{"temperature", new_temperature}};

					const auto response = request.send("POST", washerTemperature.dump(),
						{"Content-Type: application/json"});
					std::cout << std::string{response.body.begin(), response.body.end()} << '\n';
					break;
				}
				case 3:
				{
					http::Request request{"http://127.0.0.1:8094/getTemperature"};
					const auto response = request.send("GET");
					std::cout << std::string{response.body.begin(), response.body.end()} << '\n';
					break;
				}
				case 4:
				{
					http::Request request{"http://127.0.0.1:8094/setClothe"};
					
					std::cout << "Name your file:\n";
					std::string new_file;
					std::cin >> new_file;

					std::ifstream file(new_file);
					nlohmann::json new_json;
					file >> new_json;
					const auto response = request.send("POST", new_json.dump(),
						{"Content-Type: application/json"});
					std::cout << std::string{response.body.begin(), response.body.end()} << '\n';
					break;
				}
				case 5:
				{
					http::Request request{"http://127.0.0.1:8094/showClothes"};
					const auto response = request.send("GET");

					std::cout << "Name your file:\n";
					std::string new_file;
					std::cin >> new_file;

					std::ofstream output(new_file);
					output << std::string{response.body.begin(), response.body.end()} << '\n';
					break;
				}
				case 6:
				{
					http::Request request{"http://127.0.0.1:8094/washing_modes"};
					const auto response = request.send("GET");
					std::cout << std::string{response.body.begin(), response.body.end()} << '\n';
					break;
				}
				case 7:
				{
					http::Request request{"http://127.0.0.1:8094/washing_modes"};
					
					std::cout << "Name your washing mode file:\n";
					std::string new_file;
					std::cin >> new_file;

					std::ifstream file(new_file);
					nlohmann::json new_json;
					file >> new_json;
					const auto response = request.send("POST", new_json.dump(),
						{"Content-Type: application/json"});
					std::cout << std::string{response.body.begin(), response.body.end()} << '\n';
					break;
				}
				case 8:
				{
					http::Request request{"http://127.0.0.1:8094/washing_mode"};
					const auto response = request.send("GET");
					std::cout << std::string{response.body.begin(), response.body.end()} << '\n';
					break;
				}
				case 9:
				{
					std::cout << "Change washing mode to:\n";
					std::string mode;
					std::cin >> mode;

					http::Request request{"http://127.0.0.1:8094/washing_mode/" + mode};
					
					const auto response = request.send("POST", "",
						{"Content-Type: application/json"});
					std::cout << std::string{response.body.begin(), response.body.end()} << '\n';
					break;
				}
				case 10:
				{
					std::cout << "ID:\n";
					std::string id;
					std::cin >> id;

					http::Request request{"http://127.0.0.1:8094/deleteClothes/" + id};
					const auto response = request.send("DELETE");
					std::cout << std::string{response.body.begin(), response.body.end()} << '\n';
					break;
				}
				case 11:
				{
					http::Request request{"http://127.0.0.1:8094/saveModes"};
					const auto response = request.send("GET");

					std::cout << "Name your output file:\n";
					std::string new_file;
					std::cin >> new_file;

					std::ofstream output(new_file);
					output << std::string{response.body.begin(), response.body.end()} << '\n';
					break;
				}
				default:
				{
					std::cout << "Invalid option.";
					break;
				}
			}

		}
		catch (const std::exception& e)
		{
			std::cerr << "Request failed, error: " << e.what() << '\n';
		}
	}

	return 0;
}