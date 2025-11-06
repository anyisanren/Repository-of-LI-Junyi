#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
char command[120];
char variables[20][20];
double value[20];
int n=0;//the mount of the variables;
int comparison[128];
double ans;


double calculate();
double store();
int isnum(double ch);
int isoperator(double ch);
double search(char *va);


int main()
{
    comparison['^']=2;
    comparison['*']=1;comparison['/']=1;
    FILE *fp=fopen("commands.txt","r");
    while (fgets(command,sizeof(command),fp)!=NULL)
    {
        int is_output=1;
        if (strchr(command,';')!=NULL)
        {
            is_output=0;
        }
        if (strchr(command,'=')==NULL)
        {
            ans=calculate();
        }else{
            ans=store();
        }
        if (is_output)
        {
            printf("%f\n",ans);
        }
    }
    fclose(fp);
    return 0;
}

double calculate()
{
    int p=0;
    double num=0;
    char *next=command;
    double stack[120];
    int top=-1;
    int i=0;
    double RVP[120];
    int cnt=-1;
    int mark[120];
    char var[20];
    int firstoperator=0;



    while (command[p]!='\0'&&command[p]!=';')
    {
        while (!isnum(command[firstoperator]))
        {
            if (command[firstoperator]=='-'||command[firstoperator]=='+')
            {
                char tmp[120];
                strncpy(tmp,command,firstoperator);
                tmp[firstoperator]='0';
                tmp[firstoperator+1]='\0';
                strcat(tmp,command+p);
                strcpy(command,tmp);
                break;
            }
            firstoperator++;
        }

        if (command[p]>='0'&&command[p]<='9')
        {
            num=strtod(command+p,&next);
            p=next-command;
            RVP[++cnt]=num;
            mark[cnt]=1;
        }
        else if (isoperator(command[p]))
        {
            RVP[++cnt]=command[p];
            mark[cnt]=0;
            p++;
        }
        else if ((command[p]>='a'&&command[p]<='z')||(command[p]>='A'&&command[p]<='Z')||command[p]=='_')
        {
            int q=p;
            while ((command[q]>='a'&&command[q]<='z')||(command[q]>='A'&&command[q]<='Z')||command[q]=='_')
            {
                q++;
            }
            strncpy(var,command+p,q-p);
            var[q-p]='\0';
            num=search(var);
            RVP[++cnt]=num;
            mark[cnt]=1;
            p=q;
        }else{
            p++;
        }
    }
    p=0;
    while (!(i==cnt+1&&top==-1))
    {
        if (i<cnt+1)
        {
            if (mark[i])
            {
                RVP[p]=RVP[i];
                mark[p++]=1;
            }else if (top==-1||(stack[top])=='(')
            {
                stack[++top]=RVP[i];
            }else if (RVP[i]=='(')
            {
                stack[++top]=RVP[i];
            }else if (RVP[i]==')')
            {
                while (stack[top]!='(')
                {
                    RVP[p]=stack[top--];
                    mark[p++]=0;
                }
                top--;
            }else if(comparison[(int)stack[top]]>=comparison[(int)RVP[i]])
            {
                while (top>=0&&comparison[(int)stack[top]]>=comparison[(int)RVP[i]])
                {
                    RVP[p]=stack[top--];
                    mark[p++]=0;
                }
                i--;
            }else
            {
                stack[++top]=RVP[i];
            }
            i++;
        }else{
            while (top>=0)
            {
                RVP[p]=stack[top--];
                mark[p++]=0;
            }
        }  
    }
    for (i=0;i<p;i++)
    {
        if (mark[i])
        {
            stack[++top]=RVP[i];
        }else{
            switch ((int)RVP[i])
            {
                case 43:        
                stack[top-1]+=stack[top];
                break;
                case 45:
                stack[top-1]-=stack[top];
                break;
                case 42:
                stack[top-1]*=stack[top];
                break;
                case 47:
                stack[top-1]/=stack[top];
                break;
                case 94:
                stack[top-1]=pow(stack[top-1],stack[top]);
                break;
            }
            top--;
        }
    }
    return stack[0];
}

double store()
{
    char *eq=strchr(command,'=');
    int pos=eq-command;
    char v1[20];
    strncpy(v1,command,pos);
    v1[pos]='\0';
    char *tmp=eq+1;
    strcpy(command,tmp);
    for(int i=0;i<n;i++)
    {
        if (strcmp(variables[i],v1)==0)
        {
            value[i]=calculate();
            return value[i];
        }
    }
    strcpy(variables[n],v1);
    value[n]=calculate();
    n++;
    return value[n-1];
}


double search(char *va)
{
    for(int i=0;i<n;i++)
    {
        if (strcmp(variables[i],va)==0)
        {
            return value[i];
        }
    }
    return 0;
}
int isnum(double ch)
{
    int ret=1;
    int a[]={'+','-','*','/','=','(',')','^'};
    for (int j=0;j<8;j++)
    {
        if (a[j]==ch)
        {
            ret=0;
            break;
        }
    }
    return ret;
}
int isoperator(double ch)
{
    int is=0;
    int a[]={'+','-','*','/','=','(',')','^'};
    for (int j=0;j<8;j++)
    {
        if (a[j]==ch)
        {
            is=1;
            break;
        }
    }
    return is;
}



