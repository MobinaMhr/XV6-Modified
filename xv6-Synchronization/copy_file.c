#include "types.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{

  if (argc != 3)
  {
    printf(2, "copy_file takes two arguments to run.\n");
    exit();
  }

  int copy_result = copy_file(argv[1], argv[2]);
  if (copy_result < 0)
  {
    printf(2, "copy_file failed...\n");
  }
  else
  {
    printf(1, "copy_file done!\n");
  }

  exit();
}
