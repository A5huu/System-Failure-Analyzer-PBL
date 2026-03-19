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
    int lowest=999;

    int latest_risk_score=0;

    d=opendir("../logs");
    if(d==NULL){
        printf("Error opening logs folder\n");
        return;
    }
    while((dir=readdir(d))!=NULL)
    {
        if(strstr(dir->d_name, system_id) && strstr(dir->d_name, ".log"))
        {
            char filepath[150];
            sprintf(filepath,"../logs/%s", dir->d_name);
            FILE *lf = fopen(filepath,"r");
            char line[100]="";
            int log_risk_score=0;
            if(lf==NULL)
            {
                printf("Error opening log file\n");
                continue;
            }
            while(fgets(line, sizeof(line), lf))
            {
                if(strstr(line, "Risk Score:"))
                {
                    sscanf(line, "Risk Score:%d", &log_risk_score);
                }
            }
            fclose(lf);
            total_logs++;
            sum+=log_risk_score;
            if (log_risk_score > highest)
            {
                highest=log_risk_score;
            }
            if (log_risk_score < lowest)
            {
                lowest=log_risk_score;
            }
            if (strcmp(dir->d_name, latest_log) > 0)
            {
                strcpy(latest_log, dir->d_name);
                latest_risk_score=log_risk_score;
            }
        }
    
    }
    closedir(d);
    if(total_logs==0)
    {
        printf("No logs found for System ID: %s\n", system_id);
        return;
    }
    else
    {
        float avg = (float)sum/total_logs;
        float latest_risk_per = ((float)latest_risk_score*100)/250.0;
        printf("\n=====System Log Analysis=====\n");
        printf("System ID: %s\n", system_id);
        printf("Latest Log: logs/%s\n", latest_log);
        printf("Total Logs: %d\n", total_logs);
        printf("Average Risk Score: %.2f\n", avg);
        printf("Highest Risk Score: %d\n", highest);
        printf("Lowest Risk Score: %d\n", lowest);
        printf("\n---Health Status---\n");
        if(total_logs<3)
        {
            printf("Trend Prediction: Not Enough Data\n");
        }
        else
        {
            if(latest_risk_score>avg)
            {
            printf("Trend: Degrading\n");
            }
            else
            {
                printf("Trend: Stable\n");
            }
        }
        if(latest_risk_per<60)
        {
            printf("Prediction: No problems detected system should work as ususal\n");
        }
        else if(latest_risk_per<75)
        {
            printf("Prediction: Warning Signs Detected May Degrade Under Load\n");
        }
        else
        {
            printf("Prediction: Higher Failure Probability Immediate Attention Required\n");
        }
    }
}
