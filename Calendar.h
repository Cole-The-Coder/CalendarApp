#ifndef CALENDAR_H
#define CALENDAR_H

#include <string>
#include <list>
#include <vector>
#include <iostream>
using namespace std;

//Event class base
class Event
{
protected:
  string title;
  bool allDay;

public:
  bool isAllDay() const{return allDay;}
  virtual void setEvent(string, string, string) = 0;
  virtual void printEvent() const = 0;
};

//allDayEvent
class allDayEvent : public Event
{
public:
  allDayEvent(string title = "NO TITLE")
  {
    this->title = title;
    allDay = true;
  }
  void setEvent(string title, string NA = "", string NB = "") //NA & NB are placeholders to work with the base class's virtual function
  {
    this->title = title;
  }
  void printEvent() const
  {
    cout << "~" << title << "~" << endl;
    cout << "(All-Day Event)" << endl;
  }
};

//event with a specified duration
class timedEvent : public Event
{
private:
  string startTime, endTime; //24-hr clock

public:
  timedEvent(string title = "NO TITLE", string start = "00:00", string finish = "00:00")
  {
    this->title = title;
    startTime = start;
    endTime = finish;
    allDay = false;
  }
  void setEvent(string title, string start = "", string finish = "")
  {
    this->title = title;
    if(start.length() > 0){startTime = start;}
    if(finish.length() > 0){endTime = finish;}
  }
  void setDuration(string start, string finish)
  {
    startTime = start;
    endTime = finish;
  }
  void printEvent() const
  {
    cout << "~" << title << "~" << endl;
    cout << startTime << " --> " << endTime << endl;
  }
};

/**
//comparison operator for sorting event objects
bool operator<(const Event* a, const Event* b) {
  if(a->isAllDay) return true;
  else if (b->isAllDay()) return false;
  return a->
}
**/

//Calendar class
class Calendar
{
  class Month
  {
  public:
    vector<list<Event*> > days; //vector of Event object pointers for polymorphism purposes
    Month() : days(31) {}
  };
  unsigned int currentYear;
	vector<Month> months;
public:
	Calendar(unsigned int = 1970);
	int getMonthSize(int) const;
  list<Event*> getEvents(int, int) const;
  void addEvent(int, int, Event*);
  void deleteEvent(int, int, Event*);
};

//member function definitions

Calendar::Calendar(unsigned int year) : months(12)
{
  currentYear = year;
  for(int i = 0; i < 12; i++) //setting all the months to the appropriate number of days
  {
    if(i == 3 || i == 5 || i == 8 || i == 10)
    {
      months[i].days.resize(30);
    }
    else if (i == 1) //if february, check for leap year
    {
      if(!((currentYear % 4 == 0 && currentYear % 100 != 0) || (currentYear % 400 == 0)))
        months[i].days.resize(28); //if its a leap year, it has 28 days
      else
        months[i].days.resize(29);
    }
  }
}

int Calendar::getMonthSize(int month) const
{
  return months[month - 1].days.size();
}
//Returns a list of the events that occur on a certain day
list<Event*> Calendar::getEvents(int month, int day) const
{
  return months[month - 1].days[day - 1];
}


void Calendar::addEvent(int month, int day, Event* newEvent)
{
  months[month - 1].days[day - 1].push_back(newEvent);
}

void Calendar::deleteEvent(int month, int day, Event* eraseThis)
{
  months[month - 1].days[day - 1].remove(eraseThis);
}


#endif // CALENDAR_H
