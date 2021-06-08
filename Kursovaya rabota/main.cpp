#include <string>
#include <vector>
#include <list>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

int ScreenWidth = 800;
int ScreenHeight = 600;

#define MAXVOL (0.22*32768)
#define DECAY (MAXVOL/4000)

#define KEYS 32
#define M_PI 3.14159265358979323846

float vol[KEYS] = { 0 };
float phase[KEYS] = { 0 };

int sampleRate = 44100;
int numChannel = 2;

int audioBufSize = 2048;

int octave = 0;

//0 sin
//1 triangle
//2 saw
//3 square
//4 white noise
int waveShapeType = 0;

class ShapeMode
{
public:
    static int const sine = 0;
    static int const triangle = 1;
    static int const saw = 2;
    static int const square = 3;
    static int const whiteNoise = 4;
};

const double PI2 = M_PI * 2;

float baseAFreq = 440;

bool keyBuf_last[sf::Keyboard::Key::KeyCount] = { false };
bool keyBuf[sf::Keyboard::Key::KeyCount] = { false };

int keymap[]{
        sf::Keyboard::Key::Z,
        sf::Keyboard::Key::S,
        sf::Keyboard::Key::X,
        sf::Keyboard::Key::D,
        sf::Keyboard::Key::C,
        sf::Keyboard::Key::V,
        sf::Keyboard::Key::G,
        sf::Keyboard::Key::B,
        sf::Keyboard::Key::H,
        sf::Keyboard::Key::N,
        sf::Keyboard::Key::J,
        sf::Keyboard::Key::M,
        sf::Keyboard::Key::Q,
        sf::Keyboard::Key::Num2,
        sf::Keyboard::Key::W,
        sf::Keyboard::Key::Num3,
        sf::Keyboard::Key::E,
        sf::Keyboard::Key::R,
        sf::Keyboard::Key::Num5,
        sf::Keyboard::Key::T,
        sf::Keyboard::Key::Num6,
        sf::Keyboard::Key::Y,
        sf::Keyboard::Key::Num7,
        sf::Keyboard::Key::U,
        sf::Keyboard::Key::I,
        sf::Keyboard::Key::Num9,
        sf::Keyboard::Key::O,
        sf::Keyboard::Key::Num0,
        sf::Keyboard::Key::P,
        sf::Keyboard::Key::LBracket,
        sf::Keyboard::Key::RBracket,
        sf::Keyboard::Key::Backslash
};

int numKeys = sizeof(keymap) / sizeof(keymap[0]);


class MyStream : public sf::SoundStream
{
public:

    void SetBufSize(int sz, int numChannel, int sampleRate)
    {
        m_samples.resize(sz, 0);
        m_currentSample = 0;
        initialize(numChannel, sampleRate);
    }

private:

    virtual bool onGetData(Chunk& data)
    {
        int len = m_samples.size();
        for (int i = 0; i < len; ++i)
        {
            m_samples[i] = 0;
        }

        data.samples = &m_samples[m_currentSample];

        float s = 0;
        float increment = 0;

        for (int k = 0; k < numKeys; k++)
        {
            if (vol[k] <= 0) continue;

            increment = PI2 * pow(2.0, (k + 3 + 12 * octave) / 12.0) * baseAFreq / sampleRate;

            for (int c = 0; c < audioBufSize; c += numChannel)
            {
                if (waveShapeType == ShapeMode::sine)
                {
                    s = m_samples[c] + sin(phase[k]) * vol[k];
                }
                else if (waveShapeType == ShapeMode::triangle)
                {
                    double t2 = fmod(phase[k], PI2) / (PI2);
                    int t3 = floor(t2 + 0.5f);
                    double t4 = fabs(t2 - t3) * 4 - 1;
                    s = m_samples[c] + t4 * vol[k];
                }
                else if (waveShapeType == ShapeMode::saw)
                {
                    double t2 = phase[k] / PI2;
                    int t3 = floor(t2 + 0.5f);
                    double t4 = (t2 - t3) * 2;
                    s = m_samples[c] + t4 * vol[k];
                }
                else if (waveShapeType == ShapeMode::square)
                {
                    double t2 = fmodf(phase[k], PI2) / (PI2);
                    double t3 = t2 > 0.5 ? 1 : -1;
                    s = m_samples[c] + t3 * vol[k];
                }
                else if (waveShapeType == ShapeMode::whiteNoise)
                {
                    s = rand() % 65536 - 32768;
                }

                if (s > 32767) s = 32767;
                else if (s < -32768) s = -32768;

                m_samples[c] = s;
                m_samples[c + 1] = s;

                phase[k] += increment;

                if (vol[k] < MAXVOL)
                {
                    vol[k] -= DECAY;
                    if (vol[k] <= 0)
                    {
                        vol[k] = 0;
                        break;
                    }
                }
            }
            phase[k] = fmod(phase[k], PI2);
        }

        data.sampleCount = audioBufSize;
        m_currentSample = 0;

        return true;
    }

