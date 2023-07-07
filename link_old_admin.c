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

Admin	*addAdmin		(char *, int, char *, int, int, char *);
Admin	*findAdmin		(char *);
void	delAdmin		(char *);

//////////////////////////////////////////////////////////////////////////////
//

Admin *
addAdmin (nickname,level,hostname,flags,susp,password)
char	*nickname;
int	level;
char	*hostname;
int	flags;
int	susp;
char	*password;
{
	Admin	*newAdmin;
	int	mFail = 0, mPass = 0;

	newAdmin = (Admin *)calloc(1, sizeof(Admin));
	{
		if (!newAdmin)
		{
			if (config->debug)
			{
				printf(
					"addAdmin(): calloc() of newAdmin failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addAdmin(): calloc() of newAdmin [%p] passed.\n",
					newAdmin);
			}
			mPass++;
		}
	}	
	newAdmin->nickname = (char *)calloc(1, 64);
	{
		if (!newAdmin->nickname)
		{
			if (config->debug)
			{
				printf(
					"addAdmin(): calloc() of newAdmin->nickname failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addAdmin(): calloc() of newAdmin->nickname [%p] passed.\n",
					newAdmin->nickname);
			}
			mPass++;
		}
	}
	newAdmin->hostname = (char *)calloc(1, 1024);
	{
		if (!newAdmin->hostname)
		{
			if (config->debug)
			{
				printf(
					"addAdmin(): calloc() of newAdmin->hostname failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addAdmin(): calloc() of newAdmin->hostname [%p] passed.\n",
					newAdmin->hostname);
			}
			mPass++;
		}
	}
	newAdmin->password = (char *)calloc(1, 256);
	{
		if (!newAdmin->password)
		{
			if (config->debug)
			{
				printf(
					"addAdmin(): calloc() of newAdmin->password failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addAdmin(): calloc() of newAdmin->password [%p] passed.\n",
					newAdmin->password);
			}
			mPass++;
		}
	}

	if (mFail)
	{
		if (config->debug)
		{
			printf(
				"addAdmin(): %d Fail, %d Pass\n",
				mFail, mPass);
		}
		return NULL;
	}

	strcpy(newAdmin->nickname, nickname);
	strcpy(newAdmin->hostname, hostname);
	strcpy(newAdmin->password, password);

	newAdmin->level = level;
	newAdmin->flags = flags;
	newAdmin->susp  = susp;

	if (config->debug)
	{
		printf(
			"addAdmin(): %s (%s) [%s] ... [%d] %d - %d\n",
			newAdmin->nickname, newAdmin->hostname, 
			newAdmin->password, newAdmin->level, 
			newAdmin->flags, newAdmin->susp);
	}

	if (!admin)
	{
		admin = newAdmin;
		newAdmin->next = NULL;
	}
	else
	{
		newAdmin->next = admin;
		admin = newAdmin;
	}
	return newAdmin;
}

//////////////////////////////////////////////////////////////////////////////
//

Admin *
findAdmin (nickname)
char	*nickname;
{
	Admin	*a;

	a = admin;
	while (a)
	{
		if (!strcasecmp(a->nickname, nickname))
		{
			if (config->debug)
			{
				printf(
					"findAdmin(): %s [%p] found.\n",
					a->nickname, a->nickname);
			}
			return a;
		}
		a = a->next;
	}
	if (config->debug)
	{
		printf(
			"findAdmin(): %s not found.\n",
			nickname);
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////////////
//

void
delAdmin (nickname)
char	*nickname;
{
	Admin	*a, *next, *delete;

	for (a = admin; a; a = next)
	{
		next = a->next;
		if (!strcasecmp(a->nickname, nickname))
		{
			if (config->debug)
			{
				printf(
					"delAdmin(): %s [%p] found, removing.\n",
					a->nickname, a->nickname);
			}
			if (admin == a)
			{
				admin = a->next;
			}
			else
			{
				for (delete = admin; (delete->next != a) && delete;
					delete = delete->next);
				delete->next = a->next;
			}
			free(a->nickname);
			free(a->hostname);
			free(a->password);
			free(a);
			return;
		}
		if (config->debug)
		{
			printf(
				"delAdmin(): %s not found.\n",
				nickname);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//

