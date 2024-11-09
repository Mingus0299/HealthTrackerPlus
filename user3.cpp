#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <sstream>
#include <limits>
#include <exception>
#include <cstdlib>  // for std::exit
#include <iomanip> 


using namespace std;

//  csv format
//  Gender, Age, Weight, Waist, Neck, Hip, Height, Lifestyle, Name, Carbs, Protein, Fat, Calories, Bfp
//  everything must be initialized except for hip 

// Bfp format
// (%)  instead of (%, string)

struct UserInfo 
{    
     std::string gender;
     int age;
     double weight;
     double waist;
     double neck;
     double hip;
     double height;
     std::string lifestyle;
     std::string name;
     double carbs;
     double protein;
     double fat;
     double calories;
     std::string bfp;
};

//helper functions
void ValidateGender(string &input);
void ValidateString(string &input);
void ValidateDouble(string input, double &result);
void ValidateAge(string input, int &age);
void ValidateLifestyle(string input);
void ValidateFile(string &filename);


class UserInfoManager //pointer to user info linkedlist
{
     public:
          UserInfoManager(){}; // Using default constructor
          ~UserInfoManager(){};
          inline void addUserInfo(); // adds info to list
          inline void deleteUser(string username); // removes a user
          inline void readFromFile(string filename);
          void writeToFile(string filename);
          inline void display(string username);
          inline void displayUser(const UserInfo& user);
          vector<UserInfo> getUserList() const { return mylist; } 
          inline void massLoadAndCompute(string filename);
          inline void massLoadAndCompute(string filename, bool off); // helper function for UserStats
          inline void computeUserDetails(UserInfo& user, string filename);
          const vector<UserInfo>& getMyList() const { return mylist; }
          // Also provide a non-const version if you need to modify the vector
          vector<UserInfo>& getMyList() { return mylist; }
     private:
          vector<UserInfo> mylist; // pointer to first element in linked list
};

void UserInfoManager::addUserInfo() {         
    cout << "************* add new user ************" << endl;
    string input;
    string g_name;
    string g_gender;
    int g_age;
    double g_weight;
    double g_waist;
    double g_neck;
    double g_height;
    string g_lifestyle;
    double g_hip = 0; // Initialize hip, will be set for females

    // name
    cout << "Enter your name: ";
    cin >> g_name; // no exception for this assuming TA might be testing it with none string identifiers according to ed discussion
    
    // gender
    cout << "Please specify your gender as either male or female: ";
    cin >> g_gender;
    try
    {
        ValidateGender(g_gender);
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
        cout << "Exit program" << endl;
        std::exit(EXIT_FAILURE);
        
    }

    // hip optional
    if (g_gender == "female") {
        cout << "Enter your hip measurement in centimeters: ";
        cin >> input;
        try 
        {
            ValidateDouble(input, g_hip);
        }
        catch (exception& e)
        {
            cout << e.what() << endl;
            cout << "Exit program" << endl;
            std::exit(EXIT_FAILURE);
        }
    }

    // age
    cout << "Enter your age: ";
    cin >> input;
    try 
    {
        ValidateAge(input, g_age);
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
        cout << "Exit program" << endl;
        exit(EXIT_FAILURE);
    }
    //cin >> g_age;

    // weight
    cout << "Enter your body weight in kilograms: ";
    cin >> input;
    try 
    {
        ValidateDouble(input, g_weight);
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
        cout << "Exit program" << endl;
        exit(EXIT_FAILURE);
    }

    // waist
    cout << "Input your waist measurement using centimeters: ";
    cin >> input;
    try 
    {
        ValidateDouble(input, g_waist);
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
        cout << "Exit program" << endl;
        exit(EXIT_FAILURE);
    }

    // neck
    cout << "Provide your neck measurement in centimeters: ";
    cin >> input;
    try 
    {
        ValidateDouble(input, g_neck);
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
        cout << "Exit program" << endl;
        exit(EXIT_FAILURE);
    }

    // height
    cout << "Input height measurement in centimeters: ";
    cin >> input;
    try 
    {
        ValidateDouble(input, g_height);
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
        cout << "Exit program" << endl;
        exit(EXIT_FAILURE);
    }

    //lifestyle
    cout << "Provide information about your current lifestyle: sedentary, moderate (moderately active) or active: ";
    cin >> g_lifestyle;
    try 
    {
        ValidateLifestyle(g_lifestyle);
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
        cout << "Exit program" << endl;
        exit(EXIT_FAILURE);
    }
    

    cout << "*************************" << endl;

    // Create a new UserInfo object and add it to the vector
    UserInfo new_user;
    new_user.age = g_age;
    new_user.weight = g_weight;
    new_user.waist = g_waist;
    new_user.neck = g_neck;
    new_user.height = g_height;
    new_user.hip = g_hip;
    new_user.name = g_name;
    new_user.gender = g_gender;
    new_user.lifestyle = g_lifestyle;
    new_user.carbs = 0;
    new_user.protein = 0;
    new_user.fat = 0;
    new_user.calories = 0; 
    new_user.bfp = "0%"; 

    mylist.push_back(new_user);
}

// create exception for gender input
class NotValidGenderException : public exception
{
    virtual const char* what() const throw()
    {
        return "Warning: Not a valid gender input.";
    }
};
NotValidGenderException genderException;

void ValidateGender(string &input){ // either female || male in lowercase
    if ((input == "female") || (input == "male")){
        return;
    }
    throw genderException; 
}

// create exception for string input
class NotValidStringException : public exception
{
    virtual const char* what() const throw()
    {
        return "Warning: Not a valid string input.";
    }
};
NotValidStringException stringException;

void ValidateString(string &input){
    for (int i = 0; i < input.length(); ++i) {
        if (!isalpha(input[i]) && !isspace(input[i])) {
            throw stringException; // If any character is not a letter or space, return false
        }
    }
    return;
}

// create exception for double input
class NotValidDoubleException : public exception
{
    virtual const char* what() const throw()
    {
        return "Warning: Not a valid double input.";
    }
};
NotValidDoubleException doubleException;

void ValidateDouble(string input, double &result){
    istringstream stream(input);
    stream >> result;

    if (stream.fail() || !stream.eof()) {
        throw doubleException;
    }
    return;
}

// create exception for age input
class NotValidAgeException : public exception
{
    virtual const char* what() const throw()
    {
        return "Warning: Not a valid age input.";
    }
};
NotValidAgeException ageException;

void ValidateAge(string input, int &age){
    istringstream stream(input);
    stream >> age;

    if (stream.fail() || !stream.eof()) {
        throw ageException;
    }
    else {
        if (age >= 19 && age <= 79){
            return;
        }
        throw ageException;
    }
}

// create exception for lifestyle input
class NotValidLifeException : public exception
{
    virtual const char* what() const throw()
    {
        return "Warning: Not a valid lifestyle input";
    }
};
NotValidLifeException lifeException;

