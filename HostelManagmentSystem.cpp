#include<iostream>
#include<fstream>
#include<windows.h>
#include<cstring>
using namespace std ;

// Global Arrays

string username[30] ; 
string password[30] ;
string usertype[30] ;
string date[20] ;
string phonenumber[20] ;
string cnic[20] ; 
string usercomplaints[20] = {"." , "." , "." , "." , "." ,"." , "." , "." , "." , "." ,"." , "." , "." , "." , "." , "." , "." , "." , "." , "."} ;
int roomnum[20] ;
int rent[20] ;
int foodcharges[20] ;
bool roomflag[20] = {false , false , false , false , false , false , false , false , false , false , false , false , false , false , false , false , false , false , false , false} ;

// Global variables

int usernum = 0 ;
int totalroom = 20 ;
int adminnum = 0 ;
int maxinputlength = 16 ;

// Variable for colour

HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE) ;

// Prototypes

// Headers: 

void hostelnameheader() ;
string mainmenu() ;
string usermenu() ;
string adminmenu(string adminname) ;

//  Sign in / Sign up :

int signin() ;
void signup() ;

// Validations :

string setlength(string sample) ;
bool checkspace(string sample) ;
bool checkalphabets(string sample) ;
bool checklength(string sample , int length) ;

// User interefernce functions: 

void roomavailable() ;
void payableforuser(int userindex) ;
bool deleteaccount(int userindex) ;
void changefoodplan(int userindex) ;
void changeusernamepassword(int userindex) ;
void submitcomplaint(int userindex) ; 
void showuserinfo(int userindex) ; 

// Functions for admin interference:

void imposefine() ; 
void markdiscount() ;
void editdetails() ;
void removeclient() ;
void calculateincome() ;
void totalpayable() ;
void roomsdetails() ; 
void viewcomplaints() ; 
void removeclientfromarray(int userindex) ;

// Load / Store :

void store() ;
void load() ;

// Main

main(){
    load() ;
    system("color 01") ;

    startagain :

    string option ; 
    int userindex ;
    hostelnameheader() ; 
    option = mainmenu() ;

    if(option == "2"){
        signup() ;
        return main() ;
    }

    else if(option == "1"){
        signinagain :
        userindex = signin() ;
        if(userindex == 999999){
            return main() ;
        }
        else if(usertype[userindex] == "admin"){
          while(option != "10"){
            option = adminmenu(username[userindex]) ;
            if(option == "0"){
                goto signinagain ;
            }
            if(option == "1"){
                roomsdetails() ;
                system("pause") ;
                cout << endl << "(Go back)" << endl ;  
                continue ;

            }
            else if(option == "2"){
                signup() ;
                continue ;
            }
            else if(option == "3"){
                roomsdetails() ; 
                imposefine() ;
            }
            else if(option == "4"){
                markdiscount() ;
            }
            else if(option == "5"){
                editdetails() ;
            }
            else if(option == "6"){
                totalpayable() ;
            }
            else if(option == "7"){
                removeclient() ;
            }
            else if(option == "8"){
                calculateincome() ;
            }
            else if(option == "9"){
                viewcomplaints() ;
            }
            else if(option == "10"){
                store() ;
                return 0 ;
            }
            else{
                SetConsoleTextAttribute(colour , 4) ;
                cout << "Please select a valid option!" << endl ;
                system("pause") ;
                SetConsoleTextAttribute(colour , 9) ;
            }
        }
        }
        else if (usertype[userindex] == "user") {
            while (option != "9") {
                option = usermenu() ;
                if(option == "0"){
                    goto signinagain ;
                }
                else if(option == "1"){
                    roomavailable() ;
                    system("pause") ;
                    continue ;
                }
                else if(option == "2"){
                    changefoodplan(userindex) ;
                }
                else if(option == "3"){
                    cout << "Your date of joining is :    " << date[userindex] << endl << endl ;
                    system("pause") ;
                }
                else if(option == "4"){
                    payableforuser(userindex) ;
                }
                else if(option == "5"){
                    submitcomplaint(userindex) ;
                }
                else if(option == "6"){
                    changeusernamepassword(userindex) ;
                }
                else if(option == "7"){
                    showuserinfo(userindex) ;
                }
                else if(option == "8"){
                    deleteaccount(userindex) ;

                }
                else if(option == "9"){
                    store() ;
                    return 0 ;
                }
                else{
                    SetConsoleTextAttribute(colour , 4) ;
                    cout << "Please select a valid option!" << endl ;
                    system("pause") ;
                    SetConsoleTextAttribute(colour , 9) ;
                }
            }
        }
    }


    else if(option == "3"){
        store() ;
        return 0 ;
    }

    else{
        SetConsoleTextAttribute(colour , 4) ;
        cout << "Please select a valid option!" << endl ;
        system("pause") ;
        SetConsoleTextAttribute(colour , 9) ;
        goto startagain ;
    }

}

