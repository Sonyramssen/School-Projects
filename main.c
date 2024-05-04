#include "headers.h"

#define COMMENT 35
#define INDEX_STRING ",X"
#define INPUT_BUF_SIZE 60
#define NEW_LINE 10
#define SPACE 32
#define SYMBOL_TABLE_SIZE 100

// Pass 2 constants
#define BLANK_INSTRUCTION 0x000000
#define OPCODE_MULTIPLIER 0x10000
#define OUTPUT_BUF_SIZE 70
#define RSUB_INSTRUCTION 0x4C0000
#define X_MULTIPLER 0x8000


void performPass1(struct symbol* symbolArray[], char* filename, address* addresses);
struct segment* prepareSegments(char* line);
void trim(char string[]);

// Pass 2 function prototypes
char* createFilename(char* filename, const char* extension);
void performPass2(struct symbol* symbolTable[], char* filename, address* addresses);
void resetObjectFileData(objectFileData* objectData, address* addresses);
void writeToLstFile(FILE* file, int address, segment* segments, int opcode);
void writeToObjFile(FILE* file, objectFileData data);

int main(int argc, char* argv[])
{
	address addresses = { 0x00, 0x00, 0x00 };

	if(argc < 2){
displayError(MISSING_COMMAND_LINE_ARGUMENTS,argc);
}
struct symbol *symbolTable[SYMBOL_TABLE_SIZE];
initializeSymbolTable(symbolTable);
performPass1(symbolTable,argv[1],&addresses);
performPass2(symbolTable,argv[1],&addresses);
//displaySymbolTable(symbolTable);
/*printf("\n");
printf("Assembly Summary\n");
printf("----------------\n");
printf("    Starting Address: 0x%X\n", addresses.start);
printf("      Ending Address: 0x%X\n", addresses.current);
printf("Program Size (bytes):   %d\n",addresses.current - addresses.start);*/

	
}

// To implement Pass 2 of the assembler for Project 3,
// Add the following function to your existing Project 2 code
char* createFilename(char* filename, const char* extension)
{
	char* temp = (char*)malloc(sizeof(char) * strlen(filename) + 1);
	char* temp1 = (char*)malloc(sizeof(char) * strlen(filename) + 1);
	
	strcpy(temp1, filename);
	strcpy(temp, strtok(temp1, "."));
	strcat(temp, extension);
	return temp;
}
void performPass1(struct symbol* symbolTable[], char* filename, address* addresses)
{
char buff[INPUT_BUF_SIZE];
FILE* fp;
fp = fopen(filename,"r");
if(!fp){
	displayError(FILE_NOT_FOUND,filename);
	printf("\n");
	exit(0);
}
	/*printf("\nSymbol Table Log\n");
	printf("----------------\n");*/
//Reading through the buffer
while (fgets(buff,INPUT_BUF_SIZE,fp)){
//Testing the address if greater than 8000 hex 
if(addresses->current > 0x8000){
char byte[SEGMENT_SIZE];
sprintf(byte,"%X",addresses->current);
displayError(OUT_OF_MEMORY,byte);
exit(0);
}
//Buffer < 32
if(buff[0] < 32){
	displayError(BLANK_RECORD,buff);
	exit(0);
}
//Comment
if(buff[0] == 35){
	continue;
}
segment* temp = prepareSegments(buff);

if(isDirective(temp->first)){
	displayError(ILLEGAL_SYMBOL,temp->first);
exit(0);
}
bool a = isOpcode(temp->first);
if(a == 1){
displayError(ILLEGAL_SYMBOL,temp->first);
exit(0);
}
if(isDirective(temp->second)){
if(isStartDirective(isDirective(temp->second))){
	int byte = strtol(temp->third,NULL,16);
	addresses->start = byte;
	addresses->current = byte; 
	//addresses->current= strtol(temp->third,NULL,10);
	continue;
}

else{
	addresses->increment = getMemoryAmount(isDirective(temp->second),temp->third);
}
}
else if(isOpcode(temp->second)){
addresses->increment = 0x3;
}

if(!isDirective(temp->second) && !isOpcode(temp->second)){
	displayError(ILLEGAL_OPCODE_DIRECTIVE,temp->second);
	exit(0);
}


if(strlen(temp->first)){
	insertSymbol(symbolTable,temp->first,addresses->current); 
}
addresses->current = addresses->current + addresses->increment;
memset (buff,NULL,INPUT_BUF_SIZE);
}
fclose(fp);
}