void ValidateLifestyle(string input){ // either sedentary || moderate || active in lowercase
    if ((input == "sedentary") || (input == "moderate") || (input == "active")){
        return;
    }
    throw lifeException;;
}

// create exception for file that will be read
class NotValidEmptyFile : public exception
{
    virtual const char* what() const throw()
    {
        return "Warning: Not a valid empty file, file cannot be read.";
    }
};
NotValidEmptyFile fileException;

void ValidateFile(string &filename){
    ifstream myFile(filename.c_str(), ifstream::ate | ifstream::binary); 

    if (!myFile.is_open()) {
        throw fileException;
    }

    if (myFile.tellg() == 0) { // Check file size
        throw fileException;
    }

    myFile.close();
    return;
}

// deleteUser from vector list
void UserInfoManager::deleteUser(string username) {
    cout << "************* delete user ************" << endl;
    cout << "Deleting: " << username << endl;

    bool found = false;
    for (vector<UserInfo>::iterator it = mylist.begin(); it != mylist.end(); ) {
        if (it->name == username) {
            it = mylist.erase(it);  // Erase returns the next valid iterator
            cout << "User '" << username << "' deleted." << endl;
            found = true;
        } else {
            ++it; 
        }
    }

    if (!found) {
        cout << "Username '" << username << "' not found." << endl;
    }

    cout << "*************************" << endl;
}

// read from filenmae
void UserInfoManager::readFromFile(string filename) {
    cout << "************* reading file ************" << endl;
    try
    {
        ValidateFile(filename);
    }
    catch(const std::exception& e)
    {
        cout << e.what() << endl;
        cout << "Exit program" << endl;
        exit(EXIT_FAILURE);
    }
    
    ifstream myFile(filename);

    // Clear existing data in the vector
    mylist.clear();

    string line;
    while (getline(myFile, line)) {
        UserInfo new_user;
        stringstream iss(line);

        // Read data directly into the fields of the new_user struct
        getline(iss, new_user.gender, ',');
        iss >> new_user.age;
        iss.ignore(1, ',');
        iss >> new_user.weight;
        iss.ignore(1, ',');
        iss >> new_user.waist;
        iss.ignore(1, ',');
        iss >> new_user.neck;
        iss.ignore(1, ',');

        // Hip measurement for female user
        if (new_user.gender == "female") {
            iss >> new_user.hip;
        } else {
            new_user.hip = 0;  // Assign default value if not female
        }
        iss.ignore(1, ',');

        iss >> new_user.height;
        iss.ignore(1, ',');
        getline(iss, new_user.lifestyle, ',');
        getline(iss, new_user.name, ',');
        iss >> new_user.carbs;
        iss.ignore(1, ',');
        iss >> new_user.protein;
        iss.ignore(1, ',');
        iss >> new_user.fat;
        iss.ignore(1, ',');
        iss >> new_user.calories;
        iss.ignore(1, ',');

        getline(iss, new_user.bfp);

        mylist.push_back(new_user);
    }

    myFile.close();
    cout << "File read successfully." << endl;
    cout << "*************************" << endl;
}

// write to filename
void UserInfoManager::writeToFile(string filename) {
    cout << "************* writing file ************" << endl;

    // Open the file in write mode, truncating existing content
    ofstream file(filename);
    if (!file) {
        cout << "File failed to open" << endl;
        return;
    }

    for (std::vector<UserInfo>::const_iterator it = mylist.begin(); it != mylist.end(); ++it) {
        const UserInfo& user = *it;
        file << user.gender << ", "
             << user.age << ", "
             << user.weight << ", "
             << user.waist << ", "
             << user.neck << ", "
             << (user.gender == "female" ? to_string(user.hip) : "0") << ", "
             << user.height << ", "
             << user.lifestyle << ", "
             << user.name << ", "
             << user.carbs << ", "
             << user.protein << ", "
             << user.fat << ", "
             << user.calories << ", "
             << user.bfp << endl;
    }

    file.close();
    cout << "Data written to file successfully." << endl;
    cout << "*************************" << endl;
}

// display all or specific with username
void UserInfoManager::display(string username) {
    cout << "************* DISPLAY ************" << endl;

    if (username == "all") {
        for (vector<UserInfo>::const_iterator it = mylist.begin(); it != mylist.end(); ++it) {
            displayUser(*it);
        }
    } else {
        bool found = false;
        for (vector<UserInfo>::const_iterator it = mylist.begin(); it != mylist.end(); ++it) {
            if (it->name == username) {
                displayUser(*it);
                found = true;
                break; // Exit the loop once the user is found
            }
        }
        if (!found) {
            cout << "Username '" << username << "' not found." << endl;
        }
    }

    cout << "*************************" << endl;
}

// helpter function for display(string username)
void UserInfoManager::displayUser(const UserInfo& user) {
    cout << "*************************" << endl;
    cout << "Name: " << user.name << endl;
    cout << "Gender: " << user.gender << endl;
    cout << "Age: " << user.age << endl;
    cout << "Weight: " << user.weight << " kg" << endl;
    cout << "Waist: " << user.waist << " cm" << endl;
    cout << "Neck: " << user.neck << " cm" << endl;
    if (user.gender == "female") {
        cout << "Hip: " << user.hip << " cm" << endl;
    }
    cout << "Height: " << user.height << " cm" << endl;
    cout << "Lifestyle: " << user.lifestyle << endl;
    cout << "Body Fat Percentage: " << user.bfp << endl;
    cout << "Daily Caloric Intake: " << user.calories << " calories" << endl;
    cout << "Macronutrient Breakdown:" << endl;
    cout << "Carbs: " << user.carbs << "g, Protein: " << user.protein << "g, Fat: " << user.fat << "g" << endl;
    cout << "*************************" << endl;
}

// compute everything to get everything from filename
void UserInfoManager::massLoadAndCompute(string filename) {
    cout << "************* mass load and compute ************" << endl;

    try
    {
        ValidateFile(filename);
    }
    catch(const exception& e)
    {
        cout << e.what() << endl;
        cout << "Exit program" << endl;
        exit(EXIT_FAILURE);
    }
    
    ifstream myFile(filename);
    
    mylist.clear();  // Clear existing data

    string line;
    while (getline(myFile, line)) {
        UserInfo user;
        stringstream iss(line);

        getline(iss, user.gender, ',');
        iss >> user.age;
        iss.ignore();
        iss >> user.weight;
        iss.ignore();
        iss >> user.waist;
        iss.ignore();
        iss >> user.neck;
        iss.ignore();
        // Handle the hip measurement based on gender
        if (user.gender == "female") {
            iss >> user.hip;
        } else {
            iss >> user.hip;
            user.hip = 0;  // Default hip value for males
        }
        iss.ignore();
        iss >> user.height;
        iss.ignore();
        iss.ignore();
        getline(iss, user.lifestyle, ',');
        iss.ignore();
        getline(iss, user.name, ',');
        iss >> user.carbs;
        iss.ignore();
        iss >> user.protein;
        iss.ignore();
        iss >> user.fat;
        iss.ignore();
        iss >> user.calories;
        iss.ignore();
        getline(iss, user.bfp);

        // Compute additional values as needed
        computeUserDetails(user, filename);

        mylist.push_back(user);
    }

    myFile.close();
    cout << "Data loaded and computed successfully." << endl;
}

