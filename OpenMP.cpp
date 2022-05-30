#include <iostream>
#include <omp.h> 
#include <io.h>
#include "unistd.h"
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    //for (int p = 1; p < 17; p++)
    {
        int p = 4;
        omp_set_num_threads(p);
        int startTime;
        int endTime;
        srand(time(NULL));
        int minDifficuly = 3;
        int maxDifficulty = 10;
        double amountOfRolls = 1000000;
        int maxDices = 10;
        double result[8][10][4];
        startTime = time(NULL);
        cout << "Difficulty, Dices, Total Succeses, Average Succeses, Pass Chance, Botch Chance" << endl;
#pragma omp parallel for
        for (int difficulty = minDifficuly; difficulty <= maxDifficulty; difficulty++)
        {
            double totalSucceses;
            double passes;
            double botches;
            double succeses;
            int currentRoll;
            bool botch;
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
                result[difficulty - 3][currrentDices - 1][0] = totalSucceses;
                result[difficulty - 3][currrentDices - 1][1] = totalSucceses / amountOfRolls;
                result[difficulty - 3][currrentDices - 1][2] = passes / amountOfRolls;
                result[difficulty - 3][currrentDices - 1][3] = botches / amountOfRolls;
            }
        }
        for (int difficulty = minDifficuly; difficulty <= maxDifficulty; difficulty++)
        {
            for (int currrentDices = 1; currrentDices <= maxDices; currrentDices++)
            {
                cout << difficulty << ",\t" << currrentDices << ",\t" << result[difficulty - 3][currrentDices - 1][0] << ",\t" << result[difficulty - 3][currrentDices - 1][1] << ",\t" << result[difficulty - 3][currrentDices - 1][2] << ",\t" << result[difficulty - 3][currrentDices - 1][3] << endl;
            }
        }
        endTime = time(NULL);
        cout << p << ": Time passed: " << endTime - startTime << endl;
    }
}

