#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

// Datatype to extract the records from txt file
typedef struct txtfilerecord{
    int matchno;
    char bresult[5];
    int win;
    int loss;
    int draw;
    char day[5];
    char month[5];
    int date;
    char Time[10];
    int year;
}txt;

// Function to print text with some sounds

void SoundTitle(char str[20],int sfreq,int efreq,int iteration,int beepduration){
    printf("%s",str);
    for(int i=sfreq;i<efreq;i+=iteration) Beep(i,beepduration);}

// Function to compare the choices and update the amount of win,loss or draw
void decision(char user, char bot,int *winptr,int *lossptr,int *drawptr){
    if (user==bot){
        *drawptr+=1;
        printf("Hmm... Seems like bot's skills are getting equal to yours...\n\n");}
    else if (user=='r' && bot=='s' || user=='p' && bot=='r' || user=='s' && bot=='p'){
         *winptr+=1;
         printf("Bravo! You won this Match! Maintain your Winning streak...\n\n");}
    else{
        *lossptr+=1;
         printf("OOPS! You lost this one.. Bot is understanding your tactics now..\n\n");}    
}


int main(){
    char bot,user;
    FILE *record,*tempfile;
    int tempint;
    char bresult[9],condition;



 
    // Presentation of Game //
    SoundTitle("\n\n\t\t\t\t\tROCK!\t\t",425,426,2,1500);
    SoundTitle("PAPER!\t\t",350,351,2,1500);
    SoundTitle("SCISSOR!\n\n\n",550,551,2,1500);
    SoundTitle("\t\t\t\t\tGame is Starting in >>    ",300,401,100,100);
    Sleep(1000);

    char tempstr[20];
    int freq1=500,freq2=601,i;
    for(i=3;i>-1;i--){
        if (i==0) SoundTitle("\n\n\t\t\t\t\t\t\t!! GO !! \n",2500,2501,2,1500);
        else{
            itoa(i,tempstr,10);
            strcat(tempstr,"      ");
            SoundTitle(tempstr,freq1,freq2,100,100);
            freq1+=200;
            freq2+=200;
            Sleep(400);
        }}



    printf("\n\n \nBot will choose its move and then a choice will appear to you\n");
    Sleep(2500);
    printf("Choose 'r' for Rock, 'p', for Paper & 's' for Scissor\n\n");
    Sleep(2500);

    while(1){
        fflush(stdin);
        printf("\n\nWhat you want to do?\nEnter '1' to Play\nEnter '2' to  check the Records of Battles played till now.\nPress '3' to end the Game.\n->> ");
        scanf("%c",&condition);
        if (condition=='1'){


                                           //''''''''GamePlay''''''''//
                                               // Game working //
            int matchno,win=0,loss=0,draw=0,random;
        printf("\nEnter the number of matches in a battle you want to play: ");
    scanf("%d",&matchno);
    for(i=0;i<matchno;i++){
        fflush(stdin);
        printf("Make your Choice : ");
        scanf("%c",&user);
        if (user!='r' && user!='s' && user!='p'){
            printf("\nDon't Enter Invalid input!! Read the Instructions again above\n\n");
            i--;
            continue;
        }

        srand(time(NULL));
        random=rand()%3+1;
        if (random==1) bot='r';
        else if (random==2) bot='p';
        else bot='s';
        printf("Bot's Choice : %c\n\n",bot);
        Sleep(750);
        
        decision(user,bot,&win,&loss,&draw);}


    //Game Results

    if (win>loss){
        printf("Congratulations!! You WON this Series of Matches.\nThis Battle will be recorded in Won Battles.\n");
        strcpy(bresult,"Won!");
            for (int i=450;i<651;i+=150){
                Beep(i,100);
                Beep(i+150,100);
                Beep(i+300,100);
                    }
    }
    else if (loss>win){
        printf("Damn! A Thought of Comfort and Condolences for this Lost Battle.\nYou can check this Battle later in Lost Battles.\n");
        strcpy(bresult,"Lost");
            for (int i=650;i>199;i-=150){
                Beep(i,100);
                Beep(i-300,100);
                    }
    }
    else {
        printf("WOW! That was so close to Win but this Battle is Draw.\n This Battle will be recorded in Drawn Battles.\n");
        strcpy(bresult,"Draw");
            Beep(500,1200);
            Beep(200,2000);
}



    //Recording Battle Results
    time_t matchdetails;
    time(&matchdetails);

    record=fopen("BattleRecords.txt","a");
    
    fprintf(record,"%s ",bresult);
    fprintf(record,"%d ",matchno);
    fprintf(record,"%d ",win);
    fprintf(record,"%d ",loss);
    fprintf(record,"%d ",draw);
    fprintf(record,"%s ",ctime(&matchdetails));
    fclose(record);


    //Updating the rows of battles in file
    int filerow; //takes the row from file in the first line and update it later
    record=fopen("BattleRecords.txt","r");
    tempfile=fopen("temp.txt","w");
    fscanf(record,"%d",&filerow);
    fprintf(tempfile,"%d",filerow+1);

    char c=fgetc(record);
    while(c!=EOF){
        fputc(c,tempfile);
        c=fgetc(record);
    }
    fclose(record);
    fclose(tempfile);
    remove("BattleRecords.txt");
    rename("temp.txt","BattleRecords.txt");
        }



    else if (condition=='2'){

//                                           ''''''Showing Battle Records''''''

    record=fopen("BattleRecords.txt","r");
    fscanf(record,"%d",&tempint);
    txt detail;
    printf("\n\n\nS.no |Battle Results|No. of matches|  Won  |  Lost  |  Draw  | Day | Date | Month | Year | Time \n");
    for(int i=0;i<tempint;i++){
        fflush(stdin);
        fscanf(record,"%s",detail.bresult);
        fscanf(record,"%d",&detail.matchno);
        fscanf(record,"%d",&detail.win);
        fscanf(record,"%d",&detail.loss);
        fscanf(record,"%d",&detail.draw);
        fscanf(record,"%s",detail.day);
        fscanf(record,"%s",detail.month);
        fscanf(record,"%d",&detail.date);
        fscanf(record,"%s",detail.Time);
        fscanf(record,"%d",&detail.year);
        //just fixed a bit of structure of table in s.no till 100's place
        (i>98)?printf("%d  |     %s     |      %d       |   %d   |   %d    |   %d    | %s |  %d  |  %s  | %d | %s \n",i+1,detail.bresult,detail.matchno,detail.win,detail.loss,detail.draw,detail.day,detail.date,detail.month,detail.year,detail.Time):(i>8)?printf("%d   |     %s     |      %d       |   %d   |   %d    |   %d    | %s |  %d  |  %s  | %d | %s \n",i+1,detail.bresult,detail.matchno,detail.win,detail.loss,detail.draw,detail.day,detail.date,detail.month,detail.year,detail.Time):printf("%d    |     %s     |      %d       |   %d   |   %d    |   %d    | %s |  %d  |  %s  | %d | %s \n",i+1,detail.bresult,detail.matchno,detail.win,detail.loss,detail.draw,detail.day,detail.date,detail.month,detail.year,detail.Time);
    }
    fclose(record);}

    else if (condition=='3'){
        printf("\nWe will wait for you to come back and play again!\n\nTill then, See You Again.\n\n");
        break;}

    else printf("Enter a valid option.\n\n");}

}