///////////////////////////////////////////////////////////////////////////////
//		  IRCSP - Internet Realy Chat Services Package
//                  Copyright (C) 2000 Lostworld Development
//          Written By: Justin Ovens [evilicey] [ice95@lostworld.net]
//
//   This program, documentation, and everything included in this
//   package are Copyright (C) 2000 Lostworld Development. You may
//   Download this package from the lostworld site, or via CVS
//   from source forge.
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 1, or (at your option)
//   any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software
//   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
//   The authors of this program are in no way liable for any
//   consequences or damages, suffered by you or anyone else,
//   arising out of the use or inablility to use this program.
//
//   Author Contact information: ice95@lostworld.net
///////////////////////////////////////////////////////////////////////////////


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


