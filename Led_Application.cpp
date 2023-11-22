#include <iostream>
#include <string>
#include <thread>
#include <chrono>

class State
{
public:
    enum class SystemState { booting, updating, error, ready };
    enum class PlaybackState { inactive, paused, playing };
    enum class BluetoothState { inactive, pairing, connected };

    State(SystemState m_system, PlaybackState m_playback, BluetoothState m_bluetooth)
        : system(m_system), playback(m_playback), bluetooth(m_bluetooth) {}


public:
    SystemState system;
    PlaybackState playback;
    BluetoothState bluetooth;
    int volume;
    int playbackPosition;
};

class Led : public State
{
public:
    enum class Color { red, yellow, blue, white, off };

    Led(SystemState systemState, PlaybackState playbackState, BluetoothState bluetoothState)
        : State(systemState, playbackState, bluetoothState), color(Color::off), luminance(0) {}

    void setColor(Color newColor)
    {
        color = newColor;
    }

    void setLuminance(int newLuminance)
    {
        luminance = newLuminance;
    }

    Color getColor()
    {
        return color;
    }

    int getLuminance()
    {
        return luminance;
    }


    /*
    
    * SystemUpdate() function updates the state of Sytem depending upon the parameter being passed. 
    * It sets the color and the Luminance of the virtual Led in accordance with
    * different state of the System.
    * @param s-> it denotes different states of the System as {booting, updating, error and ready.} 
    
    */

    void SystemUpdate(SystemState s)
    {
        switch (s)
        {
        case SystemState::error:
            setColor(Color::red);
            setLuminance(100);
            std::cout << "system:error ->" << colorToString(getColor()) << "@" << getLuminance() << std::endl;
            break;

        case SystemState::updating:
          FlashingEffectSystemUpdate(Color::yellow, 100, 1);  // Flashing with 1Hz
            break;

        case SystemState::booting:
            setColor(Color::red);
            setLuminance(10);
            std::cout << "system:booting ->" << colorToString(getColor()) << "@" << getLuminance() << std::endl;
            break;

        case SystemState::ready:
            std::cout << "system:ready ->" << "Not Asserted" << std::endl;
            break;

        default:
            std::cout << "System States are not asserted" << std::endl;
            break;
        }
    }

    /*
    
    * PlaybackUpdate() function updates the state of Playback depending upon the parameter being passed. 
    * It sets the color and the Luminance of the virtual Led in accordance with
    * different playback state of the system.
    * @param p-> it denotes different states of the Playback as { inactive, paused, playing }. 
    
    */

    void PlaybackUpdate(PlaybackState p)
    {
        switch (p)
        {
        case PlaybackState::inactive:
            setColor(Color::off);
            std::cout << "playback:inactive ->" << colorToString(getColor()) << std::endl;
            break;

        case PlaybackState::playing:
            setColor(Color::white);
            setLuminance(10);
            std::cout << "playback:playing ->" << colorToString(getColor()) << "@" << getLuminance() << std::endl;
            break;

        case PlaybackState::paused:
            setColor(Color::white);
            setLuminance(50);
            std::cout << "playback:paused ->" << colorToString(getColor()) << "@" << getLuminance() << std::endl;
            break;

        default:
            std::cout << "Playback States are not asserted" << std::endl;
            break;
        }
    }

 /*
    
    * BluetoothUpdate() function updates the state of Bluetooth depending upon the parameter being passed. 
    * It sets the color and the Luminance of the virtual Led in accordance with
    * different Bluetooth state of the system.
    * @param b-> it denotes different states of the Bluetooth as { inactive, pairing, connected }. 
    
 */

    void BluetoothUpdate(BluetoothState b)
    {
        switch (b)
        {
        case BluetoothState::pairing:
            FlashingEffectBluetoothUpdate(Color::blue, 100, 2);  // Flashing with 2Hz
            break;

        case BluetoothState::connected:
            setColor(Color::blue);
            setLuminance(10);
            std::cout << "bluetooth:connected ->" << colorToString(getColor()) << "@" << getLuminance() << std::endl;
            break;

        case BluetoothState::inactive:
            std::cout << "bluetooth:inactive ->" << "Not Asserted" << std::endl;
            break;

        default:
            std::cout << "System States are not asserted" << std::endl;
            break;
        }
    }
/*
    
    * FlashingEffectSystemUpdate() implements a switching mechanism of Led color between color->off and color-> yellow@100 with
    * a flashing effect of 1Hz, meaning Led switches from off to yellow state one time in one second. 
    * @param flashColor-> the color to switch 
    * @param  luminance-> the luminance value to be set 
    * @param frequencyHz-> the number of time the flashing has to be done in a given second
*/


