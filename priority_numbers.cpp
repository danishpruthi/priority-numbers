/*
 * priority_numbers.cpp
 *
 *      Author: danishpruthi
 */
#include <iostream>
#include <time.h>
#include <string>
#include <stdio.h>
#include <algorithm> // binsearch,max(a,b),min(a,b)
#include <math.h>
#include <queue>
#include <vector>
#include <set>
#include <cmath>
#include <list>
#include <map>
#include <string.h> // memset
#include <cstdlib> // abs(int),labs(int),llabs(int),min,max
#include <limits.h> // int_max,int_min,long_long_max,long_long_min

using namespace std;



#define TOTAL_STUDENTS 1200
int student[TOTAL_STUDENTS+1][3];
int prNum[TOTAL_STUDENTS+1];
bool used[TOTAL_STUDENTS+1];
bool students_forced[TOTAL_STUDENTS+1];
double force_factor = 0.66;


void generateCompletelyRandom(int sem)
{
	/*
	 * generates completely random number for a given semester
	 */
	for(int i=0;i<TOTAL_STUDENTS;i++)
	{
		int temp = (rand()%TOTAL_STUDENTS)+1;
		while(used[temp])
		{
			temp = (rand()%TOTAL_STUDENTS)+1;
		}
		used[temp] = true;
		student[i][sem-1] = temp; // student has this priority number!!
		prNum[temp] = i; // i th student has temp priority number
 	}
	return ;
}
void forceSomeStudents()
{
	// this function forces some students among the top half to be
	// by default in the bottom half next time!
	int num_students_forced = 0;
	for(int i =0;i<=TOTAL_STUDENTS;i++) students_forced[i] = false;
	while((double)num_students_forced<= force_factor*(TOTAL_STUDENTS)/2)
	{
		int temp = rand()%(TOTAL_STUDENTS/2)+1;
		while(students_forced[prNum[temp]])
		{
			temp = rand()%(TOTAL_STUDENTS/2)+1;
		}
		students_forced[prNum[temp]] = true;
		num_students_forced++;
	}
}
void generateRandom(int sem)
{
	/*
	 *  generates numbers which are not completely random,but random and
	 *  dependent on the value of priority numbers generated previously.
	 */

	if(sem==0) return;// since this system is to be used only after
	// generating  random numbers once!
	forceSomeStudents();
	for(int i=0;i<=TOTAL_STUDENTS;i++)
	{
		used[i] = false;
	}
	// first assign Priority_numbers for forced_students
	for(int i=0;i<TOTAL_STUDENTS;i++)
	{
		if(students_forced[i])
		{	
			
			int temp = rand()%(TOTAL_STUDENTS/2) + (TOTAL_STUDENTS)/2 +1;
			while(used[temp])
			{
				temp = rand()%(TOTAL_STUDENTS/2) + (TOTAL_STUDENTS)/2 +1;
			}
			used[temp] = true;
			prNum[temp] = i;
			student[i][sem-1] = temp;
		}
	}
	for(int i=0;i<TOTAL_STUDENTS;i++)
	{
		if(!students_forced[i])
		{
			int temp = rand()%TOTAL_STUDENTS+1;
			while(used[temp])
			{
				temp = rand()%TOTAL_STUDENTS;
			}
			used[temp] = true;
			prNum[temp] = i;
			student[i][sem-1] = temp;
		}
	}

}
void clearAll()
{
	for(int i=0;i<TOTAL_STUDENTS;i++)
	{
		students_forced[i] =used[i] = false;
		student[i][0]=student[i][1]=student[i][2]=prNum[i] = 0;

	}
	used[TOTAL_STUDENTS] = false;
}

int main()
{
	clearAll();
	srand(time(NULL));
	generateCompletelyRandom(1);
	generateRandom(2);
	generateRandom(3);
	for(int i=0;i<TOTAL_STUDENTS;i++)
	{
		cout<<student[i][0]<<" "<<student[i][1]<<" "<<student[i][2]<<" average:"<<(student[i][0]+student[i][1]+student[i][2])/3<<endl;
	}
	return 0;
}