// To implement Pass 2 of the assembler for Project 3,
// Add the following function to your existing Project 2 code
void performPass2(struct symbol* symbolTable[], char* filename, address* addresses)
{
	// Do not modify this statement
	objectFileData objectData = { 0, { 0x0 }, { "\0" }, 0, 0x0, 0, { 0 }, 0, '\0', 0x0 };

	// Your code should start here

char buff[INPUT_BUF_SIZE];
FILE* fp;


fp = fopen(filename,"r");
if(!fp){
	displayError(FILE_NOT_FOUND,filename);
	printf("\n");
	exit(0);
}


FILE* fp1; 
FILE* fp2;

fp1 = fopen(createFilename(filename,".obj"),"w");
fp2 = fopen(createFilename(filename,".lst"),"w");

/*fp1 = fopen("objFile.obj","w");
fp2 = fopen("listFile.lst","w");*/
while (fgets(buff,INPUT_BUF_SIZE,fp)){

if(buff[0] == 35){
	continue;
}
segment* temp = prepareSegments(buff);

if(isStartDirective(isDirective(temp->second))){
 objectData.recordType = 'H';
 objectData.programName[NAME_SIZE] = memcpy(objectData.programName,temp->first,(strlen(temp->first)+1));
 objectData.startAddress = addresses->start;
 objectData.recordAddress = addresses ->start;
 objectData.programSize = addresses->current - addresses->start;
 addresses->current = addresses->start;
 //printf("%C %-6s %06X %06X\n", objectData.recordType, objectData.programName,objectData.startAddress,objectData.programSize);
 writeToObjFile(fp1,objectData);
 writeToLstFile(fp2,addresses->current,temp,BLANK_INSTRUCTION);
 objectData.recordType = 'T';
}
if(isEndDirective(isDirective(temp->second))){
 if(objectData.recordByteCount > 0){
 writeToObjFile(fp1,objectData);
 resetObjectFileData(&objectData,addresses);
}
 objectData.recordType = 'E';
 writeToObjFile(fp1,objectData);
 writeToLstFile(fp2,addresses->current,temp,BLANK_INSTRUCTION);
}
if(isReserveDirective(isDirective(temp->second))){
 if(objectData.recordByteCount > 0){
 writeToObjFile(fp1,objectData);
 resetObjectFileData(&objectData,addresses);
 }
 writeToLstFile(fp2,addresses->current,temp,BLANK_INSTRUCTION);
 addresses->increment = getMemoryAmount(isDirective(temp->second),temp->third);
 objectData.recordAddress+=addresses->increment;
}
if(isDataDirective(isDirective(temp->second))){
 addresses->increment = getMemoryAmount(isDirective(temp->second),temp->third);
 int computeDifference = MAX_RECORD_BYTE_COUNT - addresses->increment;
 if(objectData.recordByteCount > computeDifference){
 writeToObjFile(fp1,objectData);
 resetObjectFileData(&objectData,addresses);
}
char* newsegment = (char*)malloc(sizeof(newsegment));
strcpy(newsegment,temp->third);
int number = getByteWordValue(isDirective(temp->second),newsegment);
 objectData.recordEntries[objectData.recordEntryCount].numBytes = addresses->increment;
 objectData.recordEntries[objectData.recordEntryCount].value = number;
 objectData.recordEntryCount = objectData.recordEntryCount + 1;
 objectData.recordByteCount = objectData.recordByteCount + addresses->increment;
writeToLstFile(fp2,addresses->current,temp,number);
}

if(isOpcode(temp->second)==true){
 	int difference = MAX_RECORD_BYTE_COUNT - 3;
 	if(objectData.recordByteCount > difference){
 		writeToObjFile(fp1,objectData);
 		resetObjectFileData(&objectData,addresses);
	}
 	int value = getOpcodeValue(temp->second);
 	int value1 = value * OPCODE_MULTIPLIER;
 	int value2;
	int a =0;
 	if(strstr(temp->third,INDEX_STRING)){
		char* symbol = strtok(temp->third,",");
		value1 = value1 + X_MULTIPLER;
		value2 = getSymbolAddress(symbolTable,symbol) + value1;
		
	}

	else if(value != 0x4C){
		 a = getSymbolAddress(symbolTable,temp->third);
		if(a == -1){
			displayError(UNDEFINED_SYMBOL,temp->third);
			exit(0);
		}
		else{
			value2 = a + value1;
		}
	}
	else{
		value2 = RSUB_INSTRUCTION;
	}
objectData.recordEntries[objectData.recordEntryCount].numBytes = 3;
objectData.recordEntries[objectData.recordEntryCount].value = value2;
objectData.recordEntryCount += 1;
objectData.recordByteCount += 3;
writeToLstFile(fp2,addresses->current,temp,value2);
addresses->increment = 3;
}
addresses->current = addresses->current + addresses->increment;
memset(buff,NULL,INPUT_BUF_SIZE);
}
fclose(fp);
fclose(fp1);
fclose(fp2);
}