// overriding the method so it does not put any comments when used in USerstats
void UserInfoManager::massLoadAndCompute(string filename, bool off) {
    try
    {
        ValidateFile(filename);
    }
    catch(const exception& e)
    {
        cout << e.what() << endl;
        cout << "Exit program" << endl;
        exit(EXIT_FAILURE);
    }
    
    ifstream myFile(filename);
    
    mylist.clear();  // Clear existing data

    string line;
    while (getline(myFile, line)) {
        UserInfo user;
        stringstream iss(line);

        getline(iss, user.gender, ',');
        iss >> user.age;
        iss.ignore();
        iss >> user.weight;
        iss.ignore();
        iss >> user.waist;
        iss.ignore();
        iss >> user.neck;
        iss.ignore();
        // Handle the hip measurement based on gender
        if (user.gender == "female") {
            iss >> user.hip;
        } else {
            iss >> user.hip;
            user.hip = 0;  // Default hip value for males
        }
        iss.ignore();
        iss >> user.height;
        iss.ignore();
        iss.ignore();
        getline(iss, user.lifestyle, ',');
        iss.ignore();
        getline(iss, user.name, ',');
        iss >> user.carbs;
        iss.ignore();
        iss >> user.protein;
        iss.ignore();
        iss >> user.fat;
        iss.ignore();
        iss >> user.calories;
        iss.ignore();
        getline(iss, user.bfp);

        // Compute additional values as needed
        computeUserDetails(user, filename);

        mylist.push_back(user);
    }

    myFile.close();
}

// helper function for massLoadAndComput
void UserInfoManager::computeUserDetails(UserInfo& user, string filename) {
    // compute calories
    if (user.gender == "male") {
        user.calories = (user.age >= 19 && user.age <= 30) ? (user.lifestyle == "sedentary" ? 2400 : (user.lifestyle == "moderate" ? 2600 : 3000))
                            : (user.age >= 31 && user.age <= 50) ? (user.lifestyle == "sedentary" ? 2200 : (user.lifestyle == "moderate" ? 2400 : 2800))
                            : (user.lifestyle == "sedentary" ? 2000 : (user.lifestyle == "moderate" ? 2200 : 2400));
    } else if (user.gender == "female") {
        user.calories = (user.age >= 19 && user.age <= 30) ? (user.lifestyle == "sedentary" ? 2000 : (user.lifestyle == "moderate" ? 2000 : 2400))
                            : (user.age >= 31 && user.age <= 50) ? (user.lifestyle == "sedentary" ? 1800 : (user.lifestyle == "moderate" ? 2000 : 2200))
                            : (user.lifestyle == "sedentary" ? 1600 : (user.lifestyle == "moderate" ? 1800 : 2000));
    }

    // computer bfp 
    if (filename == "bmi_user_data.csv"){ // BMI method
        user.bfp = to_string( user.weight/ (user.height/100 * user.height/100) ) + "%";
    }
    else if (filename == "us_user_data.csv") { // Navy method
        if (user.gender == "female") {
            // Female BFP calculation
            user.bfp = to_string(
                495 / (1.29579 - 0.35004 * log10(user.waist + user.hip - user.neck) + 0.22100 * log10(user.height)) - 450
            ) + "%";
        } else {
            // Male BFP calculation
            user.bfp = to_string(
                495 / (1.0324 - 0.19077 * log10(user.waist - user.neck) + 0.15456 * log10(user.height)) - 450
            ) + "%";
        }
    }

    // macronutrient breakdown
    user.carbs = user.calories * 0.5 / 4; 
    user.protein = user.calories * 0.3 / 4; 
    user.fat = ceil(user.calories * 0.2 / 9); 
}


// HealthAssistant
class HealthAssistant//: public UserInfoManager
{
    public:
        HealthAssistant(){};
        virtual ~HealthAssistant(){};
        inline void getUserDetail(); // wrapper method that simply calls addUserInfo in class UserInfoManager
        inline virtual void getBfp(string username) = 0;
        inline void getDailyCalories(string username);
        inline void getMealPrep(string username);
        inline void display(string username); //wrapper method
        inline void serialize(string filename); //wrapper method
        inline void readFromFile(string filename); //wrapper method 
        inline void deleteUser(string username); // wrapper method
        inline void massLoadAndCompute(string filename);
        inline void massLoadAndCompute(string filename, bool off);
        vector<UserInfo>& getMyList() {
            return manager.getMyList(); 
        }

        const vector<UserInfo>& getMyList() const {
            return manager.getMyList(); 
        }
    protected:
        UserInfoManager manager;
};


void HealthAssistant::getUserDetail()
{
     manager.addUserInfo();

} // wrapper method that simply calls addUserInfo in class UserInfoManager


void HealthAssistant::getDailyCalories(string username) {
    cout << "************* Get Daily Calories ************" << endl;

    bool found = false;
    for (vector<UserInfo>::iterator it = manager.getMyList().begin(); it != manager.getMyList().end(); ++it) {
        if (it->name == username) {
            found = true;
            UserInfo& user = *it;

            // Calculate daily caloric needs based on user details
            if (user.gender == "male") {
                user.calories = (user.age >= 19 && user.age <= 30) ? (user.lifestyle == "sedentary" ? 2400 : (user.lifestyle == "moderate" ? 2600 : 3000))
                                 : (user.age >= 31 && user.age <= 50) ? (user.lifestyle == "sedentary" ? 2200 : (user.lifestyle == "moderate" ? 2400 : 2800))
                                 : (user.lifestyle == "sedentary" ? 2000 : (user.lifestyle == "moderate" ? 2200 : 2400));
            } else if (user.gender == "female") {
                user.calories = (user.age >= 19 && user.age <= 30) ? (user.lifestyle == "sedentary" ? 2000 : (user.lifestyle == "moderate" ? 2000 : 2400))
                                 : (user.age >= 31 && user.age <= 50) ? (user.lifestyle == "sedentary" ? 1800 : (user.lifestyle == "moderate" ? 2000 : 2200))
                                 : (user.lifestyle == "sedentary" ? 1600 : (user.lifestyle == "moderate" ? 1800 : 2000));
            }

            cout << "Daily caloric intake for " << user.name << " is " << user.calories << " calories." << endl;
            break; // Exit the loop once the user is found and processed
        }
    }

    if (!found) {
        cout << "Username '" << username << "' not found." << endl;
    }
}


