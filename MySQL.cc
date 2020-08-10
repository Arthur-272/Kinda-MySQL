#include<iostream>
#include<conio.h>
#include<windows.h>
#include<fstream>
#include<stdio.h>
#include<string.h>
const char BACKSPACE=8;
const char RETURN=13;
using namespace std;

string getpass(const char *prompt, bool show_asterisk=true)
{
    string password;
    unsigned char ch=0;
    cout <<prompt;
    while((ch=getch())!=RETURN)
    {
        if(ch==BACKSPACE)
        {
            if(password.length()!=0)
            {
                if(show_asterisk)
                    cout <<"\b \b";
                password.resize(password.length()-1);
            }
        }
        else if(ch==0 || ch==224) // handle escape sequences
        {
            getch(); // ignore non printable chars
            continue;
        }
        else
        {
            password+=ch;
            if(show_asterisk)
                cout <<'*';
        }
    }
    cout <<endl;
    return password;
}


void title()
{
    cout<<"MySQL->";
}


void secondary_title(char *filename)
{
    cout<<"MySQL\\"<<filename<<"->";
}



void in_table(char *filename,char * tablename)
{
    fstream f;
    int x;
    f.open(filename,ios::app);
    char fname[20];
    int k=0;
    for(int i=0;tablename[i]!='\0';i++)
    {
        if(tablename[i]=='#')
        {
            int j=i+1;
            for(j;tablename[j]!='(';j++)
            {
                f<<tablename[j];
                fname[k]=tablename[j];
                k++;
            }
            fname[k]='\0';
            fstream f1,f2;
            f1.open(fname,ios::in|ios::out|ios::app);
            f2.open("t123.txt",ios::out|ios::trunc);
            f1>>x;
            x++;
            f2<<x;
            f1.close();
            f2.close();
            remove(fname);
            rename("t123.txt",fname);
            f<<"-";
            f<<x<<",";
        }
    }
    for(int i=0;tablename[i]!='\0';i++)
    {
        if(tablename[i]=='(')
        {
            int j=i+1;
            for(j;tablename[j]!='\0';j++)
            {
                if(tablename[j]!=',' && tablename[j]!=')'  )
                {
                    f<<tablename[j];
                }
                else if(tablename[j]==',')
                {
                    f<<",";
                }
                else if(tablename[j]==')')
                {
                    f<<";";
                }
                else
                {
                    f<<" ";
                }
            }
        }
    }
    f.close();
}

void show_table(char *filename,char * tablename)
{
    fstream f;
    f.open(filename,ios::in);
    char ch;
    char u[100];
    int k=0;
    for(int i=0;tablename[i]!='\0';i++)
    {
        if(tablename[i]=='#')
        {
            i++;
            for(i;tablename[i]!='\0';i++)
            {
                u[k]=tablename[i];
                k++;
            }
        }
    }
    u[k]='\0';
    k=0;
    char ut[20];
    while(!f.eof())
    {
        f>>ch;
        while(ch!='-')
        {
            ut[k]=ch;
            f>>ch;
            k++;
        }
        ut[k]='\0';
        k=0;
        if(strcmp(ut,u)==0)
        {
            f>>ch;
            while(ch!=';')
            {
                if(ch==',')
                {
                    cout<<"\t";
                }
                else
                {
                    cout<<ch;
                }
                f>>ch;
            }
            cout<<endl;
        }
        else
        {
            f>>ch;
            while(ch!=';')
            {
                f>>ch;
            }
        }
    }
    f.close();
}




void createtable(char *filename,char *tablename)
{

    int k=1;
    fstream f;
    f.open(filename,ios::app|ios::out);
    for(int i=0;tablename[i]!='\0';i++)
    {
        if(tablename[i]=='(')
        {
            int j=i+1;
            for(j;tablename[j]!='\0';j++)
            {
                if(tablename[j]!=',' && tablename[j]!=')'  )
                {
                    f<<tablename[j];
                }
                else if(tablename[j]==',')
                {
                    f<<",";
                }
                else if(tablename[j]==')')
                {
                    f<<";";
                }
                else
                {
                    f<<" ";
                }
            }
        }
        else if(tablename[i]=='#')
        {
            int j=i+1;
            char fname[20];
            int k=0;
            for(j;tablename[j]!='(';j++)
            {
                f<<tablename[j];
                fname[k]=tablename[j];
                k++;
            }
            fname[k]='\0';
            fstream o;
            o.open(fname,ios::out);
            o<<"0";
            f<<"-";
            f<<"SrNo.,";
            o.close();
        }
    }
    f.close();

}


