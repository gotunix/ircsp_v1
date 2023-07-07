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

int	load_config		();

//////////////////////////////////////////////////////////////////////////////
//

int
load_config ()
{
	FILE	*cfg;
	char	read[512];
	int	errors;

	config = (Config *)calloc(1,sizeof(Config));
	cfg = fopen("services.conf", "r");
	errors = 0;

	if (!cfg)
	{
		return -1;
	}
	else
	{
		while (fgets(read, 256, cfg) != NULL)
		{
			if ((read[0] == '#') || (read[0] == ';'))
			{
				continue;
			}

			tokenize(read, ':');
			if (!strcasecmp(token(read,1), "SERVER"))
			{
				config->server = (char *)calloc(1, 1024);
				strcpy(config->server, token(read,2));
			}
			if (!strcasecmp(token(read,1), "PASSWORD"))
			{
				config->password = (char *)calloc(1, 256);
				strcpy(config->password, token(read,2));
			}
			if (!strcasecmp(token(read,1), "PORT"))
			{
				config->port = (char *)calloc(1, 6);
				strcpy(config->port, token(read,2));
			}
			if (!strcasecmp(token(read,1), "SERVNAME"))
			{
				config->servname = (char *)calloc(1, 1024);
				strcpy(config->servname, token(read,2));
			}
			if (!strcasecmp(token(read,1), "SERVDESC"))
			{
				config->servdesc = (char *)calloc(1, 1024);
				strcpy(config->servdesc, lrange(read,2));
			}
			if (!strcasecmp(token(read,1), "UNICK"))
			{
				config->unick = (char *)calloc(1, 64);
				strcpy(config->unick, token(read,2));
			}
			if (!strcasecmp(token(read,1), "UDESC"))
			{
				config->udesc = (char *)calloc(1, 512);
				strcpy(config->udesc, lrange(read,2));
			}
			if (!strcasecmp(token(read,1), "HNICK"))
			{
				config->hnick = (char *)calloc(1, 64);
				strcpy(config->hnick, token(read,2));
			}
			if (!strcasecmp(token(read,1), "HDESC"))
			{
				config->hdesc = (char *)calloc(1, 512);
				strcpy(config->hdesc, lrange(read,2));
			}
			if (!strcasecmp(token(read,1), "NNICK"))
			{
				config->nnick = (char *)calloc(1, 64);
				strcpy(config->nnick, token(read,2));
			}
			if (!strcasecmp(token(read,1), "NDESC"))
			{
				config->ndesc = (char *)calloc(1, 512);
				strcpy(config->ndesc, lrange(read,2));
			}
			if (!strcasecmp(token(read,1), "SCNICK"))
			{
				config->scnick = (char *)calloc(1, 64);
				strcpy(config->scnick, token(read,2));
			}
			if (!strcasecmp(token(read,1), "SCDESC"))
			{
				config->scdesc = (char *)calloc(1, 512);
				strcpy(config->scdesc, lrange(read,2));
			}
			if (!strcasecmp(token(read,1), "WNICK"))
			{
				config->wnick = (char *)calloc(1, 64);
				strcpy(config->wnick, token(read,2));
			}
			if (!strcasecmp(token(read,1), "WDESC"))
			{
				config->wdesc = (char *)calloc(1, 512);
				strcpy(config->wdesc, lrange(read,2));
			}
			if (!strcasecmp(token(read,1), "CLONECHAN"))
			{
				config->clonechan = (char *)calloc(1, 256);
				strcpy(config->clonechan, token(read,2));
			}
			if (!strcasecmp(token(read,1), "STATCHAN"))
			{
				config->statchan = (char *)calloc(1, 256);
				strcpy(config->statchan, token(read,2));
			}
			if (!strcasecmp(token(read,1), "DEBUG"))
			{
				config->debug = atoi(token(read,2));
			}
			if (!strcasecmp(token(read,1), "OPERGREET"))
			{
				config->opergreet = atoi(token(read,2));
			}
			if (!strcasecmp(token(read,1), "USERGREET"))
			{
				config->usergreet = atoi(token(read,2));
			}
			if (!strcasecmp(token(read,1), "SAVECYCLE"))
			{
				config->savecycle = atoi(token(read,2));
			}
			if (!strcasecmp(token(read,1), "GLNECYCLE"))
			{
				config->glinecycle = atoi(token(read,2));
			}
			if (!strcasecmp(token(read,1), "NICKCYCLE"))
			{
				config->nickcycle = atoi(token(read,2));
			}
			if (!strcasecmp(token(read,1), "CHANCYCLE"))
			{
				config->chancycle = atoi(token(read,2));
			}
		}
		return 1;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//


