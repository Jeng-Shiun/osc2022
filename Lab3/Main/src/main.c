# include "uart.h"
# include "utli.h"
# include "cpio.h"
# include "my_math.h"
# include "my_string.h"
# include "buddy.h"
# include "shell.h"
# include "mem.h"
# include "bitset.h"
# include "timer.h"
# include "svc_call.h"
# include "exception.h"

int main(){
  core_timer_init();
  uart_init();
  svc_init();
  buddy_init();
  buddy_dma_init();
  mem_init();
  uart_flush();
  IRQ_ENABLE();

  char cmd[1000];
  cmd[0] = '\0';
  int cmd_end = 0;

  while(1){
    uart_puts((char *) "\r> ");
    uart_puts(cmd);
    char c = uart_read();

    if (c == '\n'){
      uart_puts((char *) "\n");
      cmd[cmd_end] = '\0';
      invoke_cmd(cmd);
      cmd_end = 0;
      cmd[0] = '\0';
    }
    else if ((int)c == 127 || (int)c == 8){
      cmd_end--;
      cmd[cmd_end] = '\0';
      uart_puts((char *) "\b \b");
    }
    else{
      cmd[cmd_end] = c;
      cmd_end++;
      cmd[cmd_end] = '\0';
    }
  }
  return 0;
}
