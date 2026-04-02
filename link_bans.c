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

Bans	*addBan			(char *, char *, char *, char *);
Bans	*findBan		(char *, char *);
void	delBan			(char *, char *);

///////////////////////////////////////////////////////////////////////////////
//

Bans *
addBan (chan,host,setby,bot)
char	*chan;
char	*host;
char	*setby;
char	*bot;
{
	Bans	*b;
	int	mFail = 0, mPass = 0;

	b = (Bans *)calloc(1, sizeof(Bans));
	{
		if (!b)
		{
			if (config->debug)
			{
				printf(
					"addBan(): calloc() of b failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addBan(): calloc() of b [%p] passed.\n",
					b);
			}
			mPass++;
		}
	}
	b->chan = (char *)calloc(1, 256);
	{
		if (!b->chan)
		{
			if (config->debug)
			{
				printf(
					"addBan(): calloc() of b->chan failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addBan(): calloc() of b->chan [%p] passed.\n",
					b->chan);
			}
			mPass++;
		}
	}
	b->host = (char *)calloc(1, 1024);
	{
		if (!b->host)
		{
			if (config->debug)
			{
				printf(
					"addBan(): calloc() of b->host failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addBan(): calloc() of b->host [%p] passed.\n",
					b->host);
			}
			mPass++;
		}
	}
	b->setby = (char *)calloc(1, 128);
	{
		if (!b->setby)
		{
			if (config->debug)
			{
				printf(
					"addBan(): calloc() of b->setby failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addBan(): calloc() of b->setby [%p] passed.\n",
					b->setby);
			}
			mPass++;
		}
	}

	if (mFail)
	{
		if (config->debug)
		{
			printf(
				"addBan(): %d Fail, %d Pass\n",
				mFail, mPass);
		}
		return NULL;
	}

	strcpy(b->chan, chan);
	strcpy(b->host, host);
	strcpy(b->setby, setby);

	if (config->debug)
	{
		printf(
			"addBan(): CHN: %s   HST: %s   SBY: %s\n",
			b->chan, b->host, b->setby);
	}

	send_to_sock(s, 
		":%s MODE %s +b %s\n", 
		bot, chan, host);

	if (!bans)
	{
		bans = b;
		b->next = NULL;
	}
	else
	{
		b->next = bans;
		bans = b;
	}
	return b;
}

///////////////////////////////////////////////////////////////////////////////
//

Bans *
findBan (chan,host)
char	*chan;
char	*host;
{
	Bans	*b;

	b = bans;
	while (b)
	{
		if (!strcasecmp(b->chan, chan))
		{
			if (!strcasecmp(b->host, host))
			{
				if (config->debug)
				{
					printf(
						"findBan(): %s [%p] found on %s [%p].\n",
						b->host, b->host, b->chan, b->chan);
				}
				return b;
			}
		}
		b = b->next;
	}
	if (config->debug)
	{
		printf(
			"findBan(): %s on %s not found.\n",
			host, chan);
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//

void
delBan (chan,host)
char	*chan;
char	*host;
{
	Bans	*b, *next, *delete;

	for (b = bans; b; b = next)
	{
		next = b->next;
		if (!strcasecmp(b->chan, chan))
		{
			if (!strcasecmp(b->host, host))
			{
				if (config->debug)
				{
					printf(
						"delBan(): %s [%p] found on %s [%p], removing.\n",
						b->host, b->host, b->chan, b->chan);
				}
				if (bans == b)
				{
					bans = b->next;
				}
				else
				{
					for (delete = bans; (delete->next != b) &&
						delete; delete = delete->next);
					delete->next = b->next;
				}
				free(b->host);
				free(b->chan);
				free(b->setby);
				free(b);
				return;
			}
		}
		if (config->debug)
		{
			printf(
				"delBan(): %s on %s no found.\n",
				host, chan);
		}
	}
}
 
///////////////////////////////////////////////////////////////////////////////
//


