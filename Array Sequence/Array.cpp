//Implementation of a basic array

#include <iostream>

//Make a class to contain all of the functions for the array
class Array {
public:
//use a default constructor to create empty array and point to null
Array() {
    arraySize = 0;
    data = nullptr;
    numElements = 0;
}
//constructor with size parameter
Array(int size) {
    //new allocation of memory for an int array with a specific number of elements. data is the variable this is stored in
    data = new int[size];
    //size of the array is stored
    arraySize = size;
    //currently there arent any actual elements, just data allocation.
    numElements = 0;
}
//function to get the amount of elements currently in the array
int getArrayLength() {
    return numElements;
}
//function to set a value to a specific element in an array
void setAt(int index, int val) {
    //need to validate input
    if (index < 0 || index > numElements) {
        std::cout << "Error: Chosen index can not be a negative integer or an integer larger than the array size." << std::endl;
        return;
    }
    //sets the pointer in memory of data at the index to the given value.
    data[index] = val;
}
//function to expand array when it runs out of memory
void expandArray() {
    //double the arraySize variable
    arraySize *= 2;
    //create a new array with the new array size
    int* newArray = new int[arraySize];
    //set the new array values to the old array values for each element
    for (int index = 0; index < numElements; index++) {
        newArray[index] = data[index];
    }
    //delete the old array data to prevent memory leaks
    delete[] data;
    //set the newArray to the original array variable
    data = newArray;
}
//getter for testing purposes
int getArraySize() {
    return arraySize;
}
//function to insert anywhere that isn't the first or last element
void insertAt(int index, int val) {
    //expands memory space if it is full
    if (numElements == arraySize) {
        expandArray();
    }
    //validates input
    if (index < 0 || index > numElements) {
        std::cout << "Error: Chosen index can not be a negative integer or an integer larger than the array size." << std::endl;
        return;
    }
    //shifts elements at index to the right starting with the last element
    for (int i = numElements - 1; i >= index; i--) {
        data[i + 1] = data[i];
    }
    //set the index to the given value after elements are shifted
    data[index] = val;
    //update number of elements
    numElements++;
}
void deleteAt(int index) {
    //input validation
    if (index < 0 || index >= numElements) {
        std::cout << "Error: Chosen index can not be a negative integer or an integer larger than the array size." << std::endl;
        return;
    }
    for (int i = index; i < numElements -1; i++) {
        data[i] = data[i+1];
    }
    //update the number of elements
    numElements--;
}
void insertFirst(int val) {
    insertAt(0, val);
}
void insertLast(int val) {
    insertAt(numElements, val);
}
void deleteFirst() {
    deleteAt(0);
}
void deleteLast() {
    deleteAt(numElements-1);
}
void printAll() {
	     std::cout << "All the elements are: ";
		 for (int i = 0; i < numElements; ++i) {
			 std::cout << data[i] << " ";
		 }
		 std::cout << std::endl;
		 std::cout << "Number of Elements: " << numElements << std::endl;
         std::cout << "Memory Size: " << arraySize << std::endl;
	 }

private:
//private variables for the functions
int arraySize;
//variable that points to an integer
int* data;
//counter variable
int numElements;
};

int main() {
    int initialSize;
    std::cout << "Enter the initial size of the array: ";
    std::cin >> initialSize;

    //create an Array object with the initial size
    Array myArray(initialSize);
    //do while loop for a menu. Quits when choice is 10
    int choice;
    do {
        //list menu options
        std::cout << "\nMenu:\n";
        std::cout << "1. Insert element at a specific index\n";
        std::cout << "2. Delete element at a specific index\n";
        std::cout << "3. Insert element at the beginning\n";
        std::cout << "4. Insert element at the end\n";
        std::cout << "5. Delete element at the beginning\n";
        std::cout << "6. Delete element at the end\n";
        std::cout << "7. List all elements\n";
        std::cout << "8. Show memory size\n";
        std::cout << "9. Show array size\n";
        std::cout << "10. Quit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        //switch statement for menu options
        switch (choice) {
            case 1: {
                int index, val;
                std::cout << "Enter index: ";
                std::cin >> index;
                std::cout << "Enter value: ";
                std::cin >> val;
                myArray.insertAt(index, val);
                break;
            }
            case 2: {
                int index;
                std::cout << "Enter index to delete: ";
                std::cin >> index;
                myArray.deleteAt(index);
                break;
            }
            case 3: {
                int val;
                std::cout << "Enter value to insert at the beginning: ";
                std::cin >> val;
                myArray.insertFirst(val);
                break;
            }
            case 4: {
                int val;
                std::cout << "Enter value to insert at the end: ";
                std::cin >> val;
                myArray.insertLast(val);
                break;
            }
            case 5:
                myArray.deleteFirst();
                break;
            case 6:
                myArray.deleteLast();
                break;
            case 7:
                myArray.printAll();
                break;
            case 8:
                std::cout << myArray.getArraySize() << std::endl;
                break;
            case 9:
                std::cout << myArray.getArrayLength() << std::endl;
                break;
            case 10:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 10);

    return 0;
}