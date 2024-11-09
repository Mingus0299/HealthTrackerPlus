#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

//  csv format
//  Gender, Age, Weight, Waist, Neck, Hip, Height, Lifestyle, Name, Carbs, Protein, Fat, Calories, Bfp
//  everything must be initialized except for hip 

// Bfp format
// (% . string)  instead of (%, string)

struct UserInfo 
{    
     int age;
     double weight;
     double waist;
     double neck;
     double height;
     double carbs;
     double protein;
     double fat;
     double calories;
     std::string name;
     std::string gender;
     std::string lifestyle;
     std::string bfp;
     double hip;
     UserInfo* next;
};

//helper functions
bool ValidateGender(string input);
bool ValidateLifestyle(string input);


class UserInfoManager //pointer to user info linkedlist
{
     //string *username = new string;
     //string *filename = new string;

     public:
          UserInfoManager()
          {
               this->mylist = NULL;
          } // constructor. initializes linked list 


          ~UserInfoManager()
          {
               UserInfo* current = mylist;
               while (current != NULL) {
                    UserInfo* next = current->next;
                    delete current;
                    current = next;
               }
               mylist = NULL; // Ensure the head pointer is null after deletion
          } // destructor. delete allocated memory 
          inline void addUserInfo(); // adds info to list
          inline void deleteUser(string username); // removes a user


          void readFromFile(string filename)
          {    //  Gender, Age, Weight, Waist, Neck, Hip, Height, Lifestyle, Name, Carbs, Protein, Fat, Calories, bfp
               std::cout << "************* reading file ************" << endl;
               this->~UserInfoManager();
               this->mylist = NULL;
               UserInfo *temp1 = this->mylist;

               ifstream myFile(filename);
               if(!myFile){
                    std::cout << "File failed to open";
                    myFile.close();
               }

               else{
                    string line;
                    ifstream File(filename);
                    while (getline(File, line)){
                         struct UserInfo* new_user = new UserInfo;
                         string token;
                         stringstream iss(line);

                         //Gender
                         getline(iss, new_user->gender,',');

                         //Age
                         getline(iss, token,',');
                         token.erase(0,1);
                         new_user->age = atoi(token.c_str());

                         //Weight
                         getline(iss, token,',');
                         token.erase(0,1);
                         new_user->weight = atof(token.c_str());

                         //Waist
                         getline(iss, token,',');
                         token.erase(0,1);
                         new_user->waist = atof(token.c_str());

                         //Neck
                         getline(iss, token,',');
                         token.erase(0,1);
                         new_user->neck = atof(token.c_str());

                         //Hip
                         getline(iss, token,',');
                         if(new_user->gender == "female"){
                              token.erase(0,1);
                              new_user->hip = atof(token.c_str());
                         }

                         //Height
                         getline(iss, token,',');
                         token.erase(0,1);
                         new_user->height = atof(token.c_str());

                         //Lifestyle
                         getline(iss, token,',');
                         token.erase(0,1);
                         new_user->lifestyle = token;

                         //Name
                         getline(iss, token,',');
                         token.erase(0,1);
                         new_user->name = token;

                         //Carbs
                         getline(iss, token,',');
                         token.erase(0,1);
                         new_user->carbs = atof(token.c_str());

                         //Protein
                         getline(iss, token,',');
                         token.erase(0,1);
                         new_user->protein = atof(token.c_str());

                         //Fat
                         getline(iss, token,',');
                         token.erase(0,1);
                         new_user->fat = atof(token.c_str());

                         //Calories
                         getline(iss, token, ',');
                         token.erase(0,1);
                         new_user->calories = atof(token.c_str());

                         //BFP
                         getline(iss, token);
                         token.erase(0,1);
                         new_user->bfp = token;
                         new_user->next = NULL;

                         //if mylist empty adding first node
                         if (temp1 == NULL){
                              this->mylist = new_user;
                              temp1 = new_user;
                         }
                         else{
                              temp1->next = new_user;
                              temp1 = temp1->next;
                         }

                    }
                    File.close();
                    std::cout << "*************************" << endl;
               }

          }; // read and populate list 

          void writeToFile(string filename);
          inline void display(string username);
          UserInfo* getUserList() const { return mylist; } 
     private:
          UserInfo* mylist; // pointer to first element in linked list
};

