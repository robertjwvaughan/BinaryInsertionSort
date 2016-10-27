/*
--A prgoram that takes in a list of students that fall under three different types of catagories. In total, their are 36 students.
The program will read in the 3 files of different users and store them in an array. The prgoram will then sort all of the 

--Robert Vaughan
--11/03/2016
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 20
#define STUDENTS 36

//Sturucture Template
struct student_rec
{
	//Stucture memebers
	char firstname[SIZE];
	char surname[SIZE];
	char type;
};
typedef struct student_rec RECORDS;

//Prototypes
void insertionSort(RECORDS [], int);  
int Search(RECORDS [], char [], int, int);
void interSearch(int, RECORDS []);
void nameSearch(int , RECORDS [], char []);

main()
{
	//File Pointers
	FILE *fp1;
	FILE *fp2;
	FILE *fp3;
	FILE *fp4;
	
	RECORDS students[STUDENTS];
	RECORDS inter_list[10];
	
	int fun = 0;
	int non_fun = 0;
	int inter = 0;
	
	int pos = 0;
	char input = 0;
	char name[SIZE];
	int check = 0;
	
	int i = 0;
	int j = 0;
	
	//Opening + Creating Necessary files
	fp1 = fopen("fun.txt", "r");
	fp2 = fopen("non-fun.txt", "r");
	fp3 = fopen("international.txt", "r");
	fp4 = fopen("class_list.txt", "w+");

	if (fp1 == NULL || fp2 == NULL || fp3 == NULL)
	{
   		printf("Error opening the file\n");
	}//end if
	else
	{
		printf("File open!\n");
	}//end else
	
	//Reading data from files
	while (fscanf(fp1, "%s %s", students[i].firstname, students[i].surname) != EOF)
	{
		students[i].type = 'f';
		i++;
		fun++;
	}//end while
	
	//Reading data from files
	while (fscanf(fp2, "%s %s", students[i].firstname, students[i].surname) != EOF)
	{
		students[i].type = 'n';
		i++;
		non_fun++;
	}//end while
	
	//Reading data from files
	while (fscanf(fp3, "%s %s", students[i].firstname, students[i].surname) != EOF)
	{
		students[i].type = 'i';
		i++;
		inter++;
	}//end while
	
	pos = i;
	
	//Call to sort the list
	insertionSort (students, pos);
	
	//Displays sorted list
	for (i = 0; i < pos; i++)
	{
		printf("%d %s %s\n", (i + 1), students[i].firstname, students[i].surname);
		
		fprintf(fp4, "%d: %s %s\n", (i + 1), students[i].firstname, students[i].surname);
	}//end for
	
	printf("\nEnter an option to do the following:\n");
	
	//Menu loop
	while (2 != 1)
	{
		printf("\nEnter 1: Search for those that are international\n");
		printf("Enter 2: Search by surname\n");
		printf("Enter any other key to exit\n");
		printf("Option: ");
		
		scanf("%c", &input);
		
		switch (input)
		{
			case '1':
			{
				//Searches international students
				interSearch(pos, students);
				break;
			}//end case
			
			case '2':
			{
				//Searches student via second name
				printf("\n\nPlease enter a name you would like to search for:\n");
				scanf("%19s", name);
				fflush(stdin);
				
				nameSearch(pos, students, name);
				break;
			}//end case
			
			default:
			{
				exit(1);
				break;
			}//end case
			
		}//end swtich
		
	}//end while
	
	//Close file pointers
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	
}//end main

/*
	Insertion Sort that includes a binary search that will search for 
*/

void insertionSort(RECORDS people[], int size)
{
	int i = 0;
	int j = 0;
	int pivet;
	//Current values
	char current_first[SIZE];
	char current_sur[SIZE];
	char current_type;
	
	for (i = 1; i < size; i++)
	{
		strcpy(current_first, people[i].firstname);
		strcpy(current_sur, people[i].surname);
		current_type = people[i].type;
		
		j = i - 1;
		
		pivet = Search(people, current_sur, 0, j);
		
		while (pivet <= j)
		{
			strcpy(people[j + 1].firstname, people[j].firstname);
			strcpy(people[j + 1].surname, people[j].surname);
			people[j + 1].type = people[j].type;
			j--;
		}//end while
		
		strcpy(people[j + 1].firstname, current_first);
		strcpy(people[j + 1].surname, current_sur);
		people[j + 1].type = current_type;
		
	}//end for
	
}//end Insertion

/*
	The following function is  recursive Binary Search that will find the position that is requried
	for a piece of data to be placed within the struct array.
*/

int Search(RECORDS group[], char surname [], int first, int last)
{
	int mid;
	
	mid = (first + last) / 2;
	
	if (last <= first)
	{
		if (strcmp(surname, group[first].surname) < 0)
		{
			return first;
		}//end if
		else if (strcmp(surname, group[first].surname) > 0)
		{
			return (first + 1);
		}
	}//end if

	if (strcmp(surname, group[mid].surname) == 0)
	{
		return (mid + 1);
	}//end if
		
	if (strcmp(surname, group[mid].surname) > 0)
	{
		return Search(group, surname, mid+1, last);
	}//end if
	else if (strcmp(surname, group[mid].surname) < 0)
	{
		return Search(group, surname, first, mid-1);
	}//end else
}//end Search

/*
	Searches for all international students via a linear earch
*/

void interSearch(int class_list, RECORDS group[])
{
	int count = 1;
	int i;
	
	printf("The international students are the following\n");
	
	for (i = 0; i < class_list; i++)
	{
		if (group[i].type == 'i')
		{
			printf("\n%d: %s %s (Position %d)\n", count, group[i].firstname, group[i].surname, (i + 1));
			count++;
		}//end if
	}//end for
}//end Search

/*
	Name search with a binary search for the list is sorted and will be O(logn)
*/ 
void nameSearch(int class_list, RECORDS group[], char user[])
{
	int first, mid, last;
	int check = 0;
	int i;
	
	first = 0;
	last = class_list - 1;
	
	mid = (first + last) / 2;

	while (first <= last)
	{	
		if (strcmp(group[mid].surname, user) == 0)
		{
			printf("\n%s %s is found and is number %d on th list", group[mid].firstname, user, mid);
			check++;
			break;
		}//end else if
		
		//left index moved
		else if (strcmp(group[mid].surname, user) < 0)
		{
			first = mid + 1;
		}//end if
		
		//Right index moved
		else if (strcmp(group[mid].surname, user) > 0)
		{
			last = mid - 1;
		}//end else
		
		mid = (first + last) / 2;
	}//end while
	
	if (check == 0)
	{
		printf("\nA person with the surname %s was not found", user);
	}//end if
}//end Search
