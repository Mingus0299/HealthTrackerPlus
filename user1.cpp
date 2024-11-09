#include<iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct User
{
    std::string g_gender;
    int g_age;
    double g_weight;
    double g_waist;
    double g_neck;
    double g_height;
    std::string g_lifestyle;
    double g_hip; //if female
};

int getUserDetails();
bool ValidateGender(string input);
bool ValidateLifestyle(string input);

std::pair<int,string> get_bfp(double waist, double neck, double height, double hip, string gender, int age);
pair<int,string> bfpres;

int get_daily_calories(int age, string gender, string lifestyle);

void meal_prep(int calories_input, double &carbs_output, double &protein_output, double& fat_output);

void display();

void serialize(string filename);

void readFromFile(string filename);

double carbs, protein, fat;

string g_gender;
float age;
int g_age;
double g_weight;
double g_waist;
double g_neck;
double g_height;
string g_lifestyle;
double g_hip; //if female

int main(int argc, char* argv[]) {
// Check if a filename is provided as an argument 
    if (argc > 1) {
        // Load existing user data from the specified CSV file
        readFromFile(argv[1]);

    } else {
        // Gather user details
        getUserDetails();

        // Calculate body fat percentage
        auto bfpResult = get_bfp(g_waist, g_neck, g_height, g_hip,g_gender, g_age);
        std::cout << "Body Fat Percentage: " << bfpResult.first << "% (" << bfpResult.second << ")" << std::endl;
        bfpres = bfpResult;

        // Calculate daily calorie intake
        int dailyCalories = get_daily_calories(g_age, g_gender, g_lifestyle);
        std::cout << "Daily Caloric Intake: " << dailyCalories << " calories" << std::endl;

        // Calculate macronutrient breakdown
        // double carbs, protein, fat;
        meal_prep(dailyCalories, carbs, protein, fat);
        std::cout << "Macronutrient Breakdown:\n";
        std::cout << "Carbs: " << carbs << "g, Protein: " << protein << "g, Fat: " << fat << "g" << std::endl;
        
        // Display user information
        display();
        
        // Save user data to a CSV file
        serialize("user_data.csv");
    }
    return 0;
}

//Input gathering Function
int getUserDetails(){

    //gender
    do{
        cout << "Please specify your gender as either male or female: " << endl;
        cin >> g_gender; 
    } while (!ValidateGender(g_gender));
	
    //get hip if female
    if(g_gender == "female"){
        while (1){
            cout << "Enter your hip measurement in centimeters: (input double)" << endl;
            if (cin >> g_hip){
                break; // valid int
            } else {
                cin.clear();
                while (cin.get() != '\n') ; // invalid int
            }
        }
    }

    //get age
    while (1){
        cout << "Enter your age: (input only digits & 19 - 79)" << endl;
        if (cin >> age && (age == floor(age))){
            g_age = age;
            break; // valid int
        }
        else {
            cin.clear();
            while (cin.get() != '\n') ; // invalid int
        }
    } 

    //get weight
    while(1){
        cout << "Enter your body weight in kilograms: (input double) " << endl;
        if (cin >> g_weight){
            break; // valid double
        }
        else {
            cin.clear();
            while (cin.get() != '\n') ; // invalid double
        }
    } 
	
    //get waist
    while(1){
        cout << "Input your waist measurement using centimeters: (input double) " <<endl;
        if (cin >> g_waist){
            break; // valid double
        }
        else {
            cin.clear();
            while (cin.get() != '\n') ; // invalid double
        }
    } 

    //get neck
    while(1){
        cout << "Provide your neck measurement in centimeters: (input double)" << endl; 
        if (cin >> g_neck){
            break; // valid double
        }
        else {
            cin.clear();
            while (cin.get() != '\n') ; // invalid double
        }
    } 

    //get height
    while(1){
        cout << "Input height measurement in centimeters: (input double)" << endl;
        if (cin >> g_height){
            break; // valid double
        }
        else {
            cin.clear();
            while (cin.get() != '\n') ; // invalid double
        }
    } 

    //get lifestyle
    do{
        cout << "Provide information about your current lifestyle: sedentary, moderate (moderately active) or active: " << endl;
        cin >> g_lifestyle; 
    } while (!ValidateLifestyle(g_lifestyle));

    return 0;
}

bool ValidateGender(string input){ // either female || male in lowercase
    if ((input == "female") || (input == "male")){
        return true;
    }
    return false;
}