void UserInfoManager::addUserInfo()
{         
     std::cout << "************* add new user ************" << endl;
     std::string g_name;
     std::string g_gender;
     int g_age;
     double g_weight;
     double g_waist;
     double g_neck;
     double g_height;
     std::string g_lifestyle;
     double g_hip; //if female

     //name
     while(1){
          cout << "Enter your name: " << endl;
          if (cin >> g_name){
               break; // valid double
          }
          else {
               cin.clear();
               while (cin.get() != '\n') ; // invalid double
          }
     }

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
          if (cin >> g_age && (g_age == floor(g_age)) && g_age>=19 && g_age<=79){
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

     std::cout << "*************************" << endl;

     
     //create new node for user
     UserInfo* new_user = new UserInfo;
     new_user->age = g_age;
     new_user->weight = g_weight;
     new_user->waist = g_waist;
     new_user->neck = g_neck;
     new_user->height = g_height;
     new_user->carbs = 0;
     new_user->protein = 0;
     new_user->fat = 0;
     new_user->name = g_name;
     new_user->gender = g_gender;
     new_user->lifestyle = g_lifestyle;
     new_user->hip = g_hip;
     new_user->calories = 0;
     new_user->bfp = "0";

     new_user->next = NULL;
     
     //if mylist empty
     if (this->mylist == NULL)
     {
          this->mylist = new_user;
     }
     else // add new_user at the end of the linkedlist
     {
          UserInfo *temp = this->mylist;
          while (temp->next != NULL){
               temp = temp->next;
          }
          temp->next = new_user;
     }

     if(mylist == NULL){
          cout << "no user got added :(( sad" << endl;
     }

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

void UserInfoManager::deleteUser(string username)
{
     std::cout << "************* delete user ************" << endl;
     std::cout << "deleting: " << username <<endl;

          // Check if the list is empty
     if (this->mylist == NULL) {
          std::cout << "User info list is empty (cannot delete nothing)." << endl;
          return;
     }

     // Special case: The user to delete is the first in the list
     if (this->mylist->name == username) {
          UserInfo* toDelete = this->mylist;
          this->mylist = this->mylist->next; // Point head to the next element
          delete toDelete; // Delete the old head
          std::cout << "User '" << username << "' deleted." << endl;
          return;
     }

     // General case: The user to delete is not the first in the list
     UserInfo *current = this->mylist;
     UserInfo *prev = NULL;

     while (current != NULL) {
          if (current->name == username) {
               // User found; rewire the list and delete
               prev->next = current->next; // Rewire the previous node to skip the current one
               delete current; // Delete the current node
               std::cout << "User '" << username << "' deleted." << endl;
               return;
          }
          // Move the pointers forward
          prev = current;
          current = current->next;
     }

     // If we reach this point, the user was not found
     std::cout << "Username '" << username << "' not found." << endl;
     std::cout << "*************************" << endl;
}

void UserInfoManager::writeToFile(string filename){ 
     std::cout << "************* writing file ************" << endl;
     ifstream myFile(filename);
     if(!myFile)
     {
          std::cout << "File failed to open";
          myFile.close();
     }
     
     else
     {
               ofstream file;
               file.open(filename, ios::trunc); //rewrite with trunc
               UserInfo *temp = this->mylist;
               while(temp){
                    if (temp->gender == "male"){
                         file << temp->gender << ", " << temp->age << ", " << temp->weight << ", " << temp->waist << ", " << temp->neck << ",, " << temp->height << ", " << temp->lifestyle << ", " << temp->name << ", " << temp->carbs << ", " << temp->protein << ", "<< temp->fat << ", " << temp->calories << ", " << temp->bfp << endl;
                    }
                    else 
                    {
                         file << temp->gender << ", " << temp->age << ", " << temp->weight << ", " << temp->waist << ", " << temp->neck << ", "<< temp->hip << ", " << temp->height << ", " << temp->lifestyle << ", " << temp->name << ", " << temp->carbs << ", " << temp->protein << ", "<< temp->fat << ", " << temp->calories << ", " << temp->bfp << endl;
                    }
                    temp = temp->next;
               }
               file.close();
     }
     std::cout << "*************************" << endl;
}

void UserInfoManager::display(string username)
{
     std::cout << "************* DISPLAY ************" << endl;
     UserInfo *temp  = mylist;
     //display all
     if (username == "all"){

          while(temp){
               std::cout << "*************************" << endl;
               std::cout << " " << endl;
               std::cout << " " << endl;
               std::cout << "Display" << endl;
               std::cout << endl;

               std::cout << "Name: " << temp->name << endl;
               std::cout << "Gender: " << temp->gender << endl;
               std::cout << "Age: " << temp->age << endl;
               std::cout << "Weight: " << temp->weight << endl;
               std::cout << "Waist: " << temp->waist << endl;
               std::cout << "Neck: " << temp->neck << endl;
               std::cout << "Height: " << temp->height << endl;
               if (temp->gender == "female") {
                    std::cout << "Hip: " << temp->hip << endl;
               }
               std::cout << "Lifestyle: " << temp->lifestyle << endl;
               std::cout << endl;

               std::cout << "Body Fat Percentage: " << temp->bfp << endl;
               std::cout << endl;

               std::cout << "Daily Caloric Intake: " << temp->calories << " calories" << endl;
               std::cout << endl;

               std::cout << "Macronutrient Breakdown:\n";
               std::cout << "Carbs: " << temp->carbs << "g, Protein: " << temp->protein << "g, Fat: " << temp->fat << "g" << endl;
               std::cout << endl;
               std::cout << "*************************" << endl;
                    
               temp = temp->next;
          }
     }

     else {

          while(temp){
               if(temp->name == username){
                    std::cout << "*************************" << endl;
                    std::cout << " " << endl;
                    std::cout << " " << endl;
                    std::cout << "Display" << endl;
                    std::cout << endl;

                    std::cout << "Name: " << temp->name << endl;
                    std::cout << "Gender: " << temp->gender << endl;
                    std::cout << "Age: " << temp->age << endl;
                    std::cout << "Weight: " << temp->weight << endl;
                    std::cout << "Waist: " << temp->waist << endl;
                    std::cout << "Neck: " << temp->neck << endl;
                    std::cout << "Height: " << temp->height << endl;
                    if (temp->gender == "female") {
                         std::cout << "Hip: " << temp->hip << endl;
                    }
                    std::cout << "Lifestyle: " << temp->lifestyle << endl;
                    std::cout << endl;

                    std::cout << "Body Fat Percentage: " << temp->bfp << endl;
                    std::cout << endl;

                    std::cout << "Daily Caloric Intake: " << temp->calories << " calories" << endl;
                    std::cout << endl;

                    std::cout << "Macronutrient Breakdown:\n";
                    std::cout << "Carbs: " << temp->carbs << "g, Protein: " << temp->protein << "g, Fat: " << temp->fat << "g" << endl;
                    std::cout << endl;
                    std::cout << "*************************" << endl;
                    break;
               }
               temp = temp->next;

          }
          
     }
}

class HealthAssistant 
{
     public:
          inline void getUserDetail(); // wrapper method that simply calls addUserInfo in class UserInfoManager
          inline void getBfp(string username);
          inline void getDailyCalories(string username);
          inline void getMealPrep(string username);
          inline void display(string username); //wrapper method
          inline void serialize(string filename); //wrapper method
          inline void readFromFile(string filename); //wrapper method 
          inline void deleteUser(string username); // wrapper method
     private:
          UserInfoManager manager;
 };

void HealthAssistant::getUserDetail()
{
     manager.addUserInfo();

} // wrapper method that simply calls addUserInfo in class UserInfoManager

void HealthAssistant::getBfp(string username)
{
     UserInfo* temp = manager.getUserList();   
     string result;
     bool found = false;

     while(temp){
          if (temp->name == username){
               found = true;
               break;
          }
          temp = temp->next;
     }

     //if username not found
     if(!found){
          std::cout << "username not found" << endl;
          return;
     }

     // for females
     double BF_percentage;
     string group;
     if (temp->gender == "female"){
          BF_percentage = 495 / ( 1.29579 - 0.35004 * log10( temp->waist + temp->hip - temp->neck ) + 0.22100 * log10( temp->height ) ) - 450;
          int bf_perc = BF_percentage;
          cout << "bf_percentage: " << BF_percentage << endl;
          bool wrong = false; //if bf_percentage is Nan


          if (temp->age >= 20 && temp->age <= 39){
               if (BF_percentage < 21) result = "(" + std::to_string(bf_perc) + " . low)";
               else if (BF_percentage >= 21 && BF_percentage < 33.0) result = "(" + std::to_string(bf_perc) + " . normal)";
               else if (BF_percentage >= 33 && BF_percentage < 39.0) result = "(" + std::to_string(bf_perc) + " . high)";
               else if (BF_percentage >= 39) result = "(" + std::to_string(bf_perc) + " . high)";
               else {
                    cout << "bf_percentage is Nan"<<endl;
                    bool wrong = true;
                    return;
               }
          }
          else if (temp->age >= 40 && temp->age <= 59){
               if (BF_percentage < 23) result = "(" + std::to_string(bf_perc) + " . low)";
               else if (BF_percentage >= 23 && BF_percentage < 34.0) result = "(" + std::to_string(bf_perc) + " . normal)";
               else if (BF_percentage >= 34 && BF_percentage < 40.0) result = "(" + std::to_string(bf_perc) + " . high)";
               else if (BF_percentage >= 40) result = "(" + std::to_string(bf_perc) + " . high)";
               else {
                    cout << "bf_percentage is Nan"<<endl;
                    bool wrong = true;
                    return;
               }
          }
          else if (temp->age >= 60 && temp->age <= 79){
               if (BF_percentage < 24) result = "(" + std::to_string(bf_perc) + " . low)";
               else if (BF_percentage >= 24 && BF_percentage < 36.0) result = "(" + std::to_string(bf_perc) + " . normal)";
               else if (BF_percentage >= 36 && BF_percentage < 42.0) result = "(" + std::to_string(bf_perc) + " . high)";
               else if (BF_percentage >= 42) result = "(" + std::to_string(bf_perc) + " . high)";
               else {
                    cout << "bf_percentage is Nan"<<endl;
                    bool wrong = true;
                    return;
               }
          }
          cout << "bfp result: " << result << endl;
          temp->bfp = result;
          cout << "new bpf: " << temp->bfp << " for " << username << endl;
     }

     // for males
     if (temp->gender == "male"){
          BF_percentage = 495 / ( 1.0324 - 0.19077 * log10( temp->waist - temp->neck ) + 0.15456 * log10( temp->height ) ) - 450;
          int bf_perc = BF_percentage;
          cout << "bf_percentage: " << BF_percentage << endl;
          bool wrong = false; //if bf_percentage is Nan

          if (temp->age >= 20 && temp->age <= 39){
               if (BF_percentage < 8) 
               {    
                    result = "(" + std::to_string(bf_perc) + " . low)";
               }
               else if (BF_percentage >= 8 && BF_percentage < 20.0) 
               {
                    result = "(" + std::to_string(bf_perc) + " . normal)";
               }
               else if (BF_percentage >= 20 && BF_percentage < 25.0)
               {
                    result = "(" + std::to_string(bf_perc) + " . high)";
               }
               else if (BF_percentage >= 25) 
               {
                    result = "(" + std::to_string(bf_perc) + " . high)";
               }
               else {
                    cout << "bf_percentage is Nan" << endl;
                    bool wrong = true;
                    return;
               }
          }
          else if (temp->age >= 40 && temp->age <= 59){
               if (BF_percentage < 11) 
               {
                    result = "(" + std::to_string(bf_perc) + " . low)";
               }
               else if (BF_percentage >= 11 && BF_percentage < 22.0) 
               {
                    result = "(" + std::to_string(bf_perc) + " . normal)";
               }
               else if (BF_percentage >= 22 && BF_percentage < 28.0) 
          {
               result = "(" + std::to_string(bf_perc) + " . high)";
          }
               else if (BF_percentage >= 28) 
               {
                    result = "(" + std::to_string(bf_perc) + " . high)";
               }
               else {
                    cout << "bf_percentage is Nan" << endl;
                    bool wrong = true;
                    return;
               }
          }
          else if (temp->age >= 60 && temp->age <= 79){
               if (BF_percentage < 13) 
               {
                    result = "(" + std::to_string(bf_perc) + " . low)";
               }
               else if (BF_percentage >= 13 && BF_percentage < 25.0) 
               {
                    result = "(" + std::to_string(bf_perc) + " . normal)";
               }
               else if (BF_percentage >= 25 && BF_percentage < 30.0) 
               {
                    result = "(" + std::to_string(bf_perc) + " . high)";
               }
               else if (BF_percentage >= 30) 
               {
                    result = "(" + std::to_string(bf_perc) + " . high)";
               }
               else {
                    cout << "bf_percentage is Nan" << endl;
                    bool wrong = true;
                    return;
               }
          }
          if (!wrong){
               cout << "bfp result: " << result << endl;
          temp->bfp = result;
          cout << "new bpf: " << temp->bfp << " for " << username << endl;

          }

     }
}

void HealthAssistant::getDailyCalories(string username)
{
     UserInfo* temp = manager.getUserList();  //correct this too
     double result;
     bool found = false;

     while(temp){
          if (temp->name == username){
               found = true;
               break;
          }
          temp = temp->next;
     }
     
     //if username not found
     if(!found){
          std::cout << "username not found" << endl;
          return;
     }

     // for males
     if (temp->gender == "male"){
          if (temp->age >= 19 && temp->age <= 30){
               if (temp->lifestyle == "sedentary"){
                    result = 2400;
               }
               else if (temp->lifestyle == "moderate"){
                    result = 2600;
               }
               else {
                    result = 3000;
               }
          }
          else if (temp->age >= 31 && temp->age <= 50){
               if (temp->lifestyle == "sedentary"){
                    result = 2200;
               }
               else if (temp->lifestyle == "moderate"){
                    result = 2400;
               }
               else {
                    result = 2800;
               }
          }
          else{
               if (temp->lifestyle == "sedentary"){
                    result = 2000;
               }
               else if (temp->lifestyle == "mdderate"){
                    result = 2200;
               }
               else {
                    result = 2400;
               }
          }
     }

     // for females
     if (temp->gender == "female"){
          if (temp->age >= 19 && temp->age <= 30){
               if (temp->lifestyle == "sedentary"){
                    result = 2000;
               }
               else if (temp->lifestyle == "moderate"){
                    result = 2000;
               }
               else {
                    result = 2400;
               }
          }
          else if (temp->age >= 31 && temp->age <= 50){
               if (temp->lifestyle == "sedentary"){
                    result = 1800;
               }
               else if (temp->lifestyle == "moderate"){
                    result = 2000;
               }
               else {
                    result = 2200;
               }
          }
          else{
               if (temp->lifestyle == "sedentary"){
                    result = 1600;
               }
               else if (temp->lifestyle == "mdderate"){
                    result = 1800;
               }
               else {
                    result = 2000;
               }
          }
     }
     temp->calories = result;
}

void HealthAssistant::getMealPrep(string username)
{
     UserInfo* temp = manager.getUserList();  //correct this too
     double result;
     bool found = false;

     while(temp){
          if (temp->name == username){
               found = true;
               break;
          }
          temp = temp->next;
     }
     
     //if username not found
     if(!found){
          std::cout << "username not found" << endl;
          return;
     }

     double calories = temp->calories;

     if (calories == 0){
          cout << "haven't done getcalories method" << endl;
          return;
     }

     temp->carbs = (calories * 0.5) / 4;

     temp->protein = (calories * 0.3) / 4;

     temp->fat = (calories * 0.2) / 9;
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


int main() {
     HealthAssistant ha;
     // get user details from console input for 1st user 
     ha.getUserDetail();
     // get user details from console input for 2nd user 
     ha.getUserDetail();
     // display information for john (assuming that john is the name of the first user)
     ha.display("john");
     // display information for all the users
     ha.display("all");
     // get bfp for the 1st user
     ha.getBfp("john");
     ha.getDailyCalories("john");
     ha.getMealPrep("john");
     // write all the data for all the users to file 
     ha.serialize("user_data.csv");

     // Now let's get the data from file using a new instance of HealthAssistant
     HealthAssistant ha2;
     ha2.readFromFile("user_data.csv");
     ha2.display("all");
     ha2.deleteUser("jack"); // assuming 2nd user is jack
     ha2.display("all"); // should only display for john at this point
     // now use the first object to display all
     ha.display("all"); // both john and jack should be present
 }