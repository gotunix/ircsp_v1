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


Nick	*addNick			(char *, char *, char *, char *, \
					 int, time_t);
Nick	*findNick			(char *);
Nick	*findNickbyHost			(char *);
void	delNick				(char *);

///////////////////////////////////////////////////////////////////////////////
//

Nick *
addNick (nickname,userhost,server,realname,flags,ConnTime)
char	*nickname;
char	*userhost;
char	*server;
char	*realname;
int	flags;
time_t	ConnTime;
{
	Nick	*n;
	int	mFail = 0, mPass = 0;

	n = (Nick *)calloc(1, sizeof(Nick));
	{
		if (!n)
		{
			if (config->debug)
			{
				printf(
					"addNick(): calloc() of n failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addNick(): calloc() of n [%p] passed.\n",
					n);
			}
			mPass++;
		}
	}
	n->nickname = (char *)calloc(1, 64);
	{
		if (!n->nickname)
		{
			if (config->debug)
			{
				printf(
					"addNick(): calloc() of n->nickname failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addNick(): calloc() of n->nickname [%p] passed.\n",
					n->nickname);
			}
			mPass++;
		}
	}
	n->userhost = (char *)calloc(1, 1024);
	{
		if (!n->userhost)
		{
			if (config->debug)
			{
				printf(
					"addNick(): calloc() of n->userhost failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addNick(): calloc() of n->userhost [%p] passed.\n",
					n->userhost);
			}
			mPass++;
		}
	}
	n->server   = (char *)calloc(1, 1024);
	{
		if (!n->server)
		{
			if (config->debug)
			{
				printf(
					"addNick(): calloc() of n->server failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addNick(): calloc() of n->server [%p] passed.\n",
					n->server);
			}
			mPass++;
		}
	}
	n->realname = (char *)calloc(1, 512);
	{
		if (!n->realname)
		{
			if (config->debug)
			{
				printf(
					"addNick(): calloc() of n->realname failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addNick(): calloc() of n->realname [%p] passed.\n",
					n->realname);
			}
			mPass++;
		}
	}

	if (mFail)
	{
		if (config->debug)
		{
			printf(
				"addNick(): calloc(): %d fail, %d pass\n",
				mFail, mPass);
		}
		return NULL;
	}

	strcpy(n->nickname, nickname);
	strcpy(n->userhost, userhost);
	strcpy(n->server,   server);
	strcpy(n->realname, realname);

	n->flags = flags;
	n->ConnTime = ConnTime;

	if (config->debug)
	{
		printf(
			"addNick(): NN: %s    UH: %s    SRV: %s   RN: %s   FLG: %d   CT: %lu\n",
			n->nickname, n->userhost, n->server, n->realname,
			n->flags, n->ConnTime);
	}

	if (!nick)
	{
		nick = n;
		n->next = NULL;
	}
	else
	{
		n->next = nick;
		nick = n;
	}
	return n;
}

///////////////////////////////////////////////////////////////////////////////
//

Nick *
findNick(nickname)
char	*nickname;
{
	Nick	*n;

	n = nick;
	while (n)
	{
		if (!strcasecmp(n->nickname, nickname))
		{
			if (config->debug)
			{
				printf(
					"findNick(): %s [%p] found.\n",
					n->nickname, n->nickname);
			}

			return n;
		}
		n = n->next;
	}
	if (config->debug)
	{
		printf(
			"findNick(): %s not found.\n",
			nickname);
	}

	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//

Nick *
findNickbyHost (hostname)
char	*hostname;
{
	Nick	*n;
	n = nick;

	while (n)
	{
		if (!strcasecmp(n->userhost, hostname))
		{
			if (config->debug)
			{
				printf(
					"findNickbyHost(): %s [%p] found %s [%p].\n",
					n->userhost, n->userhost,
					n->nickname, n->nickname);
			}

			return n;
		}
		n = n->next;
	}
	if (config->debug)
	{
		printf(
			"findNickbyHost(): %s not found.\n",
			hostname);
	}

	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//

void
delNick (nickname) 
char	*nickname;
{
	Nick	*n, *next, *delete;

	for (n = nick; n; n = next)
	{
		next = n->next;
		if (!strcasecmp(n->nickname, nickname)) 
		{
			if (nick == n) 
			{
				nick = n->next;
			}
			else 
			{
				for (delete = nick; (delete->next != n) && 
					delete; delete = delete->next);
				delete->next = n->next;
			}
			free(n->nickname);
			free(n->userhost);
			free(n->server);
			free(n->realname);
			free(n->mode);
			free(n);
			return;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//


