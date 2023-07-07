/* ---------------------------------------------------------------------------
 * Copyright (c) GOTUNIX Networks
 * Copyright (c) GOTUNIXCODE
 * Copyright (c) Justin Ovens
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ---------------------------------------------------------------------------
 */

#include "services.h"

int	do_helpserv		(char *, char *, char *);
int	do_hs_help		(char *);

///////////////////////////////////////////////////////////////////////////////
//

int
do_helpserv (nick, mynick, buf)
char	*nick;
char	*mynick;
char	*buf;
{
	char	*ptr[9];

	ptr[0] = strtok(buf, " ");
	ptr[0]++;

	if (!strcasecmp(token(buf,1), ":HELP"))
	{
		char	*buff;

		buff = (char *)calloc(1, 1024);
		ptr[1] = strtok(NULL, "");

		sprintf(buff, "%s PRIVMSG %s :%s %s",
			nick, mynick, ptr[0], ptr[1]);
		do_hs_help(buff);

		return 0;
	}
	else
	{
		send_to_sock(s, 
			":%s NOTICE %s :Unknown Command: %s\n",
			mynick, nick, nocolon(token(buf,1)));
		return 0;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Command: HELP
// Service: Helpserv
//   ptr[0]   --   sender nickname
//   ptr[1]   --   service nickname
//   ptr[2]   --   help topic
//
//   This this send the helpfile to a user.
//
//  Syntax: HELP [topic]
//

int
do_hs_help (buf)
char	*buf;
{
	FILE	*fp;
	char	*ptr[3], read[512], file[1024];

	ptr[0] = strtok(buf, " ");
	strtok(NULL, " ");
	ptr[1] = strtok(NULL, " ");

	if (token(buf,2) == NULL)
	{  
		fp = fopen("help/helpserv/index", "r");
	}
	else
	{
		ptr[2] = token(buf,2);
		sprintf(file, "help/helpserv/%s", ptr[2]);
		fp = fopen(file, "r");
	}

	if (!fp)
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s\n",
			ptr[1], ptr[0], "Help file is missing.");
		return 0;
	}
	else
	{
		while (fgets(read,256,fp) != NULL)
		{
			send_to_sock(s, 
				":%s NOTICE %s :%s",
				ptr[1], ptr[0], read);
		}
	}
	fclose(fp);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//


