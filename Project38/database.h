#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED
#define SORT_BY_NUMBER    0
#define SORT_ASCENDING  0
#define SORT_DESCENDING 1
#define SORT_STUDENT 0
#define SORT_COURSE 1
#define NAME_MAX_LEN 10
struct student{
int number;
char name[NAME_MAX_LEN+1];
char choice[]='0';
};
struct course{
int number;
char name[NAME_MAX_LEN+1];
};
typedef struct{
void *p;
}ItemIterator;
ItemIterator GetFirstStudentIterator(void);
ItemIterator GetFirstCourseIterator(void);
ItemIterator GetNextStudentIterator(ItemIterator iter);
ItemIterator GetNextCourseIterator(ItemIterator iter);
int Valid(ItemIterator iter);
ItemIterator Find_student(int student_number);
ItemIterator Find_course(int course_number);
int Empty_student(void);
int Empty_course(void);
struct student* GetStudentPointer(ItemIterator iter);
struct course* GetCoursePointer(ItemIterator iter);
int Add_student(const struct student *p_Student);
int Add_course(const struct course *p_Course);
void Delete_student(ItemIterator iter);
void Delete_course(ItemIterator iter);
int SaveToFile(const char *file_name);
int LoadFromFile(const char *file_name);
void Sort(int sort_method, int sort_dir);
void Clear(void);
ItemIterator choice(int student_number,int course_number);
int GetNumCourse();
#endif // DATABASE_H_INCLUDED
