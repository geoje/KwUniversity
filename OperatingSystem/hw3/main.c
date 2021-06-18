#include <stdio.h>
#include <string.h>

#include "buf.h"
#include "fat.h"
#include "Disk.h"

int main()
{
    FatInit();
    FatAdd(-1, 1);
    for (int i = 1; i < 600; i += 1)
        FatAdd(i, i + 1);

    //BufSync();

    return 0;
}
