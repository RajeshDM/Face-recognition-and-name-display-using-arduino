#include <iostream.h>
#include <fstream.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>

struct student{
	int roll;
	char name[21];
	float mark;
};

void input_data	(student&);
void output_data	(student);
void add_rec		(fstream&);
void change_rec	(fstream&);
void delete_rec	(fstream&);
void view_rec		(fstream&);

int main()
{
	fstream f("kv.dat",ios::binary | ios::out);
	f.close();
	f.open("kv.dat",ios::binary|ios::in|ios::out);
	char choice;
	do{
		clrscr();
		cout 	<< "\n\tAdd record."
				<< "\n\tChange record."
				<< "\n\tDelete record."
				<< "\n\tView record."
				<< "\n\tQuit."
				<< "\n\n\tEnter Choice(A, C, D, V or Q)";
		cin >> choice; cin.get();
		switch(toupper(choice)){
		case 'A': add_rec	(f);	break;
		case 'C': change_rec	(f);	break;
		case 'D': delete_rec	(f);	break;
		case 'V': view_rec	(f);	break;
		case 'Q': f.close(); 		return(0);
		default : cerr << "\n***Incorrect Choice***\n";
		}
	}while(1);
}

void input_data(student& st)
{
	while(st.roll<1 || st.roll>40){
		cout << "\nRoll No. ? ";
		cin >> st.roll; cin.get();
	}

	do{
		cout << "\nName ? ";
		cin.getline(st.name,21);
	}while(strlen(st.name)==0);

	do{
		cout << "\nMark ? ";
		cin >> st.mark; cin.get();
	}while(st.mark < 0.0 || st.mark >100.0);
}


void output_data(student st)
{

	cout << "\nRoll No.: " << st.roll;
	cout << "\nName    : " << st.name;
	cout << "\nMark    : " << st.mark;
	cout << "\nPress ENTER "; cin.get();
}

void add_rec(fstream& f)
{
	student s;
	int r;
	cout << "\nEnter Roll Number To Add:\n";
	cin  >> r;  cin.get();
	s.roll = r;
	input_data(s);
	f.seekp(((r-1)* sizeof(student)),ios::beg);
	f.write((char*)&s,sizeof(student));
	cout << "\n***Record Added***\n";
}

void change_rec(fstream& f)
{
	int r;
	student s;
	long recpos;
	char reply;
	do{
		cout << "\nRoll Number To Change:\n";
		cin  >> r;  cin.get();
	}while (r < 1 || r > 40);
	f.seekg(((r-1)* sizeof(student)),ios::beg);
	recpos = f.tellg();
	f.read((char*)&s,sizeof(student));
	output_data(s);
	do{
		cout << "\nDo you wish to change this record ? (Y or N) ";
		cin >> reply; cin.get();
		reply = toupper(reply);
	}while (reply != 'Y' && reply != 'N');
	if (reply == 'Y'){
		s.roll = r;
		cout << "\nENTER NEW DATA:\n";
		input_data(s);
		f.seekp(recpos,ios::beg);
		f.write((char*)&s,sizeof(student));
		cout << "\n***Record Changed***\n";
	}
	else
		cout << "\n***Record NOT Changed***\n";
}

void delete_rec(fstream& f)
{
	student s;
	int r;
	long recpos;
	char reply;
	do{
		cout << "\nEnter the Roll No.To Delete.\n";
		cin >> r; cin.get();
	}while(!(r>=1 && r <=40));

	f.seekg(((r-1)* sizeof(student)),ios::beg);
	recpos = f.tellg();
	f.read((char*)&s,sizeof(student));
	output_data(s);
	do{
		cout << "\nDo you wish to delete this record ? (Y or N) ";
		cin >> reply; cin.get();
		reply = toupper(reply);
	}while (reply != 'Y' && reply != 'N');
	if (reply == 'Y'){
		s.roll = 0;
		s.name[0] ='\0';
		s.mark = -1;
		f.seekp(recpos,ios::beg);
		f.write((char*)&s,sizeof(student));
		cout << "\n***Record Deleted***\n";
	}
	else
		cout << "\n***Record NOT Deleted***\n";
}

void view_rec(fstream& f)
{
	student s;
	int r;
	do{
		cout << "\nEnter the Roll No.To View.\n";
		cin >> r; cin.get();
	}while(!(r>=1 && r <=40));

	f.seekg(((r-1)* sizeof(student)),ios::beg);
	f.read((char*)&s,sizeof(student));
	if (s.roll == 0 && s.name[0] == '\0' && s.mark == -1)
	{
		cerr << "\n***Not Found***\n";
		cerr << "\nPress <enter> "; cin.get();
	}
	else
		output_data(s);
}

/*
        Add record.
        Change record.
        Delete record.
        View record.
        Quit.

        Enter Choice(A, C, D, V or Q)A

Enter Roll Number To Add:
1

Name ? AAA

Mark ? 50



        Add record.
        Change record.
		Delete record.
        View record.
        Quit.

        Enter Choice(A, C, D, V or Q)V

Enter the Roll No.To View.
1

Roll No.: 1
Name    : AAA
Mark    : 50
Press ENTER




        Add record.
        Change record.
        Delete record.
		View record.
        Quit.

        Enter Choice(A, C, D, V or Q)C

Roll Number To Change:
1

Roll No.: 1
Name    : AAA
Mark    : 50
Press ENTER

Do you wish to change this record ? (Y or N) Y

ENTER NEW DATA:

Name ? BBB

Mark ? 55



        Add record.
        Change record.
        Delete record.
        View record.
        Quit.

        Enter Choice(A, C, D, V or Q)V

Enter the Roll No.To View.
1

Roll No.: 1
Name    : BBB
Mark    : 55
Press ENTER




        Add record.
        Change record.
        Delete record.
        View record.
        Quit.

        Enter Choice(A, C, D, V or Q)D

Enter the Roll No.To Delete.
1

Roll No.: 1
Name    : BBB
Mark    : 55
Press ENTER

Do you wish to delete this record ? (Y or N) Y




        Add record.
        Change record.
        Delete record.
        View record.
        Quit.

        Enter Choice(A, C, D, V or Q)V

Enter the Roll No.To View.
1

***Not Found***

Press <enter>
*/
