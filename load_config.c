///////////////////////////////////////////////////////////////////////////////
//		  IRCSP - Internet Realy Chat Services Package
//                  Copyright (C) 2000 Lostworld Development
//          Written By: Justin Ovens [evilicey] [ice95@lostworld.net]
//
//   This program, documentation, and everything included in this
//   package are Copyright (C) 2000 Lostworld Development. You may
//   Download this package from the lostworld site, or via CVS
//   from source forge.
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 1, or (at your option)
//   any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software
//   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
//   The authors of this program are in no way liable for any
//   consequences or damages, suffered by you or anyone else,
//   arising out of the use or inablility to use this program.
//
//   Author Contact information: ice95@lostworld.net
///////////////////////////////////////////////////////////////////////////////


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


