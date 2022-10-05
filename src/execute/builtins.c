#include "cmd.h"
#include "minishell.h"
#include <dirent.h>
#include "exec.h"
#include <errno.h>

#include <stdio.h>
#include <string.h>
#include <sys/_types/_errno_t.h>
#include <unistd.h>

void	execute_cd(t_vec cmd)
{
	int err;

	err = chdir(cmd.content[1]);
	if (err != 0)
		printf("%s\n",strerror(errno));
}
