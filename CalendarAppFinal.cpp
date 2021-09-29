/*************************************************************************
 *CALENDAR APP - FINAL
 *COMSC-200
 *Programmer: Cole W. Tynan-Wood

This application is an interactive calendar that allows users to store and
remove events, view upcoming events, and more in future updates.

***************************************************************************/

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <sstream>
using namespace std;

#include <cstring>
#include <ctime>
#include <cstdlib>
#include "Calendar.h"

const int MAX_CHARS = 50; //maximum number of event characters

//Event* valiDate(Calendar, bool); //if boolean true, asks for event title and validates
void createEvent(Calendar& ThisCal);
void displayUpcoming(Calendar&, int month, int day);
void removeEvent(Calendar&);
bool checkClock(string);

int main()
{
  cout << setw(50) << setfill('*') << ""
       << setw(51) << setfill('*') << left << "\nCALENDAR APP"
       << setw(51) << setfill('*') << left << "\nPROGRAMMER: COLE W. TYNAN-WOOD"
       << endl << setw(50) << setfill('*') << "";


  //Get todays date
  time_t rawtime;
  struct tm* timeinfo;
  time (&rawtime);
  timeinfo = localtime (&rawtime);
  unsigned int thisDay = timeinfo->tm_mday, thisMonth = timeinfo->tm_mon + 1, thisYear = 1900 + timeinfo->tm_year;

  //create a data structure to hold calendar
  Calendar ThisCal(thisYear);


  /*Events for testing
  allDayEvent* testEvent1;
  testEvent1 = new allDayEvent();
  (*testEvent1).setEvent("Title1");
  ThisCal.addEvent(7, 30, testEvent1);

  allDayEvent* testEvent2;
  testEvent2 = new allDayEvent();
  (*testEvent2).setEvent("Title2");
  ThisCal.addEvent(8, 15, testEvent2);
  */

  //introductory output
  cout << "\n\nToday's date is " << thisMonth <<"/" << thisDay << "/" << thisYear << endl;

  bool quit = false;
  while(!quit)
  {
    string selectionChk;
    cout << "\nWhat would you like to do? (enter the number of your selection)"
         << "\n\t1. View upcoming events"
         << "\n\t2. Create a new event"
         << "\n\t3. Remove an event"
         << "\n\t4. Quit\n";
    cin >> selectionChk;
    cin.ignore(1000, 10);
    int selection = atoi(selectionChk.c_str());
    if (selection < 1 || selection > 4)
    {
      cout << "\nINVALID SELECTION.\n";
      continue;
    }

    switch(selection)
    {
    case 1: //View upcoming events
    {
      displayUpcoming(ThisCal, thisMonth, thisDay);
      break;
    } //case 1
    case 2: //create a new event
    {
      createEvent(ThisCal);
      break;
    } //case 2
    case 3: //remove an event
    {
      removeEvent(ThisCal);
      break;
    } //case 3
    case 4: //Quit loop
    {
      cout << "\nOkay, quitting.\n";
      quit = true;
      break;
    }

    default:
    {
        cout << "\nWhoops, that shouldn't have happened...\n";
        break;
    }
    }
  }
  return 0;
}

//prompts the user for information, creates, and stores an event into the calendar
void createEvent(Calendar& ThisCal)
{
  int month, day;
  string title, startTime, endTime;
  bool allDay = false;
  while(true) //gets a valid date
  {
    try
    {
      string parse;
      cout << "Please enter the date below, as shown. (EX: 7/20)" << endl;
      getline(cin, parse);
      cin.clear();

      char* token;
      char buf[1000];
      strcpy(buf, parse.c_str());
      const char* const slash = "/";

      const string monthStr((token = strtok(buf, slash)) ? token : "");
      if (monthStr.length() > 2 || monthStr.length() < 1) throw runtime_error("Invalid month");
      month = atoi(monthStr.c_str());
      if (month > 12 || month < 1) throw runtime_error("Invalid month");

      const string dayStr((token = strtok(0, slash)) ? token : "");
      if (dayStr.length() > 2 || dayStr.length() < 1) throw runtime_error("Invalid day");
      day = atoi(dayStr.c_str());
      if (day > ThisCal.getMonthSize(month) || day < 1) throw runtime_error("Invalid day");
      break;
    }
    catch (runtime_error& excpt)
    {
      cout << "ERROR" << endl;
      cout << excpt.what() << endl;
    }
  }

  while(true)
  {
    try
    {
      cout << "\nNow enter the name for your event.\n";
      getline(cin, title);
      if (title.length() < 1 || title.length() > MAX_CHARS) throw runtime_error("Num of chars out of bounds");
      break;
    }
    catch (runtime_error& excpt)
    {
      cout << "ERROR" << endl;
      cout << excpt.what() << endl;
    }
  }
  while(true)
  {
    try{
    char entry;
    cout << "Is your event all day (y/n)?" << endl;
    cin >> entry;
    cin.ignore(1000,10);

    switch (entry)
    {
    case 'y':
    case 'Y':
      allDay = true;
      break;
    case 'n':
    case 'N':
    {
      cout << "\nPlease enter the start time of your event (24 hr; EX: 14:45)" << endl;
      getline(cin, startTime);
      if(!(checkClock(startTime))) throw runtime_error("Invalid entry");
      cout << "Please enter the end time of your event." << endl;
      cin >> endTime;
      cin.ignore(1000, 10);
      if(!(checkClock(endTime))) throw runtime_error("Invalid entry");
      break;
    }
    default:
      throw runtime_error("Invalid entry");
    }//switch
    break;
    } //while
    catch (runtime_error& excpt)
    {
      cout << "ERROR" << endl;
      cout << excpt.what() << endl;
    }


  }

  if (!allDay)
  {
    timedEvent* newEvent;
    newEvent = new timedEvent;
    (*newEvent).setEvent(title, startTime, endTime);
    ThisCal.addEvent(month, day, newEvent);
  }
  else
  {
    allDayEvent* newEvent;
    newEvent = new allDayEvent;
    (*newEvent).setEvent(title);
    ThisCal.addEvent(month, day, newEvent);
  }

  cout << "Your event has been added." << endl;
}

