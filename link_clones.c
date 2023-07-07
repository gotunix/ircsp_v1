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

Clones	*addClone	 (char *, char *, char *);
Clones  *findClone       (char *);
Clones  *findClonebyUser (char *);
void	delClone	 (char *);

///////////////////////////////////////////////////////////////////////////////
//

Clones *
addClone (username,nickname,hostname)
char	*username;
char	*nickname;
char	*hostname;
{
	Clones	*C;
	int	mFail = 0, mPass = 0;

	C = (Clones *)calloc(1, sizeof(Clones));
	{
		if (!C)
		{
			if (config->debug)
			{
				printf(
					"addClone(): calloc of C failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addClone(): calloc of C [%p] passed.\n",
					C);
			}
			mPass++;
		}
	}
	C->username = (char *)calloc(1, 256);
	{
		if (!C->username)
		{
			if (config->debug)
			{
				printf(
					"addClone(): calloc of C->username failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addClone(): calloc of C->username [%p] passed.\n",
					C->username);
			}
			mPass++;
		}
	}
	C->nickname = (char *)calloc(1, 256);
	{
		if (!C->nickname)
		{
			if (config->debug)
			{
				printf(
					"addClone(): calloc of C->nickname failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addClone(): calloc of C->nickname [%p] passed.\n",
					C->nickname);
			}
			mPass++;
		}
	}
	C->hostname = (char *)calloc(1, 1024);
	{
		if (!C->hostname)
		{
			if (config->debug)
			{
				printf(
					"addClone(): calloc of C->hostname failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addClone(): calloc of C->hostname [%p] passed.\n",
					C->hostname);
			}
			mPass++;
		}
	}

	if (mFail)
	{
		if (config->debug)
		{
			printf(
				"addClone(): calloc(): %d fail, %d pass\n",
				mFail, mPass);
		}
		return NULL;
	}

	strcpy(C->username, username);
	strcpy(C->nickname, nickname);
	strcpy(C->hostname, hostname);

	if (config->debug)
	{
		printf(
			"addClone(): UN: %s    NN: %s    HN: %s\n",
			C->username, C->nickname, C->hostname);
	}

	if (!clone)
	{
		clone = C;
		C->next = NULL;
	}
	else
	{
		C->next = clone;
		clone = C;
	}
	return C;
}

///////////////////////////////////////////////////////////////////////////////
//

Clones *
findClone (nickname)
char	*nickname;
{
	Clones	*c;

	c = clone;
	while (c)
	{
		if (!strcasecmp(c->nickname, nickname))
		{
			if (config->debug)
			{
				printf(
					"findClone(): %s [%p] found.\n",
					c->nickname, c->nickname);
			}
			return c;
		}
		c = c->next;
	}
	if (config->debug)
	{
		printf(
			"findClone(): %s not found.\n",
			nickname);
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//

Clones *
findClonebyUser (username)
char	*username;
{
	Clones	*c;

	c = clone;
	while (c)
	{
		if (!strcasecmp(c->username, username))
		{
			if (config->debug)
			{
				printf(
					"findClonebyUser(): %s [%p] found.\n",
					c->username, c->username);
			}
			return c;
		}
		c = c->next;
	}
	if (config->debug)
	{
		printf(
			"findClonebyUser(): %s not found.\n",
			username);
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//

void
delClone (nickname)
char	*nickname;
{
	Clones	*c, *next, *delete;

	for (c = clone; c; c = next)
	{
		next = c->next;
		if (!strcasecmp(c->nickname, nickname))
		{
			if (config->debug)
			{
				printf(
					"delClone(): %s [%s] found, removing.\n",
					c->nickname, c->nickname);
			}
			if (clone == c)
			{
				clone = c->next;
			}
			else
			{
				for (delete = clone; (delete->next != c) && 
					delete; delete = delete->next);
				delete->next = c->next;
			}
			free(c->username);
			free(c->nickname);
			free(c->hostname);
			free(c);
			return;
		}
		if (config->debug)
		{
			printf(
				"delClone(): %s not found.\n",
				nickname);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//

