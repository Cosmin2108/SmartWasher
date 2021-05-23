#include "pistache/endpoint.h"
#include <pistache/http.h>
#include <pistache/router.h>
#include <nlohmann/json.hpp>
#include "../Models/Clothes.cc"
#include "../Models/WashingMode.cc"
#include <vector>
#include <iostream>
// #include <boost/asio.hpp>

using namespace Pistache;
using namespace Rest;
using json = nlohmann::json;

class SmartWasher
{
private:
	std::vector<Clothes> clothes = {Clothes(1, "t-shirt", "cotton", "red", 0.6, 0.7), Clothes(2, "gloves", "cotton", "green", 0.2, 0.9)};
	std::vector<WashingMode> modes = {WashingMode(0, "Spalare smart", 60, 5000, 60), WashingMode(1, "Spalare rapida", 60, 5000, 60), WashingMode(2, "Spalare lunga", 60, 4000, 180)};
	WashingMode *currentMode = &modes[0];
	bool idle = true;
	double maxWeight = 20;
	double energyUsed = 0;
	Http::Mime::MediaType MIME = Http::Mime::MediaType::fromString("application/json");

	double getCurrentWeight()
	{
		double total = 0;

		for (auto cloth : clothes)
		{
			total += cloth.getWeight();
		}

		return total;
	}

	double getMaxDirtiness()
	{
		double maxDirtiness = 0;

		for (auto cloth : clothes)
		{
			if (cloth.getDirtiness() > maxDirtiness)
				maxDirtiness = cloth.getDirtiness();
		}

		return maxDirtiness;
	}

	WashingMode *getWashingModeById(int id)
	{
		for (int i = 0; i < modes.size(); i++)
		{
			if (modes[i].getId() == id)
			{
				return &modes[i];
			}
		}

		return nullptr;
	}

	void updateSmartMode(WashingMode *mode)
	{

		mode->setDuration(200);
		mode->setRPM(5000);
		mode->setTemperature(100);
		//modific params la mode in functie de hainele existente in masina
	}

public:
	SmartWasher()
	{
		Clothes newCloth(3, "pants", "cotton", "blue", 1.2, 0.6);
		clothes.push_back(newCloth);
	}

	// GET: /showClothes
	void ShowClothes(const Rest::Request &request, Http::ResponseWriter response)
	{
		json arrayClothes = json();

		for (int i = 0; i < clothes.size(); i++)
		{
			arrayClothes["Clothes"].push_back(clothes[i].Serialize());
		}

		response.send(Http::Code::Ok, arrayClothes.dump(), MIME);
	}

	// DELETE: /deleteClothes
	void DeleteClothes(const Rest::Request &request, Http::ResponseWriter response)
	{
		auto id = request.param(":id").as<int>();
		for (int i = 0; i < clothes.size(); i++)
		{
			if (clothes[i].getId() == id)
			{
				clothes.erase(clothes.begin() + i);
				break;
			}
		}
		response.send(Http::Code::Ok, "", MIME);
	}

	// POST: /setTemperature
	void getStatus(const Rest::Request &request, Http::ResponseWriter response)
	{
		json result = json();
		result["washing"] = !idle;
		result["params"] = currentMode->Serialize();

		response.send(Http::Code::Ok, result.dump(), MIME);
	}

	void startWasher(const Rest::Request &request, Http::ResponseWriter response)
	{
		if (currentMode->getId() == 0) // suntem in modul smart
		{
			updateSmartMode(currentMode);
			// trebuie sa modificam smartMode-ul pentru hainele curenete si dupa ii dam start
		}

		idle = false;
		json result = json();
		result["washing"] = true;
		result["params"] = currentMode->Serialize();

		response.send(Http::Code::Ok, result.dump(), MIME);
	}

	// GET: washing_modes
	void getWashingModes(const Rest::Request &request, Http::ResponseWriter response)
	{
		json result = json();

		for (auto mode : modes)
		{
			result.push_back(mode.Serialize());
		}

		response.send(Http::Code::Ok, result.dump(), MIME);
	}

	// POST: washing_modes
	void addWashingMode(const Rest::Request &request, Http::ResponseWriter response)
	{

		std::string body = request.body();

		json info = json::parse(body);

		auto temperature = (double)info["temperature"];
		auto duration = (int)info["duration"];
		auto rpm = (int)info["rpm"];
		auto name = info["name"];

		if (!WashingMode::isValid(temperature, rpm, duration))
		{
			response.send(Http::Code::Not_Acceptable, "Invalid mode");
			return;
		}

		auto id = (int)(modes.size() + 1);
		WashingMode newMode(id, name, temperature, rpm, duration);
		modes.push_back(newMode);

		json result = json();
		result["id"] = id;

		response.send(Http::Code::Ok, result.dump(), MIME);
	}

	// GET: washing_mode
	void getCurrentWashingMode(const Rest::Request &request, Http::ResponseWriter response)
	{
		if (!currentMode)
		{
			response.send(Http::Code::Not_Found, "No mode selected", MIME);
			return;
		}

		json result = json();
		result["active"] = currentMode->Serialize();

		response.send(Http::Code::Ok, result.dump(), MIME);
	}

	// POST: washing_mode/:id
	void changeWashingMode(const Rest::Request &request, Http::ResponseWriter response)
	{
		auto id = request.param(":id").as<int>();

		auto newMode = getWashingModeById(id);

		if (!newMode)
		{
			response.send(Http::Code::Not_Found, "ID is invalid");
			return;
		}

		currentMode = newMode;

		json result = json();
		result["new_mode"] = newMode->Serialize();
		response.send(Http::Code::Ok, result.dump(), MIME);
	}

	// POST: /setClothe
	void SetClothingItem(const Rest::Request &request, Http::ResponseWriter response)
	{
		std::string body = request.body();
		json my_request = json::parse(body);

		auto weight = (double)my_request["weight"];

		// Verificam daca depasim greutatea maxima
		if (weight + getCurrentWeight() > maxWeight)
		{
			response.send(Http::Code::Not_Acceptable, "Not enough room");
			return;
		}

		Clothes newCloth((int)my_request["id"], my_request["type"], my_request["material"], my_request["color"], (double)my_request["weight"], (double)my_request["dirtiness"]);
		clothes.push_back(newCloth);

		response.send(Http::Code::Ok, "{}", MIME);
	}

	// GET: /saveClothes
	void SaveClothes(const Rest::Request &request, Http::ResponseWriter response)
	{
		json arrayClothes = json();

		for (int i = 0; i < clothes.size(); i++)
		{
			arrayClothes["Clothes"].push_back(clothes[i].Serialize());
		}
		response.send(Http::Code::Ok, arrayClothes.dump(), MIME);
	}
};
