#include "file.hpp"

enum logInfo // better name would be good
{
	TIMESTAMP
};

virtual class LogFile
{
  public:
	virtual static LogFile& operator<<(char *arg);
	virtual static LogFile& operator<<(logInfo arg);
  private:
	
}

class errorLog : public LogFile
{
  public:
	static errorLog();
	static errorLog(char *filename);
  private:
	static File* myFile;
}

class statusLog : public LogFile
{
  public:
	static statusLog();
	static statusLog(char *filename);
  private:
	static File* myFile;
}
