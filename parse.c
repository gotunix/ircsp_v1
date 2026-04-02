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

int	parse		(char *);

//////////////////////////////////////////////////////////////////////////////
//

typedef struct
{
	char		*nickname;
	char		*userhost;
	char		*realname;
	char		*server;
	time_t		ConnTime;
	int		flags;
	int		numClones;
}	
	NickTemp;

//////////////////////////////////////////////////////////////////////////////
//

int
parse (buf)
char	*buf;
{
	char	*ptr[9];

	if (config->debug)
	{
//		printf("%s", buf);
	}

	ptr[0] = strtok(buf, " ");
	ptr[0]++; 
	ptr[1] = strtok(NULL, " ");

	if (!strcasecmp(ptr[1], "PRIVMSG"))
	{
		ptr[2] = strtok(NULL, " ");
		if (!strcasecmp(ptr[2], config->unick))
		{
			ptr[3] = strtok(NULL, "");
			do_uworld(ptr[0], ptr[2], ptr[3]);
		}
		if (!strcasecmp(ptr[2], config->nnick))
		{
			ptr[3] = strtok(NULL, "");
			do_nickserv(ptr[0], ptr[2], ptr[3]);
		}
		if (!strcasecmp(ptr[2], config->hnick))
		{
			ptr[3] = strtok(NULL, "");
			do_helpserv(ptr[0], ptr[2], ptr[3]);
		}
		if (!strcasecmp(ptr[2], config->scnick))
		{
			send_to_sock(s, 
				":%s NOTICE %s :%s\n",
				config->scnick, ptr[0],
				"Huh?");
		}
		if (!strcasecmp(ptr[2], config->wnick))
		{
			ptr[3] = strtok(NULL, "\n");
			do_wbot(ptr[0], ptr[2], ptr[3]);
		}
	}
	if (!strcasecmp(ptr[1], "PING"))
	{
		send_to_sock(s, "PONG %s\n", config->servname);
		send_to_sock(s, "PONG :%s\n", config->servname);
	}
	if (!strcasecmp(ptr[1], "STATS"))
	{
		char	*buff;

		buff = (char *)calloc(1, 1024);
		ptr[2] = strtok(NULL, " ");
		ptr[3] = strtok(NULL, " ");
		ptr[3]++;

		sprintf(buff, "%s STATS %s :%s", 
			ptr[0], ptr[2], ptr[3]);
		m_stats(buff);
	}
	if (!strcasecmp(ptr[1], "QUIT"))
	{
		Admin		*a;
		nickservDB	*ns;
		Cadmin		*ca;
		Nick		*n;
		Hosts		*h;

		a  = findAdmin(ptr[0]);
		ns = NSFindNick(ptr[0]);
		ca = findCadmin_nick(ptr[0]);
		n  = findNick(ptr[0]);

		printf("%s quit\n", ptr[0]);

		if (n)
		{
			h = findHost(n->userhost);
			if (h)
			{
				if (h->clones == 1)
				{
					delHost(n->userhost);
				}
				else
				{
					h->clones--;
				}
			}
		}
		if (!a)
		{
			delNick(ptr[0]);
		}
		else
		{
			if (!ns)
			{
				DelAdmin(a);
				delNick(ptr[0]);
			}
			else
			{
				DelAdmin(a);
				DelNSAuth(ns);
				delNick(ptr[0]);
			}
		}
		if (!ns)
		{
		}
		else
		{
			DelNSAuth(ns);
		}
		if (!ca)
		{
		}
		else
		{
			if (!IsCAdmin(ca))
			{
			}
			else
			{
				DelCAdmin(ca);
			}
		}
	}
	if (!strcasecmp(ptr[1], "NICK"))
	{
		nickservDB	*ns;
		char		*uh;

		uh = (char *)calloc(1, 1152);
		ptr[2] = strtok(NULL, " ");
		strtok(NULL, " ");
		strtok(NULL, " ");
		ptr[3] = strtok(NULL, " ");
		ptr[4] = strtok(NULL, " ");
		ptr[5] = strtok(NULL, " ");
		ptr[6] = strtok(NULL, "\n");
		ptr[6]++;

		if (ptr[4] == NULL)
		{
			Admin		*a;
			NickTemp	*nt;
			Nick		*n;
			nickservDB	*ns;

			n = findNick(ptr[0]);
			a = findAdmin(ptr[0]);
			nt = (NickTemp *)calloc(1, sizeof(NickTemp));
			nt->nickname = (char *)calloc(1,64);
			nt->userhost = (char *)calloc(1,1024);
			nt->realname = (char *)calloc(1,1024);
			nt->server   = (char *)calloc(1,1024);

			if (!n)
			{
				return 0;
			}
			else
			{
				strcpy(nt->nickname, ptr[2]);
				strcpy(nt->userhost, n->userhost);
				strcpy(nt->realname, n->realname);
				strcpy(nt->server,   n->server);
				nt->flags    = n->flags;
				nt->ConnTime = n->ConnTime;

				addNick(nt->nickname, nt->userhost, nt->server,
					nt->realname, nt->flags, nt->ConnTime);
				
				if (a)
				{
					if (IsAdmin(a))
					{
						DelAdmin(a);
					}
				}
				delNick(ptr[0]);

				free(nt->nickname);
				free(nt->userhost);
				free(nt->realname);
				free(nt->server);
				free(nt);

				ns = NSFindNick(ptr[0]);
				if (!ns)
				{
				}
				else
				{
					if (IsNSAuth(ns))
					{
						DelNSAuth(ns);
					}
				}
				ns = NSFindNick(ptr[2]);
				if (!ns)
				{
					return 0;
				}
				else
				{                     
					send_to_sock(s, 
						":%s NOTICE %s :%s\n",
						config->nnick, ptr[2],
						"This nickname is registered");

					send_to_sock(s, 
						":%s NOTICE %s :%s\n", 
						config->nnick, ptr[2],
						"Please identify.");

					send_to_sock(s, 
						":%s NOTICE %s :\2/msg %s AUTH %s [password]\n",
						config->nnick, ptr[2], 
						config->nnick, ptr[2]);
				}
			}
		}
		else
		{
			Hosts	*h;

			sprintf(uh, "%s@%s", ptr[3], ptr[4]);
			h = findHost(uh);
			if (!h)
			{
				addNick(ptr[2], uh, ptr[5], ptr[6], 
					0, time(NULL));
				addHost(uh);
			}
			else
			{
				h->clones++;
				addNick(ptr[2], uh, ptr[5], ptr[6], 0, time(NULL));
			}
			ns = NSFindNick(ptr[2]);
			if (!ns)
			{
			}
			else
			{
				send_to_sock(s, 
					":%s NOTICE %s :%s\n",
					config->nnick, ptr[2],
					"You're using a registered nickname.");

				send_to_sock(s, 
					":%s NOTICE %s :%s\n",
					config->nnick, ptr[2],
					"Please identify.");

				send_to_sock(s, 
					":%s NOTICE %s :\2/msg %s AUTH %s [password]\n",
					config->nnick, ptr[2], 
					config->nnick, ptr[2]);
			}
		}
	}
	if (!strcasecmp(ptr[1], "MODE"))
	{
		ptr[2] = strtok(NULL, " ");
		if (ptr[2][0] != '#') /* umode */
		{
			ptr[3] = strtok(NULL, "");
			ptr[3]++;

			parse_umode(ptr[0], ptr[3]);
		}
		else /* cmode */
		{
			ptr[3] = strtok(NULL, "\n");

			parse_cmode(ptr[0], ptr[2], ptr[3]);
		}
	}
	if (!strcasecmp(ptr[1], "KILL"))
	{
		ptr[3] = strtok(NULL, "\n");
		parse_kill(ptr[0], ptr[3]);
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//


