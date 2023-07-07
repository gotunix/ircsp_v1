/* ---------------------------------------------------------------------------
 * Copyright (c) GOTUNIX Networks
 * Copyright (c) GOTUNIXCODE
 * Copyright (c) Justin Ovens
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ---------------------------------------------------------------------------
 */

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


