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

nickservDB	*NSAddNick		(char *, char *, int, int);
nickservDB	*NSFindNick		(char *);
void		NSDelNick		(char *);

/////////////////////////////////////////////////////////////////////////////
//

nickservDB *
NSAddNick (nickname, password, flags, killprot)
char	*nickname;
char	*password;
int	flags;
int	killprot;
{
	nickservDB	*ns;
	int		mFail = 0, mPass = 0;

	ns = (nickservDB *)calloc(1,sizeof(nickservDB));
	{
		if (!ns)
		{
			if (config->debug)
			{
				printf(
					"AddNSNick(): calloc() of ns failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"AddNSNick(): calloc() of ns [%p] passed.\n",
					ns);
			}
		}
	}
	ns->nickname = (char *)calloc(1, 64);
	{
		if (!ns->nickname)
		{
			if (config->debug)
			{
				printf(
					"AddNSNick(): calloc() of ns->nickname failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"AddNSNick(): calloc() of ns->nickname [%p] passed.\n",
					ns->nickname);
			}
		}
	}
	ns->password = (char *)calloc(1, 256);
	{
		if (!ns->password)
		{
			if (config->debug)
			{
				printf(
					"AddNSNick(): calloc() of ns->passowrd failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"AddNSNick(): calloc() of ns->password [%p] passed.\n",
					ns->password);
			}
		}
	}

	if (mFail)
	{
		return NULL;
	}

	strcpy(ns->nickname, nickname);
	strcpy(ns->password, password);

	ns->authed = flags;
	ns->killprot = killprot;

	if (mFail)
	{
		if (config->debug)
		{
			printf(
				"AddNSNick(): calloc() %d fail, %d pass\n",
				mFail, mPass);
		}
		return NULL;
	}

	if (!nickservdb)
	{
		nickservdb = ns;
		ns->next = NULL;
	}
	else
	{
		ns->next = nickservdb;
		nickservdb = ns;
	}
	return ns;
}

/////////////////////////////////////////////////////////////////////////////
//

nickservDB *
NSFindNick (nickname)
char	*nickname;
{
	nickservDB	*ns;

	ns = nickservdb;
	while (ns)
	{
		if (!strcasecmp(ns->nickname, nickname))
		{
			if (config->debug)
			{
				printf(
					"NSFindNick(): %s [%p] found.\n",
					ns->nickname, ns->nickname);
			}
			return ns;
		}
		ns = ns->next;
	}
	if (config->debug)
	{
		printf(
			"NSFindNick(): %s not found.\n",
			nickname);
	}
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
//

void NSdelNick (nickname)
char	*nickname;
{
	nickservDB	*ns, *next, *delete;

	for (ns = nickservdb; ns; ns = next)
	{
		next = ns->next;
		if (!strcasecmp(ns->nickname, nickname))
		{
			if (nickservdb == ns)
			{
				nickservdb = ns->next;
			}
			else
			{
				for (delete = nickservdb; (delete->next != ns) &&
					delete; delete = delete->next);
				delete->next = ns->next;
			}
			free(ns->nickname);
			free(ns->password);
			free(ns);
			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
//