void hostelnameheader(){
    system("cls") ;
    SetConsoleTextAttribute(colour , 9) ;
    cout << endl << endl << endl ;
    cout << "                                                                                                                                          " << endl ;
    cout << "               ,------.        ,--.                        ,--.          ,--.  ,--.               ,--.         ,--.                       " << endl ;
    cout << "              |  .--. ' ,---. |  ,---. ,--,--,--. ,--,--.,-'  '-.        |  '--'  | ,---.  ,---.,-'  '-. ,---. |  |                       " << endl ;
    cout << "              |  '--'.'| .-. :|  .-.  ||        |' ,-.  |'-.  .-'        |  .--.  || .-. |(  .-''-.  .-'| .-. :|  |                       " << endl ;
    cout << "              |  |\\  \\ \\   --.|  | |  ||  |  |  |\\ '-'  |  |  |          |  |  |  |' '-' '.-'  `) |  |  \\   --.|  |                  " << endl ;
    cout << "              `--' '--' `----'`--' `--'`--`--`--' `--`--'  `--'          `--'  `--' `---' `----'  `--'   `----'`--'                       " << endl ;
    cout << "                                                                                                                                          " << endl ;
    cout << endl << endl << endl ;
}

void removeclientfromarray(int userindex){
    for (int i = userindex ; i < usernum - 1 ; i++)
    {
        username[i] = username[i + 1] ;
        password[i] = password[i + 1] ;
        usertype[i] = usertype[i + 1] ;
        cnic[i] = cnic[i + 1] ;
        phonenumber[i] = phonenumber[i + 1] ;
        date[i] = date[i + 1] ;
        foodcharges[i] = foodcharges[i + 1] ;
        rent[i] = rent[i + 1] ;
        roomflag[i] = roomflag[i + 1] ;
        roomnum[i] = roomnum[i + 1] ;
        usercomplaints[i] = usercomplaints[i + 1] ;
    }
    usernum = usernum - 1 ;
}

void store(){
    fstream file ;
    file.open("data.txt" , ios :: out) ;
    file << usernum << endl ;
    for(int i = 0 ; i < usernum ; i++){
        file << username[i] << " " ;
        file << password[i] << " " ;
        file << usertype[i] << " " ;
        if(usertype[i] == "user"){
            file << cnic[i] << " " ;
            file << roomnum[i] << " " ;
            file << rent[i] << " " ;
            file << foodcharges[i] << " " ;
            file << phonenumber[i] << " " ;
            file << date[i] << " " ;
            file << usercomplaints[i] << " " << "end" ;
            file << endl ;
        }
        else if(usertype[i] == "admin"){
            file << endl ;
        }
    }

    file.close() ;
}

void load(){
    string tempcomp ;
    fstream file ;
    file.open("data.txt" , ios :: in) ;
    file >> usernum ;
    for(int i = 0 ; i < usernum ; i++){
        file >> username[i] ;
        file >> password[i] ;
        file >> usertype[i] ;
        if(usertype[i] == "user"){
            file >> cnic[i] ;
            file >> roomnum[i] ;
            file >> rent[i] ;
            file >> foodcharges[i] ;
            file >> phonenumber[i] ;
            file >> date[i] ;
            file >> tempcomp ;
            if(tempcomp != "." && tempcomp != "end"){
                usercomplaints[i] = "\0" ;
            }
            while(tempcomp != "end"){
                if(tempcomp != "."){
                    usercomplaints[i] = usercomplaints[i] + " " + tempcomp ;
                }
                file >> tempcomp ;
            }        
        }
        else if(usertype[i] == "admin"){
            adminnum = adminnum + 1 ;
        }
    }

    for(int i = 0 ; i < usernum ; i++){
        roomflag[roomnum[i] - 1] = true ;
    }

}

bool checkspace(string sample){
    for(int i = 0 ; sample[i] != '\0' ; i++){
        if(sample[i] == ' '){
            SetConsoleTextAttribute(colour , 4) ;
            cout << "Can not include space!" << endl ;
            system("pause") ;
            SetConsoleTextAttribute(colour , 9) ;
            return true ;
        }
    }
    return false ;
}

bool checklength(string sample , int length){
    if(sample.size() < length || sample.size() > maxinputlength){
        SetConsoleTextAttribute(colour , 4) ;
        cout << "Please enter a valid input (at-least " << length << " digits long but no longer than " << maxinputlength << " digits)! " << endl ;
        system("pause") ; 
        SetConsoleTextAttribute(colour , 9) ;
        return false ;
    }
    return true ;
}

bool checkalphabets(string sample){
    for(int i = 0 ; sample[i] != '\0' ; i++){
        if(sample[i] != '0' && sample[i] != '1' && sample[i] != '2' && sample[i] != '3' && sample[i] != '4' && sample[i] != '5' && sample[i] != '6' && sample[i] != '7' && sample[i] != '8' && sample[i] != '9'){
            SetConsoleTextAttribute(colour , 4) ;
            cout << "Please enter a valid Input! (numbers only)" << endl ;
            system("pause") ;
            SetConsoleTextAttribute(colour , 9) ;
            return true ;
        }
    }
    return false ;
}

string setlength(string sample){
    for(int i = 0 ; sample.size() < 15 ; i++){
        sample = sample + " " ;
    }
    return sample ;
}

