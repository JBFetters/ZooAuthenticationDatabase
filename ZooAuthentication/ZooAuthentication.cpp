// ZooAuthentication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
* Main Program:     Zoo Authentication System
* Author:           J. Barrett-Fetters
* Date:             March 22, 2022
* Purpose:          This program the Zoo Authentication System. It allows authorized users to enter into the Zoo System based on their credentials. 
*                   The user is propmted to enter user id or exit. If the user enters "exit" the system will leave the program. If the user enters user id the system will verify user id from credential file.
*                   If user id is incorrect the user will have three attempts after the third attempt the system leaves the program because of invalid credentials. If the user id verified correct the system will request password.
*                   If the password is incorrect the user will have three attempts. After the third attempt the system will leave the program because of invalid credentials. If the password is correct the system determines the user role and allows access to the correct system per their role.
*                   
* Modification History:
* 2 APRIL 2022 
*    Replaced Credential File Read with reading the Credential Database
*    Created three new function, checkId, checkMD5, check role to replace Credential file read.
* 
* 16 APRIL 2022 
*    Removed checkRole function.
*    Added role to MD5 function to pull the role from the credential database.
*    Updated message when user inputted wrong user id and password.
*    Update message when user is locked out.
* 
*/


#include <iostream>
#include <string>
#include <fstream>
#include <sqlite3.h>
#include <stdio.h>

#include "UserInfo.h" //User Information Class
#include "MD5.h" // MD5 Class
using namespace std;

const char* dir = "C:\\Database\\Credentials.db"; // Database name and location
sqlite3* db{};

const char* sql;
string userId;
string password;

void outputTextFile(string filePathName); // declaring Output Text File Function
string changeString(string change); // delcaring changeString; takes uppercase or lowercase and converts to lowercase

// For the database
bool checkId(string userId); // Using Credential database verify user Id
bool checkMD5(string md5); // Using Credential database verify user password convered to MD5 Hash
string passHash;
string role;

int main()
{
    
    UserInfo myUser = UserInfo(); // Instantiation of the UserInfo Class
    int attempts = 0; // setting unber of attempts to 0
    bool numofAttemps = true; // Nunmber of attempts set to true

    //Variables for user inputs
    string userId; // lowercase of user id inputs
    string getUserId;  // gets user id inputs
    string userPassword; // User inputs User Password
    string originalPassword; // original password convered to MD5
    string credentialPassword; // User Credential Password from Credential File
    string credentialId; // Credential ID from Credential File
    string credentialRole; // Crednetial role from the credential file
    bool validCredentials{}; 
    bool userIdVaid = false;
    bool exitProgram = false;
    int index = 0; // Index
    

    //***STARTS MAIN PROGRAM***

    do
    {
        //User Welcome message
        cout << "***WELCOME to ZOO APPLICAITON*** \n";

        cout << "Enter User ID \n";
        cout << " Or exit to leave \n";

        
        getline(cin, getUserId); ////User ID 
       
        userId = changeString(getUserId); // Calls changeUserId Fuction to change user id to all lowercase
        myUser.setUserId(userId); 
         
        if (userId != "exit")// if userId does not equal exit
        {  
            while (validCredentials != true && index < 6) // searches crendential file verify user name is found
            {
                if (checkId(userId))
                {
                    validCredentials = true; //user name was found
                    userIdVaid = true;  // user Id was found
                }
                index++; // increments index
            }
            if (validCredentials == true)
            {
                validCredentials = false;
                do
                {
                    cout << "Enter Password: \n"; // Enter User Password
                        //getline of user input
                        //ws extract all whitepace character
                    getline(cin >> ws, userPassword); //getline of user password input; extract all whitespaces (ws) character
                    myUser.setUserPass(userPassword); // set userpassword in myuser UserInfo class

                    //Hash Password
                    originalPassword = md5(userPassword); // set originalPassword with the MD5 hash from the input from user
                    myUser.setHassPass(originalPassword); // set hassPass from myUser User Info class

                    index = 0;  // initialize index to zero for password
                    validCredentials = false;  // initialize validCredentials to to false for password

                    while (validCredentials != true && index < 6)   //  search credentials to see if password is found
                    {
                        if (checkMD5(originalPassword)) 
                        {
                            validCredentials = true;        // password was found
                            credentialRole = checkMD5(role);      // set role equal to the permission for the user
                        }
                        index++; // index until user inputes match credential file
                    }
                    if (validCredentials == true) // if userId is equal to credential file user ID and originalPassword is credential file hashed password
                    {
                        if (validCredentials == true) // if valid crednetials equal to true
                        {
                            // original the credential file password and number of attempts are less than or equal to 3
                            if (credentialRole == ("veterinarian")) // credential role equals vet
                            {
                                outputTextFile("Veterinarian.txt"); // Outputs Veterinarian access priviaged to

                            }
                            if (credentialRole == ("admin")) // credential role equals admin
                            {
                                outputTextFile("Admin.txt"); // Outputs Admin access priviaged to

                            }
                            if (credentialRole == ("zookeeper")) // credentila role equals zookeeper
                            {
                                outputTextFile("Zookeeper.txt"); // Outputs Zookeeper access priviaged to
                            }
                            validCredentials == true;
                            attempts = 0;
                        }
                    }
                    else // user password is incorrect
                    {
                        cout << "Password Incorrect! TRY AGAIN" << endl;
                        attempts++;
                        validCredentials == false;
                        exitProgram = true;
                    }
                } while ((!validCredentials) && attempts < 3); // while validCredentials is not true and attempts less than 3
            }
            else // user id incorrect
            {
                if (attempts < 2)
                {
                    cout << "\n";
                    cout << "User Name incorrect! Try Again!" << endl;
                    attempts++;
                }
                else
                {
                    cout << "\n";
                    cout << "User Name incorrect!" << endl;
                    exitProgram = true;
                }
            }

        }
        else // User enter exit
        {
                cout << "\n";
                cout << "You have logged out" << endl;
                exitProgram = true;
        }

    } while (exitProgram == false); // while password is correct or user id is correct keep running
}


