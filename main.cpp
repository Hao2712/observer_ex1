#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


class Observer {
    public:
        virtual void update(const std::string& state) = 0;
};

class Device {
    private:
        std::string state;
        std::vector<Observer*> observers;

    public:
        void attach(Observer* observer) {
            observers.push_back(observer);
        }

        void detach(Observer* observer) {
            observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
        }

        void setState(const std::string& newState) {
            state = newState;
            notify();
        }

        void notify() {
            for(Observer* observer : observers) {
                observer->update(state);
            }
        }

        std::string getState() const {
            return state;
        }
};

class MobileApp : public Observer {
    public:
        void update(const std::string& state) override {
            std::cout << "MobileApp: Device state changed to " << state << std::endl;
        }
};

class WebApp : public Observer {
    public:
        void update(const std::string& state) override {
            std::cout << "WebApp: Device state changed to " << state << std::endl;
        }
};

int main() {
    Device smartLight;
    Device AC;
    MobileApp mobileApp;
    WebApp webApp;

    smartLight.attach(&mobileApp);
    smartLight.attach(&webApp);
    AC.attach(&mobileApp);
    AC.attach(&webApp);

    smartLight.setState("ON");
    smartLight.setState("OFF");
    AC.setState("ON");
    AC.setState("OFF");
}