void HealthAssistant::getMealPrep(string username) {
    cout << "************* Get Meal Prep ************" << endl;

    bool found = false;
    vector<UserInfo>::iterator it; 
    for (it = manager.getMyList().begin(); it != manager.getMyList().end(); ++it) {
        if (it->name == username) {
            found = true;
            UserInfo& user = *it; // Reference to the user to modify the object

            if (user.calories == 0) {
                cout << "Calorie details are not available. Please run the getDailyCalories method first." << endl;
                return;
            }

            user.carbs = (user.calories * 0.5) / 4;  // 1 gram of carbs = 4 calories
            user.protein = (user.calories * 0.3) / 4; // 1 gram of protein = 4 calories
            user.fat = ceil((user.calories * 0.2) / 9);     // 1 gram of fat = 9 calories

            cout << "Meal prep for " << user.name << " calculated successfully." << endl;
            cout << "Carbs: " << user.carbs << "g, Protein: " << user.protein << "g, Fat: " << user.fat << "g" << endl;
            break; // Break because the iterator is invalid after modifying the vector
        }
    }

    if (!found) {
        cout << "Username '" << username << "' not found." << endl;
    }
}


void HealthAssistant::display(string username)
{
     manager.display(username); 
} //wrapper method

void HealthAssistant::serialize(string filename)
{
     manager.writeToFile(filename); 
} //wrapper method

void HealthAssistant::readFromFile(string filename)
{
     manager.readFromFile(filename);
} //wrapper method 

void HealthAssistant::deleteUser(string username)
{
     manager.deleteUser(username);
} // wrapper method

void HealthAssistant::massLoadAndCompute(string filename){
    manager.massLoadAndCompute(filename);
} // wrapper method

void HealthAssistant::massLoadAndCompute(string filename, bool off){
    manager.massLoadAndCompute(filename, off);
} // wrapper method


// USNavyMethod
class USNavyMethod: public HealthAssistant
{
    public: 
        USNavyMethod(){};
        ~USNavyMethod(){};
        inline void getBfp(string username);
};


void USNavyMethod::getBfp(string username) {
    cout << "************* Get Body Fat Percentage (BFP) ************" << endl;

    bool found = false;
    for (vector<UserInfo>::iterator it = getMyList().begin(); it != getMyList().end(); ++it) {
        if (it->name == username) {
            found = true;

            // Compute BFP based on the Navy method
            if (it->gender == "female") {
                // Female BFP calculation
                it->bfp = to_string(
                    495 / (1.29579 - 0.35004 * log10(it->waist + it->hip - it->neck) + 0.22100 * log10(it->height)) - 450
                ) + "%";
            } else {
                // Male BFP calculation
                it->bfp = to_string(
                    495 / (1.0324 - 0.19077 * log10(it->waist - it->neck) + 0.15456 * log10(it->height)) - 450
                ) + "%";
            }

            cout << "BFP for " << it->name << ": " << it->bfp << endl;
            break; 
        }
    }

    if (!found) {
        cout << "Username '" << username << "' not found." << endl;
    }
}


// bmiMethod
class BmiMethod: public HealthAssistant
{
    public: 
        BmiMethod(){};
        ~BmiMethod(){};
        inline void getBfp(string username);
};


void BmiMethod::getBfp(string username) {
    std::cout << "************* Get Body Fat Percentage (BFP) ************" << std::endl;

    bool found = false;
    vector<UserInfo>::iterator it;
    for (it = getMyList().begin(); it != getMyList().end(); ++it) {
        if (it->name == username) {
            found = true;

            // Convert height from cm to meters for BMI calculation
            double heightInMeters = it->height / 100.0;
            double BMI = it->weight / (heightInMeters * heightInMeters);

            it->bfp = to_string(BMI) + "%";
            
            std::cout << "BMI: " << it->bfp << " for " << username << std::endl;
            break;
        }
    }

    if (!found) {
        std::cout << "Username '" << username << "' not found." << std::endl;
    }
}


// UserStats
class UserStats {
    public:
        void GetHealthyUsers(string method){
            if(method == "all" || method == "bmi" || method == "USArmy"){
                return GetHealthyUsers(method, "all");
            }
            else {
                throw invalid_argument("Invalid method argument. Must be 'USArmy', 'BMI', or 'all'.");
            }
        }
        void GetHealthyUsers(string method, string gender);
        void GetUnfitUsers(string method){
            if(method == "all" || method == "bmi" || method == "USArmy"){
                return GetHealthyUsers(method, "all");
            }
            else {
                throw invalid_argument("Invalid method argument. Must be 'USArmy', 'BMI', or 'all'.");
            }
        }
        void GetUnfitUsers(string method, string gender);
        void GetFullStats();

};

