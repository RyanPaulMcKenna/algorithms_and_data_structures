#include <string>
#include <iostream>

class Device {
    public:
        virtual bool isEnabled() = 0;
        virtual void enable() = 0;
        virtual void disable() = 0;
        virtual size_t getVolume() = 0;
        virtual void setVolume(size_t) = 0;
        virtual size_t getChannel() = 0;
        virtual void setChannel(size_t) = 0;
}; // Interface

class Radio : public Device {
    bool enabled;
    size_t volume;
    size_t channel;
    // ... hardware-specific inforemation.
    public:
        Radio() : enabled(false), volume(10), channel(1) {}
        bool isEnabled() { return enabled; }
        void enable() { enabled = true; }
        void disable() { enabled = false; }
        size_t getVolume() { return volume; }
        void setVolume(size_t volume) { volume = volume; }
        size_t getChannel() { return channel; }
        void setChannel(size_t channel) { channel = channel; }
};
class TV : public Device {
    bool enabled;
    size_t volume;
    size_t channel;
    // ... hardware-specific inforemation.
    public:
        TV() : enabled(false), volume(10), channel(1) {}
        bool isEnabled() { return enabled; }
        void enable() { enabled = true; }
        void disable() { enabled = false; }
        size_t getVolume() { return volume; }
        void setVolume(size_t volume) { volume = volume; }
        size_t getChannel() { return channel; }
        void setChannel(size_t channel) { channel = channel; }
};

class Remote {
    private:
        Device *device;
    public:
        Remote(Device *device) : device(device) {}
        void togglePower() {
            if (device->isEnabled()) {
                device->disable();
            } else {
                device->enable();
            }
        }
        void volumeUp() {
            device->setVolume(device->getVolume() + 10);
        }
        void volumeDown() {
            device->setVolume(device->getVolume() - 10);
        }
        void channelUp() {
            device->setChannel(device->getChannel() + 1);
        }
        void channelDown() {
            device->setChannel(device->getChannel() - 1);
        }
};

class AdvancedRemote: public Remote {
    public:
        AdvancedRemote(Device *device) : Remote(device) {}
        void VoiceCommandChangeChannel(std::string voiceCommand) {
            std::cout << "Yes sir, I will change the channel" << std::endl; 
            if (voiceCommand == "channel up") {
                channelUp();
            } else if (voiceCommand == "channel down") {
                channelDown();
            }
        }
};

class Client {
    public:
        void test() {
            Radio radio;
            TV tv;
            Remote radioRemote(&radio);
            Remote tvRemote(&tv);
            AdvancedRemote advancedRemote(&tv);
            radioRemote.togglePower();
            tvRemote.togglePower();
            advancedRemote.VoiceCommandChangeChannel("channel up");
        }
};

int main() {
    Client client;
    client.test();
    return 0;
}

