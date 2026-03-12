#include <stdio.h>
#include <string.h>
#include<time.h>
//#include <sys.c>

struct parameters
{
    char system_id[50];
    int cpu_usage;
    int memory_usage;
    int disk_act;
    int uptime;
    int cpu_temp;
};

void show_menu();
void time_live(char *buffer);
void write_log(struct parameters p, int risk_score, float risk_score_per);
void run_diagnosis();
//void check_logs();
//void show_risk_list();
//void about();

int main()
{
    show_menu();
    return 0;
}

void show_menu()
{
    char op;
do {
        printf("-----------------------------------------------\n");
    printf("                MAIN MENU                     \n");
    printf("Select an option from the menu below:\n");
    printf("1. Run a system diagnosis\n");
    printf("2. Check logs\n");
    printf("3. Risk list\n");
    printf("4. About\n");
    printf("5. Exit\n");
    printf("-----------------------------------------------\n");
    printf("Enter your choice[1/2/3/4/5] \n");
    scanf(" %c",&op);
    switch(op)
    {
        case '1':
            printf("Running system diagnosis...\n");
            run_diagnosis();
            break;
        case '2':
            printf("Checking logs...\n");
            //check_logs();
            break;
        case '3':
            printf("Displaying risk list...\n");
            //show_risk_list();
            break;
        case '4':
            printf("About: This is a system utility program.\n");
            //about();
            break;
        case '5':
            printf("Exiting program. Goodbye!\n");
            break;
        default:
            printf("Invalid option selected. Please try again.\n");
    }
}while (op!='5');
    
}

void time_live(char *buffer){
    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    sprintf(buffer,"%d-%02d-%02d_%02d-%02d-%02d",
            tm.tm_year + 1900,
            tm.tm_mon + 1,
            tm.tm_mday,
            tm.tm_hour,
            tm.tm_min,
            tm.tm_sec);

}

void write_log(struct parameters p, int risk_score, float risk_score_per)
{
    FILE *lf;
    char logname[100];
    char time[100];

    time_live(time);
    //create the file
    sprintf(logname,"%s_%s.log",p.system_id,time);
    lf=fopen(logname,"w");
    if(lf==NULL){
        printf("Error crating log file\n");
        return;
    }
    else
    {
            fprintf(lf,"\n===========SYSTEM DIAGNOSIS REPORT===========\n");
    fprintf(lf,"System ID: %s\n",p.system_id);
    fprintf(lf,"Time: %s\n",time);
    fprintf(lf,"\n---SYSTEM PARAMETERS---\n");
    fprintf(lf,"CPU Usage: %d%%\n",p.cpu_usage);
    fprintf(lf,"CPU Temperature: %d%%\n",p.cpu_temp);
    fprintf(lf,"Memory Usage: %d%%\n",p.memory_usage);
    fprintf(lf,"Disk Activity: %d%%\n",p.disk_act);
    fprintf(lf,"Uptime(hours): %d\n",p.uptime);
    fprintf(lf,"\n---DIAGNOSIS RESULT---\n");
    fprintf(lf,"Risk Score:%d\n",risk_score);
    fprintf(lf,"Risk Score Percentage(%%):%.2f%%\n",risk_score_per);
    if (risk_score_per<50)
    {
        fprintf(lf,"System State: Safe\n");
    }
    else if (risk_score_per<75)
    {
        fprintf(lf,"System State: Warning");
    }
    else
    {
        fprintf(lf,"System State: Critical");
    }
    fprintf(lf,"END\n");
    fprintf(lf,"============================================\n");
    fclose(lf);
    printf("Log file saved: %s\n", logname);
    }
}

void run_diagnosis()
{
     struct parameters p;
    printf("Enter the System ID:");
    scanf("%s", p.system_id);
    printf("Enter CPU Usage (%%):");
    scanf("%d", &p.cpu_usage);
    printf("Enter CPU Temperature (°C):");
    scanf("%d", &p.cpu_temp);
    printf("Enter Memory Usage (%%):");
    scanf("%d", &p.memory_usage);
    printf("Enter Disk Activity (%%):");
    scanf("%d", &p.disk_act);
    printf("Enter Uptime (hours):");
    scanf("%d", &p.uptime);

    //risk score calculation
    int risk_score = 0;
    float risk_score_per = 0;
    //cpu usage
    if(p.cpu_usage <70)
    {
        risk_score += 0;
    }    
    
    else if(p.cpu_usage<=85)
    {
        risk_score += 15;
    }
    
    else if(p.cpu_usage<=95)
    {
        risk_score += 30;
    }
    
    else
    {
        risk_score += 50;
    }
    
    //cpu temp
    if(p.cpu_temp <65)
    {
        risk_score += 0;
    }
    
    else if(p.cpu_temp<=80)
    {
        risk_score += 15;
    }

    else if(p.cpu_temp<=90)
    {
        risk_score += 30;
    }
    
    else
    {
        risk_score += 50;
    }

    //memory usage
    if (p.memory_usage<70)
    {
        risk_score += 0;
    }
    
    else if(p.memory_usage<=85)
    {   
        risk_score += 15;
    }
    
    else if(p.memory_usage<=95)
    {
        risk_score += 30;
    }
    
    else
    {   
        risk_score += 50;
    }

//Disk Activity
    if(p.disk_act<60)
    {
        risk_score += 0;
    }
    
    else if(p.disk_act<=80)
    {   
        risk_score += 15;
    }
    
    else if(p.disk_act<=95)
    {
        risk_score += 30;
    }
    
    else
    {   
        risk_score += 50;
    }
    
    //Uptime
    if(p.uptime<4)
    {
        risk_score += 0;
    }
    
    else if(p.uptime<=8)
    {   
        risk_score += 15;
    }
    
    else if(p.uptime<=16)
    {
        risk_score += 30;
    }
    
    else
    {   
        risk_score += 50;
    }

    risk_score_per = ((float)risk_score*100)/250.0;
    printf("Your Risk Score is : %d\n", risk_score);
    printf("Your Risk Score Percentage is : %.2f%%\n", risk_score_per);
    printf("Diagnosis Complete.\n");
    write_log(p, risk_score, risk_score_per);
}