//#include files to use standard functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Structures declaration
struct student
{
	int id;
	char name[50];
	int age;
	float gpa;
};
struct node
{
   struct student data;
   struct node *next;
};

//Global variables
struct node *head = NULL;

//Function Declaration
void addStudent(const struct student *const ptr);
void displayStudents(void);
void searchStudentByID(int id);
void updateStudent(int id);
void deleteStudent(int id);
float calculateAverageGPA(void);
void searchHighestGPA(void);

int main(void)
{
	//two lines to print before scanf
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	//Local variables for main
	int choose=0;
	//Loop on the program without exit until user need
	while(choose!=8)
	{
		printf("1. Add student\n"
			   "2. Display students\n"
			   "3. Search student by ID\n"
			   "4. Update student information\n"
			   "5. Delete student\n"
			   "6. Calculate AVG GPA\n"
			   "7. Search for student with highest GPA\n"
			   "8. Exit\n"
			   "Enter choose: ");
		scanf("%d",&choose);
		printf("---------------------------------------------\n");
		//Selection for function
		switch (choose)
		{
			case 1:
				{
					//local student structure for temp entering
					struct student Temp;
					printf("Enter student ID: ");
					scanf("%d",&Temp.id);
					printf("Enter student Name: ");
					scanf("%s",Temp.name);
					printf("Enter student Age: ");
					scanf("%d",&Temp.age);
					printf("Enter student GPA: ");
					scanf("%f",&Temp.gpa);
					addStudent(&Temp);
					printf("---------------------------------------------\n");
				}
				break;
			case 2:
				displayStudents();
				printf("---------------------------------------------\n");
				break;
			case 3:
				{
					int id;
					printf("Enter student ID to search: ");
					scanf("%d",&id);
					searchStudentByID(id);
					printf("---------------------------------------------\n");
				}
				break;
			case 4:
				{
					int id;
					printf("Enter student ID to update it's information: ");
					scanf("%d",&id);
					updateStudent(id);
					printf("---------------------------------------------\n");
				}
				break;
			case 5:
				{
					int id;
					printf("Enter student ID to delete it's information: ");
					scanf("%d",&id);
					deleteStudent(id);
					printf("---------------------------------------------\n");
				}
				break;
			case 6:
				printf("Avg. GPA = %f\n",calculateAverageGPA());
				printf("---------------------------------------------\n");
				break;
			case 7:
				searchHighestGPA();
				printf("---------------------------------------------\n");
				break;
			case 8:
				break;
			default:
				printf(" You enter wrong number please rewrite number from the list. \n");
		}
	}
	return 0;
}

//Function Definition
void addStudent(const struct student *const ptr)
{
	//Check if the id is used or not
	//Create needed variable
	struct node *current = NULL;
	if(head!=NULL)
	{
		current = head;
		while(current != NULL)
		{
			if(current->data.id == ptr->id)
			{
				printf("This ID is already reserved. \n");
				return;
			}
			current = current->next;
		}
	}
	//create a new node
	struct node *link = (struct node*) malloc(sizeof(struct node));
	//Check If memory allocation fails
	if(link==NULL)
	{
		printf("The memory is full can not add more students\n");
		return;
	}
	//store data in the node
	link->data.id = ptr->id;
	strcpy(link->data.name , ptr->name);
	link->data.age = ptr->age;
	link->data.gpa = ptr->gpa;
	link->next = NULL;
	//Check if it is first node or not
	if(head==NULL)
	{
		head = link;
		return;
	}
	current = head;
	// loop until reach the last node in the old list
	while(current->next != NULL)
	{
		current = current->next;
	}
	// Make the last node in the old list point to new node
	current->next = link;
}

void displayStudents(void)
{
	struct node *ptr = head;
	//Check If list is empty
	if(head==NULL)
	{
		printf("The list is empty.\n");
		return;
	}
	//start looping from the head until the last node
	while(ptr != NULL)
	{
		printf("[ ID: %d, Name: %s, Age: %d, GPA: %f ] \n",ptr->data.id,ptr->data.name,ptr->data.age,ptr->data.gpa);
		ptr = ptr->next;
	}
	printf(" Finish. \n");
}

void searchStudentByID(int id)
{
	struct node *ptr = head;
	//start looping from the head until the last node
	while(ptr != NULL)
	{
		if(ptr->data.id==id)
		{
			printf("[ ID: %d, Name: %s, Age: %d, GPA: %f ] \n",ptr->data.id,ptr->data.name,ptr->data.age,ptr->data.gpa);
			return;
		}
		ptr = ptr->next;
	}
	printf("Student with ID (%d) not found.\n",id);
}

void updateStudent(int id)
{
	struct node *ptr = head;
		//start looping from the head until the last node
		while(ptr != NULL)
		{
			if(ptr->data.id==id)
			{
				printf("Enter new details for the student with ID: %d\n",id);
				printf("Enter student Name: ");
				scanf("%s",ptr->data.name);
				printf("Enter student Age: ");
				scanf("%d",&ptr->data.age);
				printf("Enter student GPA: ");
				scanf("%f",&ptr->data.gpa);
				return;
			}
			ptr = ptr->next;
		}
		printf("Student with ID (%d) not found.\n",id);
}

void deleteStudent(int id)
{
	struct node *prv = NULL;
	struct node * delete_node = head;
	//start looping from the head until the last node
	while(delete_node != NULL)
	{
		if(delete_node->data.id==id)
		{
			//if the deleted is first node
			if(delete_node==head)
			{
				if(head->next==NULL)
				{
					free(delete_node);
					printf("Student with ID (%d) deleted successfully.\nThe list become empty.\n",id);
					head=NULL;
					return;
				}
				head=head->next;
				free(delete_node);
				printf("Student with ID (%d) deleted successfully.\n",id);
				return;
			}
			prv->next=delete_node->next;
			free(delete_node);
			printf("Student with ID (%d) deleted successfully.\n",id);
			return;
		}
		prv=delete_node;
		delete_node = delete_node->next;
	}
	printf("Student with ID (%d) not found.\n",id);
}

float calculateAverageGPA(void)
{
	float avg=0.0;
	int count=0;
	struct node *ptr = head;
	//Check If list is empty
	if(head==NULL)
	{
		return avg;
	}
	//start looping from the head until the last node
	while(ptr != NULL)
	{
		avg+=ptr->data.gpa;
		count++;
		ptr = ptr->next;
	}
	return avg/count;
}

void searchHighestGPA(void)
{
	//Check If list is empty
	if(head==NULL)
	{
		printf("The list is empty.\n");
		return;
	}
	//Create needed variables
	struct node *ptr = head->next;
	struct node *max = head;
	//start looping from the head until the last node
	while(ptr != NULL)
	{
		if(ptr->data.gpa>max->data.gpa)
		{
			max=ptr;
		}
		ptr = ptr->next;
	}
	printf("Student with the Highest GPA:\n");
	printf("[ ID: %d, Name: %s, Age: %d, GPA: %f ] \n",max->data.id,max->data.name,max->data.age,max->data.gpa);
}
