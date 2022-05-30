#include <iostream>

using namespace std;

int main()
{
    int startTime;
    int endTime;
    srand(time(NULL));
    int minDifficuly = 3;
    int maxDifficulty = 10;
    double amountOfRolls = 1000000;
    int maxDices = 10;
    double totalSucceses;
    double passes;
    double botches;
    double succeses;
    int currentRoll;
    bool botch;
    startTime = time(NULL);
    cout << "Difficulty, Dices, Total Succeses, Average Succeses, Pass Chance, Botch Chance" << endl;
    for (int difficulty = minDifficuly; difficulty <= maxDifficulty; difficulty++)
    {
        for (int currrentDices = 1; currrentDices <= maxDices; currrentDices++)
        {
            totalSucceses = 0;
            passes = 0;
            botches = 0;
            for (int roll = 0; roll < amountOfRolls; roll++)
            {
                succeses = 0;
                botch = true;
                for (int dices = 0; dices < currrentDices; dices++)
                {
                    currentRoll = rand() % 10 + 1;
                    if (currentRoll == 1)
                        succeses--;
                    if (currentRoll >= difficulty)
                    {
                        succeses++;
                        botch = false;
                    }
                }
                totalSucceses += succeses;
                if (succeses > 0)
                    passes++;
                if (succeses < 0 && botch)
                    botches++;
            }
            cout << difficulty << "," << currrentDices << "," << totalSucceses << "," << totalSucceses / amountOfRolls << "," << passes / amountOfRolls << "," << botches / amountOfRolls << endl;
        }
    }
    endTime = time(NULL);
    cout <<"Time passed: " << endTime - startTime << endl;
}