string mainmenu(){
    hostelnameheader() ;
    cout << endl << endl ;
    string option ;
    cout << "Main menu: " << endl << endl ;
    cout << "1. Sign in " << endl ;
    cout << "2. Sign up " << endl ;
    cout << "3. Exit " << endl ;
    cout << endl << "Enter option(1/2/3): " ;
    getline(cin , option) ;
    if (checkalphabets(option) == true) {
        return mainmenu();
    }
    if (checkspace(option) == true) {
        return mainmenu();
    }
    return option ;
}

int signin(){
    hostelnameheader() ;
    // Initinalizing local veriables:
    string usernameentered , passwordentered ;
    int type ; bool flag1 = false , flag2 = false ;
    // Taking input(option) :
    cout << "Sign in: " << endl << endl ;
    cout << "(enter 00 to return)" << endl ;
    cout << "Enter username: " ; 
    getline(cin , usernameentered) ;
    if(usernameentered == "00"){
        return 999999 ;
    }
    cout << "Enter password: " ; 
    getline(cin , passwordentered) ;
    // Checking validity of username and password :
    for(int i = 0 ; i < usernum ; i++){
        if(usernameentered == username[i]){
            type = i ;
            flag1 = true ; 
            break ;
        }
    }
    for(int i = 0 ; i < usernum ; i++){
        if(passwordentered == password[i]){
            flag2 = true ; 
            break ;
        }
    }

    if(flag1 != true){
        SetConsoleTextAttribute(colour , 4) ;
        cout << "Please enter valid username!" << endl ; 
        system("pause") ;
        SetConsoleTextAttribute(colour , 9) ;
        return signin() ;
    }

    else if(flag2 != true){
        SetConsoleTextAttribute(colour , 4) ;
        cout << "Please enter valid password!" << endl ;
        system("pause") ;
        SetConsoleTextAttribute(colour , 9) ;
        return signin() ;
    }
    // Returning type of user :

    else if(flag1 == true && flag2 == true){
        return type ;
    }

    return 1 ;
}

void signup(){
    hostelnameheader() ;
    // Initializing local variables :
    string temprent , tempfoodcharges ;
    string tempusername , temppassword ;
    string tempdate , tempcnic ;
    string temproomnum , tempphonenumber ;

    // Taking inputs:

    cout << "Sign up / Add user: " << endl << endl ;
    cout << "(enter 00 to return)" << endl ;

    // Username :

    cout << "Enter username: " ;

    // input and validations :
    
    getline(cin , tempusername) ;
    if(checkspace(tempusername) == true){
        return signup() ;
    }
	if (checklength(tempusername , 1) == false) {
		return signup();
	}
    // Checking if username already exists or not:

    for(int i = 0 ; i <= usernum ; i++){
        if((tempusername == username[i]) && (i != usernum)){
            cout << "Username Reserved! Please enter a different username!" << endl ;
            system("pause") ; 
            return signup() ;
        }
    }

    // Return Option:

    if(tempusername == "00"){
        tempusername = "00" ;
        return ;
    }

    // Password:

    cout << "Enter password: " ; 
    getline(cin , temppassword) ;
    if(checkspace(temppassword) == true){
        return signup() ;
    }
	if (checklength(temppassword , 1) == false) {
		return signup() ;
	}

    // Usertype:

    cout << "Enter user type(user/admin): " ; 
    getline(cin , usertype[usernum]) ;
    if(usertype[usernum] == "user"){

        // Verifying input for int varibales :
        // Rent :

        cout << "Enter rent: " ; 
        getline(cin , temprent) ;
        if(checkspace(temprent) == true){
            return signup() ;
        }
        if(checkalphabets(temprent) == true){
            return signup() ;
        }
        if(checklength(temprent , 1) == false){
            return signup() ;
        }

        // Food Charges :

        cout << "Enter food charges: " ; 
        getline(cin , tempfoodcharges) ;
        if(checkspace(tempfoodcharges) == true){
            return signup() ;
        } 
        if(checkalphabets(tempfoodcharges) == true){
            return signup() ;
        }
        if(checklength(tempfoodcharges , 1) == false){
            return signup() ;
        }

        // Room no :

        cout << "Enter room no: " ; 
        getline(cin , temproomnum) ;
        if(checkspace(temproomnum) == true){
            return signup() ;
        }
        if(checkalphabets(temproomnum) == true){
            return signup() ;
        }
        if(checklength(temproomnum , 1) == false){
            return signup() ;
        }
        if((stoi(temproomnum) > totalroom) || (stoi(temproomnum) < 0)){
            cout << "Please enter a valid room no! (1-20)" << endl ;
            system("pause") ;
            return signup() ;
        }
        if(roomflag[stoi(temproomnum)-1] == true){
            cout << "Room already occupied!" << endl ;
            system("Pause") ;
            return signup() ;
        }
        roomflag[roomnum[usernum]-1] = true ;

        // Phone number : 

        cout << "Enter Phone number (11 digits , no symbols): " ;
        getline(cin , tempphonenumber) ;
        if(checkspace(tempphonenumber) == true){
            return signup() ;
        }
        if(checkalphabets(tempphonenumber) == true){
            return signup() ;
        }
        if(checklength(tempphonenumber , 11) == false){
            return signup() ;
        }

        // CNIC :

        cout << "Enter CNIC (13 digits , no symbols): " ; 
        getline(cin , tempcnic) ;
        if(checkspace(tempcnic) == true){
            return signup() ;
        }
        if(checkalphabets(tempcnic) == true){
            return signup() ;
        }
        if(checklength(tempcnic , 13) == false){
            return signup() ;
        }

        // Date of joining :

        cout << "Enter date of your joining: " ; 
        getline(cin , tempdate) ;
        if(checkspace(tempdate) == true){
            return signup() ;
        }
        if(checklength(tempdate , 5) == false){
            return signup() ;
        }

        // Assigning values: 

        username[usernum] = tempusername ;
        password[usernum] = temppassword ;
        cnic[usernum] = tempcnic ;
        phonenumber[usernum] = tempphonenumber ;
        roomnum[usernum] = stoi (temproomnum) ;
        rent[usernum] = stoi(temprent) ;
        foodcharges[usernum] = stoi(tempfoodcharges) ;
        date[usernum] = tempdate ;
    }

    else if(usertype[usernum] == "admin"){
        username[usernum] = tempusername ;
        password[usernum] = temppassword ;
        adminnum = adminnum + 1 ;
    }

    // invalid usertype:

    else{
        SetConsoleTextAttribute(colour , 4) ;
        cout << "Please try again by entering a valid usertype!" << endl ;
        system("pause") ;
        SetConsoleTextAttribute(colour , 9) ;
        return signup() ;
    }

    // Storing new data :
    
    usernum = usernum + 1 ;
    store() ;
    SetConsoleTextAttribute(colour , 2) ;
    cout << "User Added / Signed up Successfully!" << endl ; 
    system("pause") ;
    SetConsoleTextAttribute(colour , 9) ;
}

