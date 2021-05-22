#include <iostream>
#include <nlohmann/json.hpp>

class Clothes{
private:
    int id;
    std::string type;
    std::string material;
    std::string color;
    double weight;
public:
    Clothes(int id, std::string type, std::string material, std::string color, double weight): id(id), type(type), material(color), weight(weight){}

    nlohmann::json Serialize(){
        nlohmann::json arrayClothes = nlohmann::json();

        return {{"id", id}, {"type", type}, {"material", material}, {"color", color}, {"weight", weight}};
    }
};