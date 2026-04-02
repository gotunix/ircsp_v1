///////////////////////////////////////////////////////////////////////////////
//		  IRCSP - Internet Realy Chat Services Package
//                  Copyright (C) 2000 Lostworld Development
//          Written By: Justin Ovens [evilicey] [ice95@lostworld.net]
//
//   This program, documentation, and everything included in this
//   package are Copyright (C) 2000 Lostworld Development. You may
//   not use this program in any way sharp or form with out 
//   the Lostworld Developers expresss written consent.
//
//   This program is not gnu puclic license and is not freeware.
//   Possession with out permission, license, is strictly
//   prohibited.  You may purchace this program (Biniary), and
//   a license from our web page [www.lostworld.net].
//
//   The authors of this program are in no way liable for any
//   consequences or damages, suffered by you or anyone else,
//   arising out of the use or inablility to use this program.
//
//   Author Contact information: ice95@lostworld.net
///////////////////////////////////////////////////////////////////////////////

#include "services.h"

int load_admin ();

///////////////////////////////////////////////////////////////////////////////
//

int
load_admin ()
{
	char	*ptr[6], read[512];
	FILE	*fp;

	fp = fopen("admin.db", "r");
	if (!fp)
	{
		return -1;
	}
	else
	{
		while (fgets(read, 256, fp) != NULL)
		{
			if ((read[0] == '#') || (read[0] == ';'))
			{
				continue;
			}
			ptr[0] = strtok(read, ":");
			ptr[1] = strtok(NULL, ":");
			ptr[2] = strtok(NULL, ":");
			ptr[3] = strtok(NULL, ":");
			ptr[4] = strtok(NULL, ":");
			ptr[5] = strtok(NULL, "\n");

			addAdmin(ptr[0], atoi(ptr[1]), ptr[2], atoi(ptr[3]), 
				atoi(ptr[4]), ptr[5]);
		}
		return 1;
	}
	return 0;
}


///////////////////////////////////////////////////////////////////////////////

