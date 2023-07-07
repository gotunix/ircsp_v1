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


