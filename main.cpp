#include <iostream>
#include <fstream>
#include <string>
#include <chrono>


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


void Merge(Flights flight[], int start, int mid, int stop){
    int leftSize = mid - start + 1;
    int rightSize = stop - mid;

    string *leftInfo = new string [leftSize + 1];
    string *rightInfo = new string[rightSize +1];
    int i = start;

    for (; i <= mid; i++) {
        leftInfo[i-start] = flight[i].flightName;
    }
    leftInfo[i-start] =  "ZZZZZZ";
    for (int j = 0; j <= stop-mid; j++) {
        rightInfo[j] = flight[mid+1+j].flightName;
    }
    rightInfo[stop-mid] = "ZZZZZZ";
    int Lt = 0;
    int Rt = 0;
    for (int k = start; k <= stop; k++) {
        if (leftInfo[Lt]<= rightInfo[Rt]) {
            flight[k].flightName = leftInfo[Lt];
            Lt++;
        } else {
            flight[k].flightName= rightInfo[Rt];
            Rt++;
        }
    }

    delete[] leftInfo;
    delete[] rightInfo;


}





int main() {
    string filename = "Flights10_Winter2025.dat";
    const int counter = countLineNum();
    Flights *flight = new Flights[counter];






    cout<< "---------------------- Question 1 ----------------------"<< endl;
    int lineNum = 0;
//    readStoredfile(filename,flight, lineNum);
//    printFlightDetails(flight, counter);
//
//
//    clock_t start = clock();
//    selectionSort(flight, lineNum);
//    clock_t total = clock () - start;
//    cout <<" SELECTION sort took " << total / CLOCKS_PER_SEC << "s" << endl;
//    printFlightDetails(flight, counter);
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
    




    delete[] flight;
    return 0;
}