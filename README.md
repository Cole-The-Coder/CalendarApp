#CALENDAR APP FUNCTIONS AND CLASSES
#CLASSES
#Event
	Struct object that holds all the necessary data for an event. 
Year
	This class is kind of the backbone of the whole program, and works in tandem with the other class, Month, to create a calendar app that’s magnitudes more readable than my first version. It holds a vector of 12 months, and has several member functions that are listed below
Void addEvent()
	Adds an event on a specified date
Void deleteEvent()
	Self explanatory
Map<int, string> getEvents()
	returns a “map” consisting of the events for a specified day
int getMonthSize()
	returns the number of days in a month

Month
	Holds a vector of maps, which in turn hold the events listed on a certain day, in order by the hour on which they take place. Is used with the Year class, and shares some functions with it. The only unique function is the resizeMonth() function, which is only used when a Year object is initialized and sets the number of days for each month.
	
FUNCTIONS
Event validate(Year, bool)
	This function gets a date from the console that is syntactically correct and will not crash the program when inserted into the Year class. The user is asked for the same kind of input several times so its quicker just to have one function handle it all.
	The bool is for telling the function whether or not to ask for the event, as sometimes its not needed.

getUpcoming(Year, int, int)
	This function goes through the entire calendar and returns a list of every upcoming event. In the future I will refine this to specify how far into the future the program should search.
saveCalendar(Year)
	In the future I will have the data be saved onto a binary file for persistent data over different sessions. This will be used to write new data to the file, hopefully.
displayMonth(), displayYear(), display pastEvents()
	All for output. May or may not implement depending on amount of time I have to work on this class. 
