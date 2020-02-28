#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <string.h>

#include <fstream>
#include <iostream>

#include <algorithm>
#include <math.h>
#include <limits>


using namespace std;

#define block 22
#define size_deptpt 242
#define size_empptr 242

/*******************
structure for department
*******************/
struct dept{
	int did;
	string dname;
	double budget;
	int managerid;
}deptpt[size_deptpt];

/*******************
structure for employee
*******************/
struct emp{
	int eid;
	string ename;
	int age;
	double salary;
}empptr[size_empptr];

/*******************
testing for swapping
*******************/
void swapidx(struct dept &a, struct dept &b){
  dept tmp;
  tmp = a;
  a = b;
  b = tmp;
};

/*******************
determination for sorting
*******************/
bool compareTwoDept(dept a, dept b){
    return (a.managerid < b.managerid);
};

bool compareTwoEmp(emp a, emp b){
    return (a.eid < b.eid);
};
 
 /*******************
sorting function
*******************/
void computeDept(dept deptpt[], int n)
{
    // Sort structure array using user defined
    // function compareTwoStructure()
    sort(deptpt, deptpt+size_deptpt, compareTwoDept);
};

void computeEmp(emp empptr[], int n)
{
    // Sort structure array using user defined
    // function compareTwoStructure()
    sort(empptr, empptr+size_empptr, compareTwoEmp);
};

