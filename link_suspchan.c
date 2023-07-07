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

SuspChan *addSChan (char *, char *);
void delSChan (char *);

//////////////////////////////////////////////////////////////////////////////
//

SuspChan *
addSChan (channel,reason)
char	*channel;
char	*reason;
{
	SuspChan	*sc;
	int		mFail = 0, mPass = 0;

	sc = (SuspChan *)calloc(1, sizeof(SuspChan));
	{
		if (!sc)
		{
			if (config->debug)
			{
				printf(
					"addSChan(): calloc() of sc failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addSChan(): calloc() of sc [%p] passed.\n",
					sc);
			}
			mPass++;
		}
	}
	sc->channel = (char *)calloc(1, 256);
	{
		if (!sc->channel)
		{
			if (config->debug)
			{
				printf(
					"addSChan(): calloc() of sc->channel failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addSChan(): calloc() of sc->channel [%p] passed.\n",
					sc->channel);
			}
			mPass++;
		}
	}
	sc->reason  = (char *)calloc(1, 1024);
	{
		if (!sc->reason)
		{
			if (config->debug)
			{
				printf(
					"addSChan(): calloc() of sc->reason failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addSChan(): calloc() of sc->reason [%p] passed.\n",
					sc->reason);
			}
			mPass++;
		}
	}

	if (mFail)
	{
		if (config->debug)
		{
			printf(
				"addSChan(): calloc(): %d fail, %d pass\n",
				mFail, mPass);
		}
		return NULL;
	}

	strcpy(sc->channel, channel);
	strcpy(sc->reason,  reason);

	if (config->debug)
	{
		printf(
			"addSChan():  CHN: %s    RSN: %s\n",
			sc->channel, sc->reason);
	}

	send_to_sock(s, 
		":%s JOIN %s\n", 
		config->scnick, channel);

	send_to_sock(s, 
		"MODE %s +o %s\n", 
		channel, config->scnick);

	send_to_sock(s, 
		":%s MODE %s +tnsplk 11 11\n", 
		config->scnick, channel);

	send_to_sock(s, 
		":%s TOPIC %s :%s:%s\n", 
		config->scnick, channel, "Banned Channel", 
		reason);

	if (!suspchan)
	{
		suspchan = sc;
		sc->next = NULL;
	}
	else
	{
		sc = suspchan;
		suspchan = sc;
	}
	return sc;
}

//////////////////////////////////////////////////////////////////////////////
//

void
delSChan (channel)
char	*channel;
{
	SuspChan	*sc, *next, *delete;

	for (sc = suspchan; sc; sc = next)
	{
		next = sc->next;
		if (!strcasecmp(sc->channel, channel))
		{
			if (suspchan == sc)
			{
				suspchan = sc->next;
			}
			else
			{
				for (delete = suspchan; (delete->next != sc) &&
					delete; delete = delete->next);
				delete->next = sc->next;
			}
			free(sc->channel);
			free(sc->reason);
			free(sc);
			return;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//

SuspChan *
findSChan (channel)
char  *channel;
{
   SuspChan  *theChan;

   theChan = suspchan;
   while (theChan)
   {
      if (!strcasecmp(theChan->channel, channel))
      {
         return theChan;
      }
      theChan = theChan->next;
   }
   return NULL;
}

//////////////////////////////////////////////////////////////////////////////
//


