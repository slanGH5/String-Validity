#include <iostream>
#include <string>
#include <iomanip>
#include <cassert>
using namespace std;

// DECLARATIONS //////////////////////////////////////////////////////////////////////////////////////
string trim(string str);
int extractNum1(string s, int index);
int extractNum2(string s, int index);

bool isValidVehicleString(string vehicleString);
int getOccupants(string vehicleString);
int getSpeed(string vehicleString);
int getLicenseSeries(string vehicleString);
string getLetterGroup(string vehicleString);
int getLicenseGroup(string vehicleString);


// MAIN PROGRAM ///////////////////////////////////////////////////////////////////////////////////////
int main() {
    string testStr, trimmedStr, letterGroup;
    //bool valid = 0;
    //cout.setf(ios::boolalpha);
    cout << "Type in a string or 'exit' to quit: " << endl;
    getline(cin, testStr);
    
    while(testStr != "exit"){
        
        int numberofOcc = getOccupants(testStr);
        cout << "Number of occupants: " << numberofOcc << endl;
        int speed = getSpeed(testStr);
        cout << "Speed: " << speed << endl;
        int licenseSeries = getLicenseSeries(testStr);
        cout << "License series: " << licenseSeries << endl;
        string letterGroup = getLetterGroup(testStr);
        cout << "Letter group: " << letterGroup << endl;
        int licenseGroup = getLicenseGroup(testStr);
        cout << "License group: " << licenseGroup << endl;
        
        cout << endl << "Enter another teststring: " << endl;
        getline(cin, testStr);
    }
    
    getline(cin, testStr);
    
    assert( ! isValidVehicleString("UA1+1"));
    assert( ! isValidVehicleString("    "));
    assert( getOccupants( "    " ) == -1 );
    assert( getSpeed( "      " ) == -1 );
    assert( isValidVehicleString( "1ABC000:2-55" ) == true );
    assert( getOccupants( "1ABC000:2-55" ) == 2 );
    assert( getSpeed( "1ABC000:2-55" ) == 55 );
    assert( getLicenseSeries( "1ABC000:2-55" ) == 1 );
    assert( getLetterGroup( "1ABC000:2-55" ) == "ABC" );
    assert( getLicenseGroup( "1ABC219:2-55" ) == 219 );
    
    return(0);
}

