#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;
#include <cassert>

#include "Calendar.h"

int main()
{

  Calendar newCal;
  timedEvent newEvent1;
  timedEvent newEvent2("Yolo" , "12:30", "13:00");
  timedEvent newEvent3("Butts");

    cout << "newEvent1.changeTitle TEST" << endl;
  newEvent1.setEvent("Changed!");

  cout << "newEvent3.setDuration TEST" << endl;
  newEvent3.setDuration("01:00", "02:00");

  cout << "\nTESTING printEvent() MEMBER FUNCTION\n";
  newEvent1.printEvent();
  newEvent2.printEvent();
  newEvent3.printEvent();

  allDayEvent allDay1;
  allDayEvent allDay2("All Day bae");


  timedEvent* testingEvent1;
  testingEvent1 = new timedEvent;
  timedEvent* testingEvent2;
  testingEvent2 = new timedEvent;
  allDayEvent* testingEvent3;
  testingEvent3 = new allDayEvent;

  cout << "\nTESTING CALENDAR CLASS\n";
  testingEvent1->setEvent("TestTitle1", "00:01" , "00:05");
  testingEvent2->setEvent("TestTitle2", "00:06" , "00:10");
  testingEvent3->setEvent("TestTitle3");

  cout << "\nTESTING addEvent FUNCT\n";
  newCal.addEvent(7, 20, testingEvent1);
  newCal.addEvent(7, 20, testingEvent2);
  newCal.addEvent(7, 20, testingEvent3);

  cout << "\nTESTING getEvents FUNCT\n";
  list<Event*> listEvents= newCal.getEvents(7, 20);
  list<Event*>::iterator it;
  for (it = listEvents.begin(); it != listEvents.end(); it++)
  {
    (*it)->printEvent();
  }

  /* Testing list erase() function
  //playing with erase funct for lists
  list<Event*> testList = newCal.getEvents(7,20);
  for (it = testList.begin(); it != testList.end(); it++){
    if ((*it) == testingEvent1) {
      testList.erase(it);
    }
  }

  for (it = testList.begin(); it != testList.end(); it++)
  {
    (*it)->printEvent();
  }
  */

  cout << "\nTESTING deleteEvent FUNCT\n";

  list<Event*> searchList = newCal.getEvents(7,20);
  for (it = searchList.begin(); it != searchList.end(); it++){
    if ((*it) == testingEvent1) {
      newCal.deleteEvent(7, 20, *it);
      cout << "\nDELETED\n";
    }
  }

  cout << "TestTitle1 should now be deleted" << endl;
  listEvents.clear();
  listEvents= newCal.getEvents(7, 20);
  for (it = listEvents.begin(); it != listEvents.end(); it++)
  {
    (*it)->printEvent();
  }

  cout << "\ngetMonthSize() TEST\n";
  assert(newCal.getMonthSize(6) == 31);
  assert(newCal.getMonthSize(1) == 28);
}




// storage for code blocks from main

try
    {
      string invDate = "Invalid date entered.";
      string date, monthStr, dayStr;
      cout << "\nPlease enter the date on which the event takes place followed by return.(EX: 7/21)" << endl;
      getline(cin, date);
      cin.ignore(1000,10);
      if (date.length() < 3) throw runtime_error(invDate);
      stringstream inSS;
      inSS.str(date);
      char delim = '/';
      getline(inSS, monthStr, delim);
      if (monthStr.length() > 2 || monthStr.length() < 1 || atoi(monthStr.c_str()) == 0) throw runtime_error(invDate);
      inSS >> dayStr;
      inSS.clear();
      if (dayStr.length() < 1 || dayStr.length() > 2 ) throw runtime_error(invDate);
      month = atoi(monthStr.c_str());
      day = atoi(dayStr.c_str());
      if (month < 1 || month > 12) throw runtime_error(invDate);
      if (day < 1 || day > ThisCal.getMonthSize(month)) throw runtime_error(invDate);
      break; //If we've made it this far, the date is a valid one
    }
    catch (runtime_error& excpt)
    {
      cout << "ERROR" << endl;
      cout << excpt.what() << endl;
    }
