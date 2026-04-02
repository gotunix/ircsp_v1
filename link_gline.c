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

struct	aGline	*addGline		(char *, time_t, time_t, char *);
struct	aGline	*findGline		(char *);
void		rem_gline		(char *);

//////////////////////////////////////////////////////////////////////////////
//

struct aGline *
addGline (userhost,when,expire,reason)
char	*userhost;
time_t	when;
time_t	expire;
char	*reason;
{
	struct	aGline	*g;
	int	mFail = 0, mPass = 0;

	g = (struct aGline *)calloc(1,sizeof(struct aGline));
	{
		if (!g)
		{
			if (config->debug)
			{
				printf(
					"addGline(): calloc() of g failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addGline(): calloc() of g [%p] passed.\n",
					g);
			}
		}
		
	}
	g->userhost = (char *)calloc(1, 1024);
	{
		if (!g->userhost)
		{
			if (config->debug)
			{
				printf(
					"addGline(): calloc() of g->userhost failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addGline(): calloc() of g->userhost [%p] passed.\n",
					g->userhost);
			}
		}
		
	}
	g->reason   = (char *)calloc(1, 1024);
	{
		if (!g->reason)
		{
			if (config->debug)
			{
				printf(
					"addGline(): calloc() of g->reason failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addGline(): calloc() of g->reason [%p] passed.\n",
					g->reason);
			}
		}
		
	}

	if (mFail)
	{
		if (config->debug)
		{
			printf(
				"addGline(): calloc(): %d fail, %d pass\n",
				mFail, mPass);
		}
		return NULL;
	}

	strcpy(g->userhost, userhost);
	strcpy(g->reason, reason);

	g->when = when;
	g->expire = expire;

	if (config->debug)
	{
		printf(
			"addGline(): UH: %s    RSN: %s    TME: %lu EXP: %lu\n",
			g->userhost, g->reason, g->when, g->expire);
	}

	send_to_sock(s, 
		"GLINE * +%s %lu :Banned (Glined) -- %s\n",
		g->userhost, g->expire, g->reason);

	if (!gline)
	{
		gline = g;
		g->next = NULL;
	}
	else
	{
		g->next = gline;
		gline = g;
	}
	return g;
}

//////////////////////////////////////////////////////////////////////////////
//

struct aGline *
findGline (userhost)
char   *userhost;
{
	struct	aGline	*g;

	g = gline;
	while (g)
	{
		if (!strcasecmp(g->userhost, userhost))
		{
			if (config->debug)
			{
				printf(
					"findGline(): %s [%p] found.\n",
					g->userhost, g->userhost);
			}
			return g;
		}
		g = g->next;
	}
	if (config->debug)
	{
		printf(
			"findGline(): %s not found\n",
			userhost);
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////////////
//

void 
rem_gline (mask) 
char  *mask;
{
	struct	aGline	*g, *next, *delete;

	for (g = gline; g; g = next)
	{
		next = g->next;
		if (!strcasecmp(g->userhost, mask)) 
		{
			if (config->debug)
			{
				printf(
					"rem_gline(): %s [%p] found, removing.\n",
					g->userhost, g->userhost);
			}
			if (gline == g) 
			{
				gline = g->next;
			}
			else
			{
				for (delete = gline; (delete->next != g) && 
					delete; delete = delete->next);
				delete->next = g->next;
			}
			free(g->userhost);
			free(g->reason);
			free(g);
			return;
		}
		if (config->debug)
		{
			printf(
				"rem_gline(): %s not found.\n",
				mask);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//


