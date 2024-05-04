#pragma once // Prevents the header file from loading multiple times

// Constants for the Student Structure
#define EMAIL_SIZE 18
#define NAME_SIZE 24
#define NUMBER_SIZE 10

// Constants for the Hash Table
#define HASH_TABLE_SEGMENTS 7 // Used in the hashing algoritm
#define MOD_SIZE 5 // Used in the hashing algoritm
#define NEW_LINE 10 // Newline character code
#define TABLE_SIZE 35 // Number of available spaces

struct student
{
	char name[NAME_SIZE];
	char number[NUMBER_SIZE];
	char email[EMAIL_SIZE];
	int credits;
	double gpa;
};

int computerHash(char* studentName);
void displayHashTable(struct student* hashTable[]);
void displayRecord(struct student* temp, int index);
void initializeTable(struct student* hashTable[]);
void insertStudent(struct student* hashTable[], struct student* temp);
bool testEmailFormat(struct student temp);
bool testStudentData(struct student temp);


int computerHash(char* input)
{

int i = 0;
int hash = 0;
while(input[i]!='\0'){

hash = input[i] + hash;
i++;
}

return (int)(hash % MOD_SIZE * HASH_TABLE_SEGMENTS);

}

void displayHashTable(struct student* hashTable[])
{

int i;
int k;
	printf("\n");
	printf("Hash Table Contents\n");
	printf("____________________\n");
	printf("\n");
	printf("Index  Name                    Number     Email Address      Credits  GPA\n");
	printf("_____  ______________________  _________  _________________  _______  ___\n");
	for(i=0 ;i< TABLE_SIZE;i++){

	if(hashTable[i] !=NULL)
	displayRecord(hashTable[i],i);


	}
}

void displayRecord(struct student* temp, int index)
{

	printf("%5d  %-21s   %9s  %10s  %7d  %3.1f\n",index,temp->name,temp->number,temp->email,temp->credits,temp->gpa);


}

void initializeTable(struct student* hashTable[])
{
for(int i=0;i<TABLE_SIZE;i++){
	hashTable[i] = NULL;
}

return;

}

void insertStudent(struct student* hashTable[], struct student* temp)
{

int i=0;
int studenthashed = computerHash(temp->name);

if(hashTable[studenthashed] -> name == NULL){
hashTable[studenthashed] = malloc(sizeof(struct student));
strcpy(hashTable[studenthashed]->name, temp->name);
strcpy(hashTable[studenthashed]->number, temp->number);

strcpy(hashTable[studenthashed]->email, temp->email);
hashTable[studenthashed]->credits = temp->credits;
hashTable[studenthashed]->gpa = temp->gpa;


printf("Added Student to Hash Table: %-20s\t\tTarget  %2d, Actual %2d\n",temp->name,studenthashed,studenthashed);
}
else{
if(strcmp(hashTable[studenthashed] ->name,temp->name) ==0){
}
else{


for(i = studenthashed;i< TABLE_SIZE;i++){

if(strcmp(hashTable[studenthashed] ->name,temp->name) ==0){
break;
}
if(hashTable[i]->name == NULL){

hashTable[i] = malloc(sizeof(struct student));
strcpy(hashTable[i] ->name, temp->name);

strcpy(hashTable[i] ->number, temp->number);
strcpy(hashTable[i] ->email, temp->email);

hashTable[i]->credits = temp->credits;
hashTable[i]->gpa = temp->gpa;

printf("Added Student to Hash Table: %-20s\t\tTarget  %2d, Actual %2d\n",temp->name,studenthashed,i);
break;
}
}
}
	// Do not forget to use the malloc() function to reserve space for the student structure
	// Do not forget to use the strcpy() function to store the string data in the hash table

}
}

bool testEmailFormat(struct student temp)
{

if(temp.email[0] !='u' || temp.email[9] !='@' || temp.email[13] != '.'){
displayError(EmailF,temp.email);
return false;
}


int email = (int)(strstr(temp.email,"ufb") - temp.email);
if(email != 10) {
displayError(EmailF,temp.email);
return false;
}

int email2 = (int)(strstr(temp.email,"edu") - temp.email);

if(email2 != 14){
displayError(EmailF,temp.email);
return false;
}



return true;
}

bool testStudentData(struct student temp)
{

	if(strlen(temp.name) < 5){
		displayError(NameL,temp.name);
		return false;
	}
	if(strlen(temp.name) > 20){
		displayError(NameL,temp.name);
		return false;
	}

	if(strlen(temp.number) != 9 ){
		displayError(NumberL,temp.number);
		return false;

	}
	if(temp.number[0] != 'u'){
		displayError(NumberF,temp.number);
		return false;
	}
	if(strlen(temp.email) != 17){
		displayError(EmailL,temp.email);

		return false;
	}


	bool edu = testEmailFormat(temp);
	if(edu == 0){
		return false;
	}

	if(temp.credits < 0){

		char str[10];
		sprintf(str,"%d",temp.credits);
		displayError(CreditV,str);
	return false;
	}

	 if(temp.credits > 150 ){
		char str2[10];
		sprintf(str2,"%d",temp.credits);
	displayError(CreditV,str2);
	return false;
	}
	if(temp.gpa < 0.0){
	char str3[10];
	sprintf(str3,"%3f",temp.gpa);
	displayError(GPAv,str3);
	
	return false;
	}
	if(temp.gpa > 4.0){
	char str4[10];
	sprintf(str4,"%3f",temp.gpa);
	displayError(GPAv,str4);

	return false;
	}

	return true;
	
}
