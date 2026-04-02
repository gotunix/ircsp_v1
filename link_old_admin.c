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

Admin	*addAdmin		(char *, int, char *, int, int, char *);
Admin	*findAdmin		(char *);
void	delAdmin		(char *);

//////////////////////////////////////////////////////////////////////////////
//

Admin *
addAdmin (nickname,level,hostname,flags,susp,password)
char	*nickname;
int	level;
char	*hostname;
int	flags;
int	susp;
char	*password;
{
	Admin	*newAdmin;
	int	mFail = 0, mPass = 0;

	newAdmin = (Admin *)calloc(1, sizeof(Admin));
	{
		if (!newAdmin)
		{
			if (config->debug)
			{
				printf(
					"addAdmin(): calloc() of newAdmin failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addAdmin(): calloc() of newAdmin [%p] passed.\n",
					newAdmin);
			}
			mPass++;
		}
	}	
	newAdmin->nickname = (char *)calloc(1, 64);
	{
		if (!newAdmin->nickname)
		{
			if (config->debug)
			{
				printf(
					"addAdmin(): calloc() of newAdmin->nickname failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addAdmin(): calloc() of newAdmin->nickname [%p] passed.\n",
					newAdmin->nickname);
			}
			mPass++;
		}
	}
	newAdmin->hostname = (char *)calloc(1, 1024);
	{
		if (!newAdmin->hostname)
		{
			if (config->debug)
			{
				printf(
					"addAdmin(): calloc() of newAdmin->hostname failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addAdmin(): calloc() of newAdmin->hostname [%p] passed.\n",
					newAdmin->hostname);
			}
			mPass++;
		}
	}
	newAdmin->password = (char *)calloc(1, 256);
	{
		if (!newAdmin->password)
		{
			if (config->debug)
			{
				printf(
					"addAdmin(): calloc() of newAdmin->password failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addAdmin(): calloc() of newAdmin->password [%p] passed.\n",
					newAdmin->password);
			}
			mPass++;
		}
	}

	if (mFail)
	{
		if (config->debug)
		{
			printf(
				"addAdmin(): %d Fail, %d Pass\n",
				mFail, mPass);
		}
		return NULL;
	}

	strcpy(newAdmin->nickname, nickname);
	strcpy(newAdmin->hostname, hostname);
	strcpy(newAdmin->password, password);

	newAdmin->level = level;
	newAdmin->flags = flags;
	newAdmin->susp  = susp;

	if (config->debug)
	{
		printf(
			"addAdmin(): %s (%s) [%s] ... [%d] %d - %d\n",
			newAdmin->nickname, newAdmin->hostname, 
			newAdmin->password, newAdmin->level, 
			newAdmin->flags, newAdmin->susp);
	}

	if (!admin)
	{
		admin = newAdmin;
		newAdmin->next = NULL;
	}
	else
	{
		newAdmin->next = admin;
		admin = newAdmin;
	}
	return newAdmin;
}

//////////////////////////////////////////////////////////////////////////////
//

Admin *
findAdmin (nickname)
char	*nickname;
{
	Admin	*a;

	a = admin;
	while (a)
	{
		if (!strcasecmp(a->nickname, nickname))
		{
			if (config->debug)
			{
				printf(
					"findAdmin(): %s [%p] found.\n",
					a->nickname, a->nickname);
			}
			return a;
		}
		a = a->next;
	}
	if (config->debug)
	{
		printf(
			"findAdmin(): %s not found.\n",
			nickname);
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////////////
//

void
delAdmin (nickname)
char	*nickname;
{
	Admin	*a, *next, *delete;

	for (a = admin; a; a = next)
	{
		next = a->next;
		if (!strcasecmp(a->nickname, nickname))
		{
			if (config->debug)
			{
				printf(
					"delAdmin(): %s [%p] found, removing.\n",
					a->nickname, a->nickname);
			}
			if (admin == a)
			{
				admin = a->next;
			}
			else
			{
				for (delete = admin; (delete->next != a) && delete;
					delete = delete->next);
				delete->next = a->next;
			}
			free(a->nickname);
			free(a->hostname);
			free(a->password);
			free(a);
			return;
		}
		if (config->debug)
		{
			printf(
				"delAdmin(): %s not found.\n",
				nickname);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//

