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

Cadmin	*addCadmin		(char *, char *, char *, int, int);
Cadmin	*findCadmin		(char *, char *);
Cadmin	*findCadmin_nick	(char *);
void	delCadmin		(char *, char *);

///////////////////////////////////////////////////////////////////////////////
//

Cadmin *
addCadmin (nickname,password,channel,flags,level)
char	*nickname;
char	*password;
char	*channel;
int	flags;
int	level;
{
	Cadmin	*ca;
	int	mFail = 0, mPass = 0;

	ca = (Cadmin *)calloc(1, sizeof(Cadmin));
	{
		if (!ca)
		{
			if (config->debug)
			{
				printf(
					"addCadmin(): calloc() of ca failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addCadmin(): calloc() of ca [%p] passed.\n",
					ca);
			}
			mPass++;
		}
	}
	ca->nickname = (char *)calloc(1, 64);
	{
		if (!ca->nickname)
		{
			if (config->debug)
			{
				printf(
					"addCadmin(): calloc() of ca->nickname failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug) 
			{
				printf(
					"addCadmin(): calloc() of ca->nickname [%p] passed.\n",
					ca->nickname);
			}
			mPass++;
		}
	}
	ca->password = (char *)calloc(1, 256);
	{
		if (!ca->password)
		{
			if (config->debug)
			{
				printf(
					"addCadmin(): calloc() of ca->password failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug) 
			{
				printf(
					"addCadmin(): calloc() of ca->password [%p] passed.\n",
					ca->password);
			}
			mPass++;
		}
	}
	ca->channel = (char *)calloc(1, 256);
	{
		if (!ca->channel)
		{
			if (config->debug)
			{
				printf(
					"addCadmin(): calloc() of ca->channel failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug) 
			{
				printf(
					"addCadmin(): calloc() of ca->channel [%p] passed.\n",
					ca->channel);
			}
			mPass++;
		}
	}

	if (mFail)
	{
		if (config->debug)
		{
			printf(
				"addCadmin(): calloc() %d fail, %d pass\n",
				mFail, mPass);
		}
		return NULL;
	}

	strcpy(ca->nickname, nickname);
	strcpy(ca->password, password);
	strcpy(ca->channel, channel);

	ca->flags = flags;
	ca->level = level;

	if (!cadmin)
	{
		cadmin = ca;
		ca->next = NULL;
	}
	else
	{
		ca->next = cadmin;
		cadmin = ca;
	}
	return ca;
}

///////////////////////////////////////////////////////////////////////////////
//

Cadmin *
findCadmin (channel,nickname)
char	*channel;
char	*nickname;
{
	Cadmin	*ca;

	ca = cadmin;
	while (ca)
	{
		if (!strcasecmp(ca->channel, channel))
		{
			if (!strcasecmp(ca->nickname, nickname))
			{
				if (config->debug)
				{
					printf(
						"findCadmin(): %s [%p] found on %s [%p]\n",
						ca->nickname, ca->nickname, ca->channel,
						ca->channel);
				}
				return ca;
			}
		}
		ca = ca->next;
	}
	if (config->debug)
	{
		printf(
			"findCadmin(): %s not found on %s\n",
			ca->nickname, ca->channel);
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//

Cadmin *
findCadmin_nick (nick)
char	*nick;
{
	Cadmin	*ca;

	ca = cadmin;
	while (ca)
	{
		if (!strcasecmp(ca->nickname, nick))
		{
			if (config->debug)
			{
				printf(
					"findCadmin_nick(): %s [%p] found.\n",
					ca->nickname, ca->nickname);
			}
			return ca;
		}
		ca = ca->next;
	}
	if (config->debug)
	{
		printf(
			"findCadmin_nick(): %s not found.\n",
			ca->nickname);
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//

void
delCadmin (channel,nickname)
char	*channel;
char	*nickname;
{
	Cadmin	*ca, *next, *delete;

	for (ca = cadmin; ca; ca = next)
	{
		next = ca->next;
		if (!strcasecmp(ca->channel, channel))
		{
			if (!strcasecmp(ca->nickname, nickname))
			{
				if (config->debug)
				{
					printf(
						"delCadmin(): %s [%p] found on %s [%p], removing.\n",
						ca->nickname, ca->nickname, ca->channel,
						ca->channel);
				}
				if (cadmin == ca)
				{
					cadmin = ca->next;
				}
				else
				{
					for (delete = cadmin; (delete->next != ca) &&
						delete; delete = delete->next);
					delete->next = ca->next;
				}
				free(ca->nickname);
				free(ca->channel);
				free(ca->password);
				free(ca);
				return;
			}
		}
		if (config->debug)
		{
			printf(
				"delCadmin(): %s on %s not found\n",
				channel, nickname);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//


