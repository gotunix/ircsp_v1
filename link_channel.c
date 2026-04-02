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

ChanDB	*addChan		(char *, char *, char *, char *);
ChanDB	*findChan		(char *);
void	delChan			(char *);

///////////////////////////////////////////////////////////////////////////////
//

ChanDB *addChan (channel,topic,modes,bot)
char	*channel;
char	*topic;
char	*modes;
char	*bot;
{
	ChanDB	*cs;
	int	mFail = 0, mPass = 0;

	cs = (ChanDB *)calloc(1, sizeof(ChanDB));
	{
		if (!cs)
		{
			if (config->debug)
			{
				printf(
					"addChan(): calloc() of cs failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addChan(): calloc() of cs [%p] passed.\n",
					cs);
			}
			mPass++;
		}
	}
	cs->channel = (char *)calloc(1, 256);
	{
		if (!cs->channel)
		{
			if (config->debug)
			{
				printf(
					"addChan(): calloc() of cs->channel failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addChan(): calloc() of cs->channel [%p] passed.\n",
					cs->channel);
			}
			mPass++;
		} 
	}
	cs->modes = (char *)calloc(1, 64);
	{
		if (!cs->modes)
		{
			if (config->debug)
			{
				printf(
					"addChan(): calloc() of cs->modes failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addChan(): calloc() of cs->modes [%p] passed.\n",
					cs->modes);
			}
			mPass++;
		}
	}
	cs->bot = (char *)calloc(1, 256);
	{
		if (!cs->bot)
		{
			if (config->debug)
			{
				printf(
					"addChan(): calloc() of cs->bot failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addChan(): calloc() of cs->bot [%p] passed.\n",
					cs->channel);
			}
		}
	}
	cs->topic = (char *)calloc(1, 4094);
	{
		if (!cs->topic)
		{
			if (config->debug)
			{
				printf(
					"addChan(): calloc() of cs->topic failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addChan(): calloc() of cs->topic [%p] passed.\n",
					cs->topic);
			}
			mPass++;
		}
	}

	if (mFail)
	{
		if (config->debug)
		{
			printf(
				"addChan(): calloc() %d fail, %d pass\n",
				mFail, mPass);
		}
		return NULL;
	}

	strcpy(cs->channel, channel);
	strcpy(cs->modes, modes);
	strcpy(cs->bot, bot);
	strcpy(cs->topic, topic);

	if (config->debug)
	{
		printf(
			"addChan(): CHN: %s    MDS: %s   BOT: %s   TOP: %s\n",
			cs->channel, cs->modes, cs->bot, cs->topic);
	}

	send_to_sock(s, 
		":%s JOIN %s\n", 
		bot, channel);

	send_to_sock(s, 
		"MODE %s +o %s\n", 
		channel, bot);

	send_to_sock(s, 
		":%s MODE %s %s\n", 
		bot, channel, modes);

	send_to_sock(s, 
		":%s TOPIC %s :%s\n",
		bot, channel, topic);

	if (!chandb)
	{
		chandb = cs;
		cs->next = NULL;
	}
	else
	{
		cs->next = chandb;
		chandb = cs;
	}
	return cs;
}

///////////////////////////////////////////////////////////////////////////////
//

ChanDB *
findChan (chan)
char	*chan;
{
	ChanDB	*cs;

	cs = chandb;
	while (cs)
	{
		if (!strcasecmp(cs->channel, chan))
		{
			if (config->debug)
			{
				printf(
					"findChan(): %s [%p] found.\n", 
					cs->channel, cs->channel);
			}
			return cs;
		}
		cs = cs->next;
	}
	if (config->debug)
	{
		printf(
			"findChan(): %s not found.\n",
			chan);
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//

void
delChan (chan)
char	*chan;
{
	ChanDB	*cs, *next, *delete;

	for (cs = chandb; cs; cs = next)
	{
		next = cs->next;
		if (!strcasecmp(cs->channel, chan))
		{
			if (config->debug)
			{
				printf(
					"delChan(): %s [%p] found, removing.\n",
					cs->channel, cs->channel);
			}
			if (chandb == cs)
			{
				chandb = cs->next;
			}
			else
			{
				for (delete = chandb; (delete->next != cs) &&
					delete; delete = delete->next);
				delete->next = cs->next;
			}
			free(cs->channel);
			free(cs->password);
			free(cs->topic);
			free(cs->modes);
			free(cs->bot);
			free(cs);
			return;
		}
		if (config->debug)
		{
			printf(
				"delChan(): %s not found.\n",
				chan);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//