//Outputs all upcoming events to the console
void displayUpcoming(Calendar& ThisCal, int month, int day)
{
  list<Event*> eventList; //list of events to return
  bool noUpcoming = true; //boolean to see if there aren't any events stored
  for(int i = month ; i < 12; i++)
  {
    int j = 1;
    if (i == month) //if the month being traversed is the current one, start looking from today
      j = day;
    for (; j < ThisCal.getMonthSize(i + 1); j++) //traverses the days
    {
      list<Event*> events = ThisCal.getEvents(i, j);
      if (!events.empty())
      {
        noUpcoming = false;
        //int noEvent = 0;

        cout << setw(20) << setfill('_') << "" << endl;
        cout << "  " << i  << "/" << j<< endl;
        cout << setw(20) << setfill('_') << "" << endl;

        list<Event*>::iterator it;
        for (it = events.begin(); it != events.end(); it++)
        {
          //cout << ++noEvent << ". " << endl;
          (*it)->printEvent();
          cout << endl;
        }
      }
    }
  }
  if (noUpcoming) cout << "\nNo upcoming events." << endl;
}

//validates a time to be in 24 hour format
bool checkClock(string time)
{
  bool isValid = false;
  while(true)
  {
    char* token;
    char buf[1000];
    strcpy(buf, time.c_str());
    const char* const colon = ":";

    const string hour((token = strtok(buf, colon)) ? token : "");
    if (hour.length() > 2 || hour.length() < 1 || atoi(hour.c_str()) > 59|| atoi(hour.c_str()) < 0) break;
    const string minute((token = strtok(buf, colon)) ? token : "");
    if (minute.length() > 2 || minute.length() < 1 || atoi(minute.c_str()) > 59|| atoi(minute.c_str()) < 0 ) break;
    isValid = true;
    break;
  }

  return isValid;
}


void removeEvent(Calendar& ThisCal)
{
  int month, day;
  while(true) //gets a valid date
  {
    try
    {
      string parse;
      cout << "Please enter the date below, as shown. (EX: 7/20)" << endl;
      getline(cin, parse);
      cin.clear();

      char* token;
      char buf[1000];
      strcpy(buf, parse.c_str());
      const char* const slash = "/";

      const string monthStr((token = strtok(buf, slash)) ? token : "");
      if (monthStr.length() > 2 || monthStr.length() < 1) throw runtime_error("Invalid month");
      month = atoi(monthStr.c_str());
      if (month > 12 || month < 1) throw runtime_error("Invalid month");

      const string dayStr((token = strtok(0, slash)) ? token : "");
      if (dayStr.length() > 2 || dayStr.length() < 1) throw runtime_error("Invalid day");
      day = atoi(dayStr.c_str());
      if (day > ThisCal.getMonthSize(month) || day < 1) throw runtime_error("Invalid day");
      break;
    }
    catch (runtime_error& excpt)
    {
      cout << "ERROR" << endl;
      cout << excpt.what() << endl;
    }
  }

  int noEvent = 0;
  list<Event*> events = ThisCal.getEvents(month, day);
  if (!events.empty())
  {

    list<Event*>::iterator it;
    for (it = events.begin(); it != events.end(); it++)
    {
      cout << setw(20) << setfill('-') << "" << endl;
      cout << ++noEvent << ". " << endl;
      (*it)->printEvent();
      cout << endl;
    }
  }
  else
  {
    cout << "\nNo events take place on that date." << endl;
    return;
  }

  int delIndex, counter = 0;
  cout << "\nEnter the number of the event you would like to delete." << endl;
  cin >> delIndex;
  cin.ignore(1000, 10);

  list<Event*>::iterator it;
  for (it = events.begin(); it != events.end(); it++)
  {
    counter++;
    if (delIndex == counter)
    {
      ThisCal.deleteEvent(month, day, *it);
    }
  }
}
