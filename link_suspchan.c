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

SuspChan *addSChan (char *, char *);
void delSChan (char *);

//////////////////////////////////////////////////////////////////////////////
//

SuspChan *
addSChan (channel,reason)
char	*channel;
char	*reason;
{
	SuspChan	*sc;
	int		mFail = 0, mPass = 0;

	sc = (SuspChan *)calloc(1, sizeof(SuspChan));
	{
		if (!sc)
		{
			if (config->debug)
			{
				printf(
					"addSChan(): calloc() of sc failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addSChan(): calloc() of sc [%p] passed.\n",
					sc);
			}
			mPass++;
		}
	}
	sc->channel = (char *)calloc(1, 256);
	{
		if (!sc->channel)
		{
			if (config->debug)
			{
				printf(
					"addSChan(): calloc() of sc->channel failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addSChan(): calloc() of sc->channel [%p] passed.\n",
					sc->channel);
			}
			mPass++;
		}
	}
	sc->reason  = (char *)calloc(1, 1024);
	{
		if (!sc->reason)
		{
			if (config->debug)
			{
				printf(
					"addSChan(): calloc() of sc->reason failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addSChan(): calloc() of sc->reason [%p] passed.\n",
					sc->reason);
			}
			mPass++;
		}
	}

	if (mFail)
	{
		if (config->debug)
		{
			printf(
				"addSChan(): calloc(): %d fail, %d pass\n",
				mFail, mPass);
		}
		return NULL;
	}

	strcpy(sc->channel, channel);
	strcpy(sc->reason,  reason);

	if (config->debug)
	{
		printf(
			"addSChan():  CHN: %s    RSN: %s\n",
			sc->channel, sc->reason);
	}

	send_to_sock(s, 
		":%s JOIN %s\n", 
		config->scnick, channel);

	send_to_sock(s, 
		"MODE %s +o %s\n", 
		channel, config->scnick);

	send_to_sock(s, 
		":%s MODE %s +tnsplk 11 11\n", 
		config->scnick, channel);

	send_to_sock(s, 
		":%s TOPIC %s :%s:%s\n", 
		config->scnick, channel, "Banned Channel", 
		reason);

	if (!suspchan)
	{
		suspchan = sc;
		sc->next = NULL;
	}
	else
	{
		sc = suspchan;
		suspchan = sc;
	}
	return sc;
}

//////////////////////////////////////////////////////////////////////////////
//

void
delSChan (channel)
char	*channel;
{
	SuspChan	*sc, *next, *delete;

	for (sc = suspchan; sc; sc = next)
	{
		next = sc->next;
		if (!strcasecmp(sc->channel, channel))
		{
			if (suspchan == sc)
			{
				suspchan = sc->next;
			}
			else
			{
				for (delete = suspchan; (delete->next != sc) &&
					delete; delete = delete->next);
				delete->next = sc->next;
			}
			free(sc->channel);
			free(sc->reason);
			free(sc);
			return;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//

SuspChan *
findSChan (channel)
char  *channel;
{
   SuspChan  *theChan;

   theChan = suspchan;
   while (theChan)
   {
      if (!strcasecmp(theChan->channel, channel))
      {
         return theChan;
      }
      theChan = theChan->next;
   }
   return NULL;
}

//////////////////////////////////////////////////////////////////////////////
//


