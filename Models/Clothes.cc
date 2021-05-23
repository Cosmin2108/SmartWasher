#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Clothes
{
private:
	int id;
	std::string type;
	std::string material;
	std::string color;
	double weight;

public:
	Clothes(int id, std::string type, std::string material, std::string color, double weight) : id(id), type(type), material(color), weight(weight) {}

	double getWeight()
	{
		return weight;
	}

	std::string getMaterial()
	{
		return material;
	}

	std::string getColor()
	{
		return color;
	}

	std::string getType()
	{
		return type;
	}

	json Serialize()
	{
		return {{"id", id}, {"type", type}, {"material", material}, {"color", color}, {"weight", weight}};
	}
};