void outputTextFile(string filePathName) //Function to opena file, read a file and close a file
{
    fstream outputTextFile; //File variable
    outputTextFile.open(filePathName); // opening the text file
    string line; // line variable

    while (getline(outputTextFile, line)) // while getline in text file
    {

        cout << line << endl; // output the line in text file
    }
    outputTextFile.close(); // close file
}

string changeString(string change) //Function Converts Users Id String to Lowercase
{
    for (int x = 0; x < change.length(); x++) // index x until x less than the length of change
    {
        if (change[x] >= 'A' && change[x] <= 'Z') // if the change[x] greater than ascii A and less than ascii Z
        {
            change[x] = change[x] + 32; // user id array [x],  add 32 (decial); 'A' = 65; 65+32 = 97; '97' = a
        }
    } return change; //returns user id all lowercase
}

bool checkId(string userId) //Verify user ID valid in credential database
{
    int exit;
    sql = "SELECT * FROM CREDENTIALS WHERE USER_ID = ?;";//quary database
    exit = sqlite3_open(dir, &db); // open database

    sqlite3_stmt* stmt; //
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); // prepare

    // set the ? parameter to the userId or password you are looking for:
    sqlite3_bind_text(stmt, 1, userId.c_str(), -1, SQLITE_TRANSIENT); // find password

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        string id = (char*)sqlite3_column_text(stmt, 0); // set id to database column
        return true;
    }
    else
    {
        return false;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

bool checkMD5(string md5) // Verify user input convered to MD5 hash is valid in the credential database
{
    int exit;

    sql = "SELECT * FROM CREDENTIALS WHERE HASH_PASSWORD = ?;"; //quary database
    exit = sqlite3_open(dir, &db); // open database

    sqlite3_stmt* stmt; //
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); // prepare

    // set the ? parameter to the userId or password you are looking for:
    exit = sqlite3_bind_text(stmt, 1, md5.c_str(), -1, SQLITE_TRANSIENT); // find password

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        passHash = (char*)sqlite3_column_text(stmt, 1); // set password to database column
        role = (char*)sqlite3_column_text(stmt, 3); // set role to database column

        return true;
    }
    else
    {
        return false;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}