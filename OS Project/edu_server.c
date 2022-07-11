// EDU SERVER
// Compilation of this file
// gcc -o edu_server edu_server.c -lrt -lpthread
// To exit the programs use command EXIT 0 on the terminal 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <unistd.h>
#include <semaphore.h>

#define MIN_COURSES 10
#define MAX_COURSES 15
#define MIN_TEACHERS 5
#define MAX_TEACHERS 15

// /*-------------------------------- DATA STRUCTURE OPERATIONS START ------------------------------*/

#define COURSE_NAME_MAX_LENGTH 100 
#define TEACHER_NAME_MAX_LENGTH 100 


struct course {
  char course_name[COURSE_NAME_MAX_LENGTH];
  struct course* next;
  struct teacher* tlist;
};

struct teacher {
  char teacher_name[TEACHER_NAME_MAX_LENGTH];
  struct teacher* next;
};

void insertAtEnd(struct course** head_ref, char* new_course_name) {
    struct course* new_course = (struct course*)malloc(sizeof(struct course));
    struct course* last = *head_ref; /* used in step 5*/

    strcpy(new_course->course_name, new_course_name);
    new_course->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_course;
        return;
    }

    while (last->next != NULL) last = last->next;

    last->next = new_course;
    return;
}

// Delete a course
void deletecourse(struct course** head_ref, char* key) {
  struct course *temp = *head_ref, *prev;

  if (temp != NULL && (strcmp(temp->course_name, key) == 0)) {
  *head_ref = temp->next;
  free(temp);
  return;
  }
  // Find the key to be deleted
  while (temp != NULL && (strcmp(temp->course_name,key) != 0)) {
    prev = temp;
    temp = temp->next;
  }

  // If the key is not present
  if (temp == NULL) return;

  // Remove the course
  prev->next = temp->next;

  free(temp);
}

// Search a course
struct course* searchcourse(struct course** head_ref, char* key) {
    struct course* current = *head_ref;

    while (current != NULL) {
    if (strcmp(current->course_name,key) == 0) return current;
        current = current->next;    
    }
    return NULL;
}

void insertTeacher(struct teacher** head_ref, char* new_teacher_name) {
    struct teacher* new_teacher = (struct teacher*)malloc(sizeof(struct teacher));
    struct teacher* last = *head_ref; /* used in step 5*/

    strcpy(new_teacher->teacher_name, new_teacher_name);
    new_teacher->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_teacher;
        return;
    }

    while (last->next != NULL) last = last->next;

    last->next = new_teacher;
    return;
}


// Insert at the beginning
void insertTeacherBeginning(struct teacher** head_ref, char* new_teacher_name) {
  // Allocate memory to a course
    struct teacher* new_teacher = (struct teacher*)malloc(sizeof(struct teacher));

    // insert the course_name
    strcpy(new_teacher->teacher_name,new_teacher_name);

    new_teacher->next = (*head_ref);
    
    // Move head to new course
    (*head_ref) = new_teacher;
}

void insertTeacherAtK(struct course** head_ref, char* new_teacher_name,int k) {
    // printf("KVALUE: %d\n",k);

    int i = 0;
    struct course* current = *head_ref;
    while(current->next!=NULL && i<k)
    {
        current = current->next;
        i++;
    }
    insertTeacher(&(current->tlist),new_teacher_name); 
}


// Delete a course
void deleteTeacher(struct teacher** head_ref, char* key) {
  struct teacher *temp = *head_ref, *prev;

  if (temp != NULL && (strcmp(temp->teacher_name, key) == 0)) {
  *head_ref = temp->next;
  free(temp);
  return;
  }
  // Find the key to be deleted
  while (temp != NULL && (strcmp(temp->teacher_name,key) != 0)) {
    prev = temp;
    // printf("%s\n",prev->teacher_name);
    temp = temp->next;
  }

  // If the key is not present
  if (temp == NULL) return;

  // Remove the course
  prev->next = temp->next;

  free(temp);
}

// Search a course
struct teacher* searchTeacher(struct teacher** head_ref, char* key) {
    struct teacher* current = *head_ref;

    while (current != NULL) {
    if (strcmp(current->teacher_name,key) == 0) return current;
        current = current->next;    
    }
    return NULL;
}

struct course* check_nearest_free(struct course** head_ref){
    struct course* curr = *head_ref; 
    while(curr!=NULL && curr->tlist!=NULL) curr = curr->next;
    return curr;
}

int check_dup_teacher(struct course** head_ref, char *teacher_name){
    struct course* curr = *head_ref; 
    while(curr!=NULL) 
    {
        struct teacher* curr2 = curr->tlist; 
        while(curr2!=NULL) 
        {
            if(strcmp(curr2->teacher_name,teacher_name) == 0) return 0;
            curr2 = curr2->next;
        }
        curr = curr->next;
    }
    return 1;
}
/*-------------------------------- DATA STRUCTURE OPERATIONS END ------------------------------*/

