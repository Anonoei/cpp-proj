
#define DA_ALL
#include "DAdbg/DAdbg.h"
#include "otherfile.h"

#define tLog_trace(message)     daLOG_TRACE(message)
#define tLog_info(message)      daLOG_INFO(message)
#define tLog_warn(message)      daLOG_WARN(message)
#define tLog_error(message)     daLOG_ERROR(message)
#define tLog_critical(message)  daLOG_CRITICAL(message)

#define tAssert(x, ...)        daASSERT(x, __VA_ARGS__)

#define tClear()               daClear()

#define tPrint   daPrint

int main(void)
{
	daPROFILE_BEGIN_SESSION("main", "main.json");
	tLog_critical("Test");
	std::cout << "Hello there!" << std::endl;
	tLog_warn("This is a cross-platform color library!");
	daPrintl(fgRed, "\tHello there!");
	daPrint(fgYellow, "This "); daPrint(fgGreen, "is "); daPrint(fgBlue, "a ");
	daPrint(fgRed, "T"); daPrint(fgGreen, "E"); daPrint(fgMagenta, "S"); daPrintl(fgCyan, "T");
	DoSomething();
	daPrintChar(fgMagenta, "Something else!");

	std::cin.get();
	daPROFILE_END_SESSION();
	return 0;
}	//	END main