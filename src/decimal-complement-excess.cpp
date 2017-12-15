/*  Programmer: Daniel Constantine
    Contact: daniel.k.constantine@gmail.com
    Description: This program get a number and number of bits from the user
        and convert the number into One's complement, Two's complement, and
        Excess-M representation.
*/

#include <iostream>
using namespace std;

void askUser(int&, int&, int&); //prompt user to input the number, number of bits, and the excess value
int exitLoop(); //prompt user to exit loop or continue
void printNumber(const int, int[]); //print the value
void convertToBinary(const int, int, int, int, int[]); //convert the number into binary
void convertToOne(const int, int, int[]); //convert the binary number into one's complement
void convertToTwo(const int, int, int[]); //convert the one's complement into two's complement
void convertToExcess(const int, int, int, int, int, int[]); //convert the number into excess-m representation.

int main()
{
    int number = 0, bits = 0, remainder = 0, quotient = 0, excess = 0;
    while(true){
        askUser(number, bits, excess);

        int storage[bits];
        int const arraySize = sizeof(storage) / sizeof(int);

        convertToBinary(arraySize, quotient, remainder, number, storage);

        convertToOne(arraySize, number, storage);

        printNumber(arraySize, storage);

        convertToTwo(arraySize, number, storage);

        printNumber(arraySize, storage);

        convertToExcess(arraySize, quotient, remainder, number, excess, storage);

        int stopLoop = exitLoop();

        if(stopLoop == 0){
            break;
        }
        cout << endl;
    }

    return 0;
}

void askUser(int& number, int& bits, int& excess){
    cout << "Enter the decimal you want me to convert: ";
    cin >> number;
    cout << "Enter the number of bits you want to convert: ";
    cin >> bits;
    cout << "Enter the excess: ";
    cin >> excess;
}

int exitLoop(){
    int exit;
    cout << "\n\nDo you want to continue? Enter 0 to exit the program: ";
    cin >> exit;
    return exit;
}

void printNumber(const int arraySize, int storage[]){
    for(int i = 0; i < arraySize; i++){
        cout << storage[i];
    }
}

void convertToBinary(const int arraySize, int quotient, int remainder, int number, int storage[]){
    quotient = number;
    int i = 1;

    while(quotient != 0){
        remainder = quotient % 2;
        //cout << "Remainder " << remainder << endl;
        quotient = quotient / 2;
        storage[arraySize-i] = remainder;
        //cout << arraySize-i << " == " << storage[arraySize-1] << endl;
        i++;
    }
    //if i hasn't reached the first array member, then assigns it with 0's
    for(; i <= arraySize; i++){
        storage[arraySize-i] = 0;
    }
}

void convertToOne(const int arraySize, int number, int storage[]){
    //convert it into 1's complement by change 1 to 0 and vice versa
    cout << endl << "The 1's complement of your number is: " << endl;
    if(number < 0){
        for(int j = 0; j < arraySize; j++){
            if(storage[j] == 0){
                storage[j] = 1;
            } else {
                storage[j] = 0;
            }
        }
    } else {
        return;
    }
}

void convertToTwo(const int arraySize, int number, int storage[]){
    //convert by adding the last member with 1, and basic binary addition
    cout << endl << "The 2's complement of your number is: " << endl;

    if(number < 0){
        int index = arraySize-1;
        //cout << index;
        storage[index] += 1;
        //cout << storage[index];
        while(index != 0){
            //cout << "index " << index << endl;
            if(storage[index] == 2){
                storage[index] = 0;
                storage[index-1] += 1;
                index--;
            } else {
                index--;
            }
        }
    } else {
        return;
    }
}

void convertToExcess(const int arraySize, int quotient, int remainder, int number, int excess, int storage[]){
    cout << "\nThe excess representation is:  " << endl;
    int temp = number + excess;
    convertToBinary(arraySize, quotient, remainder, temp, storage);
    printNumber(arraySize, storage);
}
