#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

class Event
{
private:
  string title;
  bool allDay;

public:
  virtual void printEvent() = 0;
};

class allDayEvent : public Event
{
public:
  allDayEvent()
  {
    allDay = true;
  }
  printEvent()
  {
    cout << "Title: " << title << endl;
    cout << "(All-Day Event)" << endl;
  }
};

class timedEvent : public Event
{
private:
  string startTime, endTime
  bool PM;
public:
  timedEvent()
  {
    allDay = false;
    PM = false; //by default the event will occur in the morning
  }
  printEvent()
  {
    cout << "Title: " << title << endl;
    cout << startTime << " --> " << endTime << endl;
  }
};


#endif // EVENT_H_INCLUDED
