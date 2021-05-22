#include "Controllers/SmartWasher.cc"
using namespace Pistache;
using namespace Rest;


class DeviceHandler{

private:
    static DeviceHandler *uniqueInstance;
    Http::Endpoint *server;
    Rest::Router router;
    SmartWasher smartWasher;
    
    DeviceHandler(){
        ConfigurateServer();
        StartServer();
    }

    ~DeviceHandler(){
        StopServer();
    }

    void ConfigurateServer(){
        Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(8094));
        auto opts = Pistache::Http::Endpoint::options().threads(1);

        server = new Http::Endpoint(addr);
        server->init(opts);
        
        RegisterRoutes();
        
        server->setHandler(router.handler());
    }

    void RegisterRoutes(){
        Routes::Get (router, "/showClothes", Routes::bind(&SmartWasher::ShowClothes, &smartWasher));
        Routes::Post (router, "/setTemperature", Routes::bind(&SmartWasher::ShowClothes, &smartWasher));
    }

    void StartServer(){
        server->serve();
    }

    void StopServer(){
        server->shutdown();
    }

public:
    static DeviceHandler* GetInstance(){
        if(uniqueInstance == NULL){
            uniqueInstance = new DeviceHandler();
        }

        return uniqueInstance;
    }
};

DeviceHandler *DeviceHandler::uniqueInstance = new DeviceHandler();