// get healthy users depending on the gender and method (by default all if not specified)
void UserStats::GetHealthyUsers(string method, string gender){ // sorry for the code repetition :((
    cout << "***************** DISPLAY HEALTHY USERS *****************" << endl;
    bool off = true;
    // bmi method
    if(method == "bmi"){ 
        HealthAssistant* healthy = new BmiMethod();
        healthy->massLoadAndCompute("bmi_user_data.csv", off);
        vector<UserInfo>::iterator it; 

        cout << "------------ DISPLAY BMI ------------" << endl;

        if (gender == "male") {
            cout << "------------     male     ------------" << endl;
            for (it = healthy->getMyList().begin(); it != healthy->getMyList().end(); ++it) {
                if(it->gender == "male"){
                    string bfpStr = it->bfp;
                    bfpStr.erase(bfpStr.size() - 1); // Remove the percentage sign
                    double bfp = atof(bfpStr.c_str());
                    
                    if(it->age >= 20 && it->age <= 39 && bfp >= 8.0 && bfp <= 19.9) {
                        cout << "- " << it->name << endl;
                    }
                    else if(it->age >= 40 && it->age <= 59 && bfp >= 11.0 && bfp <= 21.9) {
                        cout << "- " << it->name << endl;
                    }
                    else if(it->age >= 60 && it->age <= 79 && bfp >= 13.0 && bfp <= 24.9) {
                        cout << "- " << it->name << endl;
                    }
                }
            }
        }
        else if (gender == "female") {
            cout << "------------    female    ------------" << endl;
            for (it = healthy->getMyList().begin(); it != healthy->getMyList().end(); ++it) {
                if(it->gender == "female"){
                    string bfpStr = it->bfp;
                    bfpStr.erase(bfpStr.size() - 1); // Remove the percentage sign
                    double bfp = atof(bfpStr.c_str());
                    
                    if(it->age >= 20 && it->age <= 39 && bfp >= 21.0 && bfp <= 32.9) {
                        cout << "- " << it->name << endl;
                    }
                    else if(it->age >= 40 && it->age <= 59 && bfp >= 23.0 && bfp <= 33.9) {
                        cout << "- " << it->name << endl;
                    }
                    else if(it->age >= 60 && it->age <= 79 && bfp >= 24.0 && bfp <= 35.9) {
                        cout << "- " << it->name << endl;
                    }
                }
            }
        }
        else { // no gender specified
            cout << "------------      all gender     ------------" << endl;
            for (it = healthy->getMyList().begin(); it != healthy->getMyList().end(); ++it) {
                if(it->gender == "female"){
                    string bfpStr = it->bfp;
                    bfpStr.erase(bfpStr.size() - 1); // Remove the percentage sign
                    double bfp = atof(bfpStr.c_str());
                    
                    if(it->age >= 20 && it->age <= 39 && bfp >= 21.0 && bfp <= 32.9) {
                        cout << "- " << it->name << endl;
                    }
                    else if(it->age >= 40 && it->age <= 59 && bfp >= 23.0 && bfp <= 33.9) {
                        cout << "- " << it->name << endl;
                    }
                    else if(it->age >= 60 && it->age <= 79 && bfp >= 24.0 && bfp <= 35.9) {
                        cout << "- " << it->name << endl;
                    }
                }

                if(it->gender == "male"){
                    string bfpStr = it->bfp;
                    bfpStr.erase(bfpStr.size() - 1); // Remove the percentage sign
                    double bfp = atof(bfpStr.c_str());
                    
                    if(it->age >= 20 && it->age <= 39 && bfp >= 8.0 && bfp <= 19.9) {
                        cout << "- " << it->name << endl;
                    }
                    else if(it->age >= 40 && it->age <= 59 && bfp >= 11.0 && bfp <= 21.9) {
                        cout << "- " << it->name << endl;
                    }
                    else if(it->age >= 60 && it->age <= 79 && bfp >= 13.0 && bfp <= 24.9) {
                        cout << "- " << it->name << endl;
                    }
                }
            }
        }
        delete healthy;
    }

    // US Navy method
    else if (method == "USArmy"){
        HealthAssistant* healthy = new USNavyMethod();
        healthy->massLoadAndCompute("us_user_data.csv");
        vector<UserInfo>::iterator it; 

        cout << "------------ DISPLAY US NAVY ------------" << endl;

        if (gender == "male") {
            cout << "------------      male      ------------" << endl;
            for (it = healthy->getMyList().begin(); it != healthy->getMyList().end(); ++it) {
                if(it->gender == "male"){
                    string bfpStr = it->bfp;
                    bfpStr.erase(bfpStr.size() - 1); // Remove the percentage sign
                    double bfp = atof(bfpStr.c_str());
                    
                    if(it->age >= 20 && it->age <= 39 && bfp >= 8.0 && bfp <= 19.9) {
                        cout << "- " << it->name << endl;
                    }
                    else if(it->age >= 40 && it->age <= 59 && bfp >= 11.0 && bfp <= 21.9) {
                        cout << "- " << it->name << endl;
                    }
                    else if(it->age >= 60 && it->age <= 79 && bfp >= 13.0 && bfp <= 24.9) {
                        cout << "- " << it->name << endl;
                    }
                }
            }
        }
        else if (gender == "female") {
            cout << "------------      female      ------------" << endl;
            for (it = healthy->getMyList().begin(); it != healthy->getMyList().end(); ++it) {
                if(it->gender == "female"){
                    string bfpStr = it->bfp;
                    bfpStr.erase(bfpStr.size() - 1); // Remove the percentage sign
                    double bfp = atof(bfpStr.c_str());
                    
                    if(it->age >= 20 && it->age <= 39 && bfp >= 21.0 && bfp <= 32.9) {
                        cout << "- " << it->name << endl;
                    }
                    else if(it->age >= 40 && it->age <= 59 && bfp >= 23.0 && bfp <= 33.9) {
                        cout << "- " << it->name << endl;
                    }
                    else if(it->age >= 60 && it->age <= 79 && bfp >= 24.0 && bfp <= 35.9) {
                        cout << "- " << it->name << endl;
                    }
                }
            }
        }
        else { // no gender specified
            cout << "------------      all gender      ------------" << endl;
            for (it = healthy->getMyList().begin(); it != healthy->getMyList().end(); ++it) {
                if(it->gender == "female"){
                    string bfpStr = it->bfp;
                    bfpStr.erase(bfpStr.size() - 1); // Remove the percentage sign
                    double bfp = atof(bfpStr.c_str());
                    
                    if(it->age >= 20 && it->age <= 39 && bfp >= 21.0 && bfp <= 32.9) {
                        cout << "- " << it->name << endl;
                    }
                    else if(it->age >= 40 && it->age <= 59 && bfp >= 23.0 && bfp <= 33.9) {
                        cout << "- " << it->name << endl;
                    }
                    else if(it->age >= 60 && it->age <= 79 && bfp >= 24.0 && bfp <= 35.9) {
                        cout << "- " << it->name << endl;
                    }
                }

                if(it->gender == "male"){
                    string bfpStr = it->bfp;
                    bfpStr.erase(bfpStr.size() - 1); // Remove the percentage sign
                    double bfp = atof(bfpStr.c_str());
                    
                    if(it->age >= 20 && it->age <= 39 && bfp >= 8.0 && bfp <= 19.9) {
                        cout << "- " << it->name << endl;
                    }
                    else if(it->age >= 40 && it->age <= 59 && bfp >= 11.0 && bfp <= 21.9) {
                        cout << "- " << it->name << endl;
                    }
                    else if(it->age >= 60 && it->age <= 79 && bfp >= 13.0 && bfp <= 24.9) {
                        cout << "- " << it->name << endl;
                    }
                }
            }
        }
        delete healthy;
    }

    // all method
    else if (method == "all") {
        HealthAssistant* healthy1 = new BmiMethod();
        healthy1->massLoadAndCompute("bmi_user_data.csv", off);
        vector<UserInfo>::iterator it1;

        HealthAssistant* healthy2 = new USNavyMethod();
        healthy2->massLoadAndCompute("us_user_data.csv", off);
        vector<UserInfo>::iterator it2; 


        cout << "------------ DISPLAY BMI and US NAVY------------" << endl;

        if (gender == "male"){
            cout << "------------      male      ------------" << endl;

            // BMI
            cout << "1) BMI display" << endl;
            for (it1 = healthy1->getMyList().begin(); it1 != healthy1->getMyList().end(); ++it1) {
                if(it1->gender == "male"){
                    string bfpStr = it1->bfp;
                    bfpStr.erase(bfpStr.size() - 1); // Remove the percentage sign
                    double bfp = atof(bfpStr.c_str());
                    
                    if(it1->age >= 20 && it1->age <= 39 && bfp >= 8.0 && bfp <= 19.9) {
                        cout << "- " << it1->name << endl;
                    }
                    else if(it1->age >= 40 && it1->age <= 59 && bfp >= 11.0 && bfp <= 21.9) {
                        cout << "- " << it1->name << endl;
                    }
                    else if(it1->age >= 60 && it1->age <= 79 && bfp >= 13.0 && bfp <= 24.9) {
                        cout << "- " << it1->name << endl;
                    }
                }
            }

            // US NAVY
            cout << "2) US NAVY display" << endl;
            for (it2 = healthy2->getMyList().begin(); it2 != healthy2->getMyList().end(); ++it2) {
                if(it2->gender == "male"){
                    string bfpStr = it2->bfp;
                    bfpStr.erase(bfpStr.size() - 1); // Remove the percentage sign
                    double bfp = atof(bfpStr.c_str());
                    
                    if(it2->age >= 20 && it2->age <= 39 && bfp >= 8.0 && bfp <= 19.9) {
                        cout << "- " << it2->name << endl;
                    }
                    else if(it2->age >= 40 && it2->age <= 59 && bfp >= 11.0 && bfp <= 21.9) {
                        cout << "- " << it2->name << endl;
                    }
                    else if(it2->age >= 60 && it2->age <= 79 && bfp >= 13.0 && bfp <= 24.9) {
                        cout << "- " << it2->name << endl;
                    }
                }
            }

        }
        else if (gender == "female"){
            cout << "------------      female      ------------" << endl;

            // BMI
            cout << "1) BMI display" << endl;
            for (it1 = healthy1->getMyList().begin(); it1 != healthy1->getMyList().end(); ++it1) {
                if(it1->gender == "female"){
                    string bfpStr = it1->bfp;
                    bfpStr.erase(bfpStr.size() - 1); // Remove the percentage sign
                    double bfp = atof(bfpStr.c_str());
                    
                    if(it1->age >= 20 && it1->age <= 39 && bfp >= 21.0 && bfp <= 32.9) {
                        cout << "- " << it1->name << endl;
                    }
                    else if(it1->age >= 40 && it1->age <= 59 && bfp >= 23.0 && bfp <= 33.9) {
                        cout << "- " << it1->name << endl;
                    }
                    else if(it1->age >= 60 && it1->age <= 79 && bfp >= 24.0 && bfp <= 35.9) {
                        cout << "- " << it1->name << endl;
                    }
                }
            }

            // US NAVY
            cout << "2) US NAVY display" << endl;
            for (it2 = healthy2->getMyList().begin(); it2 != healthy2->getMyList().end(); ++it2) {
                if(it2->gender == "female"){
                    string bfpStr = it2->bfp;
                    bfpStr.erase(bfpStr.size() - 1); // Remove the percentage sign
                    double bfp = atof(bfpStr.c_str());
                    
                    if(it2->age >= 20 && it2->age <= 39 && bfp >= 21.0 && bfp <= 32.9) {
                        cout << "- " << it2->name << endl;
                    }
                    else if(it2->age >= 40 && it2->age <= 59 && bfp >= 23.0 && bfp <= 33.9) {
                        cout << "- " << it2->name << endl;
                    }
                    else if(it2->age >= 60 && it2->age <= 79 && bfp >= 24.0 && bfp <= 35.9) {
                        cout << "- " << it2->name << endl;
                    }
                }
            }
        }
        else { // no gender specified
            cout << "------------      all gender      ------------" << endl;

            // BMI
            cout << "1) BMI display" << endl;
            for (it1 = healthy1->getMyList().begin(); it1 != healthy1->getMyList().end(); ++it1) {
                if(it1->gender == "female"){
                    string bfpStr = it1->bfp;
                    bfpStr.erase(bfpStr.size() - 1); // Remove the percentage sign
                    double bfp = atof(bfpStr.c_str());
                    
                    if(it1->age >= 20 && it1->age <= 39 && bfp >= 21.0 && bfp <= 32.9) {
                        cout << "- " << it1->name << endl;
                    }
                    else if(it1->age >= 40 && it1->age <= 59 && bfp >= 23.0 && bfp <= 33.9) {
                        cout << "- " << it1->name << endl;
                    }
                    else if(it1->age >= 60 && it1->age <= 79 && bfp >= 24.0 && bfp <= 35.9) {
                        cout << "- " << it1->name << endl;
                    }
                }

                if(it1->gender == "male"){
                    string bfpStr = it1->bfp;
                    bfpStr.erase(bfpStr.size() - 1); // Remove the percentage sign
                    double bfp = atof(bfpStr.c_str());
                    
                    if(it1->age >= 20 && it1->age <= 39 && bfp >= 8.0 && bfp <= 19.9) {
                        cout << "- " << it1->name << endl;
                    }
                    else if(it1->age >= 40 && it1->age <= 59 && bfp >= 11.0 && bfp <= 21.9) {
                        cout << "- " << it1->name << endl;
                    }
                    else if(it1->age >= 60 && it1->age <= 79 && bfp >= 13.0 && bfp <= 24.9) {
                        cout << "- " << it1->name << endl;
                    }
                }
            }

            // US NAVY
            cout << "2) US NAVY display" << endl;
            for (it2 = healthy2->getMyList().begin(); it2 != healthy2->getMyList().end(); ++it2) {
                if(it2->gender == "female"){
                    string bfpStr = it2->bfp;
                    bfpStr.erase(bfpStr.size() - 1); // Remove the percentage sign
                    double bfp = atof(bfpStr.c_str());
                    
                    if(it2->age >= 20 && it2->age <= 39 && bfp >= 21.0 && bfp <= 32.9) {
                        cout << "- " << it2->name << endl;
                    }
                    else if(it2->age >= 40 && it2->age <= 59 && bfp >= 23.0 && bfp <= 33.9) {
                        cout << "- " << it2->name << endl;
                    }
                    else if(it2->age >= 60 && it2->age <= 79 && bfp >= 24.0 && bfp <= 35.9) {
                        cout << "- " << it2->name << endl;
                    }
                }

                if(it2->gender == "male"){
                    string bfpStr = it2->bfp;
                    bfpStr.erase(bfpStr.size() - 1); // Remove the percentage sign
                    double bfp = atof(bfpStr.c_str());
                    
                    if(it2->age >= 20 && it2->age <= 39 && bfp >= 8.0 && bfp <= 19.9) {
                        cout << "- " << it2->name << endl;
                    }
                    else if(it2->age >= 40 && it2->age <= 59 && bfp >= 11.0 && bfp <= 21.9) {
                        cout << "- " << it2->name << endl;
                    }
                    else if(it2->age >= 60 && it2->age <= 79 && bfp >= 13.0 && bfp <= 24.9) {
                        cout << "- " << it2->name << endl;
                    }
                }
            }
        }
        delete healthy1;
        delete healthy2;
    }
}


