#ifdef MTK_AT_PRINT
#include "atci.h"
#include "atci_main.h"
#include "atci_adapter.h"
#include <stdio.h>
#include "test_print.h"

void test_print(char *log)
{
      atci_send_data(log, strlen(log));
}
#else
#include <stdio.h>

void test_print(char *log)
{
      printf("%s", log);
}
#endif


