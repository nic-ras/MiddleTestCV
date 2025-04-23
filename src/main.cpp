#include <iostream>

#include "dataset.h"

static const std::string s_dataFolder("/home/noyan/ws/MiddleTestCV/data");

// TODO
int main()
{
    std::string dataFolder;
    std::cout << "Enter path to data folder (\"./data/\" for example): ";
    std::getline(std::cin, dataFolder);

    std::unique_ptr<Dataset> dataset = Dataset::load(dataFolder);

    dataset->print();

    return 0;
}
