#include <random>
#include <iostream>
#include <bitset>

auto Random() -> float
{
    static std::random_device SourceRNG;
    static std::default_random_engine RNG(SourceRNG());

    std::uniform_real_distribution<float> Distribution;

    return Distribution(RNG);
}

auto main() -> int
{
    int Rule = 90;
    size_t FieldSize = 100,
           MaxGeneration = 20;
    std::string Field,
                StrRule = std::bitset<8>(Rule).to_string();

    for (size_t I = 0; I < FieldSize; ++I) 
    {
        //Field += Random() > 0.5 ? '1' : '0';
        Field += ' ';
    }
    Field[FieldSize / 2] = '1';

    for (size_t I = 0; I < MaxGeneration; ++I) 
    {
        std::string NextField;
        for (size_t J = 0; J < FieldSize; ++J) 
        {
            std::string Current;
            Current += Field[J - 1] == '1' ? '1' : '0';
            Current += Field[J]     == '1' ? '1' : '0';
            Current += Field[J + 1] == '1' ? '1' : '0';

            for (int K = 7; K > -1; --K) 
            {
                std::string SubRule = std::bitset<3>(K).to_string();
                if (Current == SubRule)
                {
                    NextField += StrRule[K];
                    break;
                }
            }
        }

        for (size_t J = 0; J < FieldSize; ++J) 
        {
            std::cout << (Field[J] == '1' ? '*' : ' ');
        } 
        std::cout << '\n';

        Field = NextField;
    }

}