     void FlashingEffectSystemUpdate(Color flashColor, int luminance, int frequencyHz)
    {
        for (int i = 0; i < frequencyHz * 2; ++i)
        {
            setColor(Color::off);
            std::cout << "sytem:updating ->" << colorToString(getColor()) << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / (2 * frequencyHz)));  
            setColor(flashColor);
            setLuminance(luminance);
            std::cout << "sytem:updating ->" << colorToString(getColor()) << "@" << getLuminance() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / (2 * frequencyHz)));  
        }
    }

/*
    
    * FlashingEffectBluetoothUpdate() implements a switching mechanism of Led color between color->off and color-> blue@100 with
    * a flashing effect of 2Hz, meaning Led switches from off to blue state two times in one second. 
    * @param flashColor-> the color to switch 
    * @param  luminance-> the luminance value to be set 
    * @param frequencyHz-> the number of time the flashing has to be done in a given second
    
 */
    
    void FlashingEffectBluetoothUpdate(Color flashColor, int luminance, int frequencyHz)
    {
        for (int i = 0; i < frequencyHz * 2; ++i)
        {
            setColor(Color::off);
            std::cout << "bluetooth:pairing ->" << colorToString(getColor()) << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / (2 * frequencyHz)));  
            setLuminance(luminance);
            std::cout << "bluetooth:pairing ->" << colorToString(getColor()) << "@" << getLuminance() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / (2 * frequencyHz)));  
        }
    }

/*
    string colorToString() returns string value of a Color from a given enum
    @param c-> Its an enum object 
    @return -> it returns a standard string of a given color as red, yellow, blue, white and off 

*/
    std::string colorToString(Color c)
    {
        switch (c)
        {
        case Color::red:
            return "red";
        case Color::yellow:
            return "yellow";
        case Color::blue:
            return "blue";
        case Color::white:
            return "white";
        case Color::off:
            return "off";
        }
        return "unknown";
    }


    // Implementation for playback:volume(changed) task

    void playbackVolumeChanged(int volume)
    {
        setColor(Color::white);
        setLuminance(volume);
        std::cout << "playback:volume(changed) ->" << colorToString(getColor()) << "@volume for " << getLuminance() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        FadeOut();
    }

  // Implementation for fade out effect
    void FadeOut()
    {
       
        for (int i = getLuminance(); i >= 0; --i)
        {
            setLuminance(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        setColor(Color::off);
    }


    void PlayBackUpdate(PlaybackState p, BluetoothState b)
    {
        if (p == PlaybackState::playing && b == BluetoothState::connected)
        {
            setColor(Color::blue);
            setLuminance(10);
            std::cout << "playback:playing && bluetooth:connected ->" << colorToString(getColor()) << "@" << getLuminance() << std::endl;
        }
    }


private:
    Color color;
    int luminance;
};

int main()
{
    Led ledInstance(State::SystemState::updating, State::PlaybackState::inactive, State::BluetoothState::pairing);

    // Simulating state updates

    ledInstance.SystemUpdate(State::SystemState::error);
    ledInstance.SystemUpdate(State::SystemState::updating);
    ledInstance.SystemUpdate(State::SystemState::booting);

    ledInstance.playbackVolumeChanged(3);

    ledInstance.BluetoothUpdate(State::BluetoothState::pairing);
    
       
    ledInstance.PlaybackUpdate(State::PlaybackState::inactive);
    ledInstance.PlayBackUpdate(State::PlaybackState::playing, State::BluetoothState::connected);

 
    ledInstance.PlaybackUpdate(State::PlaybackState::playing);
    ledInstance.PlaybackUpdate(State::PlaybackState::paused);


    return 0;
}