string adminmenu(string adminname){
    hostelnameheader() ;
    string option ;
    cout << "                   Admin Panal: " << endl << endl ;
    cout << "Welcome! " << adminname << endl << endl ;
    cout << " 0. Go back.                                   " << endl ;
    cout << " 1. See rooms details.                         " << endl ;
    cout << " 2. Add new client.                            " << endl ;
    cout << " 3. Impose a fine.                             " << endl ;
    cout << " 4. Mark a discount to a client.               " << endl ;
    cout << " 5. Edit details of a client.                  " << endl ;
    cout << " 6. See total payable of a cilent.             " << endl ;
    cout << " 7. Remove a client.                           " << endl ;
    cout << " 8. Calculate income this month.               " << endl ;
    cout << " 9. See complaints.                            " << endl ;
    cout << "10. Exit.                                      " << endl ; 
    getline(cin , option) ;
    return option ;
}

string usermenu(){
    hostelnameheader() ;
    string option ;
    cout << "User Interface: " << endl << endl ;
    cout << " 0. Go back.                                   " << endl ;
    cout << " 1. See available rooms.                       " << endl ;
    cout << " 2. Select food plan.                          " << endl ;
    cout << " 3. Check date of your joining.                " << endl ;
    cout << " 4. See your total payable.                    " << endl ;
    cout << " 5. Submit a complaint.                        " << endl ;
    cout << " 6. Change username/password.                  " << endl ;
    cout << " 7. View your information.                     " << endl ;
    cout << " 8. Delete account.                            " << endl ;
    cout << " 9. Exit.                                      " << endl ; 
    getline(cin , option) ;
    return option ;
}

void roomsdetails(){
    hostelnameheader() ;
    string tempusername , temproomno , temprent , tempcnic ;
    string tempdate , tempphonenumber ;
    cout << "Rooms Detail: " << endl << endl ;
    cout << "Room no                         Client                       Rent                       CNIC                              Phone no                    Date of Joining" << endl ; 
    for(int i = 0 ; i < usernum ; i++){
        if(usertype[i] != "admin"){
            temproomno = setlength(to_string(roomnum[i])) ;
            tempusername = setlength(username[i]) ;
            temprent = setlength(to_string(rent[i])) ;
            tempcnic = setlength(cnic[i]) ;
            tempdate = setlength(date[i]) ;
            tempphonenumber = setlength(phonenumber[i]) ;

            cout << temproomno << "                 " << tempusername << "              " << temprent << "            " << tempcnic << "                  " << tempphonenumber << "                  " << tempdate << endl ;  
        }
    }
    cout << endl << endl ;
}

