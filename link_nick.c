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

nickservDB	*NSAddNick		(char *, char *, int, int);
nickservDB	*NSFindNick		(char *);
void		NSDelNick		(char *);

/////////////////////////////////////////////////////////////////////////////
//

nickservDB *
NSAddNick (nickname, password, flags, killprot)
char	*nickname;
char	*password;
int	flags;
int	killprot;
{
	nickservDB	*ns;
	int		mFail = 0, mPass = 0;

	ns = (nickservDB *)calloc(1,sizeof(nickservDB));
	{
		if (!ns)
		{
			if (config->debug)
			{
				printf(
					"AddNSNick(): calloc() of ns failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"AddNSNick(): calloc() of ns [%p] passed.\n",
					ns);
			}
		}
	}
	ns->nickname = (char *)calloc(1, 64);
	{
		if (!ns->nickname)
		{
			if (config->debug)
			{
				printf(
					"AddNSNick(): calloc() of ns->nickname failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"AddNSNick(): calloc() of ns->nickname [%p] passed.\n",
					ns->nickname);
			}
		}
	}
	ns->password = (char *)calloc(1, 256);
	{
		if (!ns->password)
		{
			if (config->debug)
			{
				printf(
					"AddNSNick(): calloc() of ns->passowrd failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"AddNSNick(): calloc() of ns->password [%p] passed.\n",
					ns->password);
			}
		}
	}

	if (mFail)
	{
		return NULL;
	}

	strcpy(ns->nickname, nickname);
	strcpy(ns->password, password);

	ns->authed = flags;
	ns->killprot = killprot;

	if (mFail)
	{
		if (config->debug)
		{
			printf(
				"AddNSNick(): calloc() %d fail, %d pass\n",
				mFail, mPass);
		}
		return NULL;
	}

	if (!nickservdb)
	{
		nickservdb = ns;
		ns->next = NULL;
	}
	else
	{
		ns->next = nickservdb;
		nickservdb = ns;
	}
	return ns;
}

/////////////////////////////////////////////////////////////////////////////
//

nickservDB *
NSFindNick (nickname)
char	*nickname;
{
	nickservDB	*ns;

	ns = nickservdb;
	while (ns)
	{
		if (!strcasecmp(ns->nickname, nickname))
		{
			if (config->debug)
			{
				printf(
					"NSFindNick(): %s [%p] found.\n",
					ns->nickname, ns->nickname);
			}
			return ns;
		}
		ns = ns->next;
	}
	if (config->debug)
	{
		printf(
			"NSFindNick(): %s not found.\n",
			nickname);
	}
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
//

void NSdelNick (nickname)
char	*nickname;
{
	nickservDB	*ns, *next, *delete;

	for (ns = nickservdb; ns; ns = next)
	{
		next = ns->next;
		if (!strcasecmp(ns->nickname, nickname))
		{
			if (nickservdb == ns)
			{
				nickservdb = ns->next;
			}
			else
			{
				for (delete = nickservdb; (delete->next != ns) &&
					delete; delete = delete->next);
				delete->next = ns->next;
			}
			free(ns->nickname);
			free(ns->password);
			free(ns);
			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
//


