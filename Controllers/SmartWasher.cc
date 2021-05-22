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
    std::vector<Clothes> clothes = {Clothes(1, "pants", "cotton", "blue", 1.2), Clothes(1, "pants", "cotton", "blue", 1.2)};
    double temperature;
public:
    SmartWasher(){
        Clothes newCloth(1, "pants", "cotton", "blue", 1.2);
        clothes.push_back(newCloth);
    }

    // GET: /showClothes
    void ShowClothes(const Rest::Request &request, Http::ResponseWriter response){
        nlohmann::json arrayClothes = nlohmann::json();

        for (int i=0; i< clothes.size(); i++){
            arrayClothes["Clothes"].push_back(clothes[0].Serialize());
        }
        
        auto mime = Http::Mime::MediaType::fromString("application/json");

        response.send(Http::Code::Ok, arrayClothes.dump(), mime);
    }

    // POST: /setTemperature
    void SetTemperature(const Rest::Request &request, Http::ResponseWriter response){
        // auto temp = request.param(":temperature").as<double>(); // Take data from POST request
        temperature = 20.5;
    }
};