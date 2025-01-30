#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include <cstdlib>


using namespace std;

typedef struct {
    string startLocation, endLocation, flightName;
    double flightCost{};
} Flights;



int countLineNum();

void readStoredfile(const string &fileName,Flights flight[], int &lineNum);

void Loadfile(const string &fileName, Flights flight[], int &lineNum);

void printFlightDetails(Flights flights[], int counter);

void selectionSort(Flights flight[], int lineNum);

void mergeSort(Flights flight[], int lineNum);

void mergeSort(Flights flight[], int start, int stop,int lineNum);

void Merge(Flights flight[], int start, int mid, int stop);

void merge(int *a, int lineNum);

void quickSort(Flights flight[], int linenum);

void quickSort(Flights flight[], int start, int stop);

int partition(Flights flight[], int start, int stop, int pivot);

int RandomNumFunc(int min, int max);

int BinSearch(Flights flight[], string search, int lineNum);





/*
 * Function to count the number of lines in for flight files
 *
 * @return The right number of space for flightarray to store data
 */
int countLineNum() {
    int arraySpace = 0;
    ifstream file("Flights10_Winter2025.dat");
    if (!file.is_open()) {
        cout << "Error! Unable to open file!" << std::endl;
    }
    string flightInfo;
    while (getline(file, flightInfo)) {
        arraySpace++;
    }
    return arraySpace;
}


/*
 * Function to read and store data of flight files, using
 * an array of structs
 *
 * @param flight[] An array containing the flight data
 * @param &lineNum to store the length of the flight array
 */
void readStoredfile(const string &fileName, Flights flight[], int &lineNum) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error! Unable to open file!" << std::endl;
    }
    lineNum = 0;
    string flightInfo;
    while (getline(file, flightInfo)) {
        flight[lineNum].startLocation.clear();
        flight[lineNum].endLocation.clear();
        flight[lineNum].flightName.clear();

        int i;
        for (i = 0; flightInfo[i] != ','; i++) {
            flight[lineNum].startLocation += flightInfo[i];
        }
        ++i;
        for (; flightInfo[i] != ','; i++) {
            flight[lineNum].endLocation += flightInfo[i];
        }
        ++i;
        for (; flightInfo[i] != ','; i++) {
            flight[lineNum].flightName += flightInfo[i];
        }
        ++i;
        string tempCost;
        for (; flightInfo[i] != '\0'; i++) {
            tempCost += flightInfo[i];
        }
        flight[lineNum].flightCost = stod(tempCost);
        lineNum = lineNum + 1;
    }
    file.close();
}








void printFlightDetails(Flights flights[], int counter) {
    cout<<"10 flights loaded."<< endl;
    cout<<"The first 5 flights are: "<< endl;
    for (int i = 0; i < 5; i++) {
        cout << "Flight #" << flights[i].flightName << " from ";
        cout << flights[i].startLocation <<" to ";
        cout << flights[i].endLocation << " costs ";
        cout << flights[i].flightCost <<"$" << endl;
    }

    cout<<"The last 5 flights are: "<< endl;
    for (int i = counter-5; i < counter; i++) {
        cout << "Flight #" << flights[i].flightName << " from ";
        cout << flights[i].startLocation <<" to ";
        cout << flights[i].endLocation << " costs ";
        cout << flights[i].flightCost <<"$" << endl;
    }
    cout<<" "<< endl;
    cout<<" "<< endl;
    cout<<" "<< endl;


}



/*
 * This function is a selection sort function that
 * sorts all flights according to the flight number in
 * lexicographic order
 *
 * @param flight[] A dynamically allocated array containing the flight data
 * @param &lineNum int to store the length of the flight array
 */
void selectionSort(Flights flight[], int lineNum){
    for(int i = 0; i < lineNum-1; i++){
        int min = i;
        for(int j = i + 1; j < lineNum; j++){
            if(flight[j].flightName < flight[min].flightName){
                min = j;
            }
        }
        swap(flight[i].flightName, flight[min].flightName);
        swap(flight[i].flightCost, flight[min].flightCost);
        swap(flight[i].startLocation, flight[min].startLocation);
        swap(flight[i].endLocation, flight[min].endLocation);

    }
}


void mergeSort(Flights flight[], int start, int stop){
    if(start == stop){
        return;
    }
    int mid = (start+stop)/2;
    mergeSort(flight, start, mid);
    mergeSort(flight, mid+1, stop);
    Merge(flight, start, mid,  stop);
}

void mergeSort(Flights flight[], int lineNum){
    mergeSort(flight, 0, lineNum-1);

}


