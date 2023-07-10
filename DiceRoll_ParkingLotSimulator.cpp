/*                                                                                                                                                                                                                                                                                                                                                                                                                     Jaden Humphries                                                                                                                                                                                                                                         

This program will contain custom functions that satisfy the requirements of a Dice Simulator and a Parking Deck Calculator

Program: simulates rolling a pair of dice. The main function will call the functions: runDiceSimulator(void) and runParkingCalculator(void)
runDiceSimulator(void) function will call int rollDice(void) that will return the values of the dice

runParkingCalculator(void) will call two functions: void getCarinfo(void) where the user will enter up to 10 customers' time(hours) spent in the lot (use -999 as a sentinal) if fewer than 10 cars
and calculateCharges(double []) which when called should neatly print out the cars, times, and charges, as well as a sum of the hours and charges in neat tabular format
 */

 #include <iostream> // cout, cin, endl
 #include <cstdlib>
 #include <ctime>
 #include <iomanip>
 #include <limits>
 #include <cmath>
 #include <array>
  using namespace std;

  void runParkingCalculator(void);
  void getCarInfo(void);
  void calculateCharges(double []);

  void runDiceSimulator(void);
  int rollDice(void);
  bool inputFail(string numberOfDiceRolls);


  int main(){

    runParkingCalculator();
    runDiceSimulator();

    return 0;
  }

  void runParkingCalculator(){

    cout << "\nParking Deck Calculator:" << endl << endl;
    getCarInfo();
}

void getCarInfo() {

  double timeInHours[10];

  for (int i = 0; i < 10; i++) {
      cout << "Enter a customer's time in hours or -999 to end: ";
      cin >> timeInHours[i];

      if (timeInHours[i] == -999){
          timeInHours[i] = 0;
          break;
      }
      else if (cin.fail()){ // bad input other than an integer or decimal number
          cin.clear(); // reset cin.fail() to false; clear flag
// failed input will still be in the buffer, so when there is a new input, it will read the same input in the buffer and it will fail again
  // in order to prevent this, use cin.ignore() function
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << "Customer's time must be a valid number." << endl;
          i--; // decrement down in order to allow 10 inputs after an invalid input
      }
      else if (timeInHours[i] > 24){
          cout << "Customer's time must be 24 or below." << endl;
          i--;
      }
      if (timeInHours[i] <= 0){
          cout << "Customer's time must be above 0." << endl;
          i--;
      }
  }
  cout << endl;
  calculateCharges(timeInHours);

}

void calculateCharges(double timeInHours[]) {

  int car = 1;
  double hoursTotal = 0;
  double chargesTotal = 0;

  cout << left << setw(15) << "Car" << left << setw(15) << "Hours" << left << setw(15)<< "Charge ($)" << endl;
  for (int i = 0; i < 10; i++) {
      double charge;
      if(timeInHours[i] == 0){ // if time is equal to zero break from loop
          break;
      }
      if (timeInHours[i] < .5) { // if time is less than 30 min charge $0
          charge = 0;
      }
      else if (timeInHours[i] > .5 && timeInHours[i] < 1) { // if time is greater than 30min and less than 1 hour charge $2.50
          charge = 2.50;
      }
      else { // charge $1.50 each hour or part of an hour over 1 hour
          (charge = floor(timeInHours[i]) * 1.5 + 2.50);
      }
      if (charge > 15) {
          charge = 15;
      }
      if (timeInHours[i] != -999){ //
          cout << left << setw(15) << car << left << setw(15) << fixed << setprecision(2) << left << setw(15) << timeInHours[i] << left << setw(15) << charge << endl;
          car++;
          hoursTotal += timeInHours[i];
          chargesTotal += charge;
      }
  }
  cout << left << setw(15) << "Total:" << left << setw(15) << hoursTotal << left << setw(15) << chargesTotal << endl;

}

void runDiceSimulator(){

    unsigned seed; // set up random number
    seed = time(0);
    srand(seed);

    string numberOfDiceRolls;
    cout << "\nDice Simulator: " << endl << endl;
    bool badInput; //declare bad input var


    do{cout << "Enter the number of dice rolls you want: ";
    cin >> numberOfDiceRolls;

    badInput = inputFail(numberOfDiceRolls); //call inputFail() to


    if(badInput == true){
    cout << "Number must be a valid integer." << endl;
    }
    else if(badInput == false && stoi(numberOfDiceRolls) <= 0){
      badInput = true;
      cout << "Number must be greater than 0." << endl;
      //cout << "Enter the number of dice rolls you want. " << endl;

    }
    else{
      for(int i = 1; i <= stoi(numberOfDiceRolls); i++){
        cout << rollDice() << " & " << rollDice() << endl;
      }
    }
  }while(badInput == true);
}

bool inputFail(string numberOfDiceRolls){
  char checkChar;
  for(int i = 0; i <= numberOfDiceRolls.length() - 1; i++){
    checkChar = numberOfDiceRolls[i];
    if(!isdigit(numberOfDiceRolls[i]) && numberOfDiceRolls.find("-") != 0){
      return true;
    }
  }
    return false;
}

int rollDice(){ // return random dice number
  const int MAX = 6;
  const int MIN = 1;
  int diceNumber = rand() % MAX + MIN;
  return diceNumber;
}