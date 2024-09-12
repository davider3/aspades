# Drill Locating Block Diagram

``` mermaid

    classDiagram

        class MCP6S2x{
            uint8_t cs
            uint8_t channels
            uint8_t inputPin
            uint8_t gain
            uint8_t channel
            SPISettings settings

            MCP6S2x(uint8_t inputPin, uint8_t cs, uint8_t channels)
            bool setGain(uint8_t newGain)
            bool changeChannel(uint8_t ch)
            int getValue()
            uint8_t getGain()
        }
    
        class Antenna{
            -Amplifier xy
            -Amplifier xz
            -Amplifier yz
            -int input pin
        }

```

::schemdraw:: alt="My Circuit Diagram"
    += elm.Resistor().right().label('1Ω')
    += elm.Capacitor().down().label('10μF')
    += elm.Line().left()
    += elm.SourceSin().up().label('10V')
::end-schemdraw::
