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

NJupe	*addNJupe	(char *, char *);
NJupe	*findNJupe	(char *);
void	delNJupe	(char *);

///////////////////////////////////////////////////////////////////////////////
//

NJupe	*
addNJupe (nickname, reason)
char	*nickname;
char	*reason;
{
	NJupe	*nj;
	int	mFail = 0, mPass = 0;

	nj = (NJupe *)calloc(1, sizeof(NJupe));
	{
		if (!nj)
		{
			if (config->debug)
			{
				printf(
					"addNJupe(): calloc() of nj failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addNJupe(): calloc() of nj [%p] passed.\n",
					nj);
			}
			mPass++;
		}
	}
	nj->nickname = (char *)calloc(1, 256);
	{
		if (!nj->nickname)
		{
			if (config->debug)
			{
				printf(
					"addNJupe(): calloc() of nj->nickname failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addNJupe(): calloc() of nj->nickname [%p] passed.\n",
					nj->nickname);
			}
			mPass++;
		}
	}
	nj->reason = (char *)calloc(1, 1024);
	{
		if (!nj->reason)
		{
			if (config->debug)
			{
				printf(
		 			"addNJupe(): calloc() of nj->reason failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addNJupe(): calloc()of nj->reason [%p] passed.\n",
					nj->reason);
			}
			mPass++;
		}
	}

	if (mFail)
	{
		if (config->debug)
		{
			printf(
				"addNJupe(): calloc() %d fail, %d pass\n",
				mFail, mPass);
		}
		return NULL;
	}

	strcpy(nj->nickname, nickname);
	strcpy(nj->reason, reason);

	printf(
		"addNJupe(): NN: %s    RES: %s\n",
		nj->nickname, nj->reason);

	if (!njupe)
	{
		njupe = nj;
		nj->next = NULL;
	}
	else
	{
		nj->next = njupe;
		njupe = nj;
	}
	return nj;
}

///////////////////////////////////////////////////////////////////////////////
//

NJupe	*
findNJupe (nickname)
char	*nickname;
{
	NJupe	*nj;

	nj = njupe;
	while (nj)
	{
		if (!strcasecmp(nj->nickname, nickname))
		{
			if (config->debug)
			{
				printf(
					"findNJupe(): %s [%p] found.\n",
					nj->nickname, nj->nickname);
			}
			return nj;
		}
		nj = nj->next;
	}
	if (config->debug)
	{
		printf(
			"findNJupe(): %s not found\n",
			nickname);
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//

void
delNJupe (nickname)
char	*nickname;
{
	NJupe	*nj, *next, *delete;

	for (nj = njupe; nj; nj = next)
	{
		next = nj->next;
		if (!strcasecmp(nj->nickname, nickname))
		{
			if (config->debug)
			{
				printf(
					"delNJupe(): %s [%p] found, removing.\n",
					nj->nickname, nj->nickname);
			}
			if (njupe == nj)
			{
				njupe = nj->next;
			}
			else
			{
				for (delete = njupe; (delete->next != nj) &&
					delete; delete = delete->next);
				delete->next = nj->next;
			}
			free(nj->nickname);
			free(nj->reason);
			free(nj);
			return;
		}
		if (config->debug)
		{
			printf(
				"delNJupe(): %s not found.\n",
				nickname);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//

