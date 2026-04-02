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

void	checkclones	(void);

void
checkclones (void)
{
	Hosts	*h;
	Nick	*n;

	for (h = hosts; h; h = h->next)
	{
		if (h->clones == 2)		// user has 2 clones on. warn him not
		{				// load any more.
			for (n = nick; n; n = n->next)
			{
				if (!strcasecmp(n->userhost, h->hostname))
				{
					send_to_sock(s, 
						":%s NOTICE %s :Possible [%d] clones dectected from your host\n",
						config->unick, n->nickname, h->clones);
					send_to_sock(s,
						":%s NOTICE %s :One more clone and the IRC operators will be notified. If you continue to load clones, you will be auto-glined.\n",
						config->unick, n->nickname);
				}
			}
		}
		else if (h->clones >= 3)	// user has 3 clones, warn the opers.
		{
			send_to_sock(s,
				"WALLOPS :Possible [%d] clones from %s\n",
				h->clones, h->hostname);
			for (n = nick; n; n = n->next)
			{
				if (!strcasecmp(n->userhost, h->hostname))
				{
					send_to_sock(s,
						":%s NOTICE %s :Possible [%d] clones dectected from your host\n",
						config->unick, n->nickname, h->clones);
					send_to_sock(s,
						":%s NOTICE %s :One more clone and you will be glined.\n",
						config->unick, n->nickname);
				}
			}
		}
		else if (h->clones >= 4)	// BAD! a really stupid move for h->hostname 
		{				// cause he is now glined! :P
			for (n = nick; n; n = n->next)
			{
				if (!strcasecmp(n->userhost, h->hostname))
				{
					send_to_sock(s,
						":%s NOTICE %s :You have now been put on auto-gline, congraulations for not listing.\n",
						config->unick, n->nickname);
					addGline(h->hostname, time(NULL), 120+time(NULL),
						"Auto-Gline [Clones]");
				}
			}
		}
	}
}