void imposefine(){
    hostelnameheader() ; roomsdetails() ;
    // Initializing local variable:
    string usernameentered , fine ; 
    bool flag = false ;
    // Taking input and checking validity
    cout << "Impose fine: " << endl << endl ;
    cout << "(enter 00 to return)" << endl ;
    cout << "Enter username to charge fine: " ; 
    getline(cin , usernameentered) ;
    if(usernameentered == "00"){
        return ;
    }
    cout << "Enter amount of fine: " ; 
    getline(cin , fine) ;

    if(checkalphabets(fine) == true){
        return imposefine() ;
    }
    if(checklength(fine , 1) == false){
        return imposefine() ;
    }

    if(checkspace(fine) == true){
        return imposefine() ;
    }


    for(int i = 0 ; i < usernum ; i++){
        if(username[i] == usernameentered && usertype[i] == "user"){
            rent[i] = rent[i] + stoi(fine) ; 
            flag = true ;
            SetConsoleTextAttribute(colour , 2) ;
            cout << "Rent has been raised to: " << rent[i] << endl ;
            system("pause") ;
            SetConsoleTextAttribute(colour , 9) ;
            break ; 
        }
    }
    if(flag == false){
        SetConsoleTextAttribute(colour , 4) ;
        cout << "Enter valid username!" << endl ;
        system("pause") ;
        SetConsoleTextAttribute(colour , 9) ;
        return imposefine() ;
    }
    // storing data again :
    store() ;
}

void markdiscount(){
    hostelnameheader() ; roomsdetails() ; 
    // Initializing local variables
    bool flag = false ;
    string usernameentered , discount ;
    // Taking inputs and Checking validity
    cout << "Mark Discount: " << endl << endl ;
    cout << "(enter 00 to return)" << endl ;
    cout << "Enter username to mark discount: " ; 
    getline(cin , usernameentered) ;
    if(usernameentered == "00"){
        return ;
    }
    cout << "Enter amount to avail off: " ; 
    getline(cin , discount) ;

    if(checkalphabets(discount) == true){
        return markdiscount() ;
    }
    if(checkspace(discount) == true){
        return markdiscount() ;
    }
    if(checklength(discount , 1) == false){
        return markdiscount() ;
    }
    
    for(int i = 0 ; i <= usernum ; i++){
        if(username[i] == usernameentered && usertype[i] == "user"){
            rent[i] = rent[i] - stoi(discount) ; 
            flag = true ;
            SetConsoleTextAttribute(colour , 2) ;
            cout << "Rent has been reduced to: " << rent[i] << endl ;
            system("pause") ;
            SetConsoleTextAttribute(colour , 9) ;
            break ; 
        }
    }

    if(flag == false){
        SetConsoleTextAttribute(colour , 4) ;
        cout << "Please enter valid username!" << endl ;
        system("pause") ;
        SetConsoleTextAttribute(colour , 9) ;
        return markdiscount() ;
    }
    // Storing data again
    store() ;
}