int secondary_commands(char *filename)
{
   secondary_title(filename);
   char commands[50];
    char c[50],u[50];
    gets(commands);
    int j=0,k=0;
    for(int i=0;commands[i]!='\0';i++)
    {
        if(commands[i]!='#')
        {
            c[j]=commands[i];
            j++;
        }
        else if(commands[i]=='#')
        {
            for(i;commands[i]!='\0';i++)
            {
                u[k]=commands[i];
                k++;
            }
            break;
        }
    }
    c[j]='\0';
    u[k]='\0';
    if(strcmp("create table ",c)==0)
    {
        createtable(filename,u);
        return 0;
    }
    else if(strcmp("insert into ",c)==0)
    {
        in_table(filename,u);
        return 0;
    }
    else if(strcmp("select *from ",c)==0)
    {
        show_table(filename,u);
        return 0;
    }
    else if(strcmp("exit",c)==0)
    {
        return 1;
    }
    else
    {
        cout<<"Invalid Command\n";
        return 0;
    }

}





void delete_database(char * filename)
{
    fstream f(filename,ios::in);
    if(!f)
    {
        cout<<"Database does not exist\n";
        f.close();
    }
    else
    {
        f.close();
        fstream f1;
        f1.open("delete.bat",ios::out);
        f1<<"del "<<filename;
        f1.close();
        system("delete.bat");
        cout<<"Database Deleted\n";
        remove("delete.bat");
    }
}

void create_database(char  *filename)
{
    fstream f;
    f.open(filename,ios::in);
    if(f)
    {
        cout<<"Database already exists\n";
    }
    else
    {
        fstream fout(filename,ios::out);
        cout<<"Database "<<filename<<" created\n";
        fout.close();
    }
    f.close();
}


void show_databases()
{
    fstream f;
    f.open("show.bat",ios::out);
    f<<"dir *.db/b";
    f.close();
    system("show.bat");
    remove("show.bat");
}

int get_commands()
{
    char commands[50];
    char c[50],u[50];
    gets(commands);
    int j=0,k=0;
    for(int i=0;commands[i]!='\0';i++)
    {
        if(commands[i]!='#')
        {
            c[j]=commands[i];
            j++;
        }
        else if(commands[i]=='#')
        {
            for(int z=i+1;commands[z]!='\0';z++)
            {
                u[k]=commands[z];
                k++;
            }
            break;
        }
    }
    c[j]='\0';
    u[k]='.';
    u[k+1]='d';
    u[k+2]='b';
    u[k+3]='\0';

    if(strcmp("exit",c)==0)
    {
        return 1;
    }
    else if(strcmp("create database ",c)==0)
    {
        create_database(u);
        return 0;
    }
    else if(strcmp("use ",c)==0)
    {
        fstream f;
        f.open(u,ios::in);
        if(!f)
        {
            cout<<"Database Does Not Exist\n";
            f.close();
            return 0;
        }
        f.close();
        int ch;
        do
        {
            ch=secondary_commands(u);

        }while(ch!=1);
        return 0;
    }
    else if(strcmp("remove ",c)==0)
    {
        delete_database(u);
        return 0;
    }
    else  if(strcmp("show databases",c)==0)
    {
        show_databases();
        return 0;
    }
    else if(strcmp("cls",c)==0)
    {
        system("cls");
        return 0;
    }
    else
    {
        cout<<"Invalid Command\n";
        return  0;
    }
}






int main()
{
    a:
    system("cls");
    cout<<"Welcome to MySQL\n";
    const char *correct_password="Radhey";
    string password=getpass("Enter the password:",true);
    if(correct_password!=password)
    {
        cout<<"The entered password is incorrect!!! ";
        getch();
        goto a;
    }

    int m;
    for(;;)
    {
        title();
        m=get_commands();
        if(m==1)
        {
            break;;
        }
    }
}


