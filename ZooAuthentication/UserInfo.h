#pragma once
#include <iostream>
using namespace std;

class UserInfo
{
	//UserInfo Class Variables
private:
	string userId; //User ID
	string userPass; // User Password
	string userCred; // User credentials
	string userCredPass; // User Password
	string userRole; //User Role Vet, Admin, Keeper
	string hashPass; // Password has

	// UserInfo Class Constuctor
public:
	UserInfo(void)
	{
		UserInfo::userId = "";
		UserInfo::userPass = "";
		UserInfo::userCred = "";
		UserInfo::userCredPass = "";
		UserInfo::userRole = "";
		UserInfo::hashPass = "";


	}
	UserInfo(string userId, string userPass)
	{
		userId = UserInfo::userId;
		userPass = UserInfo::userPass;
		userCred = UserInfo::userCred;
		userCredPass = UserInfo::userCredPass;
		userRole = UserInfo::userRole;
		hashPass = UserInfo::hashPass;
	}

	//UserInfo Class Methods

	void setUserId(string userId)
	{
		userId = UserInfo::userId;
	}

	void setUserPass(string userPass)
	{
		userPass = UserInfo::userPass;
	}

	void setUserCred(string userCred)
	{
		userCred = UserInfo::userCred;
	}

	void setUserCredPass(string userCredPass)
	{
		userCredPass = UserInfo::userCredPass;
	}

	void setUserRole(string userRole)
	{
		userRole = UserInfo::userRole;
	}

	void setHassPass(string hassPass)
	{
		hassPass = UserInfo::hashPass;
	}
	
};



