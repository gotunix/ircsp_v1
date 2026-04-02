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

void	checknick		(void);

///////////////////////////////////////////////////////////////////////////////
//

void
checknick (void)
{
	Nick		*n;
	nickservDB	*ns;

	n = nick;
	ns = nickservdb;

	while (ns)
	{
		//////////////////////////////////////////////////////////////
		// check if temp->nickname is registered.
		//

		n = findNick(ns->nickname);
		if (!n)
		{
			//////////////////////////////////////////////////////
			// temp->nickname is not a registered nickname, 
			// so don't do anything.
			//
		}
		else
		{
			if (!IsNSAuth(ns))
			{
				//////////////////////////////////////////////
				// make sure temp->nickname is not already 
				// authorized.

				if (IsNSKillProt(ns))
				{

					///////////////////////////////////////////////////////
					// temp->nickname has kill protection on, if he does,
					// give him 2 minutes to authorize, and if he don't
					// remove him from the network.
					//

					if ((time(NULL) - n->ConnTime) > 120)
					{ 
						//////////////////////////////////////////////////
						// user has faild to authorize, so remove him/her
						// from the network.
						//
						send_to_sock(s, 
							":%s KILL %s :%s\n",
							config->nnick, ns->nickname,
							"User faild to authorize with NS.");
						delNick(ns->nickname);
					}
					else
					{
						send_to_sock(s, 
							":%s NOTICE %s :%s\n",
							config->nnick, ns->nickname,
							"You're using a registered nickname, please authorize.");
						send_to_sock(s, 
							":%s NOTICE %s :\2/msg %s AUTH %s <password>\n",
							config->nnick, ns->nickname, 
							config->nnick, ns->nickname);
					}
				}
				else
				{
					////////////////////////////////////////////////////////
					// temp->nickname doesn't have kill protection on,
					// so keep sending please auth yourself messages.
					//

					send_to_sock(s, 
						":%s NOTICE %s :%s\n",
						config->nnick, ns->nickname,
						"You're using a registered nickname, please authorize.");
					send_to_sock(s, 
						":%s NOTICE %s :\2/msg %s AUTH %s <password>\n",
						config->nnick, ns->nickname, 
						config->nnick, ns->nickname);
				}
			}
		}
         
		////////////////////////////////////////////////////////////////////
		// move to the next nickname in our nick list.
		//

		ns = ns->next;
	}
}

///////////////////////////////////////////////////////////////////////////////
//


