#include "Controllers/SmartWasher.cc"
using namespace Pistache;
using namespace Rest;

class DeviceHandler
{

private:
	static DeviceHandler *uniqueInstance;
	Http::Endpoint *server;
	Rest::Router router;
	SmartWasher smartWasher;

	DeviceHandler()
	{
		ConfigurateServer();
		StartServer();
	}

	~DeviceHandler()
	{
		StopServer();
	}

	void ConfigurateServer()
	{
		Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(8094));
		auto opts = Pistache::Http::Endpoint::options().threads(1);

		server = new Http::Endpoint(addr);
		server->init(opts);

		RegisterRoutes();

		server->setHandler(router.handler());
	}

	void RegisterRoutes()
	{
		Routes::Get(router, "/showClothes", Routes::bind(&SmartWasher::ShowClothes, &smartWasher));
		Routes::Get(router, "/getTemperature", Routes::bind(&SmartWasher::GetTemperature, &smartWasher));
		Routes::Post(router, "/setTemperature", Routes::bind(&SmartWasher::SetTemperature, &smartWasher));
		Routes::Post(router, "/setClothe", Routes::bind(&SmartWasher::SetClothe, &smartWasher));
		Routes::Get(router, "/saveClothes", Routes::bind(&SmartWasher::SaveClothes, &smartWasher));
		Routes::Get(router, "/washing_modes", Routes::bind(&SmartWasher::getWashingModes, &smartWasher));
		Routes::Post(router, "/washing_modes", Routes::bind(&SmartWasher::addWashingMode, &smartWasher));
		Routes::Get(router, "/washing_mode", Routes::bind(&SmartWasher::getCurrentWashingMode, &smartWasher));
		Routes::Post(router, "/washing_mode/:id", Routes::bind(&SmartWasher::changeWashingMode, &smartWasher));
	}

	void StartServer()
	{
		server->serve();
	}

	void StopServer()
	{
		server->shutdown();
	}

public:
	static DeviceHandler *GetInstance()
	{
		if (uniqueInstance == NULL)
		{
			uniqueInstance = new DeviceHandler();
		}

		return uniqueInstance;
	}
};

DeviceHandler *DeviceHandler::uniqueInstance = new DeviceHandler();