//  DEFINITIONS /////////////////////////////////////////////////////////////////////////////////////////
//1. ORIGINAL FUNCTION TO TRIM DOWN EMPTY SPACES IN STRING
string trim(string str){
    int beginIndex = 0, endIndex = 0;
    int length = (int)str.length();         //type-cast str.size() into an int
    bool empty = 1;
    if (length == 0){
        return "";                         //return empty string if original string is completely empty
    }
    
    //Set end-index
    for (int i = 0; i < length; i++){
        if (str[i] != 32){                  //if ASCII value = 32, there's a blank space
            endIndex = i;
            empty = 0;
        }
        else if (i == length - 1 && str[i] == 32 && empty == 1){
            return "";                    //return empty string if original string was filled with spaces
        }
    }
    
    //Set begin-index
    for (int i = length - 1; i > -1; i--){
        if (str[i] != 32){
            beginIndex = i;
        }
    }
    
    string newStr(endIndex - beginIndex + 1, 'x');   // Create a new string with length of end-begin, fill that string with 'x'
    for (int i = beginIndex; i < endIndex + 1; i++){
        newStr[i - beginIndex] = str[i];             // Replace each 'x' with character from original string
    }
    return newStr;                                   // return the new string
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//2. ORIGINAL FUNCTION TO EXTRACT AND CONCATENATE NUMBERS IN STRING (used for extracting number of occupants and speed)
int extractNum1(string s, int index){
    int result = 0;
    if  (s[index] >= '1' && s[index] <= '9'){                //leading 0s --> invalid (occupants and speed cannot have leading 0s)
        while (s[index] >= '0' && s[index] <= '9')
        {
            result = (result * 10) + (s[index] - '0');
            index = index + 1;
        }
    }
    return(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//3. ORIGINAL FUNCTION TO EXTRACT AD CONCATENATE NUMBERS IN STRING (used for extracting license group)
int extractNum2(string s, int index){
    int result = 0;
    while (s[index] >= '0' && s[index] <= '9')  //allows for leading 0s (license group can have leading 0s)
    {
        result = (result * 10) + (s[index] - '0');
        index = index + 1;
    }
    return(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//4. FUNCTION TO DETERMINE IF VEHICLE STRING IS VALID
bool isValidVehicleString(string vehicleString){
    string trimmedStr = trim(vehicleString);
    
    //Check for spaces in middle of string. Return false if any spaces found. ASCII for space is 32
    for (int i = 0; i < trimmedStr.length(); i++){
        if (trimmedStr[i] == 32){
            return false;
        }
    }
    
    //Check first character is a digit between 1-9 through index and ASCII
    if (trimmedStr[0] >= '1' && trimmedStr[0] <= '9'){}
    else {
        return false;
    }
    
    //Check if characters 2-4 (index 1-3) are UPPERCASE letters using ASCII
    for (int i = 1; i < 4; i++){
        if (trimmedStr[i] >= 65 && trimmedStr[i] <= 90){}
        else {
            return false;
        }
    }
    
    //Check license group (index 4-6) are digits between 0-9
    for (int i = 4; i < 7; i++){
        if (trimmedStr[i] >= '0' && trimmedStr[i] <= '9'){}
        else {
            return false;
        }
    }
    
    //Check for colon at index 7. ASCII for colon is 58
    if (trimmedStr[7] != 58){
        return false;
    }
    
    //Find where dash is. ASCII for dash is 45
    int dashIndex = -1;
    for (int i = 8; i < trimmedStr.length(); i++){
        if (trimmedStr[i] == 45){
            dashIndex = i;
        }
    }
    //If no dash found --> invalid string
    if (dashIndex == -1){
        return false;
    }
    
    // Check if characters between colon and dash are digits
    int lengthOcc = dashIndex - 8;
    
    for (int j = 8; j < 8 + lengthOcc; j++){
        if (trimmedStr[j] >= 48 && trimmedStr[j] <= 57){}
        else{
            return false;
        }
    }
    // Check if character between colon and dash is not 0
    int numOcc = extractNum1(trimmedStr, 8);
    if (numOcc == 0){
        return false;
    }
    
    //Check if characters after dash (speed) are digits 1-999 using extractNum1 function
    int speed = extractNum1(trimmedStr, dashIndex + 1);
    if (speed == 0 || speed > 999){
        return false;
    }
    
    //Check if speed is last item in string
    int lengthOfSpeed = 0;
    if (speed < 10){
        lengthOfSpeed = 1;
    }
    else if (speed >= 10 && speed < 100){
        lengthOfSpeed = 2;
    }
    else if (speed >= 100 && speed < 1000){
        lengthOfSpeed = 3;
    }
    
    if (trimmedStr.length() != dashIndex + lengthOfSpeed + 1){
        return false;
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//5. FUNCTION TO RETURN # OF OCCUPANTS IF STRING VALID
int getOccupants(string vehicleString){
    if (isValidVehicleString(vehicleString) == 1){
        string trimmedStr = trim(vehicleString);
        int numOcc = extractNum1(trimmedStr, 8);
        
        return numOcc;
    }
    else{
        return (-1);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//6. FUNCTION TO RETURN SPEED IF STRING VALID
int getSpeed(string vehicleString){
    string trimmedStr = trim(vehicleString);
    
    if (isValidVehicleString(vehicleString) == 1){
        int dashIndex = -1;
        for (int i = 8; i < trimmedStr.length(); i++){
            if (trimmedStr[i] == 45){
                dashIndex = i;
            }
        }
        int speed = extractNum1(trimmedStr, dashIndex + 1);
        
        return speed;
    }
    else{
        return (-1);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//7. FUNCTION TO RETURN LICENSE SERIES IF STRING VALID
int getLicenseSeries(string vehicleString){
    if (isValidVehicleString(vehicleString) == 1){
        string trimmedStr = trim(vehicleString);
        int licenseS = trimmedStr[0] - '0';               //convert string into integer through ASCII (-'0')
        
        return licenseS;
    }
    else{
        return (-1);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//8. FUNCTION TO RETURN LETTER GROUP IF STRING VALID
string getLetterGroup(string vehicleString){
    
    if (isValidVehicleString(vehicleString) == 1){
        string trimmedStr = trim(vehicleString);
        string letterGroup(3, 'x');                       // Create a new string with length of 3, fill that string with 'x'
        for (int i = 1; i < 4; i++){
            letterGroup[i - 1] = trimmedStr[i];           // Replace each 'x' with character from original string
        }
        return letterGroup;
    }
    else{
        return ("");
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//9. FUNCTION TO RETURN LICENSE GROUP IF STRING VALID
int getLicenseGroup(string vehicleString){
    
    if (isValidVehicleString(vehicleString) == 1){
        string trimmedStr = trim(vehicleString);
        int licenseG = 0;
        
        if (trimmedStr[4] == 0 && trimmedStr[5] == 0 && trimmedStr[6] == 0){   //if all 3 digits are 0, return 0
            licenseG = 0;
        }
        if (trimmedStr[4] == 0 && trimmedStr[5] == 0 && trimmedStr[6] != 0){   //if all but 3rd digit is 0, return 3rd digit
            licenseG = trimmedStr[6];
        }
        if (trimmedStr[4] == 0 && trimmedStr[5] != 0 && trimmedStr[6] != 0){   //if all but 2nd and 3rd digit is 0,
            licenseG = extractNum2(trimmedStr, 5);                             //return 2nd and 3rd digit
        }
        if (trimmedStr[4] != 0 && trimmedStr[5] != 0 && trimmedStr[6] != 0){   //if none 0, return all 3 digits
            licenseG = extractNum2(trimmedStr, 4);
        }
        return licenseG;
    }
    else{
        return (-1);
    }
}
