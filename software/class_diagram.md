# Drill Locating Block Diagram

``` mermaid

    classDiagram

        class MCP6S2x{
            -uint8_t cs
            -uint8_t channels
            -uint8_t inputPin
            -uint8_t gain
            -uint8_t channel
            -SPISettings settings

            MCP6S2x(uint8_t inputPin, uint8_t cs, uint8_t channels)
            bool setGain(uint8_t newGain)
            bool changeChannel(uint8_t ch)
            int getValue()
            uint8_t getGain()
            bool isValidGain(uint8_t newGain)
            bool shutdown()
        }
    
        class LoopAntenna{

            -struct GainInfo[int gain, uint8_t gain1, uint8_t gain2]
            -MCP6S2x* amp1
            -MCP6S2x* amp2
            -uint8_t amp1Ch
            -uint8_t amp2Ch
            -uint8_t i
            -uint8_t index
            -bool above
            -int amplitude
            -int totalGain
            -int mean
            -int readings[SAMPLES]
            -GainInfo tree[GAINS_SIZE]

            LoopAntenna(MCP6S2x* ampA, MCP6S2x* ampB, uint8_t ch1, uint8_t ch2)
            void measureAmplitude()
            void calcAmplitude()
            void bst(int desired)
            int getTotalGain()
            bool isFlat()
            void calcMean()
            int getAmplitude()
            float getOGAmplitude()
        }

        LoopAntenna --> MCP6S2x : Has
```
