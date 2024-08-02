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
    fflush(stdout); // Ensure the output is displayed immediately
}

void showNotification()
{
    // Register the window class
    const char *CLASS_NAME = "NotificationClass";
    WNDCLASS wc = {0};
    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    // Create a window
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

    // Keep the window alive for the notification to be visible
    Sleep(5000);

    // Remove the notification icon
    Shell_NotifyIcon(NIM_DELETE, &nid);

    // Destroy the window
    DestroyWindow(hwnd);
}

// Function to play a note
void play_note(int frequency, int duration) {
    Beep(frequency, duration);
    Sleep(50); // Short pause between notes
}

void FinalSound()
{
	// Frequencies for the notes (in Hertz)
    int C = 523;
    int D = 587;
    int E = 659;
    int F = 698;
    int G = 784;

    // A simple "water droplets" melody
    play_note(C, 300); // Drip
    play_note(E, 300); // Drop
    play_note(G, 300); // Drip
    play_note(C, 300); // Drop
    play_note(E, 300); // Drip
    play_note(G, 300); // Drop

    // A short cheerful sequence
    play_note(G, 300); // Happy
    play_note(F, 300); // Drinking
    play_note(E, 300); // Time!
    play_note(D, 300); // Stay
    play_note(C, 500); // Hydrated!
}


// Function to be executed by the first thread
DWORD WINAPI function1(LPVOID lpParam) {
	//int i;
    //for (i = 0; i < 5; i++) {
        //printf("Function 1 is running\n");
        //Sleep(1000); // Sleep for 1 second
   // }
   FinalSound();
    return 0;
}

// Function to be executed by the second thread
DWORD WINAPI function2(LPVOID lpParam) {
	//int i;
   // for (i = 0; i < 5; i++) {
        //printf("Function 2 is running\n");
       // Sleep(1000); // Sleep for 1 second
   // }
   showNotification();
    return 0;
}


void RunBothAtSameTime()
{
	// Create thread handles
    HANDLE thread1, thread2;
    // Create the first thread
    thread1 = CreateThread(
        NULL,                   // default security attributes
        0,                      // use default stack size
        function1,              // thread function name
        NULL,                   // argument to thread function
        0,                      // use default creation flags
        NULL);                  // returns the thread identifier

    if (thread1 == NULL) {
        fprintf(stderr, "Error creating thread 1\n");
       // return 1;
    }

    // Create the second thread
    thread2 = CreateThread(
        NULL,                   // default security attributes
        0,                      // use default stack size
        function2,              // thread function name
        NULL,                   // argument to thread function
        0,                      // use default creation flags
        NULL);                  // returns the thread identifier
        
     if (thread2 == NULL) {
        fprintf(stderr, "Error creating thread 2\n");
      //  return 1;
    }   
        
         // Wait for the threads to finish
    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    // Close the thread handles
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
            sleep(1); // Wait for 1 second
            total_seconds--;
        }
        
    }
}