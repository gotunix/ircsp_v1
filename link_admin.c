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

Admin *addAdmin (char *, int, char *, int, int, char *);
Admin *findAdmin (char *);
void delAdmin (char *);

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
