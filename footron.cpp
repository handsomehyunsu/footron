#include <iostream>
#include <fstream>
#include <stdio.h>
#include <iomanip>
#include <string>

using namespace std;

const int ttRead = 10;
const int ttWrite = 11;
const int ttLoad = 20;
const int ttStore = 21;
const int ttAdd = 30;
const int ttSubstract = 31;
const int ttDivide = 32;
const int ttMultiply = 33;
const int ttBranch = 40;
const int ttBranchNegative = 41;
const int ttBranchZero = 42;
const int ttHalt = 43;

class Footron
{
public:
    Footron(); // contructor
    void readFile();
    void enterInstruction(int memoryValue, int index);
    void printMemory();
    void instructionOperator();
    void emulator();

private:
    string file;
    int *memory;
    int accumulator;
    int instructionAddress;
    int opCode;
    int operand;
    int instruction;
    int finalValue;
};

// initialize of Footron
Footron::Footron()
{
    memory = new int[100];
    for (int i = 0; i < 100; i++)
    {
        memory[i] = 0;
    }
    accumulator = 0;
    instructionAddress = 0;
    opCode = 0;
    operand = 0;
    instruction = 0;
    finalValue = 0;
}

// This method that will read file
void Footron::readFile()
{
    string fileName;
    int num = -1;
    // int n = 0;
    ifstream readFile;
    cout << "Which file do you want to read (Only enter the option number)" << endl;
    cout << "Options : " << endl;
    cout << "1 : footronSample1.txt" << endl;
    cout << "2 : footronSample2.txt" << endl;
    cout << "3 : footronSample3.txt" << endl;
    cout << "Enter the number : ";
    cin >> fileName;
    file = fileName;

    readFile.open("footronSample" + fileName + ".txt");
    if (readFile.is_open())
    {
        while (!readFile.eof())
        {
            string str;
            getline(readFile, str);
            num++;
            //++n;
            if (str.size() != 5)
            {
                str = "0000";
                enterInstruction(stoi(str), num);
            }
            else
            {
                enterInstruction(stoi(str), num);
            }
        }
        // cout << "line : " << n << endl;

        readFile.close();
    }
    instructionOperator();
}

// This method that will fill the memory with intruction
void Footron::enterInstruction(int memoryValue, int index)
{
    memory[index] = memoryValue;
}

// This method that will start executing the instruction stored in memory by
// copy the instruction from the memory and make 100 memory cell
void Footron::instructionOperator()
{
    while (instructionAddress < 100)
    {
        instruction = memory[instructionAddress];
        emulator();
    }
}

// Execution function. This function will splits operand and opcode.
// And execute instruction by the opcode on operand.
void Footron::emulator()
{
    int num;
    opCode = instruction / 100;
    operand = instruction % 100;
    ++instructionAddress;

    switch (opCode)
    {
    case ttRead:
        cout << "Enter number from 0001 to 9999 : ";
        cin >> num;
        while (num < 0 || num >= 9999)
        {
            cout << "overflow" << endl;
            cin >> num;
        }
        memory[operand] = num;
        break;
    case ttWrite:
        finalValue = memory[operand];
        break;
    case ttLoad:
        accumulator = memory[operand];
        break;
    case ttStore:
        memory[operand] = accumulator;
        break;
    case ttAdd:
        if (accumulator + memory[operand] > 9999 || accumulator + memory[operand] < 1)
        {
            cout << "Add error" << endl;
        }
        else
        {
            accumulator += memory[operand];
        }
        break;
    case ttSubstract:
        if (accumulator - memory[operand] > 9999 || accumulator - memory[operand] < -9999)
        {
            cout << "Substract error" << endl;
        }
        else
        {
            accumulator -= memory[operand];
        }
        break;
    case ttDivide:
        if (memory[operand] == 0)
        {
            cout << "can not divide by 0" << endl;
        }
        else
        {
            accumulator /= memory[operand];
        }
        break;
    case ttMultiply:
        if (accumulator * memory[operand] > 9999 || accumulator * memory[operand] < 0)
        {
            cout << "Multiply error" << endl;
        }
        else
        {
            accumulator *= memory[operand];
        }
        break;
    case ttBranch:
        instructionAddress = operand;
        break;
    case ttBranchNegative:
        if (accumulator < 0)
        {
            instructionAddress = operand;
        }
    case ttBranchZero:
        if (accumulator == 0)
        {
            instructionAddress = operand;
        }
        break;
    case ttHalt:
        cout << "----- Footron Simulator terminated -----" << endl;
        printMemory();
        instructionAddress = 100; // set to end of the array to stop executing
        char y;
        cout << "Do you want to select another option? " << endl;
        cout << "If yes, press y. if not, press any key" << endl;
        cout << "Enter : ";
        cin >> y;
        if (y == 'y')
        {
            instructionAddress = 0;
            readFile();
        }
        else
        {
            break;
        }
    default:
        break;
    }
}

// This function is for printing memory and information
void Footron::printMemory()
{
    cout << "INFORMATION" << endl;
    cout << "accumulator:                " << internal << file << endl;
    cout << "accumulator value:          " << setw(4) << setfill('0') << internal << accumulator << endl;
    cout << "instructionAddress:         " << setw(1) << setfill('0') << internal << instructionAddress << endl;
    cout << "opCode:                     " << setw(2) << setfill('0') << internal << opCode << endl;
    cout << "operand:                    " << setw(2) << setfill('0') << internal << operand << endl;
    cout << "final value:                " << setw(1) << setfill('0') << internal << finalValue << endl;

    cout << "" << endl;
    cout << "----- MEMORY -----" << endl;
    cout << "   0    1    2    3    4    5    6    7    8    9" << endl;
    // Print out the memory block.
    cout << "00 ";
    for (int i = 0; i < 10; i++)
    {
        cout << setw(4) << setfill('0') << internal << memory[i] << " ";
    }
    cout << endl;
    for (int s = 10; s < 100; s = s + 10)
    {
        cout << noshowpos << s << " ";
        for (int i = 0; i < 10; i++)
        {
            cout << setw(4) << setfill('0') << internal << memory[s + i] << " ";
        }
        cout << endl;
    }
}

int main()
{
    Footron footron = Footron();
    footron.readFile();

    return 0;
}