    virtual void onSeek(sf::Time timeOffset)
    {
        m_currentSample = static_cast<std::size_t>(timeOffset.asSeconds() * getSampleRate() * getChannelCount());
    }

    std::vector<sf::Int16> m_samples;
    std::size_t m_currentSample = -1;
};

bool IsKeyPressOnce(int keyCode)
{
    if (keyBuf[keyCode] && !keyBuf_last[keyCode]) return true;
    else return false;
}

void MousePress(sf::RenderWindow* window, sf::RectangleShape* shape, sf::Rect<float>* rect, int keyNum)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i position = sf::Mouse::getPosition();
        if (rect->contains(position.x, position.y))
        {
            if (keyNum == 1 || keyNum == 4 || keyNum == 7 || keyNum == 10)
                shape->setFillColor(sf::Color::Cyan);
            else
                shape->setFillColor(sf::Color::Green);
            window->clear();
            window->draw(*shape);
            keyBuf[keymap[keyNum]] = true;
        }
    }
    else
    {
        if (keyNum == 1 || keyNum == 4 || keyNum == 7 || keyNum == 10)
            shape->setFillColor(sf::Color::Blue);
        else
            shape->setFillColor(sf::Color::White);
        keyBuf[keymap[keyNum]] = false;

    }
}

void DrawRect(sf::RenderWindow* window, sf::RectangleShape* shape, bool type = false)
{
    if (type == true)
        shape->setFillColor(sf::Color::Blue);
    else
        shape->setFillColor(sf::Color::White);
}

void DrawRectv2(sf::RenderWindow* window, sf::RectangleShape* shape, bool type = false)
{
    if (type == true)
        shape->setFillColor(sf::Color::Cyan);
    else
        shape->setFillColor(sf::Color::Green);
}

class FullRect
{
private:

    sf::RectangleShape* shape;
    sf::Rect<float>* rectForTrack;
    sf::Keyboard::Key key;

public:

    FullRect()
    {
        shape = nullptr;
        rectForTrack = nullptr;
        key = sf::Keyboard::Insert;
    }

    void setFullRect(sf::Vector2f forShape, sf::Vector2f move ,sf::Vector2f countingPoint, sf::Vector2f forRect, sf::Keyboard::Key key);
    
    sf::Rect<float> getTrack() { return *rectForTrack; }
    
    sf::RectangleShape* getShape() { return shape; }

    sf::Keyboard::Key getKey() { return key; }
    
    static void drawAll(sf::RenderWindow* window, FullRect* rectangles, int size);

    static void checkClick(sf::RenderWindow* window, FullRect* rectangles, int size);

    static void checkKeyPress(sf::RenderWindow* window, FullRect* rectangles, int size);
};

void FullRect::setFullRect(sf::Vector2f forShape, sf::Vector2f move ,sf::Vector2f countingPoint, sf::Vector2f forRect, sf::Keyboard::Key key)
{
    shape = new sf::RectangleShape(forShape);
    shape->move(move);
    rectForTrack = new sf::Rect<float>(countingPoint, forRect);
    this->key = key;
}

void FullRect::drawAll(sf::RenderWindow* window ,FullRect* rectangles, int size)
{
    window->clear();
    for (int i = 0; i < size+1; i++)
    {
        window->draw(*(rectangles[i].getShape()));
    }
    window->display();
}

void FullRect::checkClick(sf::RenderWindow* window, FullRect* rectangles, int size)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        for (int i = 0; i < size + 1; i++)
        {
            sf::Vector2i position = sf::Mouse::getPosition();
            if (rectangles[i].getTrack().contains(position.x, position.y))
            {
                window->clear();
                if (rectangles[i].getShape()->getSize().x == 15)
                    DrawRectv2(window, rectangles[i].shape, true);
                else
                    DrawRectv2(window, rectangles[i].shape);
                keyBuf[rectangles[i].getKey()] = true;
            }
        }
    }
    else
    {
        window->clear();
        for (int i = 0; i < size + 1; i++)
        {
            if (rectangles[i].getShape()->getSize().x == 15)
            {
                DrawRect(window, rectangles[i].getShape(), true);
            }
            else
            {
                DrawRect(window, rectangles[i].getShape());
            }
        }
    }
}

void FullRect::checkKeyPress(sf::RenderWindow* window, FullRect* rectangles, int size)
{
    for (int i = 0; i < size+1; i++)
    {
        if (rectangles[i].getShape()->getSize().x == 15)
        {
            if (sf::Keyboard::isKeyPressed(rectangles[i].getKey()))
            {
                DrawRectv2(window, rectangles[i].getShape(), true);
            }
        }
        else
        {
            if (sf::Keyboard::isKeyPressed(rectangles[i].getKey()))
            {
                DrawRectv2(window, rectangles[i].getShape());
            }
        }
    }
}