void editdetails(){
    hostelnameheader() ;
    roomsdetails() ;
    string enteredoption , enteredusername ; 
    bool flag = false ;
    
	//    Option : 
	
    cout << "Edit Details of Client: " << endl << endl ;
    cout << "(enter 0 to return)" << endl ;
    cout << "Which of entity do you want to edit: " << endl << "1. Username" << endl << "2. Password" << endl << "3. Rent" << endl << "4. CNIC" << endl << "5. Room no" << endl << "6. Date of joining" << endl << "7. Phone number" << endl ;
    getline(cin , enteredoption) ;
    if(checkspace(enteredoption) == true){
        return editdetails() ;
    }
    if(enteredoption == "0"){
        return ;
    }
    
	//    Username(registered) for change :
	
    cout << "Enter username you want to edit information about: " ; 
    getline(cin , enteredusername) ;
    if(checkspace(enteredusername) == true){
        return editdetails() ;
    }
    
	//    Changing Entity :
	
    for(int i = 0 ; i <= usernum ; i++){
        if(username[i] == enteredusername){
            flag = true ; 
            
	//            New username :
	
            if(enteredoption == "1"){
            	string tempusername ; 
                cout << "Enter new username: " ; 
                getline(cin , tempusername) ;
                if(checkspace(tempusername) == true){
                    return editdetails() ;
                }
				if (checklength(tempusername , 1) == false) {
					return editdetails();
				}
				username[i] = tempusername ;
                SetConsoleTextAttribute(colour , 2) ;
                cout << "Successfully updated!" << endl ;
                system("pause") ;
                SetConsoleTextAttribute(colour , 9) ;
            }
            
	//            New Password :
	
            else if(enteredoption == "2"){
            	string temppassword ;
                cout << "Enter new password: " ; 
                getline(cin , temppassword) ;
                if(checkspace(temppassword) == true){
                    return editdetails() ;
                }
				if (checklength(temppassword , 1) == false) {
					return editdetails() ;
				}
				password[i] = temppassword ;
                SetConsoleTextAttribute(colour , 2) ;
                cout << "Successfully updated!" << endl ; 
                system("pause") ;
                SetConsoleTextAttribute(colour , 9) ;
            }
            
	//            New Rent :

            else if(enteredoption == "3"){
                string temprent ;
                cout << "Enter new rent for selected client: " ;
                getline(cin , temprent) ;
                if(checkspace(temprent) == true){
                    return editdetails() ;
                }
                if(checkalphabets(temprent) == true){
                    return editdetails() ;
                }
				if (checklength(temprent , 1) == false) {
					return editdetails();
				}
                rent[i] = stoi(temprent) ;
                SetConsoleTextAttribute(colour , 2) ;
                cout << "Successfully updated!" << endl ;
                system("pause") ;
                SetConsoleTextAttribute(colour , 9) ;
            }
            
	//            New Cnic :

            else if(enteredoption == "4"){
                string tempcnic ;
                cout << "Enter new CNIC number of client (13 digits , no symbols): " ; 
                getline(cin , tempcnic) ;
                if(checkspace(tempcnic) == true){
                    return editdetails() ;
                }
                if(checkalphabets(tempcnic) == true){
                    return editdetails() ;
                }
				if (checklength(tempcnic , 13) == false) {
					return editdetails();
				}
                rent[i] = stoi(tempcnic) ;
                SetConsoleTextAttribute(colour , 2) ;
                cout << "Successfully updated!" << endl ;
                system("pause") ;
                SetConsoleTextAttribute(colour , 9) ;
            }
            
	//            New room no :

            else if(enteredoption == "5"){
                string temproomnum ;
                cout << "Enter updated room no of client (1-20): " ;
                getline(cin , temproomnum) ;
                if(checkspace(temproomnum) == true){
                    return editdetails() ;
                }
                if(checkalphabets(temproomnum) == true){
                    return editdetails() ;
                }
				if (checklength(temproomnum , 1) == false) {
					return editdetails();
				}
                rent[i] = stoi(temproomnum) ;
                SetConsoleTextAttribute(colour , 2) ;
                cout << "Successfully updated!" << endl ; 
                system("pause") ;
                SetConsoleTextAttribute(colour , 9) ;
            }
            
	//            New date of joining :

            else if(enteredoption == "6"){
            	string tempdate ;
                cout << "Enter new date of joining for client: " ; 
                getline(cin , tempdate) ;
                if(checkspace(tempdate) == true){
                    return editdetails() ;
                }
                if(checklength(tempdate , 5) == false){
                	return editdetails() ;
				}
                date[i] = tempdate ;
                SetConsoleTextAttribute(colour , 2) ;
                cout << "Date successfully updated!" << endl ;
                system("pause") ;
                SetConsoleTextAttribute(colour , 9) ;
            }
            
	//            New phone number :

            else if(enteredoption == "7"){
            	string tempphonenumber ;
            	cout << "Enter new phone number of client (11 digits , no symbols): " ;
            	getline(cin , tempphonenumber) ;
            	if(checkspace(tempphonenumber) == true){
            		return editdetails() ;
				}
				if(checklength(tempphonenumber , 11) == false){
					return editdetails() ;
				}
				if(checkalphabets(tempphonenumber) == true){
					return editdetails() ;
				}
				phonenumber[i] = tempphonenumber ;
                SetConsoleTextAttribute(colour , 2) ;
				cout << "Phone number of client has been successfully updated!" << endl ;
				system("pause") ;
                SetConsoleTextAttribute(colour , 9) ;
			}
			
	//			Invalid option :

            else{
                SetConsoleTextAttribute(colour , 4) ;
                cout << "Please enter valid option!" << endl ;
                system("pause") ;
                SetConsoleTextAttribute(colour , 9) ;
                return editdetails() ;
            }
            
        }
    }
    
	//    Invalid username :

    if(flag == false){
        SetConsoleTextAttribute(colour , 4) ;
        cout << "Please enter a valid username!" << endl ;
        system("pause") ;
        SetConsoleTextAttribute(colour , 9) ;
        return editdetails() ;
    }

    // Storing data again :
    
    store() ;
}

void totalpayable(){
    hostelnameheader() ; 
    roomsdetails() ;
    string month , enteredusername ;
    int payable = 0 ; bool flag = false ;
    cout << "Total Payable of a client: " << endl << endl ; 
    cout << "(enter 00 to return)" << endl ;
    cout << "Enter month: " ;  
    getline(cin, month) ;
    if(month == "00"){
        return ;
    }
    cout << "Enter username: " ; 
    getline(cin , enteredusername) ;
    if(enteredusername == "00"){
        return ;
    }
    cout << endl << endl << endl ;
    for(int i = 0 ; i <= usernum ; i++){
        if(username[i] == enteredusername){
            flag = true ;
            payable = payable + rent[i] + foodcharges[i] + 1200 /*electricity*/ + 800 /*Gas*/ + 500 /*water*/ ;
            cout << "Rent:                         " << rent[i] << endl ;
            cout << "Food charges:                 " << foodcharges[i] << endl ;
            cout << "Gas charges:                  " << 800 << endl ;
            cout << "Electricity:                  " << 1200 << endl ;
            cout << "Water:                        " << 500 << endl ;
            if(month == "october" || month == "november" || month == "december" || month == "january" || month == "febuarary"){
                payable = payable + 1200 /*Gyeser*/ ;
                cout << "Gyeser:                       " << 1200 << endl ;
            }

            cout << endl << endl << "Total Payable:                " << payable << endl ;
            system("pause") ;
        }
    }
    if(flag == false){
        SetConsoleTextAttribute(colour , 4) ;
        cout << "Enter valid username!" << endl ; 
        system("pause") ;
        SetConsoleTextAttribute(colour , 9) ;
        return totalpayable() ;
    }
    
}

