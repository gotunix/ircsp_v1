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

int	parse_kill		(char *, char *);

//////////////////////////////////////////////////////////////////////////////
//

int
parse_kill (nick,buf)
char	*nick;
char	*buf;
{
	char	*ptr[2];

	ptr[0] = strtok(buf, " ");
	strtok(NULL, "(");
	ptr[1] = strtok(NULL, ")");

	printf("ptr1 %s\n", ptr[0]);
	printf("ptr2 %s\n", ptr[1]);

	if (!strcasecmp(ptr[0], config->unick))
	{
		send_to_sock(s, 
			"WALLOPS :%s killed %s :%s\n",
			nick, ptr[0], ptr[1]);

		send_to_sock(s, 
			"NICK %s 1 0 %s %s %s :%s\n",
			config->unick, config->unick, 
			config->servname, config->servname, 
			config->udesc);

		send_to_sock(s, 
			":%s MODE %s +o\n",
			config->unick, config->unick);

		send_to_sock(s, 
			"NOTICE %s :%s\n",
			nick,"Don't KILL service bots.");
		return 0;
	}
	if (!strcasecmp(ptr[0], config->nnick))
	{
		send_to_sock(s, 
			"WALLOPS :%s killed %s :%s\n",
			nick, ptr[0], ptr[1]);

		send_to_sock(s, 
			"NICK %s 1 0 %s %s %s :%s\n",
			config->nnick, config->nnick, 
			config->servname, config->servname, 
			config->ndesc);

		send_to_sock(s, 
			":%s MODE %s +o\n",
			config->nnick, config->nnick);

		send_to_sock(s, 
			"NOTICE %s :%s\n",
			nick, "Don't KILL service bots.");
		return 0;
	}
	if (!strcasecmp(ptr[0], config->hnick))
	{
		send_to_sock(s, 
			"WALLOPS :%s killed %s :%s\n",
			nick, ptr[0], ptr[1]);

		send_to_sock(s, 
			"NICK %s 1 0 %s %s %s :%s\n",
			config->hnick, config->hnick, 
			config->servname, config->servname, 
			config->hdesc);

		send_to_sock(s, 
			"NOTICE %s :%s\n",
			nick, "Don't KILL service bots.");
		return 0;
	}
	if (!strcasecmp(ptr[0], config->scnick))
	{
		send_to_sock(s, 
			"WALLOPS :%s killed %s :%s\n",
			nick, ptr[0], ptr[1]);

		send_to_sock(s, 
			"NICK %s 1 0 %s %s %s :%s\n",
			config->scnick, config->scnick, 
			config->servname, config->servname, 
			config->scdesc);

		send_to_sock(s, 
			"NOTICE %s :%s\n",
			nick, "Don't KILL service bots.");
		return 0;
	}
	if (!strcasecmp(ptr[0], config->wnick))
	{
		send_to_sock(s, 
			"WALLOPS :%s killed %s :%s\n",
			nick, ptr[0], ptr[1]);

		send_to_sock(s, 
			"NICK %s 1 0 %s %s %s :%s\n",
			config->wnick, config->wnick, 
			config->servname, config->servname, 
			config->wdesc);

		send_to_sock(s, 
			"NOTICE %s :%s\n",
			nick, "Don't KILL service bots.");
		return 0;
	}
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//


