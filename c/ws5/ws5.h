#define NUMOPFUNCTIONS 5
#define MAXSTR 100

typedef struct {
	char *str;
	int (*comp)(const char*, const char*);
	void (*func)(const char*, const char*);
} Functions;
/*-------------------------------------------------*/
void InitializesTheStructure(Functions functions  []);

void RemoveFile(const char* filename, const char* str);
void CountLines(const char* filename, const char* str);
void Exit(const char* filename, const char* str);
void WriteFromStart(const char* filename, const char* str);
void WriteTfromEnd(const char* filename, const char* str);

void UserSelection(char *filename, Functions functions []);
void SelectFunction(const char* filename, const char* str, Functions functions []);
int Compare(const char* input, const char* expected);

void ErrorOpenFile(void *fp);
