#include <sys/types.h>
//#include <sys/stat.h>
#include "str.h"
#include "ip4.h"
#include "okclient.h"

#include <unistd.h>

static char fn[3 + IP4_FMT];

int okclient(char ip[4])
{
  //struct stat st;
  struct File * fp;
  int i;

  fn[0] = 'i';
  fn[1] = 'p';
  fn[2] = '/';
  fn[3 + ip4_fmt(fn + 3,ip)] = 0;

  /* Understanding: so basically, we have reached the point where a socket was successfully opened with a valid fd, and now we are ready to use the File
    to communicate (through read and write to the buffer). Let's attempt to open it, if there's a permission error, fp will be null
  */
  for (;;) {
    if((fp = fopen(fn, O_RDWR) != NULL)) {
      fclose(fp);
      return 1;
    } // NOTE: I saw log functions, so it's probably good to log a permission denied error (seen by checking errno)

    //if((access(fn, R_OK) == 0) && (access(fn, W_OK) == 0)) return 1;
    //if (stat(fn,&st) == 0) return 1;

    /* treat temporary error as rejection */
    i = str_rchr(fn,'.');
    if (!fn[i]) return 0;
    fn[i] = 0;
  }
}
