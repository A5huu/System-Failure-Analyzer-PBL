#include <stdio.h>
#include <string.h>
#include<dirent.h>

void check_logs();
void analyze_system_logs(char system_id[50]);
int main()
{
    check_logs();
    return 0;
}

void check_logs(){
    char system_id[50];
    printf("Enter the System ID to check logs:");
    scanf("%s",&system_id);
    analyze_system_logs(system_id);
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

    //back_menu();
}
