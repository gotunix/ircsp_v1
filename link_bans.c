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


