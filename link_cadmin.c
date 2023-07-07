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

Cadmin	*addCadmin		(char *, char *, char *, int, int);
Cadmin	*findCadmin		(char *, char *);
Cadmin	*findCadmin_nick	(char *);
void	delCadmin		(char *, char *);

///////////////////////////////////////////////////////////////////////////////
//

Cadmin *
addCadmin (nickname,password,channel,flags,level)
char	*nickname;
char	*password;
char	*channel;
int	flags;
int	level;
{
	Cadmin	*ca;
	int	mFail = 0, mPass = 0;

	ca = (Cadmin *)calloc(1, sizeof(Cadmin));
	{
		if (!ca)
		{
			if (config->debug)
			{
				printf(
					"addCadmin(): calloc() of ca failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addCadmin(): calloc() of ca [%p] passed.\n",
					ca);
			}
			mPass++;
		}
	}
	ca->nickname = (char *)calloc(1, 64);
	{
		if (!ca->nickname)
		{
			if (config->debug)
			{
				printf(
					"addCadmin(): calloc() of ca->nickname failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug) 
			{
				printf(
					"addCadmin(): calloc() of ca->nickname [%p] passed.\n",
					ca->nickname);
			}
			mPass++;
		}
	}
	ca->password = (char *)calloc(1, 256);
	{
		if (!ca->password)
		{
			if (config->debug)
			{
				printf(
					"addCadmin(): calloc() of ca->password failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug) 
			{
				printf(
					"addCadmin(): calloc() of ca->password [%p] passed.\n",
					ca->password);
			}
			mPass++;
		}
	}
	ca->channel = (char *)calloc(1, 256);
	{
		if (!ca->channel)
		{
			if (config->debug)
			{
				printf(
					"addCadmin(): calloc() of ca->channel failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug) 
			{
				printf(
					"addCadmin(): calloc() of ca->channel [%p] passed.\n",
					ca->channel);
			}
			mPass++;
		}
	}

	if (mFail)
	{
		if (config->debug)
		{
			printf(
				"addCadmin(): calloc() %d fail, %d pass\n",
				mFail, mPass);
		}
		return NULL;
	}

	strcpy(ca->nickname, nickname);
	strcpy(ca->password, password);
	strcpy(ca->channel, channel);

	ca->flags = flags;
	ca->level = level;

	if (!cadmin)
	{
		cadmin = ca;
		ca->next = NULL;
	}
	else
	{
		ca->next = cadmin;
		cadmin = ca;
	}
	return ca;
}

///////////////////////////////////////////////////////////////////////////////
//

Cadmin *
findCadmin (channel,nickname)
char	*channel;
char	*nickname;
{
	Cadmin	*ca;

	ca = cadmin;
	while (ca)
	{
		if (!strcasecmp(ca->channel, channel))
		{
			if (!strcasecmp(ca->nickname, nickname))
			{
				if (config->debug)
				{
					printf(
						"findCadmin(): %s [%p] found on %s [%p]\n",
						ca->nickname, ca->nickname, ca->channel,
						ca->channel);
				}
				return ca;
			}
		}
		ca = ca->next;
	}
	if (config->debug)
	{
		printf(
			"findCadmin(): %s not found on %s\n",
			ca->nickname, ca->channel);
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//

Cadmin *
findCadmin_nick (nick)
char	*nick;
{
	Cadmin	*ca;

	ca = cadmin;
	while (ca)
	{
		if (!strcasecmp(ca->nickname, nick))
		{
			if (config->debug)
			{
				printf(
					"findCadmin_nick(): %s [%p] found.\n",
					ca->nickname, ca->nickname);
			}
			return ca;
		}
		ca = ca->next;
	}
	if (config->debug)
	{
		printf(
			"findCadmin_nick(): %s not found.\n",
			ca->nickname);
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//

void
delCadmin (channel,nickname)
char	*channel;
char	*nickname;
{
	Cadmin	*ca, *next, *delete;

	for (ca = cadmin; ca; ca = next)
	{
		next = ca->next;
		if (!strcasecmp(ca->channel, channel))
		{
			if (!strcasecmp(ca->nickname, nickname))
			{
				if (config->debug)
				{
					printf(
						"delCadmin(): %s [%p] found on %s [%p], removing.\n",
						ca->nickname, ca->nickname, ca->channel,
						ca->channel);
				}
				if (cadmin == ca)
				{
					cadmin = ca->next;
				}
				else
				{
					for (delete = cadmin; (delete->next != ca) &&
						delete; delete = delete->next);
					delete->next = ca->next;
				}
				free(ca->nickname);
				free(ca->channel);
				free(ca->password);
				free(ca);
				return;
			}
		}
		if (config->debug)
		{
			printf(
				"delCadmin(): %s on %s not found\n",
				channel, nickname);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//