bool ValidateLifestyle(string input){ // either sedentary || moderate || active in lowercase
    if ((input == "sedentary") || (input == "moderate") || (input == "active")){
        return true;
    }
    return false;
}

//Body Fat Percentage
pair<int,string> get_bfp(double waist, double neck, double height, double hip, string gender, int age){
    // for females
    double BF_percentage;
    string group;
    if (gender == "female"){
        BF_percentage = 495 / ( 1.29579 - 0.35004 * log10( waist + hip - neck ) + 0.22100 * log10( height ) ) - 450;
        int bf_perc = BF_percentage;

        if (age >= 20 && age <= 39){
            if (BF_percentage < 21) return make_pair(bf_perc,"low");
            if (BF_percentage >= 21 && BF_percentage < 33.0) return make_pair(bf_perc,"normal");
            if (BF_percentage >= 33 && BF_percentage < 39.0) return make_pair(bf_perc,"high");
            if (BF_percentage >= 39) return make_pair(bf_perc,"very high");
        }
        else if (age >= 40 && age <= 59){
            if (BF_percentage < 23) return make_pair(bf_perc,"low");
            if (BF_percentage >= 23 && BF_percentage < 34.0) return make_pair(bf_perc,"normal");
            if (BF_percentage >= 34 && BF_percentage < 40.0) return make_pair(bf_perc,"high");
            if (BF_percentage >= 40) return make_pair(bf_perc,"very high");
        }
        else if (age >= 60 && age <= 79){
            if (BF_percentage < 24) return make_pair(bf_perc,"low");
            if (BF_percentage >= 24 && BF_percentage < 36.0) return make_pair(bf_perc,"normal");
            if (BF_percentage >= 36 && BF_percentage < 42.0) return make_pair(bf_perc,"high");
            if (BF_percentage >= 42) return make_pair(bf_perc,"very high");
        }
    }

    // for males
    if (gender == "male"){
        BF_percentage = 495 / ( 1.0324 - 0.19077 * log10( waist - neck ) + 0.15456 * log10( height ) ) - 450;
        int bf_perc = BF_percentage;

        if (age >= 20 && age <= 39){
            if (BF_percentage < 8) return make_pair(bf_perc,"low");
            if (BF_percentage >= 8 && BF_percentage < 20.0) return make_pair(bf_perc,"normal");
            if (BF_percentage >= 20 && BF_percentage < 25.0) return make_pair(bf_perc,"high");
            if (BF_percentage >= 25) return make_pair(bf_perc,"very high");
        }
        else if (age >= 40 && age <= 59){
            if (BF_percentage < 11) return make_pair(bf_perc,"low");
            if (BF_percentage >= 11 && BF_percentage < 22.0) return make_pair(bf_perc,"normal");
            if (BF_percentage >= 22 && BF_percentage < 28.0) return make_pair(bf_perc,"high");
            if (BF_percentage >= 28) return make_pair(bf_perc,"very high");
        }
        else if (age >= 60 && age <= 79){
            if (BF_percentage < 13) return make_pair(bf_perc,"low");
            if (BF_percentage >= 13 && BF_percentage < 25.0) return make_pair(bf_perc,"normal");
            if (BF_percentage >= 25 && BF_percentage < 30.0) return make_pair(bf_perc,"high");
            if (BF_percentage >= 30) return make_pair(bf_perc,"very high");
        }
    }
}

// calories/day
int get_daily_calories(int age, string gender, string lifestyle){
    // for males
    if (gender == "male"){
        if (age >= 19 && age <= 30){
            if (lifestyle == "sedentary"){
                return 2400;
            }
            else if (lifestyle == "moderate"){
                return 2600;
            }
            else {
                return 3000;
            }
        }
        else if (age >= 31 && age <= 50){
            if (lifestyle == "sedentary"){
                return 2200;
            }
            else if (lifestyle == "moderate"){
                return 2400;
            }
            else {
                return 2800;
            }
        }
        else{
            if (lifestyle == "sedentary"){
                return 2000;
            }
            else if (lifestyle == "mdderate"){
                return 2200;
            }
            else {
                return 2400;
            }
        }
    }

    // for females
    if (gender == "female"){
        if (age >= 19 && age <= 30){
            if (lifestyle == "sedentary"){
                return 2000;
            }
            else if (lifestyle == "moderate"){
                return 2000;
            }
            else {
                return 2400;
            }
        }
        else if (age >= 31 && age <= 50){
            if (lifestyle == "sedentary"){
                return 1800;
            }
            else if (lifestyle == "moderate"){
                return 2000;
            }
            else {
                return 2200;
            }
        }
        else{
            if (lifestyle == "sedentary"){
                return 1600;
            }
            else if (lifestyle == "mdderate"){
                return 1800;
            }
            else {
                return 2000;
            }
        }
    }
}

