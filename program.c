/**
 * @author Haeramb Jajpura
 * @date 21 July 2024
 * @brief this program is helpful for computer users who forget to drink water. it reminds you to drink water in every 30 minutes
 */

#include <stdio.h>
#include <unistd.h>
#include <windows.h>
#include <time.h>

// Function to display the remaining time in MM:SS format
void display_time(int minutes, int seconds)
{
    printf("\r%02d:%02d", minutes, seconds);
    fflush(stdout); 
}

void showNotification()
{
    
    const char *CLASS_NAME = "NotificationClass";
    WNDCLASS wc = {0};
    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);


    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, "Notification", 0, 0, 0, 0, 0,
        NULL, NULL, GetModuleHandle(NULL), NULL);

    // Add the notification icon
    NOTIFYICONDATA nid = {0};
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hwnd;
    nid.uID = 1001;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO;
    nid.uCallbackMessage = WM_USER + 1;
    nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    strcpy(nid.szTip, "Water Notification");
    strcpy(nid.szInfo, "Drink water Right Now and Stay hydrated!");
    strcpy(nid.szInfoTitle, "Reminder");
    nid.dwInfoFlags = NIIF_INFO;

    Shell_NotifyIcon(NIM_ADD, &nid);


    Sleep(5000);

  
    Shell_NotifyIcon(NIM_DELETE, &nid);

 
    DestroyWindow(hwnd);
}

// Function to play a note
void play_note(int frequency, int duration) {
    Beep(frequency, duration);
    Sleep(50); 
}

void FinalSound()
{
	
    int C = 523;
    int D = 587;
    int E = 659;
    int F = 698;
    int G = 784;

   
    play_note(C, 300); 
    play_note(E, 300); 
    play_note(G, 300); 
    play_note(C, 300); 
    play_note(E, 300); 
    play_note(G, 300); 

   
    play_note(G, 300); 
    play_note(F, 300); 
    play_note(E, 300);
    play_note(D, 300); 
    play_note(C, 500); 
}



DWORD WINAPI function1(LPVOID lpParam) {
   FinalSound();
    return 0;
}


DWORD WINAPI function2(LPVOID lpParam) {
   showNotification();
    return 0;
}


void RunBothAtSameTime()
{
	
    HANDLE thread1, thread2;
    
    thread1 = CreateThread(
        NULL,                  
        0,                      
        function1,              
        NULL,                  
        0,                      
        NULL);                  

    if (thread1 == NULL) {
        fprintf(stderr, "Error creating thread 1\n");
      
    }

  
    thread2 = CreateThread(
        NULL,                  
        0,                    
        function2,             
        NULL,                   
        0,                     
        NULL);                  
        
     if (thread2 == NULL) {
        fprintf(stderr, "Error creating thread 2\n");
      
    }   
        
     
    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

   
    CloseHandle(thread1);
    CloseHandle(thread2);
}

void main()
{
	
    int total_seconds = 30*60; // 30 minutes in seconds
    int total_time;
    total_time=total_seconds;
    int minutes, seconds;
    printf("Drink Water Reminder System\nDon't Close this window\n");
    while (1)
    {
    	//FinalSound();
    	//showNotification();
    	RunBothAtSameTime();
        total_seconds=total_time;
        while (total_seconds >= 0)
        {
            minutes = total_seconds / 60;
            seconds = total_seconds % 60;

            display_time(minutes, seconds);
            sleep(1);
            total_seconds--;
        }
        
    }
}