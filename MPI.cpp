#include <mpi.h>
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;
double summBuffer(int* buffer, int comm_size, int offset)
{
    double result = 0;
    for (int i = 0; i < comm_size; i++)
    {
        result += buffer[i * 3+offset];
    }
    return result;
}
int main(int argc, char** argv) {
    int startTime = time(NULL);
    double total_amount_of_tests = 1000000;
    MPI_Init(NULL, NULL);
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    int comm_size;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    int tests_per_process = total_amount_of_tests / comm_size;
    srand(time(NULL)+my_rank);
    
    int rootRank = 0;
    int endTime;
    int minDifficuly = 3;
    int maxDifficulty = 10;
    int totalDifficulties = maxDifficulty - minDifficuly + 1;
    int amountOfParams = 3;
    int maxDices = 10;
    double totalSucceses;
    double passes;
    double botches;
    double succeses;
    int currentRoll;
    bool botch;
    for (int difficulty = minDifficuly; difficulty <= maxDifficulty; difficulty++)
    {
        for (int currrentDices = 1; currrentDices <= maxDices; currrentDices++)
        {
            totalSucceses = 0;
            passes = 0;
            botches = 0;
            for (int roll = 0; roll < tests_per_process; roll++)
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
            int value[3] = { totalSucceses, passes, botches  };
            if (my_rank == rootRank)
            {
                int* buffer = new int[comm_size*3];
                MPI_Gather(&value, 3, MPI_INT, buffer, 3, MPI_INT, rootRank, MPI_COMM_WORLD);
                printf("%d\t", difficulty);
                printf("%d\t", currrentDices);
                printf("%.4f\t", summBuffer(buffer, comm_size, 0));
                printf("%.4f\t", summBuffer(buffer, comm_size, 0) / total_amount_of_tests);
                printf("%.4f\t", summBuffer(buffer, comm_size, 1) / total_amount_of_tests) ;
                printf("%.4f\n", summBuffer(buffer, comm_size, 2) / total_amount_of_tests) ;
            }
            else
            {
                MPI_Gather(&value, 3, MPI_INT, NULL, 0, MPI_INT, rootRank, MPI_COMM_WORLD);
            }        
        }
    }
    
    if (my_rank == rootRank)
    {
        int endTime = time(NULL);
        int resultTime = endTime - startTime;
        printf("%d", resultTime);
    }
    // Finalize the MPI environment.
    MPI_Finalize();
}