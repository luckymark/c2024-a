#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <ctime>

// Number of Chromosomes Used for Solve

const int noOfChromesomes = 10;
const int moveStringLength = 16;
const float crossoverRate = 0.7;
const float mutationRate = 0.05;

// Chromosones, tracking lockation, chromosome string, and fitness

class Chromosome {

public:

    std::string moveString = "";
    int currentX = 0;
    int currentY = 0;
    int finalX = 0;
    int finalY = 0;
    int positionInChrome = 0;
    float fitness = 0;

};

int main() {

    srand(time(NULL));

    // Open File Given to Solve
    std::fstream mapFile;
    std::string fileName = "";

    std::cout << "Please Enter Text File Dir. Name (Ex. 'Maze1.txt' or 'Maze2.txt'): ";
    std::cin >> fileName;

    std::cout << std::endl;

    mapFile.open(fileName, std::ios::in);

    int mapX = 0;
    int mapY = 0;
    int mapStartX = 0;
    int mapStartY = 0;
    int mapEndX = 0;
    int mapEndY = 0;

    // If File Doesn't Open, Stop
    if (!mapFile.is_open()) {

        std::cout << "ERROR: Unable to Open File\n" << std::endl;
        system("PAUSE");
        return 1;

    }

    // Grab Size of Grid from Start of String
    mapFile >> mapX >> mapY;

    // Create Int Array of Size Given
    std::vector<std::vector<int>> map;
    map.resize(mapX);
    for (int i = 0; i < mapX; i++) {

        map[i].resize(mapY);

    }

    // Run Through Map Positions and
    // Determine Their Value from Map File
    // Define Start and End

    for (int i = 0; i < mapY; i++) {

        for (int j = 0; j < mapX; j++) {

            mapFile >> map[j][i];

            if (map[j][i] == 2) {

                mapStartX = j;
                mapStartY = i;

            }
            else if (map[j][i] == 3) {

                mapEndX = j;
                mapEndY = i;

            }

        }

    }

    // Display Important Info and Map
    std::cout << "----------------------------------------------" << std::endl << "Map Size: " << mapX << ", " << mapY << std::endl
              << "\nStart Point: " << mapStartX << ", " << mapStartY
              << "\nEnd Point: " << mapEndX << ", " << mapEndY << std::endl << std::endl;


    std::cout << "Map Layout:\n" << std::endl;

    for (int i = 0; i < mapY; i++) {

        std::cout << "\t";

        for (int j = 0; j < mapX; j++) {

            if (map[j][i] == 0) {

                std::cout << ". ";

            }
            else if (map[j][i] == 1) {

                std::cout << "X ";

            }
            else if (map[j][i] == 2) {

                std::cout << "! ";
                mapStartX = j;
                mapStartY = i;

            }
            else if (map[j][i] == 3) {

                std::cout << "? ";
                mapEndX = j;
                mapEndY = i;

            }

        }

        std::cout << "\n";

    }

    std::cout << "\n----------------------------------------------\n\n";

    clock_t start = clock();

    // Create Array of Chromosomes
    Chromosome chromosomes[noOfChromesomes];
    bool routeFound = false;

    // Create Chromosome String for Each Chromosome
    // Seperate for Other For Loop so it Doesn't Override Future Generations
    for (int i = 0; i < noOfChromesomes; i++) {

        // ... Create String For Movement Control
        for (int j = 0; j < moveStringLength; j++) {

            float r = (float)rand() / RAND_MAX;

            if (r < 0.5) {

                chromosomes[i].moveString.push_back('0');

            }
            else {

                chromosomes[i].moveString.push_back('1');

            }

        }

    }

    int count = 0;
    std::string route = "";

    while (routeFound == false || count == 100000) {

        count++;
        std::cout << "Iteration No." << count << std::endl;

        // For Each Chromosome...
        for (int i = 0; i < noOfChromesomes; i++) {

            // ... Define Starting Parameters
            chromosomes[i].currentX = mapStartX;
            chromosomes[i].currentY = mapStartY;
            chromosomes[i].positionInChrome = 0;
            chromosomes[i].fitness = 0.0f;

            // ...Move Chromosome, Following it's String
            do {

                // Move Up

                if (chromosomes[i].moveString[chromosomes[i].positionInChrome] == '0' &&
                    chromosomes[i].moveString[chromosomes[i].positionInChrome + 1] == '0') {

                    chromosomes[i].currentX = chromosomes[i].currentX;
                    chromosomes[i].currentY = chromosomes[i].currentY - 1;

                    // Out Of Bounds

                    if ((chromosomes[i].currentX < 0) || (chromosomes[i].currentY < 0) ||
                        (chromosomes[i].currentX > mapX - 1) || (chromosomes[i].currentY > mapY - 1)) {

                        chromosomes[i].currentX = chromosomes[i].currentX;
                        chromosomes[i].currentY = chromosomes[i].currentY + 1;

                    }

                        // Obstacle Hit

                    else if (map[chromosomes[i].currentX][chromosomes[i].currentY] == 1) {

                        chromosomes[i].currentX = chromosomes[i].currentX;
                        chromosomes[i].currentY = chromosomes[i].currentY + 1;

                    }

                        // End Reached

                    else if (chromosomes[i].currentX == mapEndX && chromosomes[i].currentY == mapEndY) {

                        std::cout << std::endl << "\nRoute Found!" << std::endl << "Route: "
                                  << chromosomes[i].moveString.substr(0, chromosomes[i].positionInChrome + 2) << std::endl;
                        route = chromosomes[i].moveString.substr(0, chromosomes[i].positionInChrome + 2);
                        routeFound = true;
                        break;

                    }

                }

                    // Move Down

                else if (chromosomes[i].moveString[chromosomes[i].positionInChrome] == '1' &&
                         chromosomes[i].moveString[chromosomes[i].positionInChrome + 1] == '0') {

                    chromosomes[i].currentX = chromosomes[i].currentX;
                    chromosomes[i].currentY = chromosomes[i].currentY + 1;

                    // Out Of Bounds

                    if ((chromosomes[i].currentX < 0) || (chromosomes[i].currentY < 0) ||
                        (chromosomes[i].currentX > mapX - 1) || (chromosomes[i].currentY > mapY - 1)) {

                        chromosomes[i].currentX = chromosomes[i].currentX;
                        chromosomes[i].currentY = chromosomes[i].currentY - 1;

                    }

                        // Obstacle Hit

                    else if (map[chromosomes[i].currentX][chromosomes[i].currentY] == 1) {

                        chromosomes[i].currentX = chromosomes[i].currentX;
                        chromosomes[i].currentY = chromosomes[i].currentY - 1;

                    }

                        // End Reached

                    else if (chromosomes[i].currentX == mapEndX && chromosomes[i].currentY == mapEndY) {

                        std::cout << "\nRoute Found!" << std::endl << "Route: "
                                  << chromosomes[i].moveString.substr(0, chromosomes[i].positionInChrome + 2) << std::endl;
                        route = chromosomes[i].moveString.substr(0, chromosomes[i].positionInChrome + 2);
                        routeFound = true;
                        break;

                    }

                }

                    // Move Right

                else if (chromosomes[i].moveString[chromosomes[i].positionInChrome] == '0' &&
                         chromosomes[i].moveString[chromosomes[i].positionInChrome + 1] == '1') {

                    chromosomes[i].currentX = chromosomes[i].currentX + 1;
                    chromosomes[i].currentY = chromosomes[i].currentY;

                    // Out Of Bounds

                    if ((chromosomes[i].currentX < 0) || (chromosomes[i].currentY < 0) ||
                        (chromosomes[i].currentX > mapX - 1) || (chromosomes[i].currentY > mapY - 1)) {

                        chromosomes[i].currentX = chromosomes[i].currentX - 1;
                        chromosomes[i].currentY = chromosomes[i].currentY;

                    }

                        // Obstacle Hit

                    else if (map[chromosomes[i].currentX][chromosomes[i].currentY] == 1) {

                        chromosomes[i].currentX = chromosomes[i].currentX - 1;
                        chromosomes[i].currentY = chromosomes[i].currentY;

                    }

                        // End Reached

                    else if (chromosomes[i].currentX == mapEndX && chromosomes[i].currentY == mapEndY) {

                        std::cout << "\nRoute Found!" << std::endl << "Route: "
                                  << chromosomes[i].moveString.substr(0, chromosomes[i].positionInChrome + 2) << std::endl;
                        route = chromosomes[i].moveString.substr(0, chromosomes[i].positionInChrome + 2);
                        routeFound = true;
                        break;

                    }

                }

                    // Move Left

                else if (chromosomes[i].moveString[chromosomes[i].positionInChrome] == '1' &&
                         chromosomes[i].moveString[chromosomes[i].positionInChrome + 1] == '1') {

                    chromosomes[i].currentX = chromosomes[i].currentX - 1;
                    chromosomes[i].currentY = chromosomes[i].currentY;

                    // Out Of Bounds

                    if ((chromosomes[i].currentX < 0) || (chromosomes[i].currentY < 0) ||
                        (chromosomes[i].currentX > mapX - 1) || (chromosomes[i].currentY > mapY - 1)) {

                        chromosomes[i].currentX = chromosomes[i].currentX + 1;
                        chromosomes[i].currentY = chromosomes[i].currentY;

                    }

                        // Obstacle Hit

                    else if (map[chromosomes[i].currentX][chromosomes[i].currentY] == 1) {

                        chromosomes[i].currentX = chromosomes[i].currentX + 1;
                        chromosomes[i].currentY = chromosomes[i].currentY;

                    }

                        // End Reached

                    else if (chromosomes[i].currentX == mapEndX && chromosomes[i].currentY == mapEndY) {

                        std::cout << "\nRoute Found!" << std::endl << "Route: "
                                  << chromosomes[i].moveString.substr(0, chromosomes[i].positionInChrome + 2) << std::endl;
                        route = chromosomes[i].moveString.substr(0, chromosomes[i].positionInChrome + 2);
                        routeFound = true;
                        break;

                    }

                }

                chromosomes[i].positionInChrome += 2;

            } while (chromosomes[i].positionInChrome <= moveStringLength);

            // ... Define Chromosome's Final Position
            chromosomes[i].finalX = chromosomes[i].currentX;
            chromosomes[i].finalY = chromosomes[i].currentY;

            // ... Calculate Chromosome's Fitness
            int dx, dy;

            if (chromosomes[i].finalX > mapEndX) {

                dx = chromosomes[i].finalX - mapEndX;

            }
            else {

                dx = mapEndX - chromosomes[i].finalX;

            }

            if (chromosomes[i].finalY > mapEndY) {

                dy = chromosomes[i].finalY - mapEndY;

            }
            else {

                dy = mapEndY - chromosomes[i].finalY;

            }

            //std::cout << "dx: " << dx << std::endl << "dy: " << dy << std::endl;

            chromosomes[i].fitness = 1.0f / ((float)dx + (float)dy + 1.0f);

            //std::cout << "Chromosome String: " << chromosomes[i].length << std::endl << "Chromosome Fitness: " << chromosomes[i].fitness << std::endl;

        }

        // Find Fitness Sum, For Spinner Boundries
        float fitnessSum = 0.0f;

        for (int i = 0; i < noOfChromesomes; i++) {

            fitnessSum += chromosomes[i].fitness;

        }

        //std::cout << "Fitness Sum: " << fitnessSum;

        // Create List of Boundries,
        // To be Used Later to Decide What Chromosome to Reproduce
        float boundries[noOfChromesomes - 1];
        float boundrySum = 0;

        for (int i = 0; i < noOfChromesomes - 1; i++) {

            if (i == 0) {

                boundries[i] = 100 * (chromosomes[i].fitness / fitnessSum);

            }
            else {

                boundries[i] = (100 * (chromosomes[i].fitness / fitnessSum)) + boundries[i - 1];

            }

        }

        // Crossover Operation

        // Array of New Cromosomes, Looped Through in Twos
        Chromosome childChromosomes[noOfChromesomes];

        for (int i = 0; i < noOfChromesomes / 2; i++) {

            // Couplets of Randomly Chosen Cromosomes
            Chromosome parentChromosomes[2];

            for (int j = 0; j < 2; j++) {

                float randomChromosomeFloat = (float)rand() / RAND_MAX;
                int randChromosome = 100 * randomChromosomeFloat;

                if ((randChromosome >= 0) && (randChromosome < boundries[0])) {

                    parentChromosomes[j] = chromosomes[0];

                }
                else if ((randChromosome >= boundries[0]) && (randChromosome < boundries[1])) {

                    parentChromosomes[j] = chromosomes[1];

                }
                else if ((randChromosome >= boundries[1]) && (randChromosome < boundries[2])) {

                    parentChromosomes[j] = chromosomes[2];

                }
                else if ((randChromosome >= boundries[2]) && (randChromosome < boundries[3])) {

                    parentChromosomes[j] = chromosomes[3];

                }
                else if ((randChromosome >= boundries[3]) && (randChromosome < boundries[4])) {

                    parentChromosomes[j] = chromosomes[4];

                }
                else if ((randChromosome >= boundries[4]) && (randChromosome < boundries[5])) {

                    parentChromosomes[j] = chromosomes[5];

                }
                else if ((randChromosome >= boundries[5]) && (randChromosome < boundries[6])) {

                    parentChromosomes[j] = chromosomes[6];

                }
                else if ((randChromosome >= boundries[6]) && (randChromosome < boundries[7])) {

                    parentChromosomes[j] = chromosomes[7];

                }
                else if ((randChromosome >= boundries[7]) && (randChromosome < boundries[8])) {

                    parentChromosomes[j] = chromosomes[8];

                }
                else if ((randChromosome >= boundries[8]) && (randChromosome <= 100)) {

                    parentChromosomes[j] = chromosomes[9];

                }

            }

            // Decide Whether to Crossover or Not
            float crossover = (float)rand() / RAND_MAX;

            // First Child: First Half of Parent1, Last Half of Parent2
            // Second Child: First Half of Parent2, Last Half of Parent1
            if (crossover <= crossoverRate) {

                childChromosomes[i * 2].moveString.clear();
                childChromosomes[i * 2].moveString = parentChromosomes[0].moveString.substr(0, moveStringLength / 2)
                                                     + parentChromosomes[1].moveString.substr(moveStringLength / 2, moveStringLength / 2);

                childChromosomes[(i * 2) + 1].moveString.clear();
                childChromosomes[(i * 2) + 1].moveString = parentChromosomes[1].moveString.substr(0, moveStringLength / 2)
                                                           + parentChromosomes[0].moveString.substr(moveStringLength / 2, moveStringLength / 2);

            }
            else {

                childChromosomes[i * 2] = parentChromosomes[0];
                childChromosomes[(i * 2) + 1] = parentChromosomes[1];

            }

        }

        // Mutation Stage

        for (int i = 0; i < noOfChromesomes; i++) {

            for (int j = 0; j < moveStringLength; j++) {

                float mutation = (float)rand() / RAND_MAX;

                if (mutation <= mutationRate) {

                    if (childChromosomes[i].moveString[j] == '0') {

                        childChromosomes[i].moveString[j] = '1';

                    }
                    else {

                        childChromosomes[i].moveString[j] = '0';

                    }

                }

            }

            chromosomes[i] = childChromosomes[i];

        }

    }

    clock_t end = clock();

    if (routeFound == true) {

        int currPosX = mapStartX;
        int currPosY = mapStartY;

        for (int i = 0; i < route.length() - 2; i += 2) {

            if (route[i] == '0' && route[i + 1] == '0') {

                currPosX = currPosX;
                currPosY = currPosY - 1;

                // Out Of Bounds

                if ((currPosX < 0) || (currPosY < 0) ||
                    (currPosX > mapX - 1) || (currPosY > mapY - 1)) {

                    currPosX = currPosX;
                    currPosY = currPosY + 1;

                }

                    // Obstacle Hit

                else if (map[currPosX][currPosY] == 1) {

                    currPosX = currPosX;
                    currPosY = currPosY + 1;

                }

                    // Moved Over Start

                else if (map[currPosX][currPosY] == 2) {

                    map[currPosX][currPosY] = 2;

                }

                    // Route

                else {

                    map[currPosX][currPosY] = 4;

                }

            }

                // Move Down

            else if (route[i] == '1' && route[i + 1] == '0') {

                currPosX = currPosX;
                currPosY = currPosY + 1;

                // Out Of Bounds

                if ((currPosX < 0) || (currPosY < 0) ||
                    (currPosX > mapX - 1) || (currPosY > mapY - 1)) {

                    currPosX = currPosX;
                    currPosY = currPosY - 1;

                }

                    // Obstacle Hit

                else if (map[currPosX][currPosY] == 1) {

                    currPosX = currPosX;
                    currPosY = currPosY - 1;

                }

                    // Moved Over Start

                else if (map[currPosX][currPosY] == 2) {

                    map[currPosX][currPosY] = 2;

                }

                    // Route

                else {

                    map[currPosX][currPosY] = 4;

                }

            }

                // Move Right

            else if (route[i] == '0' && route[i + 1] == '1') {

                currPosX = currPosX + 1;
                currPosY = currPosY;

                // Out Of Bounds

                if ((currPosX < 0) || (currPosY < 0) ||
                    (currPosX > mapX - 1) || (currPosY > mapY - 1)) {

                    currPosX = currPosX - 1;
                    currPosY = currPosY;

                }

                    // Obstacle Hit

                else if (map[currPosX][currPosY] == 1) {

                    currPosX = currPosX - 1;
                    currPosY = currPosY;

                }

                    // Moved Over Start

                else if (map[currPosX][currPosY] == 2) {

                    map[currPosX][currPosY] = 2;

                }

                    // Route

                else {

                    map[currPosX][currPosY] = 4;

                }

            }

                // Move Left

            else if (route[i] == '1' && route[i + 1] == '1') {

                currPosX = currPosX - 1;
                currPosY = currPosY;

                // Out Of Bounds

                if ((currPosX < 0) || (currPosY < 0) ||
                    (currPosX > mapX - 1) || (currPosY > mapY - 1)) {

                    currPosX = currPosX + 1;
                    currPosY = currPosY;

                }

                    // Obstacle Hit

                else if (map[currPosX][currPosY] == 1) {

                    currPosX = currPosX + 1;
                    currPosY = currPosY;

                }

                    // Moved Over Start

                else if (map[currPosX][currPosY] == 2) {

                    map[currPosX][currPosY] = 2;

                }

                    // Route

                else {

                    map[currPosX][currPosY] = 4;

                }

            }

        }

        std::cout << std::endl << "Solved Map:\n" << std::endl;

        for (int i = 0; i < mapY; i++) {

            std::cout << "\t";

            for (int j = 0; j < mapX; j++) {

                if (map[j][i] == 0) {

                    std::cout << ". ";

                }
                else if (map[j][i] == 1) {

                    std::cout << "X ";

                }
                else if (map[j][i] == 2) {

                    std::cout << "! ";

                }
                else if (map[j][i] == 3) {

                    std::cout << "? ";

                }
                else if (map[j][i] == 4) {

                    std::cout << "r ";

                }

            }

            std::cout << "\n";

        }

    }

    std::cout << "\nTime Taken: " << end - start << std::endl << std::endl;
    system("PAUSE");

}