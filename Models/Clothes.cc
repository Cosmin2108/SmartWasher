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
	double dirtiness;


public:
	Clothes(int id, std::string type, std::string material, std::string color, double weight, double dirtiness) : id(id), type(type), material(material), color(color), weight(weight), dirtiness(dirtiness) {}

	double getWeight()
	{
		return weight;
	}

	double getDirtiness()
	{
		return dirtiness;
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

	int getId()
	{
		return id;
	}

	json Serialize()
	{
		return {{"id", id}, {"type", type}, {"material", material}, {"color", color}, {"weight", weight}, {"dirtiness", dirtiness}};
	}
};