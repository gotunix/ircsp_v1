///////////////////////////////////////////////////////////////////////////////
//		  IRCSP - Internet Realy Chat Services Package
//                  Copyright (C) 2000 Lostworld Development
//          Written By: Justin Ovens [evilicey] [ice95@lostworld.net]
//
//   This program, documentation, and everything included in this
//   package are Copyright (C) 2000 Lostworld Development. You may
//   not use this program in any way sharp or form with out 
//   the Lostworld Developers expresss written consent.
//
//   This program is not gnu puclic license and is not freeware.
//   Possession with out permission, license, is strictly
//   prohibited.  You may purchace this program (Biniary), and
//   a license from our web page [www.lostworld.net].
//
//   The authors of this program are in no way liable for any
//   consequences or damages, suffered by you or anyone else,
//   arising out of the use or inablility to use this program.
//
//   Author Contact information: ice95@lostworld.net
///////////////////////////////////////////////////////////////////////////////

#include "services.h"

Admin *addAdmin (char *, int, char *, int, int, char *);
Admin *findAdmin (char *);
void delAdmin (char *);

//////////////////////////////////////////////////////////////////////////////
//

Admin *
addAdmin (nickname,level,hostname,flags,susp,password)
char  *nickname;
int   level;
char  *hostname;
int   flags;
int   susp;
char  *password;
{
	Admin *new;
	int mPass = 0, mFail = 0;
	new = (Admin *)calloc(1, sizeof(Admin));
	{
		if (!new)
		{
#ifdef DEBUG
			{
				printf(
					"addAdmin(): calloc() of new failed.\n");
			}
#endif
			mFail++;
		}
		else
		{
#ifdef DEBUG
			{
				printf(
					"addAdmin(): calloc() of new passed [%p].\n",
					new);
			}
#endif
			mPass++;
		}
	}
	new->nickname = (char *)calloc(1, 64);
	{
		if (!new->nickname)
		{
#ifdef DEBUG
			{
				printf(
					"addAdmin(): calloc() of new->nickname failed.\n");
			}
#endif
		}
		else
		{
#ifdef DEBUG
			{
				printf(
					"addAdmin(): calloc() of new->nickname passed [%p].\n",
					new->nickname);
			}
#endif
		}
	}
	new->hostname = (char *)calloc(1, 1024);
	{
		if (!new->hostname)
		{
#ifdef DEBUG
			{
				printf(
					"addAdmin(): calloc() of new->hostname failed.\n");
			}
#endif
		}
		else
		{
#ifdef DEBUG
			{
				printf(
					"addAdmin(): calloc() of new->hostname passed [%p].\n",
					new->hostname);
			}
#endif
		}
	}
	new->password = (char *)calloc(1, 256);
	{
		if (!new->password)
		{
#ifdef DEBUG
			{
				printf(
					"addAdmin(): calloc() of new->password failed.\n");
			}
#endif
		}
		else
		{
#ifdef DEBUG
			{
				printf(
					"addAdmin(): calloc() of new->password [%p].\n",
					new->password);
			}
#endif
		}
	}
	if (mFail)
	{
#ifdef DEBUG
		{
			printf(
				"addAdmin(): %d pass, %d fail\n",
				mPass, mFail);
		}
#endif
		return NULL;
	}
	strcpy(new->nickname, nickname);
	strcpy(new->hostname, hostname);
	strcpy(new->password, password);

	new->level = level;
	new->flags = flags;
	new->susp  = susp;

#ifdef DEBUG
	{
		printf(
			"addAdmin(): NN: %s   HN: %s   PW: %s   LVL: %d   FLG: %d  SUSP: %d\n",
			new->nickname, new->hostname, new->password, new->level,
			new->flags, new->susp);
	}
#endif

	if (!admin)
	{
		admin = new;
		new->next = NULL;
	}
	else
	{
		new->next = admin;
		admin = new;
	}
	return new;
}

//////////////////////////////////////////////////////////////////////////////
//

Admin *
findAdmin (nickname)
char  *nickname;
{
	Admin *temp;
	temp = admin;
	while (temp)
	{
		if (!strcasecmp(temp->nickname, nickname))
		{
#ifdef DEBUG
			{
				printf(
					"findAdmin(): %s found.\n", nickname);
			}
#endif
			return temp;
		}
		temp = temp->next;
	}
#ifdef DEBUG
	{
		printf(
			"findAdmin(): %s not found.\n", nickname);
	}
#endif
	return NULL;
}

//////////////////////////////////////////////////////////////////////////////
//

void
delAdmin (nickname)
char  *nickname;
{
	Admin *temp, *next, *delete;
	for (temp = admin; temp; temp = next)
	{
		next = temp->next;
		if (!strcasecmp(temp->nickname, nickname))
		{
#ifdef DEBUG
			{
				printf(
					"delAdmin(): %s found, deleting.\n",
					nickname);
			}
#endif
			if (admin == temp)
			{
				admin = temp->next;
			}
			else
			{
				for (delete = admin; (delete->next != temp) && delete;
					delete = delete->next)
					;
				delete->next = temp->next;
			}
			free(temp->nickname);
			free(temp->hostname);
			free(temp->password);
			free(temp);
			return;
		}
#ifdef DEBUG
		{
			printf(
				"delAdmin(): %s not found, unable to delete.\n",
				nickname);
		}
#endif
	}
}