void removeclient(){
    hostelnameheader() ; 
    roomsdetails() ; 
    cout << endl ;
    string enteredusername ;  
    bool flag = false ;
    cout << "Remove a Client: " << endl << endl ;
    cout << "(enter 00 to return)" << endl ;
    cout << "Enter username to remove:  " ; 
    getline(cin , enteredusername) ;
    if(enteredusername == "00"){
        return ;
    }
    for(int i = 0 ; i < usernum ; i++){
        if(username[i] == enteredusername){
            removeclientfromarray(i) ;
            SetConsoleTextAttribute(colour , 2) ;
            cout << "User has been removed!" << endl  ; 
            SetConsoleTextAttribute(colour , 9) ;
            flag = true ;
        }
    }
    if(flag == false){
        SetConsoleTextAttribute(colour , 4) ;
        cout << "Enter valid username!" << endl ; 
        system("pause") ;
        SetConsoleTextAttribute(colour , 9) ;
        return removeclient() ;
    }

    store() ;
    system("pause") ;
}

void calculateincome(){
    hostelnameheader() ;
    int income , totalrent = 0 , totalfoodcharges = 0 , totalelectricbill = 0 , totalgasbill = 0 , totalwaterbill = 0 , totalgyeserbill = 0 ; 
    string month ;
    cout << "Total Income: " << endl << endl ;
    cout << "(enter 00 to return)" << endl ;
    cout << "Enter month:  " ; 
    getline(cin , month) ;
    if(month == "00"){
        return ;
    }
    cout << endl << endl << endl ;
    for(int i = 0 ; i < usernum ; i++){
        if(usertype[i] == "admin"){
            continue ;
        }
        if(rent[i] == 0){
            continue ;
        }
        if(month == "october" || month == "november" || month == "december" || month == "january" || month == "febuarary"){
            totalgyeserbill = totalgyeserbill + 1200 ;

        }
            totalrent = totalrent + rent[i] ;
            totalfoodcharges = totalfoodcharges + foodcharges[i] ;
            totalelectricbill = totalelectricbill + 1200 ;
            totalgasbill = totalgasbill + 800 ;
            totalwaterbill = totalwaterbill + 500 ;
    }

    income = totalelectricbill + totalfoodcharges + totalgasbill + totalgyeserbill + totalrent + totalwaterbill ;

    cout << "Total Rent:                                                   " << totalrent << endl ;
    cout << "Total Food charges:                                           " << totalfoodcharges << endl ;
    cout << "Total Electricity bill(obtained from clients):                " << totalelectricbill << endl ;
    cout << "Total Gyester income:                                         " << totalgyeserbill << endl ;
    cout << "Total Water bill(from clients):                               " << totalwaterbill << endl ;
    cout << "Total Gas bill(from clients):                                 " << totalgasbill << endl ;
    SetConsoleTextAttribute(colour , 2) ; 
    cout << endl << endl <<  "   Total Income:                        " << income << endl ; 
    SetConsoleTextAttribute(colour , 9) ;
    system("pause") ;
}

void roomavailable(){
    hostelnameheader() ;
    cout << "Rooms Availability: " << endl << endl ;
    cout << "Room no                     Status   " << endl << endl << endl ;
    for(int i = 0 ; i < totalroom ; i++){
        if(roomflag[i] == false){
            if(i < 9){
                cout << "  " << i+1 << "                          Free    " << endl ; }
            else{
                cout << " " << i+1 << "                          Free    " << endl ; }
            }
        
        else if(roomflag[i] == true){
            SetConsoleTextAttribute(colour , 4) ;
            if(i < 9){
                cout << "  " << i+1 << "                     Not available   " << endl ; }
            else{
                cout << " " << i+1 << "                     Not available   " << endl ; }
            SetConsoleTextAttribute(colour , 9) ;
        }
    }
}

void changefoodplan(int userindex){
    string option ;
    hostelnameheader() ;
    cout << "Select Food Plan: " << endl << endl ;
    cout << "(enter 0 to return)." << endl ;
    cout << "Plan no               Breakfast                     Lunch                  Dinner             Price  " << endl ;
    cout << " 1.                   Anda paratha                  Daal Roti              Mix Sabzi         3000pkr." << endl ;
    cout << " 2.                   Naan Chanay                   Biryani                Haleem            3500pkr." << endl ;
    cout << " 3.                   Halwa Pori                    Saag Roti              Biryani           4200pkr." << endl ;
    cout << " 4.                   Pathory                       Korma Roti             Beef Palao        5000pkr." << endl ;
    cin.ignore();
    getline(cin , option) ;
    if(option == "0"){
        return ;
    }
    else if(option == "1"){
        foodcharges[userindex] = 3000 ;
    }
    else if(option == "2"){
        foodcharges[userindex] = 3500 ;
    }
    else if(option == "3"){
        foodcharges[userindex] = 4200 ;
    }
    else if(option == "4"){
        foodcharges[userindex] = 5000 ;
    }
    else{
        cout << "Please enter a valid option!" << endl ;
        system("pause") ;
        return changefoodplan(userindex) ;
    }

    SetConsoleTextAttribute(colour , 4) ;
    cout << "Please enter a valid option!" << endl ;
    system("pause") ;
    SetConsoleTextAttribute(colour , 9) ;

    store() ;
}