void setWaveType(sf::String* str, int num)
{
    if (!str->isEmpty())
    {   switch(num)
        {
            case 0:
            {
                str->erase(11, str->getSize());
                str->insert(11, "sin");
            } break;
            case 1:
            {
                str->erase(11, str->getSize());
                str->insert(11, "triangle");
            }break;
            case 2:
            {
                str->erase(11, str->getSize());
                str->insert(11, "saw");
            }break;
            case 3:
            {
                str->erase(11, str->getSize());
                str->insert(11, "square");
            }break;
            case 4:
            {
                str->erase(11, str->getSize());
                str->insert(11, "white noise");
            }break;
            default: break;
        }
    }
}

int main()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode(ScreenWidth, ScreenHeight), "SFML2 Simple Audio Synth");
    MyStream stream;
    stream.SetBufSize(audioBufSize, numChannel, sampleRate);
    stream.play();

    FullRect* pianoKeys = new FullRect[28];
    pianoKeys[0].setFullRect(sf::Vector2f(30, 70), sf::Vector2f(10,50) ,sf::Vector2f(30, 100), sf::Vector2f(70,140), sf::Keyboard::Z);
    pianoKeys[1].setFullRect(sf::Vector2f(15, 35), sf::Vector2f(40, 50), sf::Vector2f(85, 95), sf::Vector2f(40, 70), sf::Keyboard::S);
    pianoKeys[2].setFullRect(sf::Vector2f(30, 70), sf::Vector2f(55, 50), sf::Vector2f(120, 130), sf::Vector2f(85, 140), sf::Keyboard::X);
    pianoKeys[3].setFullRect(sf::Vector2f(30, 70), sf::Vector2f(87, 50), sf::Vector2f(205, 100), sf::Vector2f(70, 140), sf::Keyboard::D);
    pianoKeys[4].setFullRect(sf::Vector2f(15, 35), sf::Vector2f(117, 50), sf::Vector2f(255, 95), sf::Vector2f(50, 70), sf::Keyboard::C);
    pianoKeys[5].setFullRect(sf::Vector2f(30, 70), sf::Vector2f(133, 50), sf::Vector2f(305, 95), sf::Vector2f(70, 140), sf::Keyboard::V);
    pianoKeys[6].setFullRect(sf::Vector2f(30, 70), sf::Vector2f(165, 50), sf::Vector2f(370, 95), sf::Vector2f(85, 140), sf::Keyboard::G);
    pianoKeys[7].setFullRect(sf::Vector2f(15, 35), sf::Vector2f(195, 50), sf::Vector2f(455, 95), sf::Vector2f(50, 70), sf::Keyboard::B);
    pianoKeys[8].setFullRect(sf::Vector2f(30, 70), sf::Vector2f(210, 50), sf::Vector2f(485, 95), sf::Vector2f(70, 140), sf::Keyboard::H);
    pianoKeys[9].setFullRect(sf::Vector2f(30, 70), sf::Vector2f(243, 50), sf::Vector2f(563, 95), sf::Vector2f(70, 140), sf::Keyboard::N);
    pianoKeys[10].setFullRect(sf::Vector2f(15, 35), sf::Vector2f(273, 50), sf::Vector2f(643, 95), sf::Vector2f(50, 70), sf::Keyboard::J);
    pianoKeys[11].setFullRect(sf::Vector2f(30, 70), sf::Vector2f(287, 50), sf::Vector2f(693, 95), sf::Vector2f(70, 140), sf::Keyboard::M);
    pianoKeys[12].setFullRect(sf::Vector2f(30, 70), sf::Vector2f(318, 50), sf::Vector2f(763, 95), sf::Vector2f(70, 140), sf::Keyboard::Q);
    pianoKeys[13].setFullRect(sf::Vector2f(15, 35), sf::Vector2f(348, 50), sf::Vector2f(833, 95), sf::Vector2f(50, 70), sf::Keyboard::Num2);
    pianoKeys[14].setFullRect(sf::Vector2f(30, 70), sf::Vector2f(363, 50), sf::Vector2f(883, 95), sf::Vector2f(70, 140), sf::Keyboard::W);
    pianoKeys[15].setFullRect(sf::Vector2f(30, 70), sf::Vector2f(395, 50), sf::Vector2f(933, 95), sf::Vector2f(70, 140), sf::Keyboard::E);
    pianoKeys[16].setFullRect(sf::Vector2f(15, 35), sf::Vector2f(425, 50), sf::Vector2f(1008, 95), sf::Vector2f(50, 70), sf::Keyboard::Num3);
    pianoKeys[17].setFullRect(sf::Vector2f(30, 70), sf::Vector2f(440, 50), sf::Vector2f(1048, 95), sf::Vector2f(80, 140), sf::Keyboard::R);
    pianoKeys[18].setFullRect(sf::Vector2f(30, 70), sf::Vector2f(473, 50), sf::Vector2f(1108, 95), sf::Vector2f(80, 140), sf::Keyboard::Num5);
    pianoKeys[19].setFullRect(sf::Vector2f(15, 35), sf::Vector2f(503, 50), sf::Vector2f(1208, 95), sf::Vector2f(50, 70), sf::Keyboard::T);
    pianoKeys[20].setFullRect(sf::Vector2f(30, 70), sf::Vector2f(516, 50), sf::Vector2f(1258, 95), sf::Vector2f(80, 140), sf::Keyboard::Y);
    pianoKeys[21].setFullRect(sf::Vector2f(30, 70), sf::Vector2f(548, 50), sf::Vector2f(1310, 95), sf::Vector2f(80, 140), sf::Keyboard::Num6);
    pianoKeys[22].setFullRect(sf::Vector2f(15, 35), sf::Vector2f(578, 50), sf::Vector2f(1360, 95), sf::Vector2f(60, 70), sf::Keyboard::U);
    pianoKeys[23].setFullRect(sf::Vector2f(30, 70), sf::Vector2f(592, 50), sf::Vector2f(1400, 95), sf::Vector2f(80, 140), sf::Keyboard::I);
    pianoKeys[24].setFullRect(sf::Vector2f(30, 70), sf::Vector2f(623, 50), sf::Vector2f(1485, 95), sf::Vector2f(85, 140), sf::Keyboard::Num9);
    pianoKeys[25].setFullRect(sf::Vector2f(15, 35), sf::Vector2f(653, 50), sf::Vector2f(1555, 95), sf::Vector2f(50, 70), sf::Keyboard::O);
    pianoKeys[26].setFullRect(sf::Vector2f(30, 70), sf::Vector2f(668, 50), sf::Vector2f(1595, 95), sf::Vector2f(80, 140), sf::Keyboard::Num0);
    pianoKeys[27].setFullRect(sf::Vector2f(30, 70), sf::Vector2f(700, 50), sf::Vector2f(1670, 95), sf::Vector2f(100, 140), sf::Keyboard::P);

    sf::String strWave = "Wave type: ";
    sf::String strOctave = "Octave: ";

    while (window.isOpen())
    {
        sf::Event ev;
        while (window.pollEvent(ev))
        {
            switch (ev.type)
            {
            case sf::Event::Closed: window.close(); break;
            case sf::Event::KeyPressed:
                keyBuf[ev.key.code] = true;
                break;
            case sf::Event::KeyReleased:
                keyBuf[ev.key.code] = false;
                break;
            case sf::Event::MouseButtonReleased:
            {
                keyBuf[sf::Keyboard::Num9] = false;
                keyBuf[sf::Keyboard::Z] = false;
                for (int i = 0; i < 33; i++)
                {
                    keyBuf[i] = false;
                }
            }break;
            default:
                break;
            }
        }

        if (keyBuf[sf::Keyboard::Escape])
        {
            window.close();
        }

        for (int key = 0; key < numKeys; ++key)
        {
            if (keyBuf[keymap[key]] && vol[key] < MAXVOL)
            {
                phase[key] = 0;
                vol[key] = MAXVOL + DECAY / 2;
            }

            if (!keyBuf[keymap[key]] && vol[key] > 0)
            {
                vol[key] -= DECAY;
            }
        }

        if (IsKeyPressOnce(sf::Keyboard::Key::Left))
        {
            --waveShapeType;
            waveShapeType = waveShapeType < 0 ? 4 : waveShapeType;
            setWaveType(&strWave, waveShapeType);
            window.setTitle(strWave);
        }
        if (IsKeyPressOnce(sf::Keyboard::Key::Right))
        {
            ++waveShapeType;
            waveShapeType = waveShapeType > 4 ? 0 : waveShapeType;
            setWaveType(&strWave, waveShapeType);
            window.setTitle(strWave);
        }

        if (IsKeyPressOnce(sf::Keyboard::Key::Down))
        {
            --octave;
            octave = octave < -3 ? -3 : octave;
        }
        if (IsKeyPressOnce(sf::Keyboard::Key::Up))
        {
            ++octave;
            octave = octave > 4 ? 4 : octave;
        }
        
        FullRect::drawAll(&window, pianoKeys, 27);

        FullRect::checkClick(&window, pianoKeys, 27);
        
        FullRect::checkKeyPress(&window, pianoKeys, 27);
        
        sf::sleep(sf::microseconds(1));

        for (int k = 0; k < sf::Keyboard::Key::KeyCount; ++k)
        {
            keyBuf_last[k] = keyBuf[k];
        }
    }
    return 0;
}