void Merge(Flights flight[], int start, int mid, int stop) {
    int leftSize = mid - start + 1;
    int rightSize = stop - mid;

    Flights* leftInfo = new Flights[leftSize];
    Flights* rightInfo = new Flights[rightSize];

    // Copy data to leftInfo
    for (int i = 0; i < leftSize; i++) {
        leftInfo[i] = flight[start + i];
    }

    // Copy data to rightInfo
    for (int j = 0; j < rightSize; j++) {
        rightInfo[j] = flight[mid + 1 + j];
    }

    int Lt = 0; // Index for leftInfo
    int Rt = 0; // Index for rightInfo
    int k = start; // Index for the original flight array

    // Merge the temporary arrays back into the original flight array
    while (Lt < leftSize && Rt < rightSize) {
        if (leftInfo[Lt].flightName <= rightInfo[Rt].flightName) {
            flight[k] = leftInfo[Lt];
            Lt++;
        } else {
            flight[k] = rightInfo[Rt];
            Rt++;
        }
        k++;
    }

    // Copy any remaining elements from leftInfo
    while (Lt < leftSize) {
        flight[k] = leftInfo[Lt];
        Lt++;
        k++;
    }

    // Copy any remaining elements from rightInfo
    while (Rt < rightSize) {
        flight[k] = rightInfo[Rt];
        Rt++;
        k++;
    }

    // Clean up memory
    delete[] leftInfo;
    delete[] rightInfo;
}


int RandomNumFunc(int min, int max) {
    return rand() % (max -min + 1) + min;

}

int partition(Flights flight[], int start, int stop, int pivot) {
    swap(flight[pivot].flightName, flight[stop].flightName);
    int i = start - 1;

    for (int j = start; j < stop; j++) {
        if (flight[j].flightName < flight[stop].flightName) {
            i++;
            swap(flight[j].flightName,flight[i].flightName);
        }
    }

    swap(flight[i + 1].flightName, flight[stop].flightName);
    return i+1;
}



void quickSort(Flights flight[], int start, int stop) {
    if (start >= stop) {
        return;
    }
    int pivot = partition(flight, start, stop, RandomNumFunc(start, stop));
    quickSort(flight, start, pivot-1);
    quickSort(flight, pivot+1, stop);
}


void quickSort(Flights flight[], int lineNum) {
    quickSort(flight, 0,lineNum-1);
}

int BinSearch(Flights flight[], string search, int lineNum) {
   int found = 0;

    for (int i = 0; i < lineNum; i++) {
        if (flight[i].flightName == search) {
            cout<<flight[i].flightName<<endl;
            return found = i;
        }



    }

    return found;

}






int main() {
    srand(time(0));
    string filename = "Flights10_Winter2025.dat";
    const int counter = countLineNum();
    Flights *flight = new Flights[counter];
    int lineNum = 0;






    //cout<< "---------------------- Question 1 ----------------------"<< endl;
    // readStoredfile(filename,flight, lineNum);
    // printFlightDetails(flight, counter);
    //
    //
    // clock_t start = clock();
    // selectionSort(flight, lineNum);
    // clock_t total = clock () - start;
    // cout <<" SELECTION sort took " << total / CLOCKS_PER_SEC << "s" << endl;
    // printFlightDetails(flight, counter);
//
//
//    start = clock();
//    selectionSort(flight, lineNum);
//    total = clock () - start;
//    cout <<" SELECTION Resort took " << total / CLOCKS_PER_SEC << "s" << endl;
//    printFlightDetails(flight, counter);







    cout<< "---------------------- Question 2 ----------------------"<< endl;


    readStoredfile(filename,flight, lineNum);
    printFlightDetails(flight, counter);
    mergeSort(flight, lineNum);
    printFlightDetails(flight, counter);

    // cout<< "---------------------- Question 3----------------------"<< endl;
    // readStoredfile(filename,flight, lineNum);
    // printFlightDetails(flight, counter);
    // quickSort(flight, lineNum);
    // printFlightDetails(flight, counter);

    //cout<< "---------------------- Question 4----------------------"<< endl;

    cout<< "---------------------- Question 5----------------------"<< endl;

    // readStoredfile(filename,flight, lineNum);
    // printFlightDetails(flight, counter);
    // quickSort(flight, lineNum);
    // printFlightDetails(flight, counter);


    // string search[3] = {"US0842", "FL0044", "GH2333"};
    //
    // int result[3];
    // result[0]= BinSearch(flight, "US0842", lineNum);
    // cout << result[0];

     // for (int i = 0; i < 3; i++) {
     //     result[i] = BinSearch(flight, search[i], lineNum);
     //     if (result[i] == 0) {
     //         cout<< "The flight "<< search[i] << " does not exist!" <<endl;
     //     }
     //     else {
     //         cout<< "The flight "<< search[i] << " leaves" << flight[result[i]].startLocation << endl;
     //     }
     //
     // }






    delete[] flight;
    return 0;
}