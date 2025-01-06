//todo list cli - evang 


//test 

//includes

#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

//struct definitions


typedef struct todo
{

    int complete;
    char task[256];
    
} Todo;




//begin user defined functions

//*******
void printHeader()
{
    mvprintw(0,0,"/========================================================================\\");
    mvprintw(1,0,"|| _____         _         _     _     _            ____ _     ___      ||");
    mvprintw(2,0,"|||_   _|__   __| | ___   | |   (_)___| |_         / ___| |   |_ _|     ||");
    mvprintw(3,0,"||  | |/ _ \\ / _` |/ _ \\  | |   | / __| __|  _____| |   | |    | |_____ ||");
    mvprintw(4,0,"||  | | (_) | (_| | (_) | | |___| \\__ \\ |_  |_____| |___| |___ | |_____|||");
    mvprintw(5,0,"||  |_|\\___/ \\__,_|\\___/  |_____|_|___/\\__|        \\____|_____|___|     ||");
    mvprintw(6,0,"\\========================================================================/");
    mvprintw(8,17,"1-ADD TASKS 2- REMOVE TASKS Q - QUIT");
    printw("\n\n");
}

//*******
void printSubHeader()
{
    printw("Tasks:\n");
    printw("-------------------------------------------------------------------------");
    printw("\n\n");
}

/*
void printTasks(Todo list[], int task_amount)
{
    for(int i = 0; i < task_amount; i++)
    {
        printw("*  %s", list[i].task);
        printw("\n\n");
    }
}
*/
//*******
void promptAddTasks()
{
    printw("Press 1 to add some tasks!");
}


//*******
int addTasks(Todo list[], int *task_amount)
{
    char temp_task[256];
    mvprintw(11,0,"Enter task, -1 to quit\n\n");
    mvprintw(13,0,"> ");
    refresh();

    wgetnstr(stdscr, temp_task, 255);
    refresh();
   
    if(strcmp(temp_task, "-1")==0)
    {
        return 1;
    }
    

    FILE *fp = fopen("todo.csv", "a+");

    if(fp != NULL)
    {
        fprintf(fp, "%d %s\n", ++*task_amount,temp_task);
        fflush(fp);
        printw("Successfully Added Task!\n");
        refresh();
        usleep(10);
        fclose(fp);
        return 0;
    }
    else
    {
        printw("Error creating task!");
        refresh();
        return 1;
    }


}


//*******
int readTaskAmount(int *task_amount)
{
    
    
    char scum[256];
    FILE *fp = fopen("todo.csv", "r");
    while(fscanf(fp, "%d %[^\n]", task_amount, scum) == 2)
    {
        
    }
    
}


//*******
int fillArray(Todo list[], const int task_amount)
{
    int count = 0;
    int scum;
    FILE *fp = fopen("todo.csv", "r");

    while(fscanf(fp, "%d %[^\n]", &scum, list[count++].task) == 2)
    {
        
    }

}


//*******
void printTasks(Todo list[], const int task_amount)
{
    for(int i = 0; i < task_amount; i++)
    {
        printw("*  %s\n\n", list[i].task);
    }
    refresh();
}

//*******
void removeTasks(Todo list[], int *task_amount)
{

    int key;

    printTasks(list, *task_amount);

    printw("Select the task you wish to remove (0-%d): ", *task_amount);

    scanw("%d ", &key);
    
    if(key < (*task_amount)-1)
    {
        list[key] = list[key+1];
        --*task_amount;
    }
    else
    {
        --*task_amount;
    }


}

//end user defined functions
//begin main function

int main()
{

    Todo list[30];
    int task_amount;
    int key = 0;
    bool shouldQuit = FALSE;
    

    if(fopen("todo.csv", "a+") != NULL)
    {

        readTaskAmount(&task_amount);
    }



    initscr();
    curs_set(FALSE);



    while(!shouldQuit)
    {
        
        
        fillArray(list, task_amount);

        printHeader();
        printSubHeader();




        if(task_amount > 0) 
        {   
            printTasks(list, task_amount);
            refresh();
        }
        else
        {
            promptAddTasks();
        }

        key = getch();

        erase();
        printHeader();
        printSubHeader();
       // printw("Task amount: %d", task_amount);
        refresh();




        switch (key)
        {
            case '1':
                addTasks(list, &task_amount);
                break;
            
            case '2':
                removeTasks(list, &task_amount);
                break;
            case 'q':
                shouldQuit = TRUE;
                break;
            default:
                printw("Pressed: other\n");
                break;
        }


    }


    

    refresh();
    endwin();

}

