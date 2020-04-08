#include <iostream>
#include <fstream>

auto main(int ArgCount, char** ArgVector) -> int
{
    if (ArgCount == 1) 
    {
        int NumberLn = 1;
        std::string Line;
        std::ifstream IStream("Todo.txt");

        while (std::getline(IStream, Line))
        {
            std::cout 
                << NumberLn 
                << ". " 
                << Line
                << '\n';
            ++NumberLn;
        }

        IStream.close();
    }

    if (ArgCount > 1) 
    {
        // Clear todo.
        if (ArgVector[1][0] == '-') {
            std::ofstream OStream("Todo.txt");
            OStream << "";
            OStream.close();
        }
        // Remove todo by ID.
        else if (std::isdigit(ArgVector[1][0])) 
        {
            int NumberLn = 1, 
                RemovedLn = std::stoi(ArgVector[1]);
            std::string Line, Tmp;
            std::ifstream IStream("Todo.txt");

            while (std::getline(IStream, Line))
            {
                if (NumberLn != RemovedLn) 
                {
                    Tmp += Line;
                    Tmp += '\n';
                }
                ++NumberLn;
            }

            IStream.close();

            std::ofstream OStream("Todo.txt");
            OStream << Tmp;
            OStream.close();
        }
        // Create new todo.
        else 
        {
            std::string NewItem = ArgVector[1];
            for (int Index = 2; Index < ArgCount; ++Index)
            {
                NewItem += ' ';
                NewItem += ArgVector[Index];
            }
            NewItem += '\n';

            std::ofstream OStream("Todo.txt", std::ios_base::app);
            OStream << NewItem;
            OStream.close();
        }
    }
}
