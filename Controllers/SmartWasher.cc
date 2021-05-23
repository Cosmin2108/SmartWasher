#include "pistache/endpoint.h"
#include <pistache/http.h>
#include <pistache/router.h>
#include <nlohmann/json.hpp>
#include "../Models/Clothes.cc"
#include <vector>

using namespace Pistache;
using namespace Rest;

class SmartWasher{
private:
    std::vector<Clothes> clothes = {Clothes(1, "t-shirt", "cotton", "red", 0.6), Clothes(2, "gloves", "cotton", "green", 0.2)};
    double temperature;
public:
    SmartWasher(){
        Clothes newCloth(3, "pants", "cotton", "blue", 1.2);
        clothes.push_back(newCloth);
    }

    // GET: /showClothes
    void ShowClothes(const Rest::Request &request, Http::ResponseWriter response){
        nlohmann::json arrayClothes = nlohmann::json();

        for (int i=0; i< clothes.size(); i++){
            arrayClothes["Clothes"].push_back(clothes[i].Serialize());
        }
        
        auto mime = Http::Mime::MediaType::fromString("application/json");

        response.send(Http::Code::Ok, arrayClothes.dump(), mime);
    }

    // POST: /setTemperature
    void SetTemperature(const Rest::Request &request, Http::ResponseWriter response){  
        std::string body = request.body();
        auto mime = Http::Mime::MediaType::fromString("application/json");

        nlohmann::json washerTemperature = nlohmann::json::parse(body);
        temperature = (double) washerTemperature["temperature"];
        response.send(Http::Code::Ok, washerTemperature.dump(), mime);
    }

    // GET: /getTemperature
    void GetTemperature(const Rest::Request &request, Http::ResponseWriter response){
        nlohmann::json washerTemperature = {{"temperature", temperature}};
        
        auto mime = Http::Mime::MediaType::fromString("application/json");
        response.send(Http::Code::Ok, washerTemperature.dump(), mime);
    }

    // POST: /setClothe
    void SetClothe(const Rest::Request &request, Http::ResponseWriter response){

        std::string body = request.body();
        auto mime = Http::Mime::MediaType::fromString("application/json");

        nlohmann::json my_request = nlohmann::json::parse(body);

        Clothes newCloth((int)my_request["id"], my_request["type"], my_request["material"], my_request["color"], (double)my_request["weight"]);
        clothes.push_back(newCloth);

        response.send(Http::Code::Ok, "{}", mime);
    }

    // GET: /saveClothes
    void SaveClothes(const Rest::Request &request, Http::ResponseWriter response){
        nlohmann::json arrayClothes = nlohmann::json();

        for (int i=0; i< clothes.size(); i++){
            arrayClothes["Clothes"].push_back(clothes[i].Serialize());
        }

        auto mime = Http::Mime::MediaType::fromString("application/json");

        response.send(Http::Code::Ok, arrayClothes.dump(), mime);
    }

};