/*******************
main function
*******************/
int main() {
	ifstream file_dept;
	ifstream file_emp;
	ofstream outfile;
	string buf;
	string substr;
	int idx = 0;
	int dept_idx = 0;
	int emp_idx = 0;
	stringstream ss;

	//using for pass 2
	int r = 0;
	int s = 0;
	int j = block;
	int R_count = ((sizeof(deptpt)/sizeof(*deptpt))/block) + 1;
	int R_target_pos;
	int S_count = ((sizeof(empptr)/sizeof(*empptr))/block) + 1;
	int S_target_pos;
	struct dept temp_R[R_count];
	struct emp temp_S[S_count];
	int R_min;
	int S_min;
	int tarR_pos;
	int tarS_pos;

	file_dept.open("Dept.csv", ios::in);
	file_emp.open("Emp.csv", ios::in);
	outfile.open("join.csv");

	if(!file_dept){
		cerr << "open file failed." << endl;
		return -1;
	}
	if(!file_emp){
		cerr << "open file failed." << endl;
		return -1;
	}

	// grabing data line by line form department, and storing to the structure array
	while(!file_dept.eof()){
		idx = 0;
		getline(file_dept, buf, '\n');
		buf.erase(remove(buf.begin(), buf.end(), '"'), buf.end());
		stringstream ss(buf);
		while(getline(ss, substr, ',')){
	   		if(idx % 4 == 0){
				deptpt[dept_idx].did = stoi(substr);
				// cout << dept_idx << '\t' << idx << endl;
				// cout << deptpt[dept_idx].did << '\n' << endl;
			}
			else if(idx % 4 == 1){
				deptpt[dept_idx].dname = substr;
				// cout << dept_idx << '\t' << idx << endl;
				// cout << deptpt[dept_idx].dname << '\n' << endl;
			}
			else if(idx % 4 == 2){
				deptpt[dept_idx].budget = stod(substr);
				// cout << dept_idx << '\t' << idx << endl;
				// cout << deptpt[dept_idx].budget << '\n' << endl;
			}
			else if(idx % 4 == 3){
				deptpt[dept_idx].managerid = stoi(substr);
				// cout << dept_idx << '\t' << idx << endl;
				// cout << deptpt[dept_idx].managerid << '\n' << endl;
			}
			idx ++;
   		}
   	dept_idx += 1;
	}

	// grabing data line by line form employee, and storing to the structure array
   	while(!file_emp.eof()){
	  	idx = 0;
		getline(file_emp, buf, '\n');
		buf.erase(remove(buf.begin(), buf.end(), '"'), buf.end());
		stringstream ss(buf);
		while(getline(ss, substr, ',')){
	   		if(idx % 4 == 0){
				empptr[emp_idx].eid = stoi(substr);
				// cout << emp_idx << idx << endl;
				// cout << empptr[emp_idx].eid << '\n' << endl;
			}
			else if(idx % 4 == 1){
				empptr[emp_idx].ename = substr;
				// cout << emp_idx << idx << endl;
				// cout << empptr[emp_idx].ename << '\n' << endl;
			}
			else if(idx % 4 == 2){
				empptr[emp_idx].age = stoi(substr);
				// cout << emp_idx << idx << endl;
				// cout << empptr[emp_idx].age << '\n' << endl;
			}
			else if(idx % 4 == 3){
				empptr[emp_idx].salary = stod(substr);
				// cout << emp_idx << idx << endl;
				// cout << empptr[emp_idx].salary << '\n' << endl;
			}
			idx ++;
		}
		emp_idx += 1;
	}

	//pass 0
	int i =0;
	while(i < (sizeof(deptpt)/sizeof(*deptpt))){ 
		if(i + block < (sizeof(deptpt)/sizeof(*deptpt))){
			sort(deptpt + i, deptpt + i + (block - 1), compareTwoDept);
			// for(int j = 0; j < size_deptpt; j++){
			// cout << deptpt[j].did << ' ' << deptpt[j].dname << ' ' << deptpt[j].budget << ' ' << deptpt[j].managerid << endl;
			// };
		}
		else if(i + block > (sizeof(deptpt)/sizeof(*deptpt))){
			sort(deptpt + i, deptpt + ((sizeof(deptpt)/sizeof(*deptpt))), compareTwoDept);
			// for(int j = 0; j < size_deptpt; j++){
			// cout << deptpt[j].did << ' ' << deptpt[j].dname << ' ' << deptpt[j].budget << ' ' << deptpt[j].managerid << endl;
			// };
		}
		i += block;
	};
	computeDept(deptpt, (sizeof(deptpt)/sizeof(*deptpt)));
	// for(int i=0; i < size_deptpt; i++){
	// 	cout << deptpt[i].did << ' ' << deptpt[i].dname << ' ' << deptpt[i].budget << ' ' << deptpt[i].managerid << endl;
	// };

	i =0;
	while(i < (sizeof(empptr)/sizeof(*empptr))){
		if(i + block < (sizeof(empptr)/sizeof(*empptr))){
			sort(empptr + i, empptr + i + (block - 1), compareTwoEmp);
			// for(int j=0; j < size_empptr; j++){
			// cout << empptr[j].eid << ' ' << empptr[j].ename << ' ' << empptr[j].age << ' ' << empptr[j].salary << endl;
			// };
		}
		else if(i + block > (sizeof(empptr)/sizeof(*empptr))){
			sort(empptr + i, empptr + ((sizeof(empptr)/sizeof(*empptr))), compareTwoEmp);
			// for(int j=0; j < size_empptr; j++){
			// cout << empptr[j].eid << ' ' << empptr[j].ename << ' ' << empptr[j].age << ' ' << empptr[j].salary << endl;
			// };
		}
		i += block;	
	};
	computeEmp(empptr, (sizeof(empptr)/sizeof(*empptr)));
	// for(int i=0; i < size_empptr; i++){
	// 	cout << empptr[i].eid << ' ' << empptr[i].ename << ' ' << empptr[i].age << ' ' << empptr[i].salary << endl;
	// };

	//pass 2
	while(1){
		if(i > size_empptr + size_deptpt)
			break;
		for(int i = 0; i < block / (R_count + S_count) * R_count; i += block){
			cout << i << '\n' << block / (R_count + S_count) * R_count << endl;
			j = 0;
			while(temp_R[j].managerid == 99999){
				j++;	
				temp_R[j].managerid = deptpt[i+j].managerid;
			}		
			if(temp_R[j].managerid < R_min){
				R_min = temp_R[i+j].managerid;
				tarR_pos = i+j;
			}
		}
		for(int i = 0; i < block / (R_count + S_count) * S_count; i += block){
			j = 0;
			while(temp_S[i+j].eid != 99999){
				j++;
				temp_S[j].eid = empptr[i+j].eid;
			}
			if(temp_S[j].eid < S_min){
				S_min = temp_S[i+j].eid;
				tarS_pos = i+j;
			}
		}
		i++;
	}
	i = 0;
	r = 0;
	s = 0;
	while(i < (sizeof(deptpt)/sizeof(*deptpt)) + (sizeof(empptr)/sizeof(*empptr))){
		if(deptpt[r].managerid > empptr[s].eid){
			// cout << deptpt[r].managerid << ' ' << empptr[s].eid << endl;
			s += 1;
		}
		else if(deptpt[r].managerid < empptr[s].eid){
			// cout << deptpt[r].managerid << ' ' << empptr[s].eid << endl;
			r += 1;
		}
		else if(deptpt[r].managerid == empptr[s].eid){
			if(deptpt[r].managerid > 0){
				// cout << deptpt[r].did << ',' << deptpt[r].dname << ',' << deptpt[r].budget << ',' << deptpt[r].managerid 
				// 		<< ',' << empptr[s].eid << ',' << empptr[s].ename << ',' << empptr[s].age << ',' << empptr[s].salary << endl;
				outfile << deptpt[r].did << ',' << deptpt[r].dname << ',' << deptpt[r].budget << ',' << deptpt[r].managerid 
						<< ',' << empptr[s].eid << ',' << empptr[s].ename << ',' << empptr[s].age << ',' << empptr[s].salary << endl;
			}
			r += 1;
		}
		i++;
	}	
	outfile.close();
	file_dept.close();
	file_emp.close();
	return 0;
}
