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


Nick	*addNick			(char *, char *, char *, char *, \
					 int, time_t);
Nick	*findNick			(char *);
Nick	*findNickbyHost			(char *);
void	delNick				(char *);

///////////////////////////////////////////////////////////////////////////////
//

Nick *
addNick (nickname,userhost,server,realname,flags,ConnTime)
char	*nickname;
char	*userhost;
char	*server;
char	*realname;
int	flags;
time_t	ConnTime;
{
	Nick	*n;
	int	mFail = 0, mPass = 0;

	n = (Nick *)calloc(1, sizeof(Nick));
	{
		if (!n)
		{
			if (config->debug)
			{
				printf(
					"addNick(): calloc() of n failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addNick(): calloc() of n [%p] passed.\n",
					n);
			}
			mPass++;
		}
	}
	n->nickname = (char *)calloc(1, 64);
	{
		if (!n->nickname)
		{
			if (config->debug)
			{
				printf(
					"addNick(): calloc() of n->nickname failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addNick(): calloc() of n->nickname [%p] passed.\n",
					n->nickname);
			}
			mPass++;
		}
	}
	n->userhost = (char *)calloc(1, 1024);
	{
		if (!n->userhost)
		{
			if (config->debug)
			{
				printf(
					"addNick(): calloc() of n->userhost failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addNick(): calloc() of n->userhost [%p] passed.\n",
					n->userhost);
			}
			mPass++;
		}
	}
	n->server   = (char *)calloc(1, 1024);
	{
		if (!n->server)
		{
			if (config->debug)
			{
				printf(
					"addNick(): calloc() of n->server failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addNick(): calloc() of n->server [%p] passed.\n",
					n->server);
			}
			mPass++;
		}
	}
	n->realname = (char *)calloc(1, 512);
	{
		if (!n->realname)
		{
			if (config->debug)
			{
				printf(
					"addNick(): calloc() of n->realname failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addNick(): calloc() of n->realname [%p] passed.\n",
					n->realname);
			}
			mPass++;
		}
	}

	if (mFail)
	{
		if (config->debug)
		{
			printf(
				"addNick(): calloc(): %d fail, %d pass\n",
				mFail, mPass);
		}
		return NULL;
	}

	strcpy(n->nickname, nickname);
	strcpy(n->userhost, userhost);
	strcpy(n->server,   server);
	strcpy(n->realname, realname);

	n->flags = flags;
	n->ConnTime = ConnTime;

	if (config->debug)
	{
		printf(
			"addNick(): NN: %s    UH: %s    SRV: %s   RN: %s   FLG: %d   CT: %lu\n",
			n->nickname, n->userhost, n->server, n->realname,
			n->flags, n->ConnTime);
	}

	if (!nick)
	{
		nick = n;
		n->next = NULL;
	}
	else
	{
		n->next = nick;
		nick = n;
	}
	return n;
}

///////////////////////////////////////////////////////////////////////////////
//

Nick *
findNick(nickname)
char	*nickname;
{
	Nick	*n;

	n = nick;
	while (n)
	{
		if (!strcasecmp(n->nickname, nickname))
		{
			if (config->debug)
			{
				printf(
					"findNick(): %s [%p] found.\n",
					n->nickname, n->nickname);
			}

			return n;
		}
		n = n->next;
	}
	if (config->debug)
	{
		printf(
			"findNick(): %s not found.\n",
			nickname);
	}

	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//

Nick *
findNickbyHost (hostname)
char	*hostname;
{
	Nick	*n;
	n = nick;

	while (n)
	{
		if (!strcasecmp(n->userhost, hostname))
		{
			if (config->debug)
			{
				printf(
					"findNickbyHost(): %s [%p] found %s [%p].\n",
					n->userhost, n->userhost,
					n->nickname, n->nickname);
			}

			return n;
		}
		n = n->next;
	}
	if (config->debug)
	{
		printf(
			"findNickbyHost(): %s not found.\n",
			hostname);
	}

	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//

void
delNick (nickname) 
char	*nickname;
{
	Nick	*n, *next, *delete;

	for (n = nick; n; n = next)
	{
		next = n->next;
		if (!strcasecmp(n->nickname, nickname)) 
		{
			if (nick == n) 
			{
				nick = n->next;
			}
			else 
			{
				for (delete = nick; (delete->next != n) && 
					delete; delete = delete->next);
				delete->next = n->next;
			}
			free(n->nickname);
			free(n->userhost);
			free(n->server);
			free(n->realname);
			free(n->mode);
			free(n);
			return;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//


