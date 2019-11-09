#pragma once
#include <string>
#include <memory>
#include "SFML/Graphics.hpp"
#include "FireParticle.hpp"

enum EventID {
    BasicEvent,
    Death,
    Crackle
};

struct Event {
    std::string name; // Eventuelt en ENUM eller annen identifier
    EventID id;
    Event() {
        id = EventID::BasicEvent;
    }
};

struct DeathEvent : Event {
    FireParticle& deadFire;
    DeathEvent(FireParticle& fire) :  deadFire(fire) {
        id = EventID::Death;
    }

};
struct CrackleEvent : Event {
    float force;
    sf::Vector2f pos;
    CrackleEvent(sf::Vector2f p) {
        id = EventID::Crackle;
        force = 5.f;
        pos = p;
    }
};

class EventManagerSingleton {

private:
    std::vector<std::unique_ptr<Event>> events{};
    EventManagerSingleton(){}

public:
    static EventManagerSingleton& getEventManager() {
        static EventManagerSingleton instance;
        return instance;
    }
    void addEvent(Event* ev) {
        events.emplace_back(ev);
    }
    std::vector <std::unique_ptr<Event>>& getEvents() {
        return events;
    }
    EventManagerSingleton(EventManagerSingleton const&) = delete;
    void operator= (EventManagerSingleton const&) = delete;
};