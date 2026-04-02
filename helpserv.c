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