void submitcomplaint(int userindex){
    hostelnameheader() ;
    cout << "Submit Complaint: " << endl << endl ;
    cout << "Enter your complaint : " << endl ;
    getline(cin , usercomplaints[userindex]) ;
    SetConsoleTextAttribute(colour , 2) ;
    cout << "Your complaint has been submitted! Please wait for admin to respond." << endl ;
    store() ;
    system("pause") ;
    SetConsoleTextAttribute(colour , 9) ;
}

void payableforuser(int userindex){
    hostelnameheader() ;
    cout << "Your Payable: " << endl << endl ;
    int payable = 0 ; 
    string month ;
    cout << "(enter 00 to return)" << endl ;
    cout << "Enter month: " << endl ;
    getline(cin , month) ;
    if(month == "00"){
        return ;
    }
    payable = payable + rent[userindex] + foodcharges[userindex] + 1200 /*electricity*/ + 800 /*Gas*/ + 500 /*water*/ ;
    cout << "Rent:                         " << rent[userindex] << endl ;
    cout << "Food charges:                 " << foodcharges[userindex] << endl ;
    cout << "Gas charges:                  " << 800 << endl ;
    cout << "Electricity:                  " << 1200 << endl ;
    cout << "Water:                        " << 500 << endl ;
    if(month == "october" || month == "november" || month == "december" || month == "january" || month == "febuarary"){
        payable = payable + 1200 /*Gyeser*/ ;
        cout << "Gyeser:                       " << 1200 << endl ;
    }
    SetConsoleTextAttribute(colour , 4) ;
    cout << endl << endl << "Total Payable:                " << payable << endl ;
    SetConsoleTextAttribute(colour , 9) ;
    system("pause") ;
}

void changeusernamepassword(int userindex){
    hostelnameheader() ;
    string newusername , newpassword ;
    cout << "Change username/password: " << endl << endl ;
    cout << "(enter 00 to return)" << endl ;
    
	//    New username: 

    cout << "Enter new username: " ; 
    getline(cin , newusername) ;
    if(checklength(newusername , 1) == false){
    	return changeusernamepassword(userindex) ;
	}
	if(checkspace(newusername) == true){
		return changeusernamepassword(userindex) ;
	}
    if(newusername == "00"){
        return ;
    }
    
	//    New password :

    cout << "Enter new password: " ;
    getline(cin , newpassword) ;
    if(checklength(newpassword , 1) == false){
    	return changeusernamepassword(userindex) ;
	}
	if(checkspace(newpassword) == true){
		return changeusernamepassword(userindex) ;
	}
	
	//	Assigning data :

    username[userindex] = newusername ;
    password[userindex] = newpassword ;
    SetConsoleTextAttribute(colour , 2) ;
    cout << "Your username and password has been updated!" << endl ;
    store() ;
    system("pause") ;
    SetConsoleTextAttribute(colour , 9) ;
}

void showuserinfo(int userindex){
    hostelnameheader() ;
    cout << " Your Information: " << endl << endl ; 
    cout << "Username:          " << username[userindex] << endl ;
    cout << "Password:          " << password[userindex] << endl ;
    cout << "Phone number:      " << phonenumber[userindex] << endl ;
    cout << "Rent:              " << rent[userindex] << endl ;
    cout << "Food charges:      " << foodcharges[userindex] << endl ;
    cout << "CNIC:              " << cnic[userindex] << endl ;
    cout << "Room no:           " << roomnum[userindex] << endl ;
    cout << "Joining Date:      " << date[userindex] << endl ;
    system("pause") ;
}

bool deleteaccount(int userindex){
    string option;
    hostelnameheader() ;
    cout << "Are you sure that you want to delete your account?" << endl << endl ;
    cout << "   0. No " << endl ;
    cout << "   1. Yes " << endl  << endl ;
    cout << "Enter option: " ;
    getline(cin, option);
    if (option == "1") {
        removeclientfromarray(userindex) ;
        SetConsoleTextAttribute(colour, 2) ;
        cout << "Your account has been deleted!" << endl ;
        store() ;
        system("pause") ;
        SetConsoleTextAttribute(colour , 9) ;
        return main() ;
    }
    else if(option == "0"){
        return false ;
    }
    else{
        SetConsoleTextAttribute(colour , 4) ;
        cout << "Please enter a valid option!" << endl ;
        SetConsoleTextAttribute(colour , 9) ;
        system("pause") ;
        return deleteaccount(userindex) ;
    }
    return false ;
}

void viewcomplaints(){
    bool flag = false ;
    hostelnameheader() ;
    cout << "Clients Complaints: " << endl << endl ;
    for(int i = 0 ; i < usernum ; i++){
        if(usertype[i] == "user"){
            flag = true ;
            cout << "                          " << username[i] << ":  " << endl ;
            cout << usercomplaints[i] << endl << endl ;
        }
    }
    if(flag == false){
        SetConsoleTextAttribute(colour , 4) ; 
        cout << "No complaints!" << endl ;
        SetConsoleTextAttribute(colour , 9) ;
    }
    system("pause") ;
}
