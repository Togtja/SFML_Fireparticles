#include <vector>
#include <iostream>

#include <TGUI/TGUI.hpp>
#include "FirePlace.hpp"
#include "EventManager.hpp"


int main() {
    //EventManagerSingleton& EventM = EventManagerSingleton::getEventManager();
    sf::RenderWindow window(sf::VideoMode(SCREEN, SCREEN), "Events");
    tgui::Gui gui{window};
    //The fire place
    FirePlace firePlace;

    //Create the wood
    sf::RectangleShape wood1(sf::Vector2f(WOODSIZE_X, WOODSIZE_Y));
    wood1.setFillColor(sf::Color(161, 64, 5, 255));

    wood1.setOrigin(ORIGIN);
    wood1.setPosition(WOODPOS);
    
    sf::RectangleShape wood2 = wood1;

    wood1.rotate(WOOD_ROT);
    wood2.rotate(-WOOD_ROT);

    //Set up widget to do customasations
    //Label for spread slider
    tgui::Label::Ptr spreadLabel = tgui::Label::create();
    spreadLabel->setText("Starting up");
    spreadLabel->setPosition(10, 0);
    spreadLabel->getRenderer()->setTextColor(tgui::Color::White);
    
    //The spread slider itself
    tgui::Slider::Ptr spreadSlider = tgui::Slider::create();
    spreadSlider->setPosition(10,  spreadLabel->getSize().y + spreadLabel->getPosition().y);
    spreadSlider->setMaximum(100.f);
    spreadSlider->setValue(firePlace.getSpread());

    //Label for speed slider
    tgui::Label::Ptr speedLabel = tgui::Label::create();
    speedLabel->setText("Starting up");
    speedLabel->setPosition(10, spreadSlider->getFullSize().y/2 + spreadSlider->getPosition().y);
    speedLabel->getRenderer()->setTextColor(tgui::Color::White);

    //The speed slider itself
    tgui::Slider::Ptr speedSlider = tgui::Slider::create();
    speedSlider->setPosition(10, speedLabel->getSize().y + speedLabel->getPosition().y);
    speedSlider->setMaximum(100.f);
    speedSlider->setValue(firePlace.getSpeed());


    //Label for life slider
    tgui::Label::Ptr lifeLabel = tgui::Label::create();
    lifeLabel->setText("Starting up");
    lifeLabel->setPosition(10, speedSlider->getFullSize().y / 2 + speedSlider->getPosition().y);
    lifeLabel->getRenderer()->setTextColor(tgui::Color::White);

    //The speed slider itself
    tgui::Slider::Ptr lifeSlider = tgui::Slider::create();
    lifeSlider->setPosition(10, lifeLabel->getSize().y + lifeLabel->getPosition().y);
    lifeSlider->setMinimum(firePlace.getMinLife()+1);
    lifeSlider->setMaximum(50.f); 
    lifeSlider->setStep(0.5);
    lifeSlider->setValue(firePlace.getMaxLife());

    //Mouse force label
    tgui::Label::Ptr forceLabel = tgui::Label::create();
    forceLabel->setText("Mouse click Force:  " + std::to_string(5.0f));
    forceLabel->setPosition(SCREEN - forceLabel->getSize().x - 10, 0);
    forceLabel->getRenderer()->setTextColor(tgui::Color::White);

    //The force slider itself
    tgui::Slider::Ptr forceSlider = tgui::Slider::create();
    forceSlider->setPosition(forceLabel->getPosition().x, forceLabel->getSize().y + forceLabel->getPosition().y);
    forceSlider->setMaximum(50.f);
    forceSlider->setStep(0.5);
    forceSlider->setValue(5);

    //Inc/Dec force label
    tgui::Label::Ptr incdecLabel = tgui::Label::create();
    incdecLabel->setText("Amount of Triangle points");
    incdecLabel->setPosition(forceLabel->getPosition().x, forceSlider->getSize().y + forceSlider->getPosition().y);
    incdecLabel->getRenderer()->setTextColor(tgui::Color::White);

    //buttons for shape
    tgui::Button::Ptr incPoint = tgui::Button::create();
    incPoint->setSize(50, 50);
    incPoint->setText("+"); incPoint->setTextSize(35);
    incPoint->connect("pressed", [&]() { firePlace.incPoints(); });
    incPoint->setPosition(incdecLabel->getPosition().x, incdecLabel->getSize().y + incdecLabel->getPosition().y);

    tgui::Button::Ptr decPoint = tgui::Button::create();
    decPoint->setSize(50, 50);
    decPoint->setText("-"); decPoint->setTextSize(35);
    decPoint->connect("pressed", [&]() { firePlace.decPoints(); });
    decPoint->setPosition(incPoint->getPosition().x + incPoint->getSize().x, incPoint->getPosition().y);


    //Add the gui elemets
    gui.add(spreadLabel);
    gui.add(spreadSlider);

    gui.add(speedLabel);
    gui.add(speedSlider);

    gui.add(lifeLabel);
    gui.add(lifeSlider);

    gui.add(forceLabel);
    gui.add(forceSlider);

    gui.add(incdecLabel);
    gui.add(incPoint);
    gui.add(decPoint);

    sf::Clock deltaClock;

    
    float spawnTimer = .1;
    std::vector<std::unique_ptr<Event>>& events = EventManagerSingleton::getEventManager().getEvents();

    while(window.isOpen()) {
        float dt = deltaClock.restart().asSeconds();
        events.clear();

        sf::Event e;
        while(window.pollEvent(e)) {
            if(e.type == sf::Event::Closed) {
                window.close();
            }
            if (e.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                CrackleEvent* crackleE = new CrackleEvent((sf::Vector2f)pixelPos);
                crackleE->force = forceSlider->getValue();
                EventManagerSingleton::getEventManager().addEvent(crackleE);

            }
            gui.handleEvent(e);

        }
        //update gui elemets
        spreadLabel->setText("Spread: " + std::to_string(spreadSlider->getValue()));
        firePlace.setSpread(spreadSlider->getValue());

        speedLabel->setText("Speed: " + std::to_string(speedSlider->getValue()));
        firePlace.setSpeed(speedSlider->getValue());

        lifeLabel->setText("Maxlife (in seconds) " + std::to_string(lifeSlider->getValue()));
        firePlace.setMaxLife(lifeSlider->getValue());

        forceLabel->setText("Mouse click Force:  " + std::to_string(forceSlider->getValue()));

        spawnTimer -= dt;
        if (spawnTimer < 0) {
            firePlace.draw();
            spawnTimer = .1;
        }
        
        window.clear();
        gui.draw();
        window.draw(wood1);
        window.draw(wood2);
        for (auto& fire : firePlace.GetFireParticles()) {
            fire->Tick(dt);
            window.draw(fire->getParticle());
        }
        window.display();

        for (auto& ev : events) {
            if (ev->id == EventID::Death) {
                DeathEvent* death = static_cast<DeathEvent*>(ev.get());
                firePlace.createFire(death->deadFire);
            }
            else if(ev->id == EventID::Crackle) {
                CrackleEvent* crackle = static_cast<CrackleEvent *>(ev.get());
                firePlace.crackle(crackle->pos, crackle->force);

            }
        }
    } 
}