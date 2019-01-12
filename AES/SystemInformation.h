class SystemInformation
{
	int globalArgC;
	char **globalArgV;
	SystemInformation();
public:
	static SystemInformation& getInstance();
	void setSystemInformation(int globalArgC, char **globalArgV);
	int getGlobalArgC() const;
	char** getGlobalArgV() const;
};