// macronutrient breakdown
void meal_prep(int calories_input, double &carbs_output, double &protein_output, double& fat_output){
    int rest;
    carbs_output = calories_input * 2/5 / 4;
    protein_output = calories_input * 12/50 / 4;
    fat_output = calories_input *18/50 / 9;

    rest = calories_input - carbs_output*4 - protein_output*4 - fat_output*9;

    while(rest > 0){
        carbs_output += 1;
        protein_output += 1;
        fat_output += 1;
        rest = calories_input - carbs_output*4 - protein_output*4 - fat_output*9;

    // 4 * 5 = 20 carb        2/5        10     
    // 4 * 3 = 12 protein     12/50      6      
    // 9 * 2 = 18 fat         18/50      4
    //         50 cal total
    }
}

// Display
void display(){
    cout << " " << endl;
    cout << " " << endl;
    cout << "Display" << endl;
    cout << endl;

    cout << "Gender: " << g_gender << endl;
    cout << "Age: " << g_age << endl;
    cout << "Weight: " << g_weight << endl;
    cout << "Waist: " << g_waist << endl;
    cout << "Neck: " << g_neck << endl;
    cout << "Height: " << g_height << endl;
    if (g_gender == "female") {
        cout << "Hip: " << g_hip << endl;
    }
    cout << "Lifestyle: " << g_lifestyle << endl;
    cout << endl;

    cout << "Body Fat Percentage: " << bfpres.first << "% (" << bfpres.second << ")" << endl;
    cout << endl;

    int dailyCalories = get_daily_calories(g_age, g_gender, g_lifestyle);
    cout << "Daily Caloric Intake: " << dailyCalories << " calories" << endl;
    cout << endl;

    meal_prep(dailyCalories, carbs, protein, fat);
    cout << "Macronutrient Breakdown:\n";
    cout << "Carbs: " << carbs << "g, Protein: " << protein << "g, Fat: " << fat << "g" << endl;
    cout << endl;
}

// Persistence
void serialize(string filename){
    ifstream myFile(filename);
    if(!myFile){
       cout << "File failed to open";
       myFile.close();
    }
    
    else{
        ofstream file;
        file.open(filename, ios::app);
        if (g_gender == "male"){
            file << g_gender << ", " << g_age << ", " << g_waist << ", " << g_neck << ",, " << g_height << ", " << g_lifestyle << endl;
        }
        else {
            file << g_gender << ", " << g_age << ", " << g_waist << ", " << g_neck << ", "<< g_hip << ", " << g_height << ", " << g_lifestyle << endl;
        }
        file.close();
    }
}

// read from file
void readFromFile(string filename){
    ifstream myFile(filename);
    if(!myFile){
       cout << "File failed to open";
       myFile.close();
    }

    else{
        string line;
        ifstream File(filename);
        vector<User> users;
        while (getline(File, line)){
            User user;
            string token;
            stringstream iss(line);

            getline(iss, user.g_gender,',');

            getline(iss, token,',');
            token.erase(0,1);
            user.g_age = atoi(token.c_str());

            getline(iss, token,',');
            token.erase(0,1);
            user.g_weight = atof(token.c_str());

            getline(iss, token,',');
            token.erase(0,1);
            user.g_waist = atof(token.c_str());

            getline(iss, token,',');
            token.erase(0,1);
            user.g_neck = atof(token.c_str());

            getline(iss, token,',');
            if(user.g_gender == "female"){
                token.erase(0,1);
                user.g_hip = atof(token.c_str());
            }

            getline(iss, token,',');
            token.erase(0,1);
            user.g_height = atof(token.c_str());

            getline(iss, token);
            user.g_lifestyle = token;
            users.push_back(user);
        }
        File.close();

        // for (auto user: users){
        //     g_gender = user.g_gender;
        //     g_age = user.g_age;
        //     g_weight = user.g_weight;
        //     g_waist = user.g_waist;
        //     g_neck = user.g_neck;
        //     g_height = user.g_height;
        //     g_lifestyle = user.g_lifestyle;
        //     g_hip = user.g_hip; //if female
        //     serialize("user_data.csv");
        // }
    }
}