// ***** more efficient way for GetUnfitUsers(string method, string gender) with less code repetition
// Helper methods for UserStats::GetUnfitUsers(string method, string gender)
void maleUnfit(string method);
void femaleUnfit(string method);
void allGenderUnfit(string method);

// get unfit users depending on the gender and method (by default all if not specified)
void UserStats::GetUnfitUsers(string method, string gender){
    cout << "***************** DISPLAY UNFIT USERS *****************" << endl;
    if (gender == "male") {
        cout << "------------      male      ------------" << endl;
        if (method == "all"){
            cout << "------------      bmi and US Navy      ------------" << endl;
            maleUnfit("bmi");
            maleUnfit("USArmy");
        }
        else {
            maleUnfit(method);
        }
    }
    else if (gender == "female") {
        cout << "------------      female      ------------" << endl;
        if (method == "all"){
            cout << "------------      bmi and US Navy      ------------" << endl;
            femaleUnfit("bmi");
            femaleUnfit("USArmy");
        }
        else {
            femaleUnfit(method);
        }
    }
    else { // no gender specified
        cout << "------------      all gender      ------------" << endl;
        if (method == "all"){
            cout << "------------      bmi and US Navy      ------------" << endl;
            allGenderUnfit("bmi");
            allGenderUnfit("USArmy");
        }
        else {
            allGenderUnfit(method);
        }
    }
}