void save_data(struct course** head_ref);
void *thread_function(void*);
char* itoa(int val);

int no_of_courses = 0;
int no_of_teachers = 0;

// Semaphore declaration
sem_t bin_sem1;

#define MSG_TYPE_LEN 16
#define MSG_VAL_LEN  16

typedef struct{
    // char msg_type[MSG_TYPE_LEN];
    char function[MSG_VAL_LEN];
    char args[MSG_VAL_LEN];
} my_msg_t;

static my_msg_t rx_msg;

#define RX_QUEUE_NAME   "/xmy_msgq_rx"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE sizeof(my_msg_t)
#define MSG_BUFFER_SIZE (MAX_MSG_SIZE * MAX_MESSAGES) 

int main (int argc, char **argv)
{
    
/*---------------------------- SERVER INITIALIZATION ----------------------------*/

    printf("-------------------Edu Server-------------------\n");
    int res_sem = sem_init(&bin_sem1, 0, 1);  
    struct course* head = NULL;
    for(int i = 1;i<=MIN_COURSES;i++)
    {
        char curr_course_name[COURSE_NAME_MAX_LENGTH] = "C";
        strcat(curr_course_name,itoa(i));
        sem_wait(&bin_sem1);
        sem_init(&bin_sem1, 0, 0);
        insertAtEnd(&head,curr_course_name);
        sem_post(&bin_sem1);
        no_of_courses++;
    }
    
    for(int i = 1;i<=MIN_TEACHERS;i++)
    {
        char curr_teacher_name[TEACHER_NAME_MAX_LENGTH]="T";
        strcat(curr_teacher_name,itoa(i));
        sem_wait(&bin_sem1);
        sem_init(&bin_sem1, 0, 0);
        struct course *curr = check_nearest_free(&head);
        if(curr!=NULL) 
        {
            insertTeacher(&(curr->tlist),curr_teacher_name);
        }
        else
        {
            int r = rand()%no_of_courses;
            insertTeacherAtK(&head,curr_teacher_name,r);
        }
        sem_post(&bin_sem1);
        no_of_teachers++;
    }
/*---------------------------- MESSAGE QUEUE INITIALIZATION ----------------------------*/

    mqd_t qd_rx;   // Rx Msg queue descriptor

    // printf ("MsgQ Rx: Welcome!!!\n");

    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    if ((qd_rx = mq_open (RX_QUEUE_NAME, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS,
                           &attr)) == -1) {
        perror ("MsgQ Rx: mq_open (rx_msgq)");
        exit (1);
    }
    
    my_msg_t in_msg;

/*---------------------------- THREAD INITIALIZATION ----------------------------*/
    int res;
	char *t_stat;
	pthread_t thread;

	if( (res = pthread_create( &thread, NULL, &thread_function, &head)) ) {
	  printf("Server: Client Thread creation failed: %d\n", res);
	  exit(1);
	}    
    
/*---------------------------- READY TO RECEIVE MESSAGES ----------------------------*/
    while (1) {
        if (mq_receive (qd_rx,(char *) &in_msg, MAX_MSG_SIZE, NULL) == -1) {
            perror ("Rx Msg Q: mq_receive");
            exit (1);
        }
        else printf("Message recieved\n");
        
        char function[30];
        char args[100];
        
        strcpy(function,in_msg.function);
        strcpy(args, in_msg.args);
        
        
        char* token = strtok(args, ",");
        char arg_val[100][100];
        int argc = 0;
        
        while (token != NULL) {    
            strcpy(arg_val[argc],token);
            argc++;
            token = strtok(NULL, ",");
        }
        printf("Command: %s\n",function);
        if(strcmp(function,"ADD_COURSE")==0)
        {
            for(int i = 0;i<argc;i++)
            {    
                sem_wait(&bin_sem1);
                sem_init(&bin_sem1, 0, 0);
                if(MAX_COURSES <= no_of_courses) 
                {
                    printf("Max Courses limit reached\n");
                    break;
                }
                else if(searchcourse(&head,arg_val[i]) == NULL) 
                {
                    insertAtEnd(&head,arg_val[i]);   
                    printf("Course %s added\n",arg_val[i]);
                    no_of_courses++;
                }
                else printf("%s not added. Duplicate Entry\n",arg_val[i]);
                sem_post(&bin_sem1);
            }
        }
        else if(strcmp(function,"ADD_TEACHER")==0)
        {
            for(int i = 0;i<argc;i++)
            {
                if(check_dup_teacher(&head,arg_val[i]) == 0)
                {
                    printf("Error: '%s' named teacher is already present in the server\n",arg_val[i]);
                }
                else if(MAX_TEACHERS <= no_of_teachers) 
                {
                    printf("Max teachers limit reached\n");
                    break;
                }
                else if(head == NULL) printf("No courses to teach\n");
                else  
                {
                    sem_wait(&bin_sem1);
                    sem_init(&bin_sem1, 0, 0);
                    struct course *curr = check_nearest_free(&head);
                    if(curr!=NULL) 
                    {
                        insertTeacher(&(curr->tlist),arg_val[i]);
                    }
                    else
                    {
                        int r = rand()%no_of_courses;
                        insertTeacherAtK(&head,arg_val[i],r);
                    }
                    sem_post(&bin_sem1);
                    printf("Teacher %s added\n",arg_val[i]);
                    no_of_teachers++;
                }
            }
        }
        else if(strcmp(function,"DEL_COURSE")==0)
        {
            for(int i = 0;i<argc;i++)
            {
                if(no_of_courses <= MIN_COURSES) 
                {   
                    printf("Error: Minimum %d number of courses must be present in the server\n",MIN_COURSES);
                    continue;
                } 
                sem_wait(&bin_sem1);
                sem_init(&bin_sem1, 0, 0);
                if(searchcourse(&head,arg_val[i]) != NULL) 
                {
                    deletecourse(&head,arg_val[i]);
                    printf("Course %s deleted\n",arg_val[i]);
                    no_of_courses--;
                }
                else printf("%s not deleted. Course not found\n",arg_val[i]);
                sem_post(&bin_sem1);
            }
        }
        else if(strcmp(function,"DEL_TEACHER")==0)
        {
            for(int i = 0;i<argc;i++)
            {
                if(no_of_teachers <= MIN_TEACHERS) 
                {   
                    printf("Error: Minimum %d number of teachers must be present in the server\n",MIN_TEACHERS);
                    continue;
                } 
                struct course* curr = head; 
                while(curr!=NULL)
                {
                    sem_wait(&bin_sem1);
                    sem_init(&bin_sem1, 0, 0);
                    if(searchTeacher(&(curr->tlist),arg_val[i]) != NULL) 
                    {
                        deleteTeacher(&(curr->tlist),arg_val[i]);
                        printf("Teacher %s deleted\n",arg_val[i]);
                        no_of_teachers--;
                    }
                    sem_post(&bin_sem1);
                    curr = curr->next;
                }
            }
        }
        else if(strcmp(function,"EXIT")==0) break;
        else printf("Error: Command not found\n");
    }
    save_data(&head);
}