segment* prepareSegments(char* statement)
{
	struct segment* temp = (segment*)malloc(sizeof(segment));
	strncpy(temp->first, statement, SEGMENT_SIZE - 1);
	strncpy(temp->second, statement + SEGMENT_SIZE - 1, SEGMENT_SIZE - 1);
	strncpy(temp->third, statement + (SEGMENT_SIZE - 1) * 2, SEGMENT_SIZE - 1);

	trim(temp->first);
	trim(temp->second);
	trim(temp->third);
	return temp;
}

// To implement Pass 2 of the assembler for Project 3,
// Add the following function to your existing Project 2 code
void resetObjectFileData(objectFileData* objectData, address* addresses)
{

objectData->recordAddress = addresses->current;
objectData->recordByteCount = 0;
objectData->recordEntryCount = 0;

}

// To implement Pass 2 of the assembler for Project 3,
// Use the following function to replace the function
// In your existing Project 2 code
void trim(char value[])
{
	for (int x = 0; x < SEGMENT_SIZE; x++)
	{
		if (value[x] == SPACE || x == (SEGMENT_SIZE - 1))
		{
			value[x] = '\0';
		}
	}
}

// To implement Pass 2 of the assembler for Project 3,
// Add the following function to your existing Project 2 code
void writeToLstFile(FILE* file, int address, segment* segments, int opcode)
{
if(isDirective(segments->second)){
if(isStartDirective(isDirective(segments->second))){
	fprintf(file, "%04X    %-8s%-8s%-8s", address, segments->first, segments->second, segments->third);
}
else if(isReserveDirective(isDirective(segments->second))){
	
	fprintf(file, "\n%04X    %-8s%-8s%-8s", address, segments->first, segments->second, segments->third);
	}
	else if(isEndDirective(isDirective(segments->second))){
fprintf(file, "\n%04X    %-8s%-8s%-8s", address, segments->first, segments->second, segments->third);
}
}
if(isDirective(segments->second) == 1){
if(isDataDirective(isDirective(segments->second))){
fprintf(file, "\n%04X    %-8s%-8s%-8s    %02X", address, segments->first, segments->second, segments->third, opcode);
}
}
else if(isDirective(segments->second) == 6){
if(isDataDirective(isDirective(segments->second))){
fprintf(file, "\n%04X    %-8s%-8s%-8s    %06X", address, segments->first, segments->second, segments->third, opcode);
}
}
else if(isOpcode(segments->second)){
fprintf(file, "\n%04X    %-8s%-8s%-8s    %06X", address, segments->first, segments->second, segments->third, opcode);
}
}

// To implement Pass 2 of the assembler for Project 3,
// Add the following function to your existing Project 2 code
void writeToObjFile(FILE* file, objectFileData fileData)
{
  if (fileData.recordType == 'H'){
    fprintf(file,"%C%-6s%06X%06X", fileData.recordType, fileData.programName, fileData.startAddress,fileData.programSize);
  }
  else if (fileData.recordType == 'T'){
    fprintf(file,"\n%C%06X%02X", fileData.recordType, fileData.recordAddress, fileData.recordByteCount);
	
    for (int i=0;i<fileData.recordEntryCount;i++){ 
      if (fileData.recordEntries[i].numBytes==3){

        fprintf(file,"%06X",fileData.recordEntries[i].value);
	  }
      else{
        fprintf(file,"%02X",fileData.recordEntries[i].value);
	  }
      }
  }
  else if (fileData.recordType == 'E'){
    fprintf(file,"\n%C%06X", fileData.recordType,fileData.startAddress);
  }

}