void maleUnfit(string method){
    vector<UserInfo>::iterator it;
    HealthAssistant* unfit;
    bool off = true;

    if (method == "bmi"){
        cout << "------------      bmi     ------------" << endl;
        unfit = new BmiMethod();
        unfit->massLoadAndCompute("bmi_user_data.csv", off);
    }
    else if (method == "USArmy"){
        cout << "------------      US Navy     ------------" << endl;
        unfit = new USNavyMethod();
        unfit->massLoadAndCompute("us_user_data.csv", off);
    }

    for (it = unfit->getMyList().begin(); it != unfit->getMyList().end(); ++it) {
        if(it->gender == "male"){
            string bfpStr = it->bfp;
            bfpStr.erase(bfpStr.size() - 1); // Remove the percentage sign
            double bfp = atof(bfpStr.c_str());
            
            if(it->age >= 20 && it->age <= 39 && bfp >= 20.0) {
                cout << "- " << it->name << endl;
            }
            else if(it->age >= 40 && it->age <= 59 && bfp >= 22.0) {
                cout << "- " << it->name << endl;
            }
            else if(it->age >= 60 && it->age <= 79 && bfp >= 25.0) {
                cout << "- " << it->name << endl;
            }
        }
    }
    delete unfit;
}


void femaleUnfit(string method){
    vector<UserInfo>::iterator it;
    HealthAssistant* unfit;
    bool off = true;

    if (method == "bmi"){
        cout << "------------      bmi     ------------" << endl;
        unfit = new BmiMethod();
        unfit->massLoadAndCompute("bmi_user_data.csv", off);
    }
    else if (method == "USArmy"){
        cout << "------------      US Navy     ------------" << endl;
        unfit = new USNavyMethod();
        unfit->massLoadAndCompute("us_user_data.csv", off);
    }

    for (it = unfit->getMyList().begin(); it != unfit->getMyList().end(); ++it) {
        if(it->gender == "female"){
            string bfpStr = it->bfp;
            bfpStr.erase(bfpStr.size() - 1); // Remove the percentage sign
            double bfp = atof(bfpStr.c_str());
            
            if(it->age >= 20 && it->age <= 39 && bfp >= 33.0) {
                cout << "- " << it->name << endl;
            }
            else if(it->age >= 40 && it->age <= 59 && bfp >= 34.0) {
                cout << "- " << it->name << endl;
            }
            else if(it->age >= 60 && it->age <= 79 && bfp >= 36.0) {
                cout << "- " << it->name << endl;
            }
        }
    }
    delete unfit;
}

void allGenderUnfit(string method){
    vector<UserInfo>::iterator it;
    HealthAssistant* unfit;
    bool off = true;

    if (method == "bmi"){
        cout << "------------      bmi     ------------" << endl;
        unfit = new BmiMethod();
        unfit->massLoadAndCompute("bmi_user_data.csv", off);
    }
    else if (method == "USArmy"){
        cout << "------------      US Navy     ------------" << endl;
        unfit = new USNavyMethod();
        unfit->massLoadAndCompute("us_user_data.csv", off);
    }

    for (it = unfit->getMyList().begin(); it != unfit->getMyList().end(); ++it) {
        if(it->gender == "female"){
            string bfpStr = it->bfp;
            bfpStr.erase(bfpStr.size() - 1); // Remove the percentage sign
            double bfp = atof(bfpStr.c_str());
            
            if(it->age >= 20 && it->age <= 39 && bfp >= 33.0) {
                cout << "- " << it->name << endl;
            }
            else if(it->age >= 40 && it->age <= 59 && bfp >= 34.0) {
                cout << "- " << it->name << endl;
            }
            else if(it->age >= 60 && it->age <= 79 && bfp >= 36.0) {
                cout << "- " << it->name << endl;
            }
        }

        if(it->gender == "male"){
            string bfpStr = it->bfp;
            bfpStr.erase(bfpStr.size() - 1); // Remove the percentage sign
            double bfp = atof(bfpStr.c_str());
            
            if(it->age >= 20 && it->age <= 39 && bfp >= 20.0) {
                cout << "- " << it->name << endl;
            }
            else if(it->age >= 40 && it->age <= 59 && bfp >= 22.0) {
                cout << "- " << it->name << endl;
            }
            else if(it->age >= 60 && it->age <= 79 && bfp >= 25.0) {
                cout << "- " << it->name << endl;
            }
        }
    }
    delete unfit;
}

// helper functions for GetFullStats()
void get_bfp_healthy(string method, int &male_total, int &female_total, int &bmi, int &USArmy, int &hmale, int &hfemale, int &hbmi, int &hUSArmy, int &h_bmi_male, int &h_bmi_female, int &h_US_male, int &h_US_female);