void *thread_function(void* head_ref)
{
    while(1)
    {
        sleep(10);
        sem_wait(&bin_sem1);
        sem_init(&bin_sem1, 0, 0);
        printf("-----------------------SUMMARY-------------------------\n");
        printf("Number of courses: %d\n",no_of_courses);
        printf("Number of teachers: %d\n\n",no_of_teachers);
        struct course* curr = *(struct course **)head_ref;
        while(curr!=NULL)
        {
            printf("Course Name: %s\n", curr->course_name);
            struct teacher* curr2 = curr->tlist;
            int teacher_count = 0;
            while(curr2 != NULL)
            {
                printf("Teacher %d: %s \n",teacher_count+1,curr2->teacher_name);
                curr2 = curr2->next;
                teacher_count++;
            }
            if(teacher_count == 0) printf("No Teachers enrolled this course!\n");
            curr = curr->next;
            printf("------------------------------------------------\n");
        }
        sem_post(&bin_sem1);
        printf("------------------------------------------------\n");
    }
}  

void save_data(struct course** head_ref)
{
    sem_wait(&bin_sem1);
    sem_init(&bin_sem1, 0, 0);
    
    FILE *fptr;
    fptr = fopen("logdata.txt","w");
    fprintf(fptr,"------------------------------------------------\n");
    fprintf(fptr,"Number of courses: %d\n",no_of_courses);
    fprintf(fptr,"Number of teachers: %d\n\n",no_of_teachers);
    struct course* curr = *(struct course **)head_ref;
    while(curr!=NULL)
    {
        fprintf(fptr,"Course Name: %s\n", curr->course_name);
        struct teacher* curr2 = curr->tlist;
        int teacher_count = 0;
        while(curr2 != NULL)
        {
            fprintf(fptr,"Teacher %d: %s \n",teacher_count+1,curr2->teacher_name);
            curr2 = curr2->next;
            teacher_count++;
        }
        if(teacher_count == 0) fprintf(fptr,"No Teachers enrolled this course!\n");
        curr = curr->next;
        fprintf(fptr,"------------------------------------------------\n");
    }
    sem_post(&bin_sem1);
    fprintf(fptr,"------------------------------------------------\n");
    fclose(fptr);
    printf("Data saved to log_data.txt\n");
}

char* itoa(int val){
	static char buf[32] = {0};
	int i = 30;
	for(; val && i ; --i, val /= 10) buf[i] = "0123456789abcdef"[val % 10];
	return &buf[i+1];
}
