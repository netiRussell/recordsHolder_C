#include <stdio.h>
#include <stdint.h>

// Utilize header file
// Utilize sorted array
// Utilize binary search
// Utilize structures

struct Student{
	uint32_t rollNumber;
	uint8_t semester;
	char dob[10];
	char branch[50];
	char fullName[100];
};

struct Student recordsHolder[10];
uint8_t maxSize;
uint8_t currentSize;


void display();
int binarySearch( uint32_t rollNumber );
void add();
void delete();

int main(){

	maxSize = sizeof(recordsHolder) / sizeof(struct Student);
	currentSize = 0;
	char mode;


	do{

		printf("1 -> Display all records\n2 -> Add a new record\n3 -> Delete a record\n0 -> Exit the application");
		printf("\nEnter your option: ");
		scanf(" %c", &mode);
		printf("\n\n");

		if( mode == '1' ){
			display();
		} else if( mode == '2' ){
			add();
		} else if( mode == '3' ){
			delete();
		} else if ( mode != '0' ){
			printf("No such option");
		}

		printf("\n\n");

	} while( mode != '0');

	return 0;
}

void display(){

	if (currentSize == 0) {
		printf("The records holder is empty => Nothing to show.");
		return;
	}

	printf("## Displaying all the records\n");

	for( uint32_t i = 0; i < currentSize; i++ ){
		printf("Student's roll number: %u\n", recordsHolder[i].rollNumber);
		printf("Student's semester: %u\n", recordsHolder[i].semester);
		printf("Student's DOB(mm/dd/yyyy): %s\n", recordsHolder[i].dob);
		printf("Student's branch: %s\n", recordsHolder[i].branch);
		printf("Student's full name: %s", recordsHolder[i].fullName);

		printf("\n******************************\n");
	}
}

int binarySearch( uint32_t rollNumber ){

	if(currentSize == 0)
		return -1;

	int8_t currentPosition, low = 0, high = currentSize-1;

	while( low <= high ){

		currentPosition = (high + low) / 2;

		if( recordsHolder[currentPosition].rollNumber == rollNumber ) {
			return currentPosition;
		} else if( recordsHolder[currentPosition].rollNumber < rollNumber ){
			low = currentPosition+1;
		} else {
			high = currentPosition-1;
		}

	}

	return -1;
}

void add(){

	if(currentSize == maxSize){
		printf("The records holder is full.");
		return;
	}

	printf("## Adding a new record\n");
	struct Student newRecord;
	int8_t duplicateIndex;

	printf("Enter student's roll number(do not insert negative #s): ");
	scanf(" %u", &newRecord.rollNumber);

	// Make sure there is no duplicate
	duplicateIndex = binarySearch(newRecord.rollNumber);
	if( duplicateIndex != -1 ){
		printf("\nCan't insert a duplicate");
		return;
	}

	// Gather the rest of the info
	printf("Enter student's semester: ");
	scanf(" %c", &newRecord.semester);
	printf("Enter student's DOB(mm/dd/yyyy): ");
	scanf(" %10[^\n]s", &newRecord.dob);
	printf("Enter student's branch: ");
	scanf(" %50[^\n]s", &newRecord.branch);
	printf("Enter student's full name: ");
	scanf(" %100[^\n]s", &newRecord.fullName);

	// Add the info to the array but keep it sorted.
	// Common case(insert in-between)
	for( uint32_t i = 0; i < currentSize; i++ ){
		if( newRecord.rollNumber < recordsHolder[i].rollNumber ){

			for( uint32_t j = currentSize; j > i; j--  ){
				recordsHolder[j] = recordsHolder[j-1];
			}
			recordsHolder[i] = newRecord;
			currentSize++;

			return;
		}
	}

	// Insert first or last case.
	recordsHolder[currentSize] = newRecord;
	currentSize++;

}

void delete(){

	if (currentSize == 0) {
		printf("The records holder is empty => Nothing to delete.");
		return;
	}

	uint32_t holder;
	printf("Roll number of the student's info to be deleted: ");
	scanf("%d", &holder);
	holder = binarySearch( holder );

	if(holder == -1){
		printf("There is no student with such roll number in the records holder");
		return;
	}

	// Delete the info from the array but keep it sorted.
	currentSize--;
	for (uint32_t i = holder; i < currentSize; i++) {
		recordsHolder[i] = recordsHolder[i + 1];
	}

}

