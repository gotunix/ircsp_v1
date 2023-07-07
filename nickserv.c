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

int	do_nickserv		(char *, char *, char *);
int	do_ns_help		(char *);
int	do_ns_auth		(char *);
int	do_ns_reg		(char *);
int	do_ns_drop		(char *);

///////////////////////////////////////////////////////////////////////////////
//

int
do_nickserv(nick,mynick,buf)
char	*nick;
char	*mynick;
char	*buf;
{
	char	*ptr[9];

	ptr[0] = strtok(buf, " ");
	ptr[0]++;

	if (!strcasecmp(token(buf,1), ":AUTH"))
	{
		char	*buff;

		buff = (char *)calloc(1, 1024);
		ptr[1] = strtok(NULL, "");
		if (ptr[1] == NULL)
		{
			send_to_sock(s, 
				":%s NOTICE %s :%s\n",
				mynick, nick,
				"Syntax: AUTH [nickname] [password]");
			return 0;
		}
		sprintf(buff, "%s PRIVMSG %s :%s %s",
			nick, mynick, ptr[0], 
			ptr[1]);
		do_ns_auth(buff);
		return 0;
	}
	if (!strcasecmp(token(buf,1), ":REGISTER"))
	{
		char	*buff;

		buff = (char *)calloc(1, 1024);
		ptr[1] = strtok(NULL, "");
		if (ptr[1] == NULL)
		{
			send_to_sock(s, 
				":%s NOTICE %s :%s\n",
				mynick, nick,
				"Syntax: REGISTER [password]");
			return 0;
		}
		sprintf(buff, "%s PRIVMSG %s :%s %s",
			nick, mynick, ptr[0], 
			ptr[1]);
		do_ns_reg(buff);
		return 0;
	}
	if (!strcasecmp(token(buf,1), ":DROP"))
	{
		char	*buff;

		buff = (char *)calloc(1, 1024);
		ptr[1] = strtok(NULL, "");
		if (ptr[1] == NULL)
		{
			send_to_sock(s, 
				":%s NOTICE %s :%s\n",
				mynick, nick,
				"Syntax: DROP [nickname]");
			return 0;
		}
		sprintf(buff, "%s PRIVMSG %s :%s %s",
			nick, mynick, ptr[0], 
			ptr[1]);
		do_ns_drop(buff);
		return 0;
	}
	if (!strcasecmp(token(buf,1), ":HELP"))
	{
		char	*buff;

		buff = (char *)calloc(1, 1024);
		ptr[1] = strtok(NULL, "");
		sprintf(buff, "%s PRIVMSG %s :%s %s",
			nick, mynick, ptr[0], 
			ptr[1]);
		do_ns_help(buff);
		return 0;
	}
	else
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s: %s\n",
			mynick, nick, 
			"Unknown Command",
			nocolon(token(buf,1)));
		return 0;
	}
}

///////////////////////////////////////////////////////////////////////////////
//

int
do_ns_auth (buf)
char	*buf;
{
	char		*ptr[4];
	nickservDB	*ns;

	ptr[0] = strtok(buf, " ");
	strtok(NULL, " ");
	ptr[1] = strtok(NULL, " ");

	if ((token(buf,1) == NULL) || (token(buf,2) == NULL) || 
		(token(buf,3) == NULL))
	{
		return 0;
	}

	ns = NSFindNick(ptr[0]);
	if (!ns)
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s\n",  
			ptr[1], ptr[0],
			"The nick you're using is not registered.");
		return 0;
	}
	if (ns->authed == NSAUTH_FLAG)
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s\n",
			ptr[1], ptr[0],
			"You're already authorized.");
		return 0;
	}
	if (!strcasecmp(token(buf,2), ns->nickname))
	{
		if (!strcasecmp(token(buf,3), ns->password))
		{
			send_to_sock(s, 
				":%s NOTICE %s :%s\n",
				ptr[1], ptr[0],
				"Authentication successful.");
			SetNSAuth(ns);
		}
		else
		{
			send_to_sock(s, 
				":%s NOTICE %s :%s\n", 
				ptr[1], ptr[0],
				"Authentication failed.");
			DelNSAuth(ns);
			return 0;
		}
	}
	else
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s\n", 
			ptr[1], ptr[0],
			"Authentication failed.");
		DelNSAuth(ns);
		return 0;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//

int
do_ns_help(buf)
char	*buf;
{
	FILE	*fp;
	char	*ptr[2], read[512], file[1024];

	ptr[0] = strtok(buf, " ");
	strtok(NULL, " ");
	ptr[1] = strtok(NULL, " ");

	if (token(buf,2) == NULL)
	{
		fp = fopen("help/nickserv/index", "r");
	}
	else
	{
		sprintf(file, "help/nickserv/%s", token(buf,2));
		fp = fopen(file, "r");
	}
	if (!fp)
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s\n",
			ptr[1], ptr[0],
			"HELP file is missing");
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

int
do_ns_reg (buf)
char	*buf;
{
	nickservDB	*ns;
	char		*ptr[9];

	ns = nickservdb;
	ptr[0] = strtok(buf, " ");
	strtok(NULL, " ");
	ptr[1] = strtok(NULL, " ");

	if (token(buf,2) == NULL)
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s\n",
			ptr[1], ptr[0],
			"Syntax: REGISTER [\2password\2]");
		return 0;
	}
	ns = NSFindNick(ptr[0]);
	if (!ns)
	{
		send_to_sock(s, 
			":%s NOTICE %s :\2%s\2 %s\n", 
			ptr[1], ptr[0], ptr[0],
			"is now registered");
		send_to_sock(s, 
			":%s NOTICE %s :\2%s\2 %s\n",
			ptr[1], ptr[0], token(buf,2),
			"is your password");
		NSAddNick(ptr[0], token(buf,2), 0, 10);
		return 1;
	}
	else
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s\n",
			ptr[1], ptr[0],
			"Sorry, that nickname is already registered.");
		return 0;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//

int
do_ns_drop (buf)
char	*buf;
{
	nickservDB	*ns;
	char		*ptr[5];

	ns = nickservdb;
	ptr[0] = strtok(buf, " ");
	strtok(NULL, " ");
	ptr[1] = strtok(NULL, " ");

	if (token(buf,2) == NULL)
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s\n",
			ptr[1], ptr[0],
			"Syntax: DROP [\2nickname\2]");
		return 0;
	}
	ns = NSFindNick(token(buf,2));
	if (!ns)
	{
		send_to_sock(s, 
			":%s NOTICE %s :\2%s\2 %s\n",
			ptr[1], ptr[0], token(buf,2),
			"is not registered.");
		return 0;
	}
	else
	{
		if (IsNSAuth(ns))
		{
			send_to_sock(s, 
				":%s NOTICE %s :\2%s\2 %s\n",
				ptr[1], ptr[0], token(buf,2),
				"is no longer regiestered.");
			DelNSAuth(ns);
			NSdelNick(token(buf,2));
			return 0;
		}
		else
		{
			send_to_sock(s, 
				":%s NOTICE %s :%s\n",
				ptr[1], ptr[0],
				"You must be Authorized to DROP a nickname");
			send_to_sock(s, 
				":%s NOTICE %s :\2/msg %s AUTH %s [password]\2\n",
				ptr[1], ptr[0], ptr[1], token(buf,2));
			return 0;
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//


