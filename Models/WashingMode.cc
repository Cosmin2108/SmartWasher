#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

const double MIN_TEMPERATURE = 20;
const double MAX_TEMPERATURE = 160;
const int MIN_RPM = 2000;
const int MAX_RPM = 9000;

class WashingMode
{
private:
    int id;
    std::string name;
    double temperature;
    int rpm;
    int duration; // minutes

public:
    WashingMode(int id, std::string name, double temperature, int rpm, int duration) : id(id), name(name), temperature(temperature), rpm(rpm), duration(duration) {}

    int getId()
    {
        return id;
    }

    int getRPM()
    {
        return rpm;
    }

    int getDuration()
    {
        return duration;
    }

    double getTemperature()
    {
        return temperature;
    }

    std::string getName()
    {
        return name;
    }

    json Serialize()
    {
        return {{"id", id}, {"name", name}, {"temperature", temperature}, {"RPM", rpm}, {"duration", duration}};
    }

    static bool isValid(double temperature, int rpm, int duration)
    {
        if (temperature > MAX_TEMPERATURE || temperature < MIN_TEMPERATURE)
        {
            return false;
        }

        if (rpm > MAX_RPM || rpm < MIN_RPM)
        {
            return false;
        }

        if (duration <= 0)
        {
            return false;
        }

        return true;
    }
};