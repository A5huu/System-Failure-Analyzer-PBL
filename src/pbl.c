#include <stdio.h>
#include <string.h>
#include<time.h>
#include<dirent.h>
#include<stdlib.h>
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
void back_menu();
void time_live(char *buffer);
void write_log(struct parameters p, int risk_score, float risk_score_per);
void run_diagnosis();
void check_logs();
void about_help();
void analyze_system_logs(char system_id[50]);
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
            check_logs();
            break;
        case '3':
            printf("Displaying risk list...\nFeature Not Ready Yet :<\n");
            //show_risk_list();
            break;
        case '4':
            printf("About: This is a system utility program.\n");
            about_help();
            break;
        case '5':
            printf("Exiting program. Goodbye!\n");
            break;
        default:
            printf("Invalid option selected. Please try again.\n");
    }
}while (op!='5');
    
}

void back_menu()
{
    char op2;
    while(1)
    {
        printf("\nEnter 'M for Main Menu or 'E' to Exit\n");
        printf("Enter M/E: ");
        scanf(" %c",&op2);

        if(op2=='m' || op2=='M')
        {
            return;
        }
        else if (op2=='e' || op2=='E')
        {
            printf("Exiting Program, Goodbye.");
            exit(0);
        }
        else
        {
            printf("Invalid input!\n");
        }
    }
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

void write_log(struct parameters p, int risk_score, float risk_score_per){
    FILE *lf;
    char logname[100];
    char time[100];
    char filepath[150];
    int issue_found=0;

    time_live(time);
    mkdir("../logs");
    //create the file
    sprintf(logname,"%s_%s.log",p.system_id,time);
    sprintf(filepath,"../logs/%s", logname);
    lf=fopen(filepath,"w");
    if(lf==NULL){
        printf("Error crating log file\n");
        return;
    }
    else
    {
    fprintf(lf,"\n=====================================\n");
    fprintf(lf,"       System Diagnosis Report\n");
    fprintf(lf,"\n=====================================\n");
    fprintf(lf,"System ID: %s\n",p.system_id);
    fprintf(lf,"-------------------------------------\n");
    fprintf(lf,"CPU Usage       : %d%%\n",p.cpu_usage);
    fprintf(lf,"CPU Temperature : %d\n",p.cpu_temp);
    fprintf(lf,"Memory Usage    : %d%%\n",p.memory_usage);
    fprintf(lf,"Disk Activity   : %d%%\n",p.disk_act);
    fprintf(lf,"Uptime          : %d\n",p.uptime);
    fprintf(lf,"-------------------------------------\n");
    fprintf(lf,"Risk Score      : %d/250\n", risk_score);
    fprintf(lf,"Risk Percentage : %.2f%%\n", risk_score_per);
    if(risk_score_per<41)
    {
        fprintf(lf,"System Status   : Safe\n");
    }
    else if(risk_score_per<71)
    {
        fprintf(lf,"System Status   : Warning\n");
    }
    else
    {
        fprintf(lf,"System Status   : Critical\n");
    }

    fprintf(lf,"--- Issues Detected ---\n");
    if(p.cpu_usage>85)
    {
        fprintf(lf,"* High CPU usage detected\n");
        issue_found=1;
    }
    if(p.cpu_temp>85)
    {
        fprintf(lf,"* CPU Overheating detected\n");
        issue_found=1;
    }
    if(p.memory_usage>85)
    {
        fprintf(lf,"* High Memory Usage detected\n");
        issue_found=1;
    }
    if(p.disk_act>85)
    {
        fprintf(lf,"* High Disk Activity detected\n");
        issue_found=1;
    }
    if(p.uptime>85)
    {
        fprintf(lf,"* System Running for longer durations\n");
        issue_found=1;
    }
    if(issue_found==0)
    {
        fprintf(lf,"No Major Issue Detected\n");
    }

    fprintf(lf,"--- Possible Fixes ---\n");
    if(p.cpu_usage>85)
    {
        fprintf(lf,"* Close unnecessary background applications\n");
        
    }
    if(p.cpu_temp>85)
    {
        fprintf(lf,"* Check cooling system or fan performance\n");
    }
    if(p.memory_usage>85)
    {
        fprintf(lf,"* Restart system of free up memory\n");
    }
    if(p.disk_act>85)
    {
        fprintf(lf,"* Reduce disk intensive operations\n");
    }
    if(p.uptime>12)
    {
        fprintf(lf,"* Consider restarting the system\n");
    }
    if(issue_found==0)
    {
        fprintf(lf,"No action required system is operating optimally\n");
    }
    fprintf(lf,"\n=====================================\n");
    fprintf(lf,"       END\n");
    fprintf(lf,"=====================================\n");
    fclose(lf);
    printf("Log file saved: logs/%s\n", logname);
    }
}

void run_diagnosis()
{
    struct parameters p;
    int issue_found=0;
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
    
    printf("\n=====================================\n");
    printf("       System Diagnosis Report\n");
    printf("\n=====================================\n");
    printf("System ID: %s\n",p.system_id);
    printf("-------------------------------------\n");
    printf("CPU Usage       : %d%%\n",p.cpu_usage);
    printf("CPU Temperature : %d\n",p.cpu_temp);
    printf("Memory Usage    : %d%%\n",p.memory_usage);
    printf("Disk Activity   : %d%%\n",p.disk_act);
    printf("Uptime          : %d\n",p.uptime);
    printf("-------------------------------------\n");
    printf("Risk Score      : %d/250\n", risk_score);
    printf("Risk Percentage : %.2f%%\n", risk_score_per);
    if(risk_score_per<41)
    {
        printf("System Status   : Safe\n");
    }
    else if(risk_score_per<71)
    {
        printf("System Status   : Warning\n");
    }
    else
    {
        printf("System Status   : Critical\n");
    }

    printf("--- Issues Detected ---\n");
    if(p.cpu_usage>85)
    {
        printf("* High CPU usage detected\n");
        issue_found=1;
    }
    if(p.cpu_temp>85)
    {
        printf("* CPU Overheating detected\n");
        issue_found=1;
    }
    if(p.memory_usage>85)
    {
        printf("* High Memory Usage detected\n");
        issue_found=1;
    }
    if(p.disk_act>85)
    {
        printf("* High Disk Activity detected\n");
        issue_found=1;
    }
    if(p.uptime>85)
    {
        printf("* System Running for longer durations\n");
        issue_found=1;
    }
    if(issue_found==0)
    {
        printf("No Major Issue Detected\n");
    }

    printf("--- Possible Fixes ---\n");
    if(p.cpu_usage>85)
    {
        printf("* Close unnecessary background applications\n");
        
    }
    if(p.cpu_temp>85)
    {
        printf("* Check cooling system or fan performance\n");
    }
    if(p.memory_usage>85)
    {
        printf("* Restart system of free up memory\n");
    }
    if(p.disk_act>85)
    {
        printf("* Reduce disk intensive operations\n");
    }
    if(p.uptime>12)
    {
        printf("* Consider restarting the system\n");
    }
    if(issue_found==0)
    {
        printf("No action required system is operating optimally\n");
    }
    printf("\n=====================================\n");
    printf("       DIAGNOSIS COMPLETE\n");
    printf("=====================================\n");
    write_log(p, risk_score, risk_score_per);
    back_menu();
}

void analyze_system_logs(char system_id[50])
{
    DIR *d;
    struct dirent *dir;
    char latest_log[100]="";
    int total_logs=0;
    int sum=0;
    int highest=0;
    int lowest=251;
    int latest_risk_score=0;

    d = opendir("../logs");

    if(d == NULL)
    {
        printf("Error Opening Logs Folder\n");
        return;
    }

    while((dir = readdir(d)) != NULL)
    {
        if(strstr(dir->d_name, system_id) && strstr(dir->d_name, ".log"))
        {
            char filepath[100];
            sprintf(filepath,"../logs/%s",dir->d_name);

            FILE *lf = fopen(filepath, "r");
            char line[100];
            int log_risk_score = 0;

            if(lf == NULL)
            {
                printf("Error opening log file\n");
                continue;
            }

            while(fgets(line, sizeof(line), lf))
            {
                if (strstr(line, "Risk Score"))
                {
                    sscanf(line,"Risk Score      : %d",&log_risk_score);
                }
            }

            fclose(lf);

            total_logs++;
            sum += log_risk_score;

            if(log_risk_score > highest)
                highest = log_risk_score;

            if(log_risk_score < lowest)
                lowest = log_risk_score;

            if(strcmp(dir->d_name, latest_log) > 0)
            {
                strcpy(latest_log, dir->d_name);
                latest_risk_score = log_risk_score;
            }
        }
    }

    closedir(d);

    if(total_logs == 0)
    {
        printf("No Logs Found For System ID: %s\n", system_id);
        return;
    }

    
    float avg = (float)sum / total_logs;
    float latest_risk_score_per = (latest_risk_score * 100.0) / 250.0;

   
    printf("\n=====================================\n");
    printf("       SYSTEM LOG ANALYSIS REPORT\n");
    printf("=====================================\n");

    printf("System ID       : %s\n", system_id);
    printf("Latest Log      : logs/%s\n", latest_log);
    printf("Total Logs      : %d\n", total_logs);

    printf("-------------------------------------\n");
    printf("Average Score   : %.2f\n", avg);
    printf("Highest Score   : %d\n", highest);
    printf("Lowest Score    : %d\n", lowest);
    printf("Latest Score    : %d (%.2f%%)\n", latest_risk_score, latest_risk_score_per);

    
    printf("-------------------------------------\n");

    if(latest_risk_score_per < 41)
        printf("Current Status  : SAFE\n");
    else if(latest_risk_score_per < 71)
        printf("Current Status  : WARNING\n");
    else
        printf("Current Status  : CRITICAL\n");

    
    printf("\n--- TREND ANALYSIS ---\n");

    if(total_logs < 3)
    {
        printf("Trend           : Not enough data\n");
    }
    else
    {
        if(latest_risk_score > avg + 10)
            printf("Trend           : Degrading\n");
        else if(latest_risk_score < avg - 10)
            printf("Trend           : Improving\n");
        else
            printf("Trend           : Stable\n");
    }

    printf("\n--- PREDICTION ---\n");

    if(latest_risk_score_per < 41)
    {
        printf("System is stable and operating normally\n");
    }
    else if(latest_risk_score_per < 71)
    {
        printf("System shows warning signs, may degrade under load\n");
    }
    else
    {
        printf("High probability of failure, immediate attention required\n");
    }
    printf("\n=====================================\n");

    back_menu();
}

void check_logs()
{
    char system_id[50];
    printf("\nEnter the System ID:");
    scanf("%s",system_id);
    analyze_system_logs(system_id);
}
void about_help()
{
    printf("\n=================================================\n");
    printf(" SYSTEM FAILURE ANALYZER (SFA)\n");
    printf("=================================================\n");

    printf("\n>> ABOUT THE SYSTEM:\n");
    printf("- This system is designed to diagnose & analyze system failures,\n in centralized way for distributed systems\n");
    printf("- logs critical events, and help users understand\n");
    printf("- possible causes and risks associated with failures.\n");
    printf("- identifies problems with your systems and gives preventive measures and predictions\n");

    printf("\n>> WORKFLOW OVERVIEW:\n");
    printf("1. Select an option from the Main Menu.\n");
    printf("2. Input required system details.\n");
    printf("3. System analyzes the input and identifies:\n");
    printf(" - Type of failure\n");
    printf(" - Possible causes\n");
    printf(" - Risk level\n");
    printf("4. A detailed report is generated.\n");
    printf("5. Report is automatically saved as a log file.\n");

    printf("\n>> KEY FEATURES:\n");
    printf("- Failure Classification\n");
    printf("- Risk Level Detection\n");
    printf("- Log File Generation\n");
    printf("- Simple & Interactive CLI Interface\n");
    printf("- Hostorical data analysis and trends, predictions\n");

    printf("\n>> HOW TO USE:\n");
    printf("- Choose '1. Run Diagnosis' to input system issues.\n");
    printf("- Choose '2. Check logs' to check latest log reports.\n");
    printf("- Choose '3.Risk List' to get a distributed list of ciritical systems.");
    printf("- Use the Back Menu to return anytime.\n");

    printf("\n>> LOG FILE INFO:\n");
    printf("- Logs are saved with unique names:\n");
    printf(" systemID_date_time.log\n");
    printf("- Helps in tracking and future analysis.\n");

    printf("\n>> DEVELOPED BY:\n");
    printf("BCA 2nd Sem Project Team ID: 33 \n");
    printf("@GEHU Bhimtal\n");

    printf("\n=================================================\n");

    back_menu();
}