void UserStats::GetFullStats(){
    // assuming that we have different users for the two csv files
    int total_user = 0;
    int male_user = 0;
    int female_user = 0;

    int bmi_user = 0;
    int USArmy_user = 0;

    int healthy_male = 0;
    int healthy_female = 0;

    int healthy_bmi = 0;
    int healthy_USArmy = 0;

    int h_bmi_male = 0;
    int h_bmi_female = 0;

    int h_US_male = 0;
    int h_US_female = 0;

    // bmi method
    get_bfp_healthy("bmi", male_user, female_user, bmi_user, USArmy_user, healthy_male, healthy_female, healthy_bmi, healthy_USArmy, h_bmi_male, h_bmi_female, h_US_male, h_US_female);

    // US Navy method
    get_bfp_healthy("USArmy", male_user, female_user, bmi_user, USArmy_user, healthy_male, healthy_female, healthy_bmi, healthy_USArmy, h_bmi_male, h_bmi_female, h_US_male, h_US_female);

    total_user = bmi_user + USArmy_user;
    double percentage_male = (double) male_user/total_user*100;
    double percentage_female = (double) female_user/total_user*100;
    double percentage_healthy_bmi = (double) healthy_bmi/bmi_user*100;
    double percentage_healthy_USArmy = (double) healthy_USArmy/USArmy_user*100;
    double percentage_h_female_bmi = (double) h_bmi_female/bmi_user*100; // eg. (number of healthy females in BMI) / (total number of users in bmi)
    double percentage_h_female_US = (double) h_US_female/USArmy_user*100;
    double percentage_h_male_bmi = (double) h_bmi_male/bmi_user*100;
    double percentage_h_male_US = (double) h_US_male/USArmy_user*100;

    cout << "Total number of users: " << total_user << endl;
    cout << "Percentage of male users: " << fixed << setprecision(2) << percentage_male << "%" << endl;
    cout << "Percentage of female users: " << fixed << setprecision(2) << percentage_female << "%" << endl;
    cout << "Percentage of healthy users according to bmi method: " << fixed << setprecision(2) << percentage_healthy_bmi << "%" << endl;
    cout << "Percentage of healthy users according to USArmy method: " << fixed << setprecision(2) << percentage_healthy_USArmy << "%" << endl;
    cout << "Percentage of healthy female users according to bmi method: " << fixed << setprecision(2) << percentage_h_female_bmi << "%" << endl;
    cout << "Percentage of healthy male users according to bmi method: " << fixed << setprecision(2) << percentage_h_male_bmi << "%" << endl;
    cout << "Percentage of healthy female users according to USArmy method: " << fixed << setprecision(2) << percentage_h_female_US << "%" << endl;
    cout << "Percentage of healthy male users according to USArmy method: " << fixed << setprecision(2) << percentage_h_male_US << "%" << endl;
    
}


void get_bfp_healthy(string method, int &male_total, int &female_total, int &bmi, int &USArmy, int &hmale, int &hfemale, int &hbmi, int &hUSArmy, int &h_bmi_male, int &h_bmi_female, int &h_US_male, int &h_US_female){
    vector<UserInfo>::iterator it;
    HealthAssistant* healthy;
    bool off;

    if (method == "bmi"){
        healthy = new BmiMethod();
        healthy->massLoadAndCompute("bmi_user_data.csv", off);
    }
    else if (method == "USArmy"){
        healthy = new USNavyMethod();
        healthy->massLoadAndCompute("us_user_data.csv", off);
    }

    for (it = healthy->getMyList().begin(); it != healthy->getMyList().end(); ++it) {
        if (method == "bmi") bmi +=1;
        if (method == "USArmy") USArmy +=1;

        if(it->gender == "female"){
            female_total +=1;

            string bfpStr = it->bfp;
            bfpStr.erase(bfpStr.size() - 1); // Remove the percentage sign
            double bfp = atof(bfpStr.c_str());
            
            if(it->age >= 20 && it->age <= 39 && bfp >= 21.0 && bfp <= 32.9) {
                hfemale+=1;
                if (method == "bmi") hbmi +=1;
                if (method == "USArmy") hUSArmy +=1;
                if (method == "bmi") h_bmi_female +=1;
                if (method == "USArmy") h_US_female +=1;

            }
            else if(it->age >= 40 && it->age <= 59 && bfp >= 23.0 && bfp <= 33.9) {
                hfemale+=1;
                if (method == "bmi") hbmi +=1;
                if (method == "USArmy") hUSArmy +=1;
                if (method == "bmi") h_bmi_female +=1;
                if (method == "USArmy") h_US_female +=1;

            }
            else if(it->age >= 60 && it->age <= 79 && bfp >= 24.0 && bfp <= 35.9) {
                hfemale+=1;
                if (method == "bmi") hbmi +=1;
                if (method == "USArmy") hUSArmy +=1;
                if (method == "bmi") h_bmi_female +=1;
                if (method == "USArmy") h_US_female +=1;
            }
        }

        if(it->gender == "male"){
            male_total +=1;

            string bfpStr = it->bfp;
            bfpStr.erase(bfpStr.size() - 1); // Remove the percentage sign
            double bfp = atof(bfpStr.c_str());
            
            if(it->age >= 20 && it->age <= 39 && bfp >= 8.0 && bfp <= 19.9) {
                hmale+=1;
                if (method == "bmi") hbmi +=1;
                if (method == "USArmy") hUSArmy +=1;
                if (method == "bmi") h_bmi_male +=1;
                if (method == "USArmy") h_US_male +=1;

            }
            else if(it->age >= 40 && it->age <= 59 && bfp >= 11.0 && bfp <= 21.9) {
                hmale+=1;
                if (method == "bmi") hbmi +=1;
                if (method == "USArmy") hUSArmy +=1;
                if (method == "bmi") h_bmi_male +=1;
                if (method == "USArmy") h_US_male +=1;
            }
            else if(it->age >= 60 && it->age <= 79 && bfp >= 13.0 && bfp <= 24.9) {
                hmale+=1;
                if (method == "bmi") hbmi +=1;
                if (method == "USArmy") hUSArmy +=1;
                if (method == "bmi") h_bmi_male +=1;
                if (method == "USArmy") h_US_male +=1;
            }
        }
    }
}


int main() {
    HealthAssistant* ha = new USNavyMethod(); 
    std::string userInput;

    // Loop until the user inputs "exit"
    while (true) {
        // Get user details
        ha->getUserDetail();

        // Ignore any newline characters left in the input stream
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Ask for user input
        std::cout << "Enter 'exit' to quit, or press Enter to continue: \n";
        
        std::getline(std::cin, userInput);

        // Check if the user wants to exit
        if (userInput == "exit") {
            break; // Exit the loop
        } 
    }
    ha->display("all");
    ha->getBfp("john");
    ha->getDailyCalories("john");
    ha->getMealPrep("john");
    ha->serialize("us_user_data.csv");
    delete ha;

    ha = new BmiMethod();
    
    // Loop until the user inputs "exit"
    while (true) {
        // Get user details
        ha->getUserDetail();

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Ask for user input
        std::cout << "Enter 'exit' to quit, or press Enter to continue: \n";
        
        std::getline(std::cin, userInput);
        
        // Check if the user wants to exit
        if (userInput == "exit") {
            break; // Exit the loop
        } 
    }

    ha->display("all");

    ha->getBfp("john");
    ha->getDailyCalories("john");
    ha->getMealPrep("john");

    ha->deleteUser("jack"); // assuming we have a user jack
    ha->display("all"); // should display all except for jack

    ha->serialize("bmi_user_data.csv");
    delete ha;

    ha = new USNavyMethod();
    ha->massLoadAndCompute("us_user_data.csv");
    ha->display("all");
    delete ha;

    ha = new BmiMethod();
    ha->massLoadAndCompute("bmi_user_data.csv");
    ha->display("all");

    delete ha;

    UserStats stat;
    stat.GetHealthyUsers("bmi", "female");
    stat.GetHealthyUsers("all");
    stat.GetUnfitUsers("USArmy", "male");
    stat.GetFullStats();
 }