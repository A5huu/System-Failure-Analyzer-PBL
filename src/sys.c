#include <stdio.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
struct parameters
{
    char system_id[50];
    int cpu_usage;
    int memory_usage;
    int disk_act;
    int uptime;
    int cpu_temp;
    
};
void run_diagnosis();
void time_live(char *buffer);
void write_log(struct parameters p, int risk_score, float risk_score_per);
int main()
{
    run_diagnosis();
    